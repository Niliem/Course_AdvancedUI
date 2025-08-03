// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "FrontendFunctionLibrary.generated.h"


/**
 * 
 */
UCLASS()
class FRONTENDUI_API UFrontendFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category = "Frontend")
    static TSoftClassPtr<UCommonActivatableWidget> GetFrontendWidgetClassByTag(UPARAM(meta = (Categories = "Frontend.Widget")) FGameplayTag WidgetTag);
};