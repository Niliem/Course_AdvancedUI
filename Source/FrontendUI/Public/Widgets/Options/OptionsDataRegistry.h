// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "OptionsDataRegistry.generated.h"

class UListDataObject_Base;
class UListDataObject_Collection;
/**
 * 
 */
UCLASS()
class FRONTENDUI_API UOptionsDataRegistry : public UObject
{
	GENERATED_BODY()

public:
    void InitOptionsDataRegistry(ULocalPlayer* InOwningLocalPlayer);
    const TArray<UListDataObject_Collection*>& GetRegisteredOptionsTabCollections() const
    {
        return RegisteredOptionsTabCollections;
    }

    TArray<UListDataObject_Base*> GetListSourceItemsBySelectedTabId(const FName& InSelectedTabId) const;

private:
    void InitGameplayCollectionTab();
    void InitAudioCollectionTab();
    void InitVideoCollectionTab();
    void InitControlCollectionTab();

    UPROPERTY(Transient)
    TArray<UListDataObject_Collection*> RegisteredOptionsTabCollections;
};
