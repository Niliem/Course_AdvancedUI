// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FrontendLoadingScreenSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class FRONTENDUI_API UFrontendLoadingScreenSubsystem : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

public:
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoadingReasonUpdatedDelegate, const FString&, CurrentLoadingReason);
    UPROPERTY(BlueprintAssignable)
    FOnLoadingReasonUpdatedDelegate OnLoadingReasonUpdated;
    
    //~ Begin USubsystem Interface
    virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;   
    virtual void Deinitialize() override;
    //~ End USubsystem Interface

    //~ Begin FTickableGameObject Interface
    virtual void Tick(float DeltaTime) override;
    virtual UWorld* GetTickableGameObjectWorld() const override;
    virtual bool IsTickable() const override;
    virtual ETickableTickType GetTickableTickType() const override;
    virtual TStatId GetStatId() const override;
    //~ End FTickableGameObject Interface

private:
    void OnMapPreLoaded(const FWorldContext& WorldContext, const FString& MapName);
    void OnMapPostLoaded(UWorld* LoadedWorld);

    void TryUpdateLoadingScreen();
    bool IsPreLoadScreenActive() const;
    bool ShouldShowLoadingScreen() const;
    bool CheckTheNeedToShowLoadingScreen() const;
    
    void TryDisplayLoadingScreenIfNone();

    bool bIsCurrentlyLoadingMap = false;
    TSharedPtr<SWidget> CachedCreatedLoadingScreenWidget;
    
    mutable float HoldLoadingScreenStartUpTime = -1.0f;
    mutable FString CurrentLoadingReason;
};

