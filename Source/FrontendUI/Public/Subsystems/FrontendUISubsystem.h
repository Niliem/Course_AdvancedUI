// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FrontendUISubsystem.generated.h"

class UCommonActivatableWidget;
class UWidget_PrimaryLayout;
struct FGameplayTag;

enum class EAsyncPushWidgetState : uint8
{
    BeforePush,
    AfterPush
};

/**
 * 
 */
UCLASS()
class FRONTENDUI_API UFrontendUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
    static UFrontendUISubsystem* Get(const UObject* WorldContextObject);

    //~ Begin USubsystem Interface
    virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
    //~ End USubsystem Interface

    UFUNCTION(BlueprintCallable)
    void RegisteredCreatedPrimaryLayoutWidget(UWidget_PrimaryLayout* InCreatedPrimaryLayout);

    void PushSoftWidgetToLayerStackAsync(UPARAM(meta = (Categories = "UI.Layer")) const FGameplayTag& LayerTag, TSoftClassPtr<UCommonActivatableWidget> SoftWidgetClass, TFunction<void(EAsyncPushWidgetState, UCommonActivatableWidget*)> AsyncPushStateCallback);

private:
    UPROPERTY(Transient)
    TObjectPtr<UWidget_PrimaryLayout> CreatedPrimaryLayout;
};
