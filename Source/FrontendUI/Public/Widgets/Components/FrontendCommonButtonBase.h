// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "FrontendCommonButtonBase.generated.h"

class UCommonLazyImage;
class UCommonTextBlock;

/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UFrontendCommonButtonBase : public UCommonButtonBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Frontend Button")
    void SetButtonText(FText Text);

    UFUNCTION(BlueprintCallable, Category = "Frontend Button")
    FText GetButtonText() const;

    UFUNCTION(BlueprintCallable, Category = "Frontend Button")
    void SetButtonDisplayImage(const FSlateBrush& Image);
    
private:
    //~ Begin UUserWidget Interface
    virtual void NativePreConstruct() override;
    //~ End UUserWidget Interface
    
    //~ Begin UCommonButtonBase Interface
    virtual void NativeOnCurrentTextStyleChanged() override;
    virtual void NativeOnHovered() override;
    virtual void NativeOnUnhovered() override;
    //~ End UCommonButtonBase Interface
    
    //***** Bound Widgets *****//
    UPROPERTY(meta = (BindWidgetOptional))
    UCommonTextBlock* CommonTextBlock_ButtonText;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, AllowPrivateAccess= "true"))
    UCommonLazyImage* CommonLazyImage_ButtonImage;
    //***** Bound Widgets *****//

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Frontend Button", meta = (AllowPrivateAccess = "true"))
    FText ButtonDisplayText;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Frontend Button", meta = (AllowPrivateAccess = "true"))
    bool bUseUpperCaseForButtonText = false;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Frontend Button", meta = (AllowPrivateAccess = "true"))
    FText ButtonDescriptionText;
};