// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Options/ListEntries/Widget_ListEntry_String.h"
#include "Widgets/Components/FrontendCommonButtonBase.h"
#include "Widgets/Components/FrontendCommonRotator.h"
#include "Widgets/Options/DataObjects/ListDataObject_String.h"
#include "FrontendDebugHelper.h"

void UWidget_ListEntry_String::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    CommonButton_PreviousOption->OnClicked().AddUObject(this, &UWidget_ListEntry_String::OnPreviousOptionButtonClicked);
    CommonButton_NextOption->OnClicked().AddUObject(this, &UWidget_ListEntry_String::OnNextOptionButtonClicked);
}

void UWidget_ListEntry_String::OnOwningListDataObjectSet(UListDataObject_Base* ListDataObject)
{
    Super::OnOwningListDataObjectSet(ListDataObject);

    CachedListDataObject = CastChecked<UListDataObject_String>(ListDataObject);

    CommonRotator_AvailableOptions->PopulateTextLabels(CachedListDataObject->GetAvailableOptionsTextArray());
    CommonRotator_AvailableOptions->SetSelectedOptionByText(CachedListDataObject->GetCurrentDisplayText());
}

void UWidget_ListEntry_String::OnPreviousOptionButtonClicked()
{
    if (CachedListDataObject)
    {
        CachedListDataObject->BackToPreviousOption();
    }
}

void UWidget_ListEntry_String::OnNextOptionButtonClicked()
{
    if (CachedListDataObject)
    {
        CachedListDataObject->AdvanceToNextOption();
    }
}


