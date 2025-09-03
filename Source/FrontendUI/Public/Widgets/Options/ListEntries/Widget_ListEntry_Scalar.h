// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Options/ListEntries/Widget_ListEntry_Base.h"
#include "Widget_ListEntry_Scalar.generated.h"

class UCommonNumericTextBlock;
class UAnalogSlider;
class UListDataObject_Scalar;

/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UWidget_ListEntry_Scalar : public UWidget_ListEntry_Base
{
    GENERATED_BODY()

protected:
    //~ Begin UUserWidget Interface
    virtual void NativeOnInitialized() override;
    //~ End UUserWidget Interface

    //~ Begin UWidget_ListEntry_Base Interface
    virtual void OnOwningListDataObjectSet(UListDataObject_Base* ListDataObject) override;
    virtual void OnOwningListDataObjectModified(UListDataObject_Base* ModifiedData, EOptionsListDataModifyReason ModifyReason) override;
    //~ End UWidget_ListEntry_Base Interface
    
private:
    //***** Bound Widgets *****//
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess= "true"))
    UCommonNumericTextBlock* CommonNumeric_SettingValue;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess= "true"))
    UAnalogSlider* AnalogSlider_SettingSlider;    
    //***** Bound Widgets *****//

    UPROPERTY(Transient)
    UListDataObject_Scalar* CachedListDataObject;
};
