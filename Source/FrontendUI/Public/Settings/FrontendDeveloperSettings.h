// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameplayTagContainer.h"
#include "Widgets/Widget_PrimaryLayout.h"
#include "FrontendDeveloperSettings.generated.h"

class UCommonActivatableWidget;

/**
 * 
 */
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Frontend UI Settings"))
class FRONTENDUI_API UFrontendDeveloperSettings : public UDeveloperSettings
{
    GENERATED_BODY()

public:
    UPROPERTY(Config, EditAnywhere, Category = "Widget Reference", meta = (ForceInlineRow, Categories = "Frontend.Widget"))
    TMap<FGameplayTag, TSoftClassPtr<UCommonActivatableWidget>> FrontendWidgetMap;

    UPROPERTY(Config, EditAnywhere, Category = "Widget Reference", meta = (ForceInlineRow, Categories = "Frontend.Widget"))
    TSubclassOf<UWidget_PrimaryLayout> PrimaryLayoutClass;
};