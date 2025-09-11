// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Options/ListEntries/Widget_ListEntry_Base.h"
#include "Widget_ListEntry_KeyRemap.generated.h"

class UFrontendCommonButtonBase;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UWidget_ListEntry_KeyRemap : public UWidget_ListEntry_Base
{
	GENERATED_BODY()

private:
    //***** Bound Widgets *****//
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess= "true"))
    UFrontendCommonButtonBase* CommonButton_RemapKey;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess= "true"))
    UFrontendCommonButtonBase* CommonButton_ResetKeyBinding;
    //***** Bound Widgets *****//
};
