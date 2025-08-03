// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/FrontendUISubsystem.h"
#include "Engine/AssetManager.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "Widgets/Widget_ActivatableBase.h"
#include "Widgets/Widget_PrimaryLayout.h"

UFrontendUISubsystem* UFrontendUISubsystem::Get(const UObject* WorldContextObject)
{
    if (GEngine)
    {
        if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert))
        {
            if (UGameInstance* GameInstance = World->GetGameInstance())
            {
                return UGameInstance::GetSubsystem<UFrontendUISubsystem>(GameInstance);
            }
        }
    }
    return nullptr;
}

bool UFrontendUISubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
    {
        TArray<UClass*> FoundClasses;
        GetDerivedClasses(GetClass(), FoundClasses);

        return FoundClasses.IsEmpty();
    }
    return false;
}

void UFrontendUISubsystem::RegisteredCreatedPrimaryLayoutWidget(UWidget_PrimaryLayout* InCreatedPrimaryLayout)
{
    check(InCreatedPrimaryLayout);

    CreatedPrimaryLayout = InCreatedPrimaryLayout;
}

void UFrontendUISubsystem::PushSoftWidgetToLayerStackAsync(const FGameplayTag& LayerTag, TSoftClassPtr<UWidget_ActivatableBase> SoftWidgetClass, TFunction<void(EAsyncPushWidgetState, UWidget_ActivatableBase*)> AsyncPushStateCallback)
{
    check(!SoftWidgetClass.IsNull());

    UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(SoftWidgetClass.ToSoftObjectPath(), FStreamableDelegate::CreateLambda(
            [SoftWidgetClass, LayerTag, AsyncPushStateCallback, this]()
            {
                UClass* LoadedWidgetClass = SoftWidgetClass.Get();
                check(LoadedWidgetClass);

                check(CreatedPrimaryLayout);
                if (UCommonActivatableWidgetContainerBase* FoundLayer = CreatedPrimaryLayout->FindWidgetLayerByTag(LayerTag))
                {
                    UWidget_ActivatableBase* CreatedWidget = FoundLayer->AddWidget<UWidget_ActivatableBase>(LoadedWidgetClass,
                        [AsyncPushStateCallback](UWidget_ActivatableBase& CreatedWidgetInstance)
                        {
                            AsyncPushStateCallback(EAsyncPushWidgetState::BeforePush, &CreatedWidgetInstance);
                        }
                        );

                    AsyncPushStateCallback(EAsyncPushWidgetState::AfterPush, CreatedWidget);
                }
            })
        );
}