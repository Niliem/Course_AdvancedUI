// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Options/DataObjects/ListDataObject_Base.h"

#include "Settings/FrontendGameUserSettings.h"

void UListDataObject_Base::InitDataObject()
{
    OnDataObjectInitialized();
}

void UListDataObject_Base::AddEditCondition(const FOptionsDataEditConditionDescriptor& InEditCondition)
{
    EditConditionDescArray.Add(InEditCondition);
}

bool UListDataObject_Base::IsDataCurrentlyEditable()
{
    if (EditConditionDescArray.IsEmpty())
        return true;

    bool bIsEditable = true;
    FString CachedDisabledRichReason;

    for (const FOptionsDataEditConditionDescriptor& EditCondition : EditConditionDescArray)
    {
        if (!EditCondition.IsValid() || EditCondition.IsEditConditionMet())
            continue;

        bIsEditable = false;
        CachedDisabledRichReason.Append(EditCondition.GetDisabledRichReason());

        if (EditCondition.HasForcedStringValue())
        {
            const FString ForcedStringValue = EditCondition.GetDisabledForcedStringValue();

            if (CanSetToForcedStringValue(ForcedStringValue))
            {
                OnSetToForcedStringValue(ForcedStringValue);
            }            
        }
    }

    SetDisabledRichText(FText::FromString(CachedDisabledRichReason));
    
    return bIsEditable;
}

void UListDataObject_Base::OnDataObjectInitialized()
{
}

void UListDataObject_Base::NotifyListDataModified(UListDataObject_Base* ModifiedData, EOptionsListDataModifyReason ModifyReason)
{
    OnListDataModified.Broadcast(ModifiedData, ModifyReason);
    
    if (bShouldApplyChangesImmediately)
    {
        UFrontendGameUserSettings::Get()->ApplySettings(true);
    }
}