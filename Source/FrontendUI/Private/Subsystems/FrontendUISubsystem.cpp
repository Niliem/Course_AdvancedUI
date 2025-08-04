// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/FrontendUISubsystem.h"
#include "CommonActivatableWidget.h"
#include "Engine/AssetManager.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "Widgets/Widget_PrimaryLayout.h"
#include "FrontendFunctionLibrary.h"
#include "FrontendGameplayTags.h"
#include "Widgets/Widget_ConfirmScreen.h"

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

void UFrontendUISubsystem::PushSoftWidgetToLayerStackAsync(const FGameplayTag& LayerTag, TSoftClassPtr<UCommonActivatableWidget> SoftWidgetClass, TFunction<void(EAsyncPushWidgetState, UCommonActivatableWidget*)> AsyncPushStateCallback)
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
                    UCommonActivatableWidget* CreatedWidget = FoundLayer->AddWidget<UCommonActivatableWidget>(LoadedWidgetClass,
                        [AsyncPushStateCallback](UCommonActivatableWidget& CreatedWidgetInstance)
                        {
                            AsyncPushStateCallback(EAsyncPushWidgetState::BeforePush, &CreatedWidgetInstance);
                        }
                        );

                    AsyncPushStateCallback(EAsyncPushWidgetState::AfterPush, CreatedWidget);
                }
            })
        );
}

void UFrontendUISubsystem::PushConfirmScreenAsync(EConfirmScreenType ConfirmScreenType, const FText& Title, const FText& Message, TFunction<void(EConfirmScreenButtonType)> ButtonClickedCallback)
{
    UConfirmScreenInfoObject* ConfirmScreenInfoObject = nullptr;
    switch (ConfirmScreenType)
    {
        case EConfirmScreenType::Ok:
            ConfirmScreenInfoObject = UConfirmScreenInfoObject::CreateOkScreen(Title, Message);
            break;
        case EConfirmScreenType::YesNo:
            ConfirmScreenInfoObject = UConfirmScreenInfoObject::CreateYesNoScreen(Title, Message);
            break;
        case EConfirmScreenType::OkCancel:
            ConfirmScreenInfoObject = UConfirmScreenInfoObject::CreateOkCancelScreen(Title, Message);
            break;
        case EConfirmScreenType::Unknown:
            break;
    }

    check(ConfirmScreenInfoObject);

    PushSoftWidgetToLayerStackAsync(UIGameplayTags::UI_Layer_Modal, UFrontendFunctionLibrary::GetFrontendWidgetClassByTag(FrontendGameplayTags::Frontend_Widget_Confirm),
        [ConfirmScreenInfoObject, ButtonClickedCallback](EAsyncPushWidgetState PushState, UCommonActivatableWidget* PushedWidget)
        {
            if (PushState == EAsyncPushWidgetState::BeforePush)
            {
                if (UWidget_ConfirmScreen* CreatedScreen = CastChecked<UWidget_ConfirmScreen>(PushedWidget))
                {
                    CreatedScreen->InitConfirmScreen(ConfirmScreenInfoObject, ButtonClickedCallback);
                }
            }
        }
        );
}