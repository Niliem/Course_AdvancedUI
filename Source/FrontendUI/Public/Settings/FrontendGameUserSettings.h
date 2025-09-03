// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "FrontendGameUserSettings.generated.h"

/**
 * 
 */
UCLASS()
class FRONTENDUI_API UFrontendGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
    UFrontendGameUserSettings();
    
    static UFrontendGameUserSettings* Get();

    //***** Gameplay Collection Tab *****//
    UFUNCTION()
    FString GetGameDifficulty() const { return GameDifficulty; }

    UFUNCTION()
    void SetGameDifficulty(const FString& InNewGameDifficulty) { GameDifficulty = InNewGameDifficulty; }    
    //***** Gameplay Collection Tab *****//

    
    //***** Audio Collection Tab *****//
    UFUNCTION()
    float GetOverallVolume() const { return OverallVolume; }

    UFUNCTION()
    void SetOverallVolume(float InNewOverallVolume);
    //***** Audio Collection Tab *****//

private:
    //***** Gameplay Collection Tab *****//
    UPROPERTY(Config)
    FString GameDifficulty;
    //***** Gameplay Collection Tab *****//


    //***** Audio Collection Tab *****//
    UPROPERTY(Config)
    float OverallVolume;
    //***** Audio Collection Tab *****//
};
