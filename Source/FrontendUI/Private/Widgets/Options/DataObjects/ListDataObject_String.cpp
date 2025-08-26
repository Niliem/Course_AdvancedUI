// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Options/DataObjects/ListDataObject_String.h"

#include "Widgets/Options/OptionsDataInteractionHelper.h"

void UListDataObject_String::AddDynamicOption(const FString& InStringValue, const FText& InDisplayText)
{
    AvailableOptionsStringArray.Add(InStringValue);
    AvailableOptionsTextArray.Add(InDisplayText);
}

void UListDataObject_String::OnDataObjectInitialized()
{
    if (!AvailableOptionsStringArray.IsEmpty())
    {
        CurrentStringValue = AvailableOptionsStringArray[0];
    }

    if (DataDynamicGetter)
    {
        FString DataDynamicValue = DataDynamicGetter->GetValueAsString();
        if (!DataDynamicValue.IsEmpty())
        {
            CurrentStringValue = DataDynamicValue;
        }
    }
    
    if (!TrySetDisplayTextFromStringValue(CurrentStringValue))
    {
        CurrentDisplayText = FText::FromString(TEXT("Invalid Option"));
    }
}

void UListDataObject_String::AdvanceToNextOption()
{
    if (AvailableOptionsStringArray.IsEmpty() || AvailableOptionsTextArray.IsEmpty())
        return;

    const int32 CurrentStringIndex = AvailableOptionsStringArray.IndexOfByKey(CurrentStringValue);
    const int32 NextStringIndex = (CurrentStringIndex + 1) % AvailableOptionsStringArray.Num();

    TrySetOptionValueFromIndexValue(NextStringIndex);
    TrySetDisplayTextFromIndexValue(NextStringIndex);
}

void UListDataObject_String::BackToPreviousOption()
{
    if (AvailableOptionsStringArray.IsEmpty() || AvailableOptionsTextArray.IsEmpty())
        return;

    const int32 CurrentStringIndex = AvailableOptionsStringArray.IndexOfByKey(CurrentStringValue);
    const int32 PreviousStringIndex = (CurrentStringIndex - 1 + AvailableOptionsStringArray.Num()) % AvailableOptionsStringArray.Num();

    TrySetOptionValueFromIndexValue(PreviousStringIndex);
    TrySetDisplayTextFromIndexValue(PreviousStringIndex);
}

void UListDataObject_String::TrySetOptionValueFromIndexValue(const int32 InOptionIndex)
{
    CurrentStringValue = AvailableOptionsStringArray[InOptionIndex];
    
    if (DataDynamicSetter)
    {
        DataDynamicSetter->SetValueFromString(CurrentStringValue);
        NotifyListDataModified(this);
    }
}

bool UListDataObject_String::TrySetDisplayTextFromStringValue(const FString& InStringValue)
{
    const int32 CurrentFoundIndex = AvailableOptionsStringArray.IndexOfByKey(InStringValue);
    
    if (!AvailableOptionsTextArray.IsValidIndex(CurrentFoundIndex))
        return false;
    
    CurrentDisplayText = AvailableOptionsTextArray[CurrentFoundIndex];
    return true;
}

bool UListDataObject_String::TrySetDisplayTextFromIndexValue(const int32 InStringIndexValue)
{
    if (!AvailableOptionsTextArray.IsValidIndex(InStringIndexValue))
        return false;
    
    CurrentDisplayText = AvailableOptionsTextArray[InStringIndexValue];
    return true;
}

