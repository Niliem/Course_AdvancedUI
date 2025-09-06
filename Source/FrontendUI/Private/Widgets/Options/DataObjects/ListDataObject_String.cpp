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

bool UListDataObject_String::CanSetToForcedStringValue(const FString& InForcedValue) const
{
    return CurrentStringValue != InForcedValue;
}

void UListDataObject_String::OnSetToForcedStringValue(const FString& InForcedValue)
{
    CurrentStringValue = InForcedValue;
    TrySetDisplayTextFromStringValue(CurrentStringValue);
    TrySetOptionValueFromStringValue(CurrentStringValue, EOptionsListDataModifyReason::DependencyModified);
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

void UListDataObject_String::SelectOptionByIndex(int32 Index)
{
    TrySetDisplayTextFromIndexValue(Index);
    TrySetOptionValueFromIndexValue(Index, EOptionsListDataModifyReason::DirectlyModified);
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


//********** UListDataObject_StringBool **********//


void UListDataObject_StringBool::OverrideTrueDisplayText(const FText& InDisplayText)
{
    if (!AvailableOptionsStringArray.Contains(TrueString))
    {
        AddDynamicOption(TrueString, InDisplayText);
    }
}

void UListDataObject_StringBool::OverrideFalseDisplayText(const FText& InDisplayText)
{
    if (!AvailableOptionsStringArray.Contains(FalseString))
    {
        AddDynamicOption(FalseString, InDisplayText);
    }
}

void UListDataObject_StringBool::SetTrueAsDefaultValue()
{
    SetDefaultValueFromString(TrueString);
}

void UListDataObject_StringBool::SetFalseAsDefaultValue()
{
    SetDefaultValueFromString(FalseString);
}

void UListDataObject_StringBool::OnDataObjectInitialized()
{
    TryInitBoolValues();
    
    Super::OnDataObjectInitialized();
}

void UListDataObject_StringBool::TryInitBoolValues()
{
    if (!AvailableOptionsStringArray.Contains(TrueString))
    {
        AddDynamicOption(TrueString, FText::FromString(TEXT("ON")));
    }
    if (!AvailableOptionsStringArray.Contains(FalseString))
    {
        AddDynamicOption(FalseString, FText::FromString(TEXT("OFF")));
    }
}


//********** UListDataObject_StringInteger **********//


void UListDataObject_StringInteger::AddIntegerOption(int32 InIntegerValue, const FText& InDisplayText)
{
    AddDynamicOption(LexToString(InIntegerValue), InDisplayText);
}

void UListDataObject_StringInteger::OnDataObjectInitialized()
{
    Super::OnDataObjectInitialized();

    if (!TrySetDisplayTextFromStringValue(CurrentStringValue))
    {
        CurrentDisplayText = FText::FromString(TEXT("Custom"));
    }
}

void UListDataObject_StringInteger::OnEditDependencyDataModified(UListDataObject_Base* ModifiedDependencyData, EOptionsListDataModifyReason ModifyReason)
{
    if (DataDynamicGetter)
    {
        CurrentStringValue = DataDynamicGetter->GetValueAsString();

        if (TrySetDisplayTextFromStringValue(CurrentStringValue))
        {
            CurrentDisplayText = FText::FromString(TEXT("Custom"));
        }

        NotifyListDataModified(this, EOptionsListDataModifyReason::DependencyModified);
    }
    
    Super::OnEditDependencyDataModified(ModifiedDependencyData, ModifyReason);
}

