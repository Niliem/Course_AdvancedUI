// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "FrontendEnumTypes.h"
#include "Widget_ConfirmScreen.generated.h"

class UDynamicEntryBox;
class UCommonTextBlock;

USTRUCT(BlueprintType)
struct FConfirmScreenButtonInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EConfirmScreenButtonType ButtonType = EConfirmScreenButtonType::Unknown;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText ButtonTextToDisplay;
};

UCLASS()
class FRONTENDUI_API UConfirmScreenInfoObject : public UObject
{
    GENERATED_BODY()

public:
    static UConfirmScreenInfoObject* CreateOkScreen(const FText& ScreenTitle, const FText& ScreenMessage);
    static UConfirmScreenInfoObject* CreateYesNoScreen(const FText& ScreenTitle, const FText& ScreenMessage);
    static UConfirmScreenInfoObject* CreateOkCancelScreen(const FText& ScreenTitle, const FText& ScreenMessage);
    
    UPROPERTY(Transient)
    FText ScreenTitle;

    UPROPERTY(Transient)
    FText ScreenMessage;

    UPROPERTY(Transient)
    TArray<FConfirmScreenButtonInfo> ScreenButtons;
};

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
