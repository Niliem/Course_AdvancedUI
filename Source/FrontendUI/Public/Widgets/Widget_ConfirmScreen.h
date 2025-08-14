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

public:
    struct FConfirmScreenButtonInfo
    {
        EConfirmScreenButtonType Type = EConfirmScreenButtonType::Unknown;
        FText TextToDisplay = FText::GetEmpty();
    };

    struct FConfirmScreenInfo
    {
        FText Title = FText::GetEmpty();
        FText Message = FText::GetEmpty();
        TArray<FConfirmScreenButtonInfo> AvailableButtons {};
    };
    
    static FConfirmScreenInfo CreateOkScreen(const FText& ScreenTitle, const FText& ScreenMessage);
    static FConfirmScreenInfo CreateOkCancelScreen(const FText& ScreenTitle, const FText& ScreenMessage);
    static FConfirmScreenInfo CreateYesNoScreen(const FText& ScreenTitle, const FText& ScreenMessage);    
    static FConfirmScreenInfo CreateYesNoCancelScreen(const FText& ScreenTitle, const FText& ScreenMessage);
    
    void InitConfirmScreen(const FConfirmScreenInfo& ConfirmScreenInfo, TFunction<void (EConfirmScreenButtonType)> ClickedButtonCallback);
    
private:
    UPROPERTY(meta = (BindWidgetOptional))
    UCommonTextBlock* CommonTextBlock_Title;

    UPROPERTY(meta = (BindWidgetOptional))
    UCommonTextBlock* CommonTextBlock_Message;

    UPROPERTY(meta = (BindWidgetOptional))
    UDynamicEntryBox* DynamicEntryBox_Buttons;
};
