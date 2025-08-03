// Fill out your copyright notice in the Description page of Project Settings.


#include "FrontendFunctionLibrary.h"
#include "Settings/FrontendDeveloperSettings.h"

TSoftClassPtr<UCommonActivatableWidget> UFrontendFunctionLibrary::GetFrontendWidgetClassByTag(FGameplayTag WidgetTag)
{
    const UFrontendDeveloperSettings* FrontendDeveloperSettings = GetDefault<UFrontendDeveloperSettings>();

    checkf(FrontendDeveloperSettings->FrontendWidgetMap.Contains(WidgetTag), TEXT("Could not find the corresponding widget under the tag %s"), *WidgetTag.ToString());

    return FrontendDeveloperSettings->FrontendWidgetMap.FindRef(WidgetTag);
}