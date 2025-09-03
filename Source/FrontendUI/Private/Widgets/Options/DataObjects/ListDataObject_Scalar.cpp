// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Options/DataObjects/ListDataObject_Scalar.h"

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