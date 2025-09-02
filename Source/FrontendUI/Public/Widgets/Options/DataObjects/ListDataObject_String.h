// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Options/DataObjects/ListDataObject_Value.h"
#include "ListDataObject_String.generated.h"

/**
 * 
 */
UCLASS()
class FRONTENDUI_API UListDataObject_String : public UListDataObject_Value
{
    GENERATED_BODY()

public:
    void AddDynamicOption(const FString& InStringValue, const FText& InDisplayText);
    void AdvanceToNextOption();
    void BackToPreviousOption();
    void SelectOptionByIndex(int32 Index);

    FORCEINLINE const FText& GetCurrentDisplayText() const
    {
        return CurrentDisplayText;
    }

    FORCEINLINE const TArray<FText>& GetAvailableOptionsTextArray() const
    {
        return AvailableOptionsTextArray;
    }

protected:
    //~ Begin UListDataObject_Base Interface
    virtual void OnDataObjectInitialized() override;
    virtual bool CanResetBackToDefaultValue() const override;
    virtual bool TryResetBackToDefaultValue() override;
    //~ End UListDataObject_Base Interface

    bool TrySetOptionValueFromStringValue(const FString& InStringValue, EOptionsListDataModifyReason ModifyReason);
    bool TrySetOptionValueFromIndexValue(const int32 InOptionIndex, EOptionsListDataModifyReason ModifyReason);
    
    bool TrySetDisplayTextFromStringValue(const FString& InStringValue);
    bool TrySetDisplayTextFromIndexValue(const int32 InStringIndexValue);

    FString CurrentStringValue;
    FText CurrentDisplayText;

    TArray<FString> AvailableOptionsStringArray;
    TArray<FText> AvailableOptionsTextArray;
};

