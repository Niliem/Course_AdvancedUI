// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Widget_ListEntry_Base.generated.h"

class UCommonTextBlock;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UWidget_ListEntry_Base : public UCommonUserWidget, public IUserObjectListEntry
{
    GENERATED_BODY()

public:
    //~ Begin IUserObjectListEntry Interface    
    virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
    //~ End IUserObjectListEntry Interface

private:
    //**** Bound Widgets ****//
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess= "true"))
    UCommonTextBlock* CommonText_SettingDisplayName;
    //**** Bound Widgets ****//
};