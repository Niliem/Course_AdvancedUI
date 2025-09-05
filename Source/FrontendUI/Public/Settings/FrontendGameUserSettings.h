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

    UFUNCTION()
    float GetMusicVolume() const { return MusicVolume; }

    UFUNCTION()
    void SetMusicVolume(float InNewMusicVolume);

    UFUNCTION()
    float GetSFXVolume() const { return SFXVolume; }

    UFUNCTION()
    void SetSFXVolume(float InNewSFXVolume);

    UFUNCTION()
    bool GetAllowBackgroundAudio() const { return bAllowBackgroundAudio; }

    UFUNCTION()
    void SetAllowBackgroundAudio(bool bIsAllowed);

    UFUNCTION()
    bool GetUseHDRAudio() const { return bUseHDRAudio; }

    UFUNCTION()
    void SetUseHDRAudio(bool bUse);
    //***** Audio Collection Tab *****//


    //***** Video Collection Tab *****//
    UFUNCTION()
    float GetDisplayGamma() const;

    UFUNCTION()
    void SetDisplayGamma(float InNewDisplayGamma);
    //***** Video Collection Tab *****//

private:
    //***** Gameplay Collection Tab *****//
    UPROPERTY(Config)
    FString GameDifficulty;
    //***** Gameplay Collection Tab *****//


    //***** Audio Collection Tab *****//
    UPROPERTY(Config)
    float OverallVolume;

    UPROPERTY(Config)
    float MusicVolume;

    UPROPERTY(Config)
    float SFXVolume;

    UPROPERTY(Config)
    bool bAllowBackgroundAudio;
    
    UPROPERTY(Config)
    bool bUseHDRAudio;
    //***** Audio Collection Tab *****//


    //***** Video Collection Tab *****//

    //***** Video Collection Tab *****//
};
