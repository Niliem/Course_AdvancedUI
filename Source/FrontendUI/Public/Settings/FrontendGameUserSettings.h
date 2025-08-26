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
    static UFrontendGameUserSettings* Get();

    //***** Gameplay Collection Tab *****//
    UFUNCTION()
    FString GetGameDifficulty() const { return GameDifficulty; }

    UFUNCTION()
    void SetGameDifficulty(const FString& InNewGameDifficulty) { GameDifficulty = InNewGameDifficulty; }
    
    //***** Gameplay Collection Tab *****//

private:
    UPROPERTY(Config)
    FString GameDifficulty;
};
