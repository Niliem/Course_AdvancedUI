// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Options/ListEntries/Widget_ListEntry_Base.h"

#include "CommonInputSubsystem.h"
#include "CommonTextBlock.h"
#include "Components/ListView.h"
#include "Widgets/Options/DataObjects/ListDataObject_Base.h"

void UWidget_ListEntry_Base::NativeOnListEntryWidgetHovered(bool bWasHovered)
{
    BP_OnListEntryWidgetHovered(bWasHovered, IsListItemSelected());
}

void UWidget_ListEntry_Base::NativeOnEntryReleased()
{
    IUserObjectListEntry::NativeOnEntryReleased();

    NativeOnListEntryWidgetHovered(false);
}

void UWidget_ListEntry_Base::NativeOnListItemObjectSet(UObject* ListItemObject)
{
    IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

    SetVisibility(ESlateVisibility::Visible);

    if (UListDataObject_Base* CastedListItemObject = Cast<UListDataObject_Base>(ListItemObject))
    {
        OnOwningListDataObjectSet(CastedListItemObject);
    }
}

FReply UWidget_ListEntry_Base::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
    UCommonInputSubsystem* CommonInputSubsystem = GetInputSubsystem();
    if (!CommonInputSubsystem)
        return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);

    if (CommonInputSubsystem->GetCurrentInputType() == ECommonInputType::Gamepad)
    {
        if (UWidget* WidgetToFocus = BP_GetWidgetToFocusForGamepad())
        {
            if (TSharedPtr<SWidget> CachedWidgetToFocus = WidgetToFocus->GetCachedWidget())
            {
                return FReply::Handled().SetUserFocus(CachedWidgetToFocus.ToSharedRef());
            }
        }
    } 
    
    return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
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

void UWidget_ListEntry_Base::SelectThisEntryWidget()
{
    UListView* ListView = Cast<UListView>(GetOwningListView());
    if (!ListView)
        return;

    ListView->SetSelectedItem(GetListItem());
}