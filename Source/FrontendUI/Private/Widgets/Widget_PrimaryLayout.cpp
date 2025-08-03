// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Widget_PrimaryLayout.h"

UCommonActivatableWidgetContainerBase* UWidget_PrimaryLayout::FindWidgetLayerByTag(const FGameplayTag& InTag) const
{
    checkf(RegisteredWidgetLayerMap.Contains(InTag), TEXT("Can not find the widget layer by the tag %s"), *InTag.ToString());

    return RegisteredWidgetLayerMap.FindRef(InTag);
}

void UWidget_PrimaryLayout::RegisterLayer(FGameplayTag Tag, UCommonActivatableWidgetContainerBase* Widget)
{
    if (IsDesignTime())
        return;

    if (RegisteredWidgetLayerMap.Contains(Tag))
        return;

    RegisteredWidgetLayerMap.Add(Tag, Widget);
}