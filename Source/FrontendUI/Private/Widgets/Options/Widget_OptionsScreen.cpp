// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Options/Widget_OptionsScreen.h"
#include "ICommonInputModule.h"
#include "Input/CommonUIInputTypes.h"
#include "Widgets/Components/FrontendCommonListView.h"
#include "Widgets/Components/FrontendTabListWidgetBase.h"
#include "Widgets/Options/OptionsDataRegistry.h"
#include "Widgets/Options/DataObjects/ListDataObject_Collection.h"
#include "FrontendDebugHelper.h"
#include "Settings/FrontendGameUserSettings.h"
#include "Widgets/Options/Widget_OptionsDetailsView.h"
#include "Widgets/Options/ListEntries/Widget_ListEntry_Base.h"

void UWidget_OptionsScreen::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (EnhancedInputResetAction)
    {
        ResetActionHandle = RegisterUIActionBinding(FBindUIActionArgs(EnhancedInputResetAction, true,
           FSimpleDelegate::CreateUObject(this, &ThisClass::HandleResetBoundAction)));
    }

    RegisterUIActionBinding(FBindUIActionArgs(ICommonInputModule::GetSettings().GetEnhancedInputBackAction(), true,
           FSimpleDelegate::CreateUObject(this, &ThisClass::HandleBackBoundAction)));

    TabListWidget_OptionsTabs->OnTabSelected.AddUniqueDynamic(this, &ThisClass::OnOptionsTabSelected);

    CommonListView_OptionsList->OnItemIsHoveredChanged().AddUObject(this, &ThisClass::OnListViewItemHovered);
    CommonListView_OptionsList->OnItemSelectionChanged().AddUObject(this, &ThisClass::OnListViewItemSelected);
}

void UWidget_OptionsScreen::NativeOnActivated()
{
    Super::NativeOnActivated();

    for (UListDataObject_Collection* TabCollection : GetOrCreateDataRegistry()->GetRegisteredOptionsTabCollections())
    {
        if (!TabCollection)
            continue;

        const FName TabId = TabCollection->GetDataId();
        if (TabListWidget_OptionsTabs->GetTabButtonBaseByID(TabId))
            continue;

        TabListWidget_OptionsTabs->RequestRegisterTab(TabId, TabCollection->GetDataDisplayName());
    }
}

void UWidget_OptionsScreen::NativeOnDeactivated()
{
    Super::NativeOnDeactivated();

    UFrontendGameUserSettings::Get()->ApplySettings(true);
}

UOptionsDataRegistry* UWidget_OptionsScreen::GetOrCreateDataRegistry()
{
    if (!OwningDataRegistry)
    {
        OwningDataRegistry = NewObject<UOptionsDataRegistry>();
        OwningDataRegistry->InitOptionsDataRegistry(GetOwningLocalPlayer());
    }
    
    return OwningDataRegistry;
}

void UWidget_OptionsScreen::HandleResetBoundAction()
{
    Debug::Print(TEXT("UInputAction::HandleResetBoundAction"));
}

void UWidget_OptionsScreen::HandleBackBoundAction()
{
    DeactivateWidget();
}

void UWidget_OptionsScreen::OnOptionsTabSelected(FName TabId)
{
    DetailsView_ListEntryInfo->ClearDetailsViewInfo();
    
    TArray<UListDataObject_Base*> FoundListSourceItems = GetOrCreateDataRegistry()->GetListSourceItemsBySelectedTabId(TabId);
    CommonListView_OptionsList->SetListItems(FoundListSourceItems);

    if (CommonListView_OptionsList->GetNumItems() != 0)
    {
        CommonListView_OptionsList->NavigateToIndex(0);
        CommonListView_OptionsList->SetSelectedIndex(0);
    }

    ResettableDataArray.Empty();

    for (UListDataObject_Base* FoundListSourceItem : FoundListSourceItems)
    {
        if (!FoundListSourceItem)
            continue;

        if (!FoundListSourceItem->OnListDataModified.IsBoundToObject(this))
            FoundListSourceItem->OnListDataModified.AddUObject(this, &ThisClass::OnListViewListDataModified);

        if (FoundListSourceItem->CanResetBackToDefaultValue())
            ResettableDataArray.AddUnique(FoundListSourceItem);
    }

    if (ResettableDataArray.IsEmpty())
    {
        RemoveActionBinding(ResetActionHandle);
    }
    else
    {
        if (!GetActionBindings().Contains(ResetActionHandle))
        {
            AddActionBinding(ResetActionHandle);
        }
    }
}

void UWidget_OptionsScreen::OnListViewItemHovered(UObject* InHoveredItem, bool bWasHovered)
{
    if (!InHoveredItem)
        return;

    UWidget_ListEntry_Base* HoveredEntryWidget = CommonListView_OptionsList->GetEntryWidgetFromItem<UWidget_ListEntry_Base>(InHoveredItem);
    if (!HoveredEntryWidget)
        return;

    HoveredEntryWidget->NativeOnListEntryWidgetHovered(bWasHovered);

    if (bWasHovered)
    {
        if(UListDataObject_Base* DataObject = Cast<UListDataObject_Base>(InHoveredItem))
        {
            DetailsView_ListEntryInfo->UpdateDetailsViewInfo(DataObject, TryGetEntryWidgetClassName(InHoveredItem));
        }
    }
    else
    {
        if (UListDataObject_Base* SelectedItem = CommonListView_OptionsList->GetSelectedItem<UListDataObject_Base>())
        {
            DetailsView_ListEntryInfo->UpdateDetailsViewInfo(SelectedItem, TryGetEntryWidgetClassName(SelectedItem));
        }
    }
}

void UWidget_OptionsScreen::OnListViewItemSelected(UObject* InSelectedItem)
{
    if (!InSelectedItem)
        return;

    if(UListDataObject_Base* DataObject = Cast<UListDataObject_Base>(InSelectedItem))
    {
        DetailsView_ListEntryInfo->UpdateDetailsViewInfo(DataObject, TryGetEntryWidgetClassName(InSelectedItem));
    }
}

FString UWidget_OptionsScreen::TryGetEntryWidgetClassName(UObject* InOwningListItem) const
{
    if (UUserWidget* FoundEntryWidget = CommonListView_OptionsList->GetEntryWidgetFromItem(InOwningListItem))
    {
        return FoundEntryWidget->GetClass()->GetName();
    }

    return TEXT("Entry Widget Not Valid!");
}

void UWidget_OptionsScreen::OnListViewListDataModified(UListDataObject_Base* ModifiedData, EOptionsListDataModifyReason ModifyReason)
{
    if (!ModifiedData)
        return;

    if (ModifiedData->CanResetBackToDefaultValue())
    {
        ResettableDataArray.AddUnique(ModifiedData);

        if (!GetActionBindings().Contains(ResetActionHandle))
        {
            AddActionBinding(ResetActionHandle);
        }
    }
    else
    {
        if (ResettableDataArray.Contains(ModifiedData))
        {
            ResettableDataArray.Remove(ModifiedData);
        }        
    }

    if (ResettableDataArray.IsEmpty())
    {
        RemoveActionBinding(ResetActionHandle);
    }
}