// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace UIGameplayTags
{
    FRONTENDUI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Layer_Modal);
    FRONTENDUI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Layer_GameMenu);
    FRONTENDUI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Layer_GameHUD);
    FRONTENDUI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Layer_Frontend);
}; //UIGameplayTags

namespace FrontendGameplayTags
{
    FRONTENDUI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_Widget_PressAnyKey);
    FRONTENDUI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_Widget_MainMenu);
    FRONTENDUI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_Widget_Confirm);
}; //FrontendGameplayTags