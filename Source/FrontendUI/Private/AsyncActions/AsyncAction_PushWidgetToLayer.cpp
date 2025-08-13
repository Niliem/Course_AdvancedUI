// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncActions/AsyncAction_PushWidgetToLayer.h"
#include "CommonActivatableWidget.h"
#include "FrontendFunctionLibrary.h"
#include "Subsystems/FrontendUISubsystem.h"

UAsyncAction_PushWidgetToLayer* UAsyncAction_PushWidgetToLayer::PushWidgetToLayerByClass(const UObject* WorldContextObject, APlayerController* PlayerController, TSoftClassPtr<UCommonActivatableWidget> WidgetClass, FGameplayTag LayerTag, bool bFocusOnNewlyPushedWidget)
{
    checkf(!WidgetClass.IsNull(), TEXT("PushSoftWidgetToStack was passed a null soft widget class"));

    if (GEngine)
    {
        if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
        {
            UAsyncAction_PushWidgetToLayer* Action = NewObject<UAsyncAction_PushWidgetToLayer>();
            Action->World = World;
            Action->WidgetClass = WidgetClass;
            Action->PlayerController = PlayerController;
            Action->LayerTag = LayerTag;
            Action->bFocusOnNewlyPushedWidget = bFocusOnNewlyPushedWidget;
            Action->RegisterWithGameInstance(World);

            return Action;
        }
    }

    return nullptr;
}

UAsyncAction_PushWidgetToLayer* UAsyncAction_PushWidgetToLayer::PushWidgetToLayerByTag(const UObject* WorldContextObject, APlayerController* PlayerController, FGameplayTag WidgetTag, FGameplayTag LayerTag, bool bFocusOnNewlyPushedWidget)
{
    return PushWidgetToLayerByClass(WorldContextObject, PlayerController, UFrontendFunctionLibrary::GetFrontendWidgetClassByTag(WidgetTag), LayerTag, bFocusOnNewlyPushedWidget);
}

void UAsyncAction_PushWidgetToLayer::Activate()
{
    if (UFrontendUISubsystem* FrontendUISubsystem = UFrontendUISubsystem::Get(World.Get()))
    {
        FrontendUISubsystem->PushSoftWidgetToLayerStackAsync(LayerTag, WidgetClass,
            [this](EAsyncPushWidgetState PushState, UCommonActivatableWidget* PushedWidget)
            {
                switch (PushState)
                {
                    case EAsyncPushWidgetState::BeforePush:
                        PushedWidget->SetOwningPlayer(PlayerController.Get());
                        BeforePush.Broadcast(PushedWidget);
                        break;
                    case EAsyncPushWidgetState::AfterPush:
                        AfterPush.Broadcast(PushedWidget);
                        if (bFocusOnNewlyPushedWidget)
                        {
                            if (UWidget* WidgetToFocus = PushedWidget->GetDesiredFocusTarget())
                            {
                                WidgetToFocus->SetFocus();
                            }
                        }
                        SetReadyToDestroy();
                        break;
                }
            }
            );
    }
    SetReadyToDestroy();
}