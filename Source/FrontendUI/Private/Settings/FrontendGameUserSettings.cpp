// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/FrontendGameUserSettings.h"

#include "Kismet/GameplayStatics.h"
#include "Settings/FrontendDeveloperSettings.h"
#include "Sound/SoundClass.h"
#include "Sound/SoundMix.h"

UFrontendGameUserSettings::UFrontendGameUserSettings()
    : OverallVolume(1.0f)
    , MusicVolume(1.0f)
    , SFXVolume(1.0f)
    , bAllowBackgroundAudio()
{
}

UFrontendGameUserSettings* UFrontendGameUserSettings::Get()
{
    if(!GEngine)
        return nullptr;

    return CastChecked<UFrontendGameUserSettings>(GEngine->GetGameUserSettings());
}

void UFrontendGameUserSettings::SetOverallVolume(float InNewOverallVolume)
{
    UWorld* InAudioWorld = nullptr;
    const UFrontendDeveloperSettings* FrontendDeveloperSettings = GetDefault<UFrontendDeveloperSettings>();
 
    if (GEngine)
    {
        InAudioWorld = GEngine->GetCurrentPlayWorld();
    }
 
    if (!InAudioWorld || !FrontendDeveloperSettings)
    {
        return;
    }
 
    USoundClass* MasterSoundClass = nullptr;
    if (UObject* LoadedObject = FrontendDeveloperSettings->MasterSoundClass.TryLoad())
    {
        MasterSoundClass = CastChecked<USoundClass>(LoadedObject);
    }
 
    USoundMix* DefaultSoundMix = nullptr;
    if (UObject* LoadedObject = FrontendDeveloperSettings->DefaultSoundMix.TryLoad())
    {
        DefaultSoundMix = CastChecked<USoundMix>(LoadedObject);
    }
 
    OverallVolume = InNewOverallVolume;
 
    UGameplayStatics::SetSoundMixClassOverride(
        InAudioWorld,
        DefaultSoundMix,
        MasterSoundClass,
        OverallVolume,
        1.f,
        0.2f
    );
 
    UGameplayStatics::PushSoundMixModifier(InAudioWorld, DefaultSoundMix);
}

void UFrontendGameUserSettings::SetMusicVolume(float InNewMusicVolume)
{
    UWorld* InAudioWorld = nullptr;
    const UFrontendDeveloperSettings* FrontendDeveloperSettings = GetDefault<UFrontendDeveloperSettings>();
 
    if (GEngine)
    {
        InAudioWorld = GEngine->GetCurrentPlayWorld();
    }
 
    if (!InAudioWorld || !FrontendDeveloperSettings)
    {
        return;
    }
 
    USoundClass* MusicSoundClass = nullptr;
    if (UObject* LoadedObject = FrontendDeveloperSettings->MusicSoundClass.TryLoad())
    {
        MusicSoundClass = CastChecked<USoundClass>(LoadedObject);
    }
 
    USoundMix* DefaultSoundMix = nullptr;
    if (UObject* LoadedObject = FrontendDeveloperSettings->DefaultSoundMix.TryLoad())
    {
        DefaultSoundMix = CastChecked<USoundMix>(LoadedObject);
    }
 
    MusicVolume = InNewMusicVolume;
 
    UGameplayStatics::SetSoundMixClassOverride(
        InAudioWorld,
        DefaultSoundMix,
        MusicSoundClass,
        MusicVolume,
        1.f,
        0.2f
    );
 
    UGameplayStatics::PushSoundMixModifier(InAudioWorld, DefaultSoundMix);
}

void UFrontendGameUserSettings::SetSFXVolume(float InNewSFXVolume)
{
    UWorld* InAudioWorld = nullptr;
    const UFrontendDeveloperSettings* FrontendDeveloperSettings = GetDefault<UFrontendDeveloperSettings>();
 
    if (GEngine)
    {
        InAudioWorld = GEngine->GetCurrentPlayWorld();
    }
 
    if (!InAudioWorld || !FrontendDeveloperSettings)
    {
        return;
    }
 
    USoundClass* SoundFXSoundClass = nullptr;
    if (UObject* LoadedObject = FrontendDeveloperSettings->SoundFXSoundClass.TryLoad())
    {
        SoundFXSoundClass = CastChecked<USoundClass>(LoadedObject);
    }
 
    USoundMix* DefaultSoundMix = nullptr;
    if (UObject* LoadedObject = FrontendDeveloperSettings->DefaultSoundMix.TryLoad())
    {
        DefaultSoundMix = CastChecked<USoundMix>(LoadedObject);
    }
 
    SFXVolume = InNewSFXVolume;
 
    UGameplayStatics::SetSoundMixClassOverride(
        InAudioWorld,
        DefaultSoundMix,
        SoundFXSoundClass,
        SFXVolume,
        1.f,
        0.2f
    );
 
    UGameplayStatics::PushSoundMixModifier(InAudioWorld, DefaultSoundMix);
}

void UFrontendGameUserSettings::SetAllowBackgroundAudio(bool bIsAllowed)
{
    bAllowBackgroundAudio = bIsAllowed;
}