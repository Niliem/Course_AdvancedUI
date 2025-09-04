// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FrontendEnumTypes.h"
#include "FrontendStructTypes.h"
#include "ListDataObject_Base.generated.h"

#define LIST_DATA_ACCESSOR(DataType, PropertyName) \
    FORCEINLINE DataType Get##PropertyName() const { return PropertyName; } \
    void Set##PropertyName(DataType In##PropertyName) { PropertyName = In##PropertyName; }

/**
 * 
 */
UCLASS(Abstract)
class FRONTENDUI_API UListDataObject_Base : public UObject
{
	GENERATED_BODY()

public:
    DECLARE_MULTICAST_DELEGATE_TwoParams(FOnListDataModifiedDelegate, UListDataObject_Base*, EOptionsListDataModifyReason);
    FOnListDataModifiedDelegate OnListDataModified;
    
    LIST_DATA_ACCESSOR(FName, DataId);
    LIST_DATA_ACCESSOR(FText, DataDisplayName);
    LIST_DATA_ACCESSOR(FText, DescriptionRichText);
    LIST_DATA_ACCESSOR(FText, DisabledRichText);
    LIST_DATA_ACCESSOR(TSoftObjectPtr<UTexture2D>, SoftDescriptionImage);
    
    LIST_DATA_ACCESSOR(UListDataObject_Base*, ParentData);

    void InitDataObject();

    //Empty in the base class. Child class ListDataObject_Collection should override it. The function should return all the child data a tab has
    virtual TArray<UListDataObject_Base*> GetAllChildListData() const { return TArray<UListDataObject_Base*>();}
    virtual bool HasAnyChildListData() const { return false; }

    //The child class should override them to provide implementations for resetting the data
    virtual bool HasDefaultValue() const { return false; }
    virtual bool CanResetBackToDefaultValue() const { return false; }
    virtual bool TryResetBackToDefaultValue() { return false; }

    void SetShouldApplyChangesImmediately(bool bShouldApplyImmediately) { bShouldApplyChangesImmediately = bShouldApplyImmediately; }

protected:
    virtual void OnDataObjectInitialized();
    virtual void NotifyListDataModified(UListDataObject_Base* ModifiedData, EOptionsListDataModifyReason ModifyReason = EOptionsListDataModifyReason::DirectlyModified);

private:
    FName DataId;
    FText DataDisplayName;
    FText DescriptionRichText;
    FText DisabledRichText;
    TSoftObjectPtr<UTexture2D> SoftDescriptionImage;

    UPROPERTY(Transient)
    UListDataObject_Base* ParentData;

    bool bShouldApplyChangesImmediately = false;
};
