// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "FrontendEnumTypes.h"
#include "Widget_ListEntry_Base.generated.h"

class UCommonTextBlock;
class UListDataObject_Base;

/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UWidget_ListEntry_Base : public UCommonUserWidget, public IUserObjectListEntry
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On List Entry Widget Hovered"))    
    void BP_OnListEntryWidgetHovered(bool bWasHovered, bool bIsEntryWidgetStillSelected);
    void NativeOnListEntryWidgetHovered(bool bWasHovered);

protected:
    UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Get Widget To Focus For Gamepad"))
    UWidget* BP_GetWidgetToFocusForGamepad();
    
    //~ Begin IUserObjectListEntry Interface
    virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
    virtual void NativeOnEntryReleased() override;
    //~ End IUserObjectListEntry Interface

    //~ Begin UUserWidget Interface
    virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
    //~ End UUserWidget Interface

    virtual void OnOwningListDataObjectSet(UListDataObject_Base* ListDataObject);
    virtual void OnOwningListDataObjectModified(UListDataObject_Base* ModifiedData, EOptionsListDataModifyReason ModifyReason);
    virtual void OnOwningDependencyObjectModified(UListDataObject_Base* ModifiedDependencyData, EOptionsListDataModifyReason ModifyReason);

    virtual void OnToggleEditableState(bool bIsEditable);

    void SelectThisEntryWidget();

private:
    //***** Bound Widgets *****//
    UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, AllowPrivateAccess= "true"))
    UCommonTextBlock* CommonText_SettingDisplayName;
    //***** Bound Widgets *****//

    UPROPERTY(Transient)
    UListDataObject_Base* CachedOwningDataObject;
};