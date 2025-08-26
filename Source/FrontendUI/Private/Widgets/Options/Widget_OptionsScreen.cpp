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

void UWidget_OptionsScreen::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (EnhancedInputCancelAction)
    {
        CancelActionHandle = RegisterUIActionBinding(FBindUIActionArgs(EnhancedInputCancelAction, true,
           FSimpleDelegate::CreateUObject(this, &ThisClass::HandleCancelBoundAction)));
    }

    RegisterUIActionBinding(FBindUIActionArgs(ICommonInputModule::GetSettings().GetEnhancedInputBackAction(), true,
           FSimpleDelegate::CreateUObject(this, &ThisClass::HandleBackBoundAction)));

    TabListWidget_OptionsTabs->OnTabSelected.AddUniqueDynamic(this, &ThisClass::OnOptionsTabSelected);
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

void UWidget_OptionsScreen::HandleCancelBoundAction()
{
    Debug::Print(TEXT("UInputAction::HandleCancelBoundAction"));
}

void UWidget_OptionsScreen::HandleBackBoundAction()
{
    DeactivateWidget();
}

void UWidget_OptionsScreen::OnOptionsTabSelected(FName TabId)
{
    TArray<UListDataObject_Base*> FoundListSourceItems = GetOrCreateDataRegistry()->GetListSourceItemsBySelectedTabId(TabId);
    CommonListView_OptionsList->SetListItems(FoundListSourceItems);

    if (CommonListView_OptionsList->GetNumItems() != 0)
    {
        CommonListView_OptionsList->NavigateToIndex(0);
        CommonListView_OptionsList->SetSelectedIndex(0);
    }
}
