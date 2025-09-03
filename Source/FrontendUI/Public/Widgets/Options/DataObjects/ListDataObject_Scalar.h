// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Options/DataObjects/ListDataObject_Value.h"
#include "CommonNumericTextBlock.h"
#include "ListDataObject_Scalar.generated.h"

/**
 * 
 */
UCLASS()
class FRONTENDUI_API UListDataObject_Scalar : public UListDataObject_Value
{
	GENERATED_BODY()

public:
    LIST_DATA_ACCESSOR(TRange<float>, DisplayValueRange);
    LIST_DATA_ACCESSOR(TRange<float>, OutputValueRange);
    LIST_DATA_ACCESSOR(float, SliderStepSize);
    LIST_DATA_ACCESSOR(ECommonNumericType, DisplayNumericType);
    LIST_DATA_ACCESSOR(FCommonNumberFormattingOptions, NumberFormattingOptions);

    static FCommonNumberFormattingOptions NoDecimal();
    static FCommonNumberFormattingOptions WithDecimal(int32 NumFragDigit);

    float GetCurrentValue() const;
    void SetCurrentValue(float Value);

private:
    float StringToFloat(const FString& InString) const;
    
    TRange<float> DisplayValueRange = TRange<float>(0.0f, 1.0f);
    TRange<float> OutputValueRange = TRange<float>(0.0f, 1.0f);
    float SliderStepSize = 0.1f;

    ECommonNumericType DisplayNumericType = ECommonNumericType::Number;
    FCommonNumberFormattingOptions NumberFormattingOptions;    
};

