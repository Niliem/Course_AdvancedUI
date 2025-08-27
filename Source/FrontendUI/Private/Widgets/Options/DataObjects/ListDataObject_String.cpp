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

    if (HasDefaultValue())
    {
        CurrentStringValue = GetDefaultValueAsString();
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

bool UListDataObject_String::CanResetBackToDefaultValue() const
{
    return HasDefaultValue() && CurrentStringValue != GetDefaultValueAsString();
}

bool UListDataObject_String::TryResetBackToDefaultValue()
{
    if (!CanResetBackToDefaultValue())
        return false;

    CurrentStringValue = GetDefaultValueAsString();

    bool bResult = true;
    bResult &= TrySetDisplayTextFromStringValue(CurrentStringValue);
    bResult &= TrySetOptionValueFromStringValue(CurrentStringValue, EOptionsListDataModifyReason::ResetToDefault);
    return bResult;
}

void UListDataObject_String::AdvanceToNextOption()
{
    if (AvailableOptionsStringArray.IsEmpty() || AvailableOptionsTextArray.IsEmpty())
        return;

    const int32 CurrentStringIndex = AvailableOptionsStringArray.IndexOfByKey(CurrentStringValue);
    const int32 NextStringIndex = (CurrentStringIndex + 1) % AvailableOptionsStringArray.Num();

    TrySetDisplayTextFromIndexValue(NextStringIndex);
    TrySetOptionValueFromIndexValue(NextStringIndex, EOptionsListDataModifyReason::DirectlyModified);
}

void UListDataObject_String::BackToPreviousOption()
{
    if (AvailableOptionsStringArray.IsEmpty() || AvailableOptionsTextArray.IsEmpty())
        return;

    const int32 CurrentStringIndex = AvailableOptionsStringArray.IndexOfByKey(CurrentStringValue);
    const int32 PreviousStringIndex = (CurrentStringIndex - 1 + AvailableOptionsStringArray.Num()) % AvailableOptionsStringArray.Num();

    TrySetDisplayTextFromIndexValue(PreviousStringIndex);
    TrySetOptionValueFromIndexValue(PreviousStringIndex, EOptionsListDataModifyReason::DirectlyModified);
}

bool UListDataObject_String::TrySetOptionValueFromStringValue(const FString& InStringValue, EOptionsListDataModifyReason ModifyReason)
{
    const int32 CurrentFoundIndex = AvailableOptionsStringArray.IndexOfByKey(InStringValue);

    return TrySetOptionValueFromIndexValue(CurrentFoundIndex, ModifyReason);
}

bool UListDataObject_String::TrySetOptionValueFromIndexValue(const int32 InOptionIndex, EOptionsListDataModifyReason ModifyReason)
{
    if (!AvailableOptionsStringArray.IsValidIndex(InOptionIndex))
        return false;
    
    CurrentStringValue = AvailableOptionsStringArray[InOptionIndex];
    
    if (DataDynamicSetter)
    {
        DataDynamicSetter->SetValueFromString(CurrentStringValue);
        NotifyListDataModified(this, ModifyReason);
    }
    return true;
}

bool UListDataObject_String::TrySetDisplayTextFromStringValue(const FString& InStringValue)
{
    const int32 CurrentFoundIndex = AvailableOptionsStringArray.IndexOfByKey(InStringValue);
    
    return TrySetDisplayTextFromIndexValue(CurrentFoundIndex);
}

bool UListDataObject_String::TrySetDisplayTextFromIndexValue(const int32 InStringIndexValue)
{
    if (!AvailableOptionsTextArray.IsValidIndex(InStringIndexValue))
        return false;
    
    CurrentDisplayText = AvailableOptionsTextArray[InStringIndexValue];
    return true;
}

