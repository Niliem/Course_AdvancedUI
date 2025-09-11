// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Options/ListEntries/Widget_ListEntry_KeyRemap.h"

#include "Widgets/Components/FrontendCommonButtonBase.h"
#include "Widgets/Options/DataObjects/ListDataObject_KeyRemap.h"

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