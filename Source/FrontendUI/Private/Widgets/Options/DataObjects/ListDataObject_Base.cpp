// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Options/DataObjects/ListDataObject_Base.h"

#include "Settings/FrontendGameUserSettings.h"

void UListDataObject_Base::InitDataObject()
{
    OnDataObjectInitialized();
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