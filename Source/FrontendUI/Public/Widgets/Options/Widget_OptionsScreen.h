// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "FrontendEnumTypes.h"
#include "Widget_OptionsScreen.generated.h"

class UListDataObject_Base;
class UWidget_OptionsDetailsView;
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
    virtual UWidget* NativeGetDesiredFocusTarget() const override;
    //~ End UCommonActivatableWidget Interface
    
private:
    UOptionsDataRegistry* GetOrCreateDataRegistry();
    
    void HandleResetBoundAction();
    void HandleBackBoundAction();

    UFUNCTION()
    void OnOptionsTabSelected(FName TabId);

    void OnListViewItemHovered(UObject* InHoveredItem, bool bWasHovered);
    void OnListViewItemSelected(UObject* InSelectedItem);

    FString TryGetEntryWidgetClassName(UObject* InOwningListItem) const;
    
    void OnListViewListDataModified(UListDataObject_Base* ModifiedData, EOptionsListDataModifyReason ModifyReason);

    //***** Bound Widgets *****//
    UPROPERTY(meta = (BindWidget))
    UFrontendTabListWidgetBase* TabListWidget_OptionsTabs;

    UPROPERTY(meta = (BindWidget))
    UFrontendCommonListView* CommonListView_OptionsList;

    UPROPERTY(meta = (BindWidget))
    UWidget_OptionsDetailsView* DetailsView_ListEntryInfo;
    //***** Bound Widgets *****//

    UPROPERTY(Transient)
    UOptionsDataRegistry* OwningDataRegistry;
    
    UPROPERTY(EditDefaultsOnly, Category = "Frontend Options Screen", meta = (EditCondition = "CommonInput.CommonInputSettings.IsEnhancedInputSupportEnabled", EditConditionHides))
    TObjectPtr<UInputAction> EnhancedInputResetAction;

    FUIActionBindingHandle ResetActionHandle;

    UPROPERTY(Transient)
    TArray<UListDataObject_Base*> ResettableDataArray;

    bool bIsResettingData = false;
};

