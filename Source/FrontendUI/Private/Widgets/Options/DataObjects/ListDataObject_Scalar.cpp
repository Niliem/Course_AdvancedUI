// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Options/DataObjects/ListDataObject_Scalar.h"

#include "Widgets/Options/OptionsDataInteractionHelper.h"

FCommonNumberFormattingOptions UListDataObject_Scalar::NoDecimal()
{
    FCommonNumberFormattingOptions FormattingOptions;
    FormattingOptions.MaximumFractionalDigits = 0;

    return FormattingOptions;
}

FCommonNumberFormattingOptions UListDataObject_Scalar::WithDecimal(int32 NumFragDigit)
{
    FCommonNumberFormattingOptions FormattingOptions;
    FormattingOptions.MaximumFractionalDigits = NumFragDigit;

    return FormattingOptions;
}

float UListDataObject_Scalar::GetCurrentValue() const
{
    if (DataDynamicGetter)
    {
        return FMath::GetMappedRangeValueClamped(OutputValueRange, DisplayValueRange, StringToFloat(DataDynamicGetter->GetValueAsString()));
    }

    return 0.0f;
}

void UListDataObject_Scalar::SetCurrentValue(float Value)
{
    if (DataDynamicSetter)
    {
        const float ClampedValue = FMath::GetMappedRangeValueClamped(DisplayValueRange, OutputValueRange, Value);
        DataDynamicSetter->SetValueFromString(LexToString(ClampedValue));

        NotifyListDataModified(this, EOptionsListDataModifyReason::DirectlyModified);
    }
}

float UListDataObject_Scalar::StringToFloat(const FString& InString) const
{
    float Result = 0.0f;
    LexFromString(Result, *InString);
    return Result;
}