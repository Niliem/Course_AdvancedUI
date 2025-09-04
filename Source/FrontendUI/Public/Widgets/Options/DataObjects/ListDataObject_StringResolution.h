// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Options/DataObjects/ListDataObject_String.h"
#include "ListDataObject_StringResolution.generated.h"

/**
 * 
 */
UCLASS()
class FRONTENDUI_API UListDataObject_StringResolution : public UListDataObject_String
{
    GENERATED_BODY()
	
public:
    void InitResolutionValues();

    FORCEINLINE FString GetMaximumAllowedResolution() const { return MaximumAllowedResolution; }

protected:
    //~ Begin UListDataObject_Base Interface
    virtual void OnDataObjectInitialized() override;
    //~ End UListDataObject_Base Interface

private:
    FString ResolutionToValueString(const FIntPoint& InResolution) const;
    FText ResolutionToDisplayText(const FIntPoint& InResolution) const;

    FString MaximumAllowedResolution;
};
