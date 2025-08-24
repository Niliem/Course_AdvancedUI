// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Options/DataObjects/ListDataObject_String.h"

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
    
    if (!TrySetDisplayTextFromStringValue(CurrentStringValue))
    {
        CurrentDisplayText = FText::FromString(TEXT("Invalid Option"));
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