// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/FrontendPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "Settings/FrontendGameUserSettings.h"


void AFrontendPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    TArray<AActor*> FoundCameras;
    UGameplayStatics::GetAllActorsOfClassWithTag(this, ACameraActor::StaticClass(), FName("Default"), FoundCameras);
    if (!FoundCameras.IsEmpty())
    {
        SetViewTarget(FoundCameras[0]);
    }

    if (UFrontendGameUserSettings* GameUserSettings = UFrontendGameUserSettings::Get())
    {
        if (GameUserSettings->GetLastCPUBenchmarkResult() == -1.f || GameUserSettings->GetLastGPUBenchmarkResult() == -1.f)
        {
            GameUserSettings->RunHardwareBenchmark();
            GameUserSettings->ApplyHardwareBenchmarkResults();
        }
    }
}