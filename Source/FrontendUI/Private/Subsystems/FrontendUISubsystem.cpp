// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/FrontendUISubsystem.h"
#include "FrontendDebugHelper.h"

UFrontendUISubsystem* UFrontendUISubsystem::Get(const UObject* WorldContextObject)
{
    if (GEngine)
    {
        if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert))
        {
            if (UGameInstance* GameInstance = World->GetGameInstance())
            {
                return UGameInstance::GetSubsystem<UFrontendUISubsystem>(GameInstance);
            }
        }
    }
    return nullptr;
}

bool UFrontendUISubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
    {
        TArray<UClass*> FoundClasses;
        GetDerivedClasses(GetClass(), FoundClasses);
        
        return FoundClasses.IsEmpty();
    }
    return false;
}

void UFrontendUISubsystem::RegisteredCreatedPrimaryLayoutWidget(UWidget_PrimaryLayout* InCreatedPrimaryLayout)
{
    check(InCreatedPrimaryLayout);
    
    CreatedPrimaryLayout = InCreatedPrimaryLayout;

    Debug::Print(TEXT("Primary layout widget stored"));
}