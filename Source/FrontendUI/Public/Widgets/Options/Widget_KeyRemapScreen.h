// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "CommonInputTypeEnum.h"
#include "Widget_KeyRemapScreen.generated.h"

class UCommonRichTextBlock;
class FKeyRemapScreenInputPreprocessor;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UWidget_KeyRemapScreen : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
    void SetDesiredInputTypeToFilter(ECommonInputType InDesiredInputType);

protected:    
    //~ Begin UCommonActivatableWidget Interface
    virtual void NativeOnActivated() override;
    virtual void NativeOnDeactivated() override;
    //~ End UCommonActivatableWidget Interface
    
private:
    //***** Bound Widgets *****//
    UPROPERTY(meta = (BindWidget))
    UCommonRichTextBlock* CommonRichTextBlock_RemapMessage;
    //***** Bound Widgets *****//

    TSharedPtr<FKeyRemapScreenInputPreprocessor> CachedInputPreprocessor;
    ECommonInputType CachedDesiredInputType;
};
