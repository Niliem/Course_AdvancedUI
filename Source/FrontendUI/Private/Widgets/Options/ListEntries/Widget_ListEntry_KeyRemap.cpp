// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Options/ListEntries/Widget_ListEntry_KeyRemap.h"

#include "FrontendFunctionLibrary.h"
#include "FrontendGameplayTags.h"
#include "Subsystems/FrontendUISubsystem.h"
#include "Widgets/Components/FrontendCommonButtonBase.h"
#include "Widgets/Options/DataObjects/ListDataObject_KeyRemap.h"

void UWidget_ListEntry_KeyRemap::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    CommonButton_RemapKey->OnClicked().AddUObject(this, &UWidget_ListEntry_KeyRemap::OnRemapKeyBottonClicked);
    CommonButton_ResetKeyBinding->OnClicked().AddUObject(this, &UWidget_ListEntry_KeyRemap::OnResetKeyBindingBottonClicked);    
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

void UWidget_ListEntry_KeyRemap::OnRemapKeyBottonClicked()
{
    UFrontendUISubsystem::Get(this)->PushSoftWidgetToLayerStackAsync(
        UIGameplayTags::UI_Layer_Modal,
        UFrontendFunctionLibrary::GetFrontendWidgetClassByTag(FrontendGameplayTags::Frontend_Widget_KeyRemap),
        [](EAsyncPushWidgetState PushState, UCommonActivatableWidget* PushedWidget)
        {
            
        });
}

void UWidget_ListEntry_KeyRemap::OnResetKeyBindingBottonClicked()
{
}