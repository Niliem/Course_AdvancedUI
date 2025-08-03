// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Widget_PrimaryLayout.h"
#include "FrontendDebugHelper.h"

UCommonActivatableWidgetContainerBase* UWidget_PrimaryLayout::FindWidgetLayerByTag(const FGameplayTag& InTag) const
{
    checkf(RegisteredWidgetLayerMap.Contains(InTag), TEXT("Can not find the widget layer by the tag %s"), *InTag.ToString());

    return RegisteredWidgetLayerMap.FindRef(InTag);
}

void UWidget_PrimaryLayout::RegisterWidgetLayer(FGameplayTag InLayerTag, UCommonActivatableWidgetContainerBase* InLayerWidget)
{
    if (IsDesignTime())
        return;

    if (RegisteredWidgetLayerMap.Contains(InLayerTag))
        return;

    RegisteredWidgetLayerMap.Add(InLayerTag, InLayerWidget);
    Debug::Print(TEXT("Widget layer registered under the tag ") + InLayerTag.ToString());
}