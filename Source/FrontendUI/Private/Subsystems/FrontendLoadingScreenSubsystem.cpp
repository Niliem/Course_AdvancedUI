// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/FrontendLoadingScreenSubsystem.h"

#include "FrontendDebugHelper.h"

bool UFrontendLoadingScreenSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
    {
        TArray<UClass*> FoundClasses;
        GetDerivedClasses(GetClass(), FoundClasses);
        return FoundClasses.IsEmpty();
    }
    return false;
}

void UFrontendLoadingScreenSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    FCoreUObjectDelegates::PreLoadMapWithContext.AddUObject(this, &UFrontendLoadingScreenSubsystem::OnMapPreLoaded);
    FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UFrontendLoadingScreenSubsystem::OnMapPostLoaded);
}

void UFrontendLoadingScreenSubsystem::Deinitialize()
{
    FCoreUObjectDelegates::PreLoadMapWithContext.RemoveAll(this);
    FCoreUObjectDelegates::PostLoadMapWithWorld.RemoveAll(this);
    
    Super::Deinitialize();
}

void UFrontendLoadingScreenSubsystem::OnMapPreLoaded(const FWorldContext& WorldContext, const FString& MapName)
{
    Debug::Print(TEXT("On Map Pre Loaded"));
}

void UFrontendLoadingScreenSubsystem::OnMapPostLoaded(UWorld* LoadedWorld)
{
    Debug::Print(TEXT("On Map Post Loaded"));
}