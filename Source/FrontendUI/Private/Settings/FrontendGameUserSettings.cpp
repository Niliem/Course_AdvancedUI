// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/FrontendGameUserSettings.h"

UFrontendGameUserSettings* UFrontendGameUserSettings::Get()
{
    if(!GEngine)
        return nullptr;

    return CastChecked<UFrontendGameUserSettings>(GEngine->GetGameUserSettings());
}