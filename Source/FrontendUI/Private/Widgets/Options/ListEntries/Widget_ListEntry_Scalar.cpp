// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Options/ListEntries/Widget_ListEntry_Scalar.h"
#include "Widgets/Options/DataObjects/ListDataObject_Scalar.h"
#include "AnalogSlider.h"

void UWidget_ListEntry_Scalar::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    AnalogSlider_SettingSlider->OnValueChanged.AddUniqueDynamic(this, &UWidget_ListEntry_Scalar::OnSliderValueChanged);
}

void UWidget_ListEntry_Scalar::OnOwningListDataObjectSet(UListDataObject_Base* ListDataObject)
{
    Super::OnOwningListDataObjectSet(ListDataObject);

    CachedListDataObject = CastChecked<UListDataObject_Scalar>(ListDataObject);

    CommonNumeric_SettingValue->SetNumericType(CachedListDataObject->GetDisplayNumericType());
    CommonNumeric_SettingValue->FormattingSpecification = CachedListDataObject->GetNumberFormattingOptions();
    CommonNumeric_SettingValue->SetCurrentValue(CachedListDataObject->GetCurrentValue());

    AnalogSlider_SettingSlider->SetMinValue(CachedListDataObject->GetDisplayValueRange().GetLowerBoundValue());
    AnalogSlider_SettingSlider->SetMaxValue(CachedListDataObject->GetDisplayValueRange().GetUpperBoundValue());
    AnalogSlider_SettingSlider->SetStepSize(CachedListDataObject->GetSliderStepSize());
    AnalogSlider_SettingSlider->SetValue(CachedListDataObject->GetCurrentValue());
}

void UWidget_ListEntry_Scalar::OnOwningListDataObjectModified(UListDataObject_Base* ModifiedData, EOptionsListDataModifyReason ModifyReason)
{
    if (!CachedListDataObject)
        return;

    CommonNumeric_SettingValue->SetCurrentValue(CachedListDataObject->GetCurrentValue());
    AnalogSlider_SettingSlider->SetValue(CachedListDataObject->GetCurrentValue());
}

void UWidget_ListEntry_Scalar::OnSliderValueChanged(float Value)
{
    if (!CachedListDataObject)
        return;

    CachedListDataObject->SetCurrentValue(Value);
}