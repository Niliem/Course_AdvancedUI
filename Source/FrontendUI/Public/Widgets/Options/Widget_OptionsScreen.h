// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Widget_OptionsScreen.generated.h"

class UInputAction;
class UOptionsDataRegistry;
class UFrontendTabListWidgetBase;
class UFrontendCommonListView;

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

    //~ Begin UCommonActivatableWidget Interface
    virtual void NativeOnActivated() override;
    virtual void NativeOnDeactivated() override;
    //~ End UCommonActivatableWidget Interface
    
private:
    UOptionsDataRegistry* GetOrCreateDataRegistry();
    
    void HandleCancelBoundAction();
    void HandleBackBoundAction();

    UFUNCTION()
    void OnOptionsTabSelected(FName TabId);

    //**** Bound Widgets ****//
    UPROPERTY(meta = (BindWidget))
    UFrontendTabListWidgetBase* TabListWidget_OptionsTabs;

    UPROPERTY(meta = (BindWidget))
    UFrontendCommonListView* CommonListView_OptionsList;
    //**** Bound Widgets ****//

    UPROPERTY(Transient)
    UOptionsDataRegistry* OwningDataRegistry;
    
    UPROPERTY(EditDefaultsOnly, Category = "Frontend Options Screen", meta = (EditCondition = "CommonInput.CommonInputSettings.IsEnhancedInputSupportEnabled", EditConditionHides))
    TObjectPtr<UInputAction> EnhancedInputCancelAction;

    FUIActionBindingHandle CancelActionHandle;
};
