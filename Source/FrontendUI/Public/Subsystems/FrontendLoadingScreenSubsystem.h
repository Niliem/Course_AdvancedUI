// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FrontendLoadingScreenSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class FRONTENDUI_API UFrontendLoadingScreenSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
    //~ Begin USubsystem Interface
    virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;   
    virtual void Deinitialize() override;
    //~ End USubsystem Interface

private:
    void OnMapPreLoaded(const FWorldContext& WorldContext, const FString& MapName);
    void OnMapPostLoaded(UWorld* LoadedWorld);
};
