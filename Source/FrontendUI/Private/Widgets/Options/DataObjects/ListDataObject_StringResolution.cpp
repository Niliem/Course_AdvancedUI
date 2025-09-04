// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Options/DataObjects/ListDataObject_StringResolution.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Settings/FrontendGameUserSettings.h"

void UListDataObject_StringResolution::InitResolutionValues()
{
    TArray<FIntPoint> AvailableResolutions;
    UKismetSystemLibrary::GetSupportedFullscreenResolutions(AvailableResolutions);

    AvailableResolutions.Sort([](const FIntPoint& A, const FIntPoint& B) -> bool
    {
        return A.SizeSquared() < B.SizeSquared();
    });

    for (const FIntPoint& Resolution : AvailableResolutions)
    {
        AddDynamicOption(ResolutionToValueString(Resolution), ResolutionToDisplayText(Resolution));
    }

    MaximumAllowedResolution = ResolutionToValueString(AvailableResolutions.Last());
    SetDefaultValueFromString(MaximumAllowedResolution);
}

void UListDataObject_StringResolution::OnDataObjectInitialized()
{
    Super::OnDataObjectInitialized();

    if (!TrySetDisplayTextFromStringValue(CurrentStringValue))
    {
        CurrentDisplayText = ResolutionToDisplayText(UFrontendGameUserSettings::Get()->GetScreenResolution());
    }
}

FString UListDataObject_StringResolution::ResolutionToValueString(const FIntPoint& InResolution) const
{
    return FString::Printf(TEXT("(X=%i,Y=%i)"), InResolution.X, InResolution.Y);
}

FText UListDataObject_StringResolution::ResolutionToDisplayText(const FIntPoint& InResolution) const
{
    return FText::FromString(FString::Printf(TEXT("%i x %i"), InResolution.X, InResolution.Y));
}