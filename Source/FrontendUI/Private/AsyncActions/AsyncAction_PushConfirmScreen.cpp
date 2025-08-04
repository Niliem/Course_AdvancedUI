// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncActions/AsyncAction_PushConfirmScreen.h"

#include "Subsystems/FrontendUISubsystem.h"

UAsyncAction_PushConfirmScreen* UAsyncAction_PushConfirmScreen::PushConfirmScreen(const UObject* WorldContextObject, EConfirmScreenType ScreenType, FText Title, FText Message)
{
    if (GEngine)
    {
        if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
        {
            UAsyncAction_PushConfirmScreen* Action = NewObject<UAsyncAction_PushConfirmScreen>();
            Action->World = World;
            Action->ScreenType = ScreenType;
            Action->Title = Title;
            Action->Message = Message;
            Action->RegisterWithGameInstance(World);

            return Action;
        }
    }
    return nullptr;
}

void UAsyncAction_PushConfirmScreen::Activate()
{
    if (UFrontendUISubsystem* FrontendUISubsystem = UFrontendUISubsystem::Get(World.Get()))
    {
        FrontendUISubsystem->PushConfirmScreenAsync(ScreenType, Title, Message,
            [this](EConfirmScreenButtonType ClickedButtonType)
            {
                OnButtonClicked.Broadcast(ClickedButtonType);
                SetReadyToDestroy();
            });
    }
    SetReadyToDestroy();
}