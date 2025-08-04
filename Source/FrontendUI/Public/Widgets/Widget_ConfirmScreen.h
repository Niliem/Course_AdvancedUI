// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "FrontendEnumTypes.h"
#include "Widget_ConfirmScreen.generated.h"

class UDynamicEntryBox;
class UCommonTextBlock;

/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UWidget_ConfirmScreen : public UCommonActivatableWidget
{
	GENERATED_BODY()

private:
    UPROPERTY(meta = (BindWidgetOptional))
    UCommonTextBlock* CommonTextBlock_ButtonText;

    UPROPERTY(meta = (BindWidgetOptional))
    UCommonTextBlock* CommonTextBlock_Message;

    UPROPERTY(meta = (BindWidgetOptional))
    UDynamicEntryBox* DynamicEntryBox_Buttons;
};
