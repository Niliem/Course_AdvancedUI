// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Components/FrontendCommonButtonBase.h"
#include "CommonTextBlock.h"

void UFrontendCommonButtonBase::SetButtonText(FText Text)
{
    if (CommonTextBlock_ButtonText && !Text.IsEmpty())
    {
        CommonTextBlock_ButtonText->SetText(bUseUpperCaseForButtonText ? Text.ToUpper() : Text);
    }
}

void UFrontendCommonButtonBase::NativePreConstruct()
{
    Super::NativePreConstruct();

    SetButtonText(ButtonDisplayText);
}