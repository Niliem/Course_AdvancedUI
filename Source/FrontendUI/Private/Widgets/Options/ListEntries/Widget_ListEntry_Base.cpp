// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Options/ListEntries/Widget_ListEntry_Base.h"
#include "CommonTextBlock.h"
#include "Widgets/Options/DataObjects/ListDataObject_Base.h"

void UWidget_ListEntry_Base::NativeOnListItemObjectSet(UObject* ListItemObject)
{
    IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

    SetVisibility(ESlateVisibility::Visible);

    if (UListDataObject_Base* CastedListItemObject = Cast<UListDataObject_Base>(ListItemObject))
    {
        OnOwningListDataObjectSet(CastedListItemObject);
    }
}

void UWidget_ListEntry_Base::OnOwningListDataObjectSet(UListDataObject_Base* ListDataObject)
{
    if (CommonText_SettingDisplayName)
        CommonText_SettingDisplayName->SetText(ListDataObject->GetDataDisplayName());
    
    if (!ListDataObject->OnListDataModified.IsBoundToObject(this))
        ListDataObject->OnListDataModified.AddUObject(this, &UWidget_ListEntry_Base::OnOwningListDataObjectModified);
}

void UWidget_ListEntry_Base::OnOwningListDataObjectModified(UListDataObject_Base* ModifiedData, EOptionsListDataModifyReason ModifyReason)
{
}