// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Options/DataObjects/ListDataObject_StringResolution.h"

#include "FrontendDebugHelper.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Widgets/Options/OptionsDataInteractionHelper.h"

void UListDataObject_StringResolution::InitResolutionValues()
{
    TArray<FIntPoint> AvailableResolutions;
    UKismetSystemLibrary::GetSupportedFullscreenResolutions(AvailableResolutions);

    for (const FIntPoint& Resolution : AvailableResolutions)
    {
        Debug::Print(TEXT("Available Resolution : ") + Resolution.ToString());
    }
}

void UListDataObject_StringResolution::OnDataObjectInitialized()
{
    Super::OnDataObjectInitialized();

    if (DataDynamicGetter)
    {
        Debug::Print(TEXT("Resolution from DataDynamicGetter : ") + DataDynamicGetter->GetValueAsString());        
    }
}