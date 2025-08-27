// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Components/FrontendCommonButtonBase.h"
#include "Subsystems/FrontendUISubsystem.h"
#include "CommonTextBlock.h"

void UFrontendCommonButtonBase::SetButtonText(FText Text)
{
    if (CommonTextBlock_ButtonText && !Text.IsEmpty())
    {
        CommonTextBlock_ButtonText->SetText(bUseUpperCaseForButtonText ? Text.ToUpper() : Text);
    }
}

FText UFrontendCommonButtonBase::GetButtonText() const
{
    if (CommonTextBlock_ButtonText)
        return CommonTextBlock_ButtonText->GetText();

    return FText();
}

void UFrontendCommonButtonBase::NativePreConstruct()
{
    Super::NativePreConstruct();

    SetButtonText(ButtonDisplayText);
}

void UFrontendCommonButtonBase::NativeOnCurrentTextStyleChanged()
{
    Super::NativeOnCurrentTextStyleChanged();

    if (CommonTextBlock_ButtonText && GetCurrentTextStyleClass())
    {
        CommonTextBlock_ButtonText->SetStyle(GetCurrentTextStyleClass());
    }
}

void UFrontendCommonButtonBase::NativeOnHovered()
{
    Super::NativeOnHovered();
    
    if (!ButtonDescriptionText.IsEmpty())
    {
        UFrontendUISubsystem::Get(this)->OnButtonDescriptionTextUpdated.Broadcast(this, ButtonDescriptionText);
    }
}

void UFrontendCommonButtonBase::NativeOnUnhovered()
{
    Super::NativeOnUnhovered();

    UFrontendUISubsystem::Get(this)->OnButtonDescriptionTextUpdated.Broadcast(this, FText::GetEmpty());
}