// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Options/DataObjects/ListDataObject_Base.h"
#include "CommonInputTypeEnum.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "ListDataObject_KeyRemap.generated.h"

class UEnhancedInputUserSettings;
class UEnhancedPlayerMappableKeyProfile;

/**
 * 
 */
UCLASS()
class FRONTENDUI_API UListDataObject_KeyRemap : public UListDataObject_Base
{
	GENERATED_BODY()

public:
    void InitKeyRemapData(UEnhancedInputUserSettings* InOwningUserSettings, UEnhancedPlayerMappableKeyProfile* InKeyProfile, ECommonInputType InDesiredInputKeyType, const FPlayerKeyMapping& InOwningPlayerKeyMapping);

    FSlateBrush GetIconFromCurrentKey() const;

    void BindNewInputKey(const FKey& InNewKey);

    FORCEINLINE ECommonInputType GetDesiredInputKeyType() const { return CachedDesiredInputKeyType; }
    
private:
    FPlayerKeyMapping* GetOwningKeyMapping() const;
    
    UPROPERTY(Transient)
    UEnhancedInputUserSettings* CachedOwningUserSettings;

    UPROPERTY(Transient)
    UEnhancedPlayerMappableKeyProfile* CachedOwningKeyProfile;

    ECommonInputType CachedDesiredInputKeyType;
    FName CachedOwningMappingName;
    EPlayerMappableKeySlot CachedOwningMappableKeySlot;
};
