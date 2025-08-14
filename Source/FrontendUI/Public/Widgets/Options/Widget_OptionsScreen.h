// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Widget_OptionsScreen.generated.h"

class UInputAction;

/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UWidget_OptionsScreen : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
    //~ Begin UUserWidget Interface
    virtual void NativeOnInitialized() override;
    //~ End UUserWidget Interface
    
private:
    void HandleCancelBoundAction();
    void HandleBackBoundAction();
    
    UPROPERTY(EditDefaultsOnly, Category = "Frontend Options Screen", meta = (EditCondition = "CommonInput.CommonInputSettings.IsEnhancedInputSupportEnabled", EditConditionHides))
    TObjectPtr<UInputAction> EnhancedInputCancelAction;

    FUIActionBindingHandle CancelActionHandle;
};
