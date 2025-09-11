// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Options/DataObjects/ListDataObject_KeyRemap.h"

#include "CommonInputBaseTypes.h"
#include "CommonInputSubsystem.h"

void UListDataObject_KeyRemap::InitKeyRemapData(UEnhancedInputUserSettings* InOwningUserSettings, UEnhancedPlayerMappableKeyProfile* InKeyProfile, ECommonInputType InDesiredInputKeyType, const FPlayerKeyMapping& InOwningPlayerKeyMapping)
{
    CachedOwningUserSettings = InOwningUserSettings;
    CachedOwningKeyProfile = InKeyProfile;
    CachedDesiredInputKeyType = InDesiredInputKeyType;
    CachedOwningMappingName = InOwningPlayerKeyMapping.GetMappingName();
    CachedOwningMappableKeySlot = InOwningPlayerKeyMapping.GetSlot();
}

FSlateBrush UListDataObject_KeyRemap::GetIconFromCurrentKey() const
{
    check(CachedOwningUserSettings);
    
    UCommonInputSubsystem* CommonInputSubsystem = UCommonInputSubsystem::Get(CachedOwningUserSettings->GetLocalPlayer());
    check(CommonInputSubsystem);
    
    FSlateBrush FoundBrush;
    UCommonInputPlatformSettings::Get()->TryGetInputBrush(FoundBrush, GetOwningKeyMapping()->GetCurrentKey(), CachedDesiredInputKeyType, CommonInputSubsystem->GetCurrentGamepadName());
    
    return FoundBrush;
}

FPlayerKeyMapping* UListDataObject_KeyRemap::GetOwningKeyMapping() const
{
    check(CachedOwningKeyProfile);

    FMapPlayerKeyArgs KeyArgs;
    KeyArgs.MappingName = CachedOwningMappingName;
    KeyArgs.Slot = CachedOwningMappableKeySlot;
    
    return CachedOwningKeyProfile->FindKeyMapping(KeyArgs);
}