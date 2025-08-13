// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FrontendEnumTypes.h"
#include "FrontendUISubsystem.generated.h"

class UFrontendCommonButtonBase;
class UCommonActivatableWidget;
class UWidget_PrimaryLayout;
struct FGameplayTag;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonDescriptionTextUpdatedDelegate, UFrontendCommonButtonBase*, BroadcastingButton, FText, Description);

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

    UFUNCTION(BlueprintCallable, Category="UI")
    UWidget_PrimaryLayout* SetupPrimaryLayoutWidget(APlayerController* OwnerController, int32 ZOrder);

    void PushSoftWidgetToLayerStackAsync(UPARAM(meta = (Categories = "UI.Layer")) const FGameplayTag& LayerTag, TSoftClassPtr<UCommonActivatableWidget> SoftWidgetClass, TFunction<void(EAsyncPushWidgetState, UCommonActivatableWidget*)> AsyncPushStateCallback);
    void PushConfirmScreenAsync(EConfirmScreenType ConfirmScreenType, const FText& Title, const FText& Message, TFunction<void(EConfirmScreenButtonType)> ButtonClickedCallback);

    UPROPERTY(BlueprintAssignable)
    FOnButtonDescriptionTextUpdatedDelegate OnButtonDescriptionTextUpdated;

private:
    UPROPERTY(Transient)
    TObjectPtr<UWidget_PrimaryLayout> CreatedPrimaryLayout;
};