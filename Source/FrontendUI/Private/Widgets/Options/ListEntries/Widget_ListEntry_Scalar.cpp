// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Options/ListEntries/Widget_ListEntry_Scalar.h"

void UWidget_ListEntry_Scalar::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}

void UWidget_ListEntry_Scalar::OnOwningListDataObjectSet(UListDataObject_Base* ListDataObject)
{
    Super::OnOwningListDataObjectSet(ListDataObject);
}

void UWidget_ListEntry_Scalar::OnOwningListDataObjectModified(UListDataObject_Base* ModifiedData, EOptionsListDataModifyReason ModifyReason)
{
    
}