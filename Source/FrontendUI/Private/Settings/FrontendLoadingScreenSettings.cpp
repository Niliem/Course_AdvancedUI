// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/FrontendLoadingScreenSettings.h"
#include "Blueprint/UserWidget.h"

TSubclassOf<UUserWidget> UFrontendLoadingScreenSettings::GetLoadingScreenWidgetClassChecked() const
{
    checkf(!SoftLoadingWidgetClass.IsNull(), TEXT("Forgot to assign a valid widget blueprint in the project settings as loading screen"));
    TSubclassOf<UUserWidget> LoadedLoadingScreenWidget = SoftLoadingWidgetClass.LoadSynchronous();
    return LoadedLoadingScreenWidget;
}