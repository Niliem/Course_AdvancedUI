// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncAction_PushWidgetToLayer.generated.h"

class UWidget_ActivatableBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPushWidgetToLayerAsyncSignature, UWidget_ActivatableBase*, Widget);
/**
 * 
 */
UCLASS()
class FRONTENDUI_API UAsyncAction_PushWidgetToLayer : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject", BlueprintInternalUseOnly = "true" ))
    static UAsyncAction_PushWidgetToLayer* PushWidgetToLayer(const UObject* WorldContextObject,
        APlayerController* PlayerController,
        TSoftClassPtr<UWidget_ActivatableBase> WidgetClass,
        UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag LayerTag,
        bool bFocusOnNewlyPushedWidget = true);

    UPROPERTY(BlueprintAssignable)
    FOnPushWidgetToLayerAsyncSignature BeforePush;

    UPROPERTY(BlueprintAssignable)
    FOnPushWidgetToLayerAsyncSignature AfterPush;
};