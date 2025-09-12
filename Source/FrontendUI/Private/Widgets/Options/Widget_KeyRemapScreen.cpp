// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Options/Widget_KeyRemapScreen.h"


#include "FrontendDebugHelper.h"
#include "Framework/Application/IInputProcessor.h"

class FKeyRemapScreenInputPreprocessor : public IInputProcessor
{
public:
    FKeyRemapScreenInputPreprocessor(ECommonInputType InInputTypeToListenTo)
        : CachedInputTypeToListenTo(InInputTypeToListenTo)
    {        
    }

    DECLARE_DELEGATE_OneParam(FOnInputPreprocessorKeyPressedDelegate, const FKey&);
    FOnInputPreprocessorKeyPressedDelegate OnInputPreprocessorKeyPressed;

    DECLARE_DELEGATE_OneParam(FOnInputPreprocessorKeySelectCanceledDelegate, const FString&);
    FOnInputPreprocessorKeySelectCanceledDelegate OnInputPreprocessorKeySelectCanceled;
    
protected:
    //~ Begin IInputProcessor Interface
    virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override
    {
        
    }

    virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override
    {
        ProcessPressedKey(InKeyEvent.GetKey());
        return true;
    }

    virtual bool HandleMouseButtonDownEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override
    {
        ProcessPressedKey(MouseEvent.GetEffectingButton());
        return true;
    }
    //~ End IInputProcessor Interface

    void ProcessPressedKey(const FKey& InPressedKey)
    {
        if (InPressedKey == EKeys::Escape)
        {
            OnInputPreprocessorKeySelectCanceled.ExecuteIfBound(TEXT("Key Remap has been canceled"));
            return;
        }

        switch (CachedInputTypeToListenTo)
        {
            case ECommonInputType::MouseAndKeyboard:
                if (InPressedKey.IsGamepadKey())
                {
                    OnInputPreprocessorKeySelectCanceled.ExecuteIfBound(TEXT("Detected Gamepad Key pressed for keyboard inputs. Key Remap has been cancled."));
                    return;
                }
                break;
            case ECommonInputType::Gamepad:
                if (!InPressedKey.IsGamepadKey())
                {
                    OnInputPreprocessorKeySelectCanceled.ExecuteIfBound(TEXT("Detected non Gamepad Key pressed for Gamepad inputs. Key Remap has been cancled."));
                    return;
                }
                break;
        }

        OnInputPreprocessorKeyPressed.ExecuteIfBound(InPressedKey);
    }

private:
    ECommonInputType CachedInputTypeToListenTo;
};

void UWidget_KeyRemapScreen::SetDesiredInputTypeToFilter(ECommonInputType InDesiredInputType)
{
    CachedDesiredInputType = InDesiredInputType;
}

void UWidget_KeyRemapScreen::NativeOnActivated()
{
    Super::NativeOnActivated();

    CachedInputPreprocessor = MakeShared<FKeyRemapScreenInputPreprocessor>(CachedDesiredInputType);
    FSlateApplication::Get().RegisterInputPreProcessor(CachedInputPreprocessor, -1);
}

void UWidget_KeyRemapScreen::NativeOnDeactivated()
{
    Super::NativeOnDeactivated();

    if (CachedInputPreprocessor)
    {
        FSlateApplication::Get().UnregisterInputPreProcessor(CachedInputPreprocessor);
        CachedInputPreprocessor.Reset();
    }
}