// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "Widget_PrimaryLayout.generated.h"

class UCommonActivatableWidgetContainerBase;

/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UWidget_PrimaryLayout : public UCommonUserWidget
{
    GENERATED_BODY()

public:
    UCommonActivatableWidgetContainerBase* FindWidgetLayerByTag(const FGameplayTag& InTag) const;

protected:
    UFUNCTION(BlueprintCallable)
    void RegisterWidgetLayer(UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag InLayerTag, UCommonActivatableWidgetContainerBase* InLayerWidget);

private:
    UPROPERTY(Transient)
    TMap<FGameplayTag, UCommonActivatableWidgetContainerBase*> RegisteredWidgetLayerMap;
};