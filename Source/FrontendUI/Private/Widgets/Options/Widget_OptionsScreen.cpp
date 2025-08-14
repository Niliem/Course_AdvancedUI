// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Options/Widget_OptionsScreen.h"
#include "ICommonInputModule.h"
#include "Input/CommonUIInputTypes.h"

void UWidget_OptionsScreen::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (EnhancedInputCancelAction)
    {
        CancelActionHandle = RegisterUIActionBinding(FBindUIActionArgs(EnhancedInputCancelAction, true,
           FSimpleDelegate::CreateUObject(this, &ThisClass::HandleCancelBoundAction)));
    }

    RegisterUIActionBinding(FBindUIActionArgs(ICommonInputModule::GetSettings().GetEnhancedInputBackAction(), true,
           FSimpleDelegate::CreateUObject(this, &ThisClass::HandleBackBoundAction)));    
}

void UWidget_OptionsScreen::HandleCancelBoundAction()
{
    UE_LOG(LogTemp, Warning, TEXT("UInputAction::HandleCancelBoundAction"));
}

void UWidget_OptionsScreen::HandleBackBoundAction()
{
    DeactivateWidget();
}
