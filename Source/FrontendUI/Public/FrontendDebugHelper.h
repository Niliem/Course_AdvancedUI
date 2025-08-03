// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FrontendLogChannels.h"

namespace Debug
{
    static void Print(const FString& Message, int32 InKey = -1, const FColor& InColor = FColor::MakeRandomColor())
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(InKey, 7.0f, InColor, Message);

            UE_LOG(LogFrontend, Warning, TEXT("%s"), *Message);
        }
    }
}