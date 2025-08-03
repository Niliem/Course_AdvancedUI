// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncAction_PushWidgetToLayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPushWidgetToLayerAsyncSignature, UCommonActivatableWidget*, Widget);

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
        TSoftClassPtr<UCommonActivatableWidget> WidgetClass,
        UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag LayerTag,
        bool bFocusOnNewlyPushedWidget = true);

    //~ Begin UBlueprintAsyncActionBase Interface
    virtual void Activate() override;
    //~ End UBlueprintAsyncActionBase Interface
    
    UPROPERTY(BlueprintAssignable)
    FOnPushWidgetToLayerAsyncSignature BeforePush;

    UPROPERTY(BlueprintAssignable)
    FOnPushWidgetToLayerAsyncSignature AfterPush;
    
private:
    TWeakObjectPtr<UWorld> World;
    TWeakObjectPtr<APlayerController> PlayerController;
    TSoftClassPtr<UCommonActivatableWidget> WidgetClass;
    FGameplayTag LayerTag;
    bool bFocusOnNewlyPushedWidget;
};