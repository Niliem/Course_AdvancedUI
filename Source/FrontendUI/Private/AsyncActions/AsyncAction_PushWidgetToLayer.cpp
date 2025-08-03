// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncActions/AsyncAction_PushWidgetToLayer.h"
#include "GameplayTagContainer.h"

UAsyncAction_PushWidgetToLayer* UAsyncAction_PushWidgetToLayer::PushWidgetToLayer(const UObject* WorldContextObject, APlayerController* PlayerController, TSoftClassPtr<UWidget_ActivatableBase> WidgetClass, FGameplayTag LayerTag, bool bFocusOnNewlyPushedWidget)
{
    checkf(!WidgetClass.IsNull(), TEXT("PushSoftWidgetToStack was passed a null soft widget class"));

    if (GEngine)
    {
        if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
        {
            UAsyncAction_PushWidgetToLayer* Action = NewObject<UAsyncAction_PushWidgetToLayer>();
            Action->RegisterWithGameInstance(World);
            
            return Action;
        }
    }

    return nullptr;
}