// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Options/ListEntries/Widget_ListEntry_KeyRemap.h"

#include "FrontendFunctionLibrary.h"
#include "FrontendGameplayTags.h"
#include "Subsystems/FrontendUISubsystem.h"
#include "Widgets/Components/FrontendCommonButtonBase.h"
#include "Widgets/Options/Widget_KeyRemapScreen.h"
#include "Widgets/Options/DataObjects/ListDataObject_KeyRemap.h"
#include "FrontendDebugHelper.h"

void UWidget_ListEntry_KeyRemap::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    CommonButton_RemapKey->OnClicked().AddUObject(this, &UWidget_ListEntry_KeyRemap::OnRemapKeyButtonClicked);
    CommonButton_ResetKeyBinding->OnClicked().AddUObject(this, &UWidget_ListEntry_KeyRemap::OnResetKeyBindingButtonClicked);    
}

void UWidget_ListEntry_KeyRemap::OnOwningListDataObjectSet(UListDataObject_Base* ListDataObject)
{
    Super::OnOwningListDataObjectSet(ListDataObject);

    CachedOwningKeyRemapDataObject = CastChecked<UListDataObject_KeyRemap>(ListDataObject);

    CommonButton_RemapKey->SetButtonDisplayImage(CachedOwningKeyRemapDataObject->GetIconFromCurrentKey());
}

void UWidget_ListEntry_KeyRemap::OnOwningListDataObjectModified(UListDataObject_Base* ModifiedData, EOptionsListDataModifyReason ModifyReason)
{
    if (CachedOwningKeyRemapDataObject)
        CommonButton_RemapKey->SetButtonDisplayImage(CachedOwningKeyRemapDataObject->GetIconFromCurrentKey());
    
    Super::OnOwningListDataObjectModified(ModifiedData, ModifyReason);
}

void UWidget_ListEntry_KeyRemap::OnRemapKeyButtonClicked()
{
    UFrontendUISubsystem::Get(this)->PushSoftWidgetToLayerStackAsync(
        UIGameplayTags::UI_Layer_Modal,
        UFrontendFunctionLibrary::GetFrontendWidgetClassByTag(FrontendGameplayTags::Frontend_Widget_KeyRemap),
        [this](EAsyncPushWidgetState PushState, UCommonActivatableWidget* PushedWidget)
        {
            if (PushState == EAsyncPushWidgetState::BeforePush)
            {
                if (UWidget_KeyRemapScreen* KeyRemapScreen = Cast<UWidget_KeyRemapScreen>(PushedWidget))
                {
                    KeyRemapScreen->OnKeyRemapScreenKeyPressed.BindUObject(this, &UWidget_ListEntry_KeyRemap::OnKeyToRemapPressed);
                    KeyRemapScreen->OnKeyRemapScreenKeySelectCanceled.BindUObject(this, &UWidget_ListEntry_KeyRemap::OnKeyRemapCanceled);
                    
                    if (CachedOwningKeyRemapDataObject)
                    {
                        KeyRemapScreen->SetDesiredInputTypeToFilter(CachedOwningKeyRemapDataObject->GetDesiredInputKeyType());
                    }
                }
            }
        });
}

void UWidget_ListEntry_KeyRemap::OnResetKeyBindingButtonClicked()
{
}

void UWidget_ListEntry_KeyRemap::OnKeyToRemapPressed(const FKey& PressedKey)
{
    Debug::Print(TEXT("Valid key to remap detected. Key: ") + PressedKey.GetDisplayName().ToString());
}

void UWidget_ListEntry_KeyRemap::OnKeyRemapCanceled(const FString& CancelReason)
{
    UFrontendUISubsystem::Get(this)->PushConfirmScreenAsync(
        EConfirmScreenType::Ok,
        FText::FromString(TEXT("Key Remap")),
        FText::FromString(CancelReason),
        [](EConfirmScreenButtonType ClickedButton){}
    );
}