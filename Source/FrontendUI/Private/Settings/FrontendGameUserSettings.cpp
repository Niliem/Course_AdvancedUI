// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/FrontendGameUserSettings.h"

#include "Kismet/GameplayStatics.h"
#include "Settings/FrontendDeveloperSettings.h"
#include "Sound/SoundClass.h"
#include "Sound/SoundMix.h"

UFrontendGameUserSettings::UFrontendGameUserSettings()
    : OverallVolume(1.0f)
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