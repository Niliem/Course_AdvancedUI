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

void UListDataObject_Scalar::SetCurrentValue(float InNewValue)
{
    TrySetCurrentOptionValueFromFloat(InNewValue, EOptionsListDataModifyReason::DirectlyModified);
}

bool UListDataObject_Scalar::TrySetCurrentOptionValueFromFloat(float Value, EOptionsListDataModifyReason ModifyReason)
{
    if (DataDynamicSetter)
    {
        const float ClampedValue = FMath::GetMappedRangeValueClamped(DisplayValueRange, OutputValueRange, Value);
        DataDynamicSetter->SetValueFromString(LexToString(ClampedValue));

        NotifyListDataModified(this, ModifyReason);
        return true;
    }
    return false;
}

bool UListDataObject_Scalar::TrySetCurrentOptionValueFromString(const FString& InStringValue, EOptionsListDataModifyReason ModifyReason)
{
    if (DataDynamicSetter)
    {
        DataDynamicSetter->SetValueFromString(InStringValue);
        NotifyListDataModified(this, ModifyReason);
        return true;
    }
    return false;
}

bool UListDataObject_Scalar::CanResetBackToDefaultValue() const
{
    if (HasDefaultValue() && DataDynamicGetter)
    {
        const float DefaultValue = StringToFloat(GetDefaultValueAsString());
        const float CurrentValue = StringToFloat(DataDynamicGetter->GetValueAsString());

        return !FMath::IsNearlyEqual(DefaultValue, CurrentValue, 0.01f);
    }
    return  false;
}

bool UListDataObject_Scalar::TryResetBackToDefaultValue()
{
    if (!CanResetBackToDefaultValue())
        return false;

    return TrySetCurrentOptionValueFromString(GetDefaultValueAsString(), EOptionsListDataModifyReason::ResetToDefault);;
}

void UListDataObject_Scalar::OnEditDependencyDataModified(UListDataObject_Base* ModifiedDependencyData, EOptionsListDataModifyReason ModifyReason)
{
    NotifyListDataModified(this, EOptionsListDataModifyReason::DependencyModified);
    
    Super::OnEditDependencyDataModified(ModifiedDependencyData, ModifyReason);
}

float UListDataObject_Scalar::StringToFloat(const FString& InString) const
{
    float Result = 0.0f;
    LexFromString(Result, *InString);
    return Result;
}