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
    
protected:
    //~ Begin IInputProcessor Interface
    virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override
    {
        
    }

    virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override
    {
        Debug::Print(TEXT("Pressed Key: ") + InKeyEvent.GetKey().GetDisplayName().ToString());
        return true;
    }

    virtual bool HandleMouseButtonDownEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override
    {
        Debug::Print(TEXT("Pressed Key: ") + MouseEvent.GetEffectingButton().GetDisplayName().ToString());
        return true;
    }
    //~ End IInputProcessor Interface

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