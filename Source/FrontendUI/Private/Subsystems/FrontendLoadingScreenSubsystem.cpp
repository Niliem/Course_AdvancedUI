// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/FrontendLoadingScreenSubsystem.h"

#include "PreLoadScreenManager.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/FrontendLoadingScreenInterface.h"
#include "Settings/FrontendLoadingScreenSettings.h"

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
    
    if (ShouldShowLoadingScreen())
    {
        TryDisplayLoadingScreenIfNone();
        OnLoadingReasonUpdated.Broadcast(CurrentLoadingReason);
    }
    else
    {
        TryRemoveLoadingScreen();

        HoldLoadingScreenStartUpTime = -1.0f;
        
        SetTickableTickType(ETickableTickType::Never);
    }
}

bool UFrontendLoadingScreenSubsystem::IsPreLoadScreenActive() const
{
    if(FPreLoadScreenManager* PreLoadScreenManager = FPreLoadScreenManager::Get())
        return PreLoadScreenManager->HasValidActivePreLoadScreen();
    return false;
}

bool UFrontendLoadingScreenSubsystem::ShouldShowLoadingScreen() const
{
    const UFrontendLoadingScreenSettings* LoadingScreenSettings = GetDefault<UFrontendLoadingScreenSettings>();
    
    if (GIsEditor && !LoadingScreenSettings->bShouldLoadingScreenInEditor)
        return false;

    if (CheckTheNeedToShowLoadingScreen())
    {
        GetGameInstance()->GetGameViewportClient()->bDisableWorldRendering = true;
        return true;
    }

    CurrentLoadingReason = TEXT("Waiting for Texture Streaming");

    GetGameInstance()->GetGameViewportClient()->bDisableWorldRendering = false;

    const float CurrentTime = FPlatformTime::Seconds();

    if (HoldLoadingScreenStartUpTime < 0.0f)
        HoldLoadingScreenStartUpTime = CurrentTime;

    const float ElapsedTime = CurrentTime - HoldLoadingScreenStartUpTime;
    if (ElapsedTime < LoadingScreenSettings->HoldLoadingScreenExtraSeconds)
        return true;
    
    return false;
}

bool UFrontendLoadingScreenSubsystem::CheckTheNeedToShowLoadingScreen() const
{
    if (bIsCurrentlyLoadingMap)
    {
        CurrentLoadingReason = TEXT("Loading Level");
        return true;
    }

    UWorld* OwningWorld = GetGameInstance()->GetWorld();
    if (!OwningWorld)
    {
        CurrentLoadingReason = TEXT("Initializing World");
        return true;
    }

    if (!OwningWorld->HasBegunPlay())
    {
        CurrentLoadingReason = TEXT("World hasn't begun play yet");
        return true;
    }

    if (!OwningWorld->GetFirstPlayerController())
    {
        CurrentLoadingReason = TEXT("Player Controller is not valid yet");
        return true;
    }
    
    return false;
}

void UFrontendLoadingScreenSubsystem::TryDisplayLoadingScreenIfNone()
{
    if (CachedCreatedLoadingScreenWidget)
        return;
    
    const UFrontendLoadingScreenSettings* LoadingScreenSettings = GetDefault<UFrontendLoadingScreenSettings>();

    TSubclassOf<UUserWidget> LoadedWidgetClass = LoadingScreenSettings->GetLoadingScreenWidgetClassChecked();
    
    UUserWidget* CreatedWidget = UUserWidget::CreateWidgetInstance(*GetGameInstance(), LoadedWidgetClass, NAME_None);
    check(CreatedWidget);

    CachedCreatedLoadingScreenWidget = CreatedWidget->TakeWidget();
    
    GetGameInstance()->GetGameViewportClient()->AddViewportWidgetContent(CachedCreatedLoadingScreenWidget.ToSharedRef(), 999);
    
    NotifyLoadingScreenVisibilityChanged(true);
}

void UFrontendLoadingScreenSubsystem::TryRemoveLoadingScreen()
{
    if (!CachedCreatedLoadingScreenWidget)
        return;

    GetGameInstance()->GetGameViewportClient()->RemoveViewportWidgetContent(CachedCreatedLoadingScreenWidget.ToSharedRef());
    CachedCreatedLoadingScreenWidget.Reset();
    
    NotifyLoadingScreenVisibilityChanged(false);
}

void UFrontendLoadingScreenSubsystem::NotifyLoadingScreenVisibilityChanged(bool bIsVisible)
{
    for (ULocalPlayer* LocalPlayer : GetGameInstance()->GetLocalPlayers())
    {
        if (!LocalPlayer)
            continue;

        if (APlayerController* PlayerController = LocalPlayer->GetPlayerController(GetGameInstance()->GetWorld()))
        {
            if (PlayerController->Implements<UFrontendLoadingScreenInterface>())
            {
                if (bIsVisible)
                    IFrontendLoadingScreenInterface::Execute_OnLoadingScreenActivated(PlayerController);
                else
                    IFrontendLoadingScreenInterface::Execute_OnLoadingScreenDeactivated(PlayerController);
            }

            if (APawn* Pawn = PlayerController->GetPawn())
            {
                if (Pawn->Implements<UFrontendLoadingScreenInterface>())
                {
                    if (bIsVisible)
                        IFrontendLoadingScreenInterface::Execute_OnLoadingScreenActivated(Pawn);
                    else
                        IFrontendLoadingScreenInterface::Execute_OnLoadingScreenDeactivated(Pawn);
                }
            }
        }
    }
}