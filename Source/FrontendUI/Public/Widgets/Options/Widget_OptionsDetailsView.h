// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_OptionsDetailsView.generated.h"

class UListDataObject_Base;
class UCommonTextBlock;
class UCommonLazyImage;
class UCommonRichTextBlock;

/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UWidget_OptionsDetailsView : public UUserWidget
{
	GENERATED_BODY()

public:
    void UpdateDetailsViewInfo(UListDataObject_Base* InDataObject, const FString& InEntryWidgetClassName = FString());
    void ClearDetailsViewInfo();

protected:
    //~ Begin UUserWidget Interface
    virtual void NativeOnInitialized() override;
    //~ End UUserWidget Interface

private:
    //***** Bound Widgets *****//
    UPROPERTY(meta = (BindWidget))
    UCommonTextBlock* CommonTextBlock_Title;

    UPROPERTY(meta = (BindWidget))
    UCommonLazyImage* CommonLazyImage_DescriptionImage;

    UPROPERTY(meta = (BindWidget))
    UCommonRichTextBlock* CommonRichTextBlock_Description;

    UPROPERTY(meta = (BindWidget))
    UCommonRichTextBlock* CommonRichTextBlock_DynamicDetails;
    
    UPROPERTY(meta = (BindWidget))
    UCommonRichTextBlock* CommonRichTextBlock_DisabledReason;
    //***** Bound Widgets *****//
};
