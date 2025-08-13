// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncAction_PushWidgetToLayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPushWidgetToLayerAsyncDelegate, UCommonActivatableWidget*, Widget);

/**
 * 
 */
UCLASS()
class FRONTENDUI_API UAsyncAction_PushWidgetToLayer : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject", BlueprintInternalUseOnly = "true", DisplayName="Push Widget To Layer(By Class)" ))
    static UAsyncAction_PushWidgetToLayer* PushWidgetToLayerByClass(const UObject* WorldContextObject,
        APlayerController* PlayerController,
        TSoftClassPtr<UCommonActivatableWidget> WidgetClass,
        UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag LayerTag,
        bool bFocusOnNewlyPushedWidget = true);

    UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject", BlueprintInternalUseOnly = "true", DisplayName="Push Widget To Layer(By Tag)" ))
    static UAsyncAction_PushWidgetToLayer* PushWidgetToLayerByTag(const UObject* WorldContextObject,
        APlayerController* PlayerController,
        UPARAM(meta = (Categories = "Frontend.Widget")) FGameplayTag WidgetTag,
        UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag LayerTag,
        bool bFocusOnNewlyPushedWidget = true);

    //~ Begin UBlueprintAsyncActionBase Interface
    virtual void Activate() override;
    //~ End UBlueprintAsyncActionBase Interface
    
    UPROPERTY(BlueprintAssignable)
    FOnPushWidgetToLayerAsyncDelegate BeforePush;

    UPROPERTY(BlueprintAssignable)
    FOnPushWidgetToLayerAsyncDelegate AfterPush;
    
private:
    TWeakObjectPtr<UWorld> World;
    TWeakObjectPtr<APlayerController> PlayerController;
    TSoftClassPtr<UCommonActivatableWidget> WidgetClass;
    FGameplayTag LayerTag;
    bool bFocusOnNewlyPushedWidget;
};