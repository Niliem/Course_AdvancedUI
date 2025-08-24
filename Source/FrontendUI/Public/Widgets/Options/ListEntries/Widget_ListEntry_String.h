// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Options/ListEntries/Widget_ListEntry_Base.h"
#include "Widget_ListEntry_String.generated.h"

class UFrontendCommonRotator;
class UFrontendCommonButtonBase;
class UListDataObject_String;

/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UWidget_ListEntry_String : public UWidget_ListEntry_Base
{
	GENERATED_BODY()

protected:
    //~ Begin UWidget_ListEntry_Base Interface
    virtual void OnOwningListDataObjectSet(UListDataObject_Base* ListDataObject) override;
    //~ End UWidget_ListEntry_Base Interface
    
private:
    //**** Bound Widgets ****//
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess= "true"))
    UFrontendCommonButtonBase* CommonButton_PreviousOption;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess= "true"))
    UFrontendCommonRotator* CommonRotator_AvailableOptions;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess= "true"))
    UFrontendCommonButtonBase* CommonButton_NextOption;
    //**** Bound Widgets ****//

    UPROPERTY(Transient)
    UListDataObject_String* CachedListDataObject;
};
