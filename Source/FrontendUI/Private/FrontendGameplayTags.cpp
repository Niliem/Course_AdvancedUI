// Fill out your copyright notice in the Description page of Project Settings.


#include "FrontendGameplayTags.h"

namespace UIGameplayTags
{
    UE_DEFINE_GAMEPLAY_TAG(UI_Layer_Modal, "UI.Layer.Modal");
    UE_DEFINE_GAMEPLAY_TAG(UI_Layer_GameMenu, "UI.Layer.GameMenu");
    UE_DEFINE_GAMEPLAY_TAG(UI_Layer_GameHUD, "UI.Layer.GameHUD");
    UE_DEFINE_GAMEPLAY_TAG(UI_Layer_Frontend, "UI.Layer.Frontend");
}

namespace FrontendGameplayTags
{
    UE_DEFINE_GAMEPLAY_TAG(Frontend_Widget_PressAnyKey, "Frontend.Widget.PressAnyKey");
    UE_DEFINE_GAMEPLAY_TAG(Frontend_Widget_MainMenu, "Frontend.Widget.MainMenu");
    UE_DEFINE_GAMEPLAY_TAG(Frontend_Widget_Options, "Frontend.Widget.Options");
    UE_DEFINE_GAMEPLAY_TAG(Frontend_Widget_Confirm, "Frontend.Widget.Confirm");
}; //FrontendGameplayTags