// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FrontendPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class FRONTENDUI_API AFrontendPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    //~ Begin APlayerController Interface
    virtual void OnPossess(APawn* InPawn) override;
    //~ End APlayerController Interface
};
