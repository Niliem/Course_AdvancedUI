// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Options/DataObjects/ListDataObject_KeyRemap.h"

void UListDataObject_KeyRemap::InitKeyRemapData(UEnhancedInputUserSettings* InOwningUserSettings, UEnhancedPlayerMappableKeyProfile* InKeyProfile, ECommonInputType InDesiredInputKeyType, const FPlayerKeyMapping& InOwningPlayerKeyMapping)
{
    CachedOwningUserSettings = InOwningUserSettings;
    CachedOwningKeyProfile = InKeyProfile;
    CachedDesiredInputKeyType = InDesiredInputKeyType;
    CachedOwningMappingName = InOwningPlayerKeyMapping.GetMappingName();
    CachedOwningMappableKeySlot = InOwningPlayerKeyMapping.GetSlot();
}