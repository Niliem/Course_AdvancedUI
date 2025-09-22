// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/FrontendLoadingScreenSubsystem.h"

#include "PreLoadScreenManager.h"

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

void UFrontendLoadingScreenSubsystem::Tick(float DeltaTime)
{
    TryUpdateLoadingScreen();
}

UWorld* UFrontendLoadingScreenSubsystem::GetTickableGameObjectWorld() const
{
    if (UGameInstance* OwningGameInstance = GetGameInstance())
        return OwningGameInstance->GetWorld();
    
    return FTickableGameObject::GetTickableGameObjectWorld();
}

bool UFrontendLoadingScreenSubsystem::IsTickable() const
{
    return GetGameInstance() && GetGameInstance()->GetGameViewportClient();
}

ETickableTickType UFrontendLoadingScreenSubsystem::GetTickableTickType() const
{
    if (IsTemplate())
        return ETickableTickType::Never;
    
    return ETickableTickType::Conditional;
}

TStatId UFrontendLoadingScreenSubsystem::GetStatId() const
{
    RETURN_QUICK_DECLARE_CYCLE_STAT(UFrontendLoadingScreenSubsystem, STATGROUP_Tickables);
}

void UFrontendLoadingScreenSubsystem::OnMapPreLoaded(const FWorldContext& WorldContext, const FString& MapName)
{
    if (WorldContext.OwningGameInstance != GetGameInstance())
        return;

    SetTickableTickType(ETickableTickType::Conditional);

    bIsCurrentlyLoadingMap = true;

    TryUpdateLoadingScreen();
}

void UFrontendLoadingScreenSubsystem::OnMapPostLoaded(UWorld* LoadedWorld)
{
    if (LoadedWorld && LoadedWorld->GetGameInstance() == GetGameInstance())
        bIsCurrentlyLoadingMap = false;
}

void UFrontendLoadingScreenSubsystem::TryUpdateLoadingScreen()
{
    if (IsPreLoadScreenActive())
        return;
    
    if (true)
    {
        
    }
    else
    {
        SetTickableTickType(ETickableTickType::Never);
    }
}

bool UFrontendLoadingScreenSubsystem::IsPreLoadScreenActive() const
{
    if(FPreLoadScreenManager* PreLoadScreenManager = FPreLoadScreenManager::Get())
        return PreLoadScreenManager->HasValidActivePreLoadScreen();
    return false;
}