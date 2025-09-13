// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Options/DataObjects/ListDataObject_Collection.h"

void UListDataObject_Collection::AddChildListData(UListDataObject_Base* ChildListData)
{
    ChildListData->InitDataObject();
    ChildListData->SetParentData(this);
    ChildListDataArray.Add(ChildListData);
}

void UListDataObject_Collection::Sort()
{
    ChildListDataArray.Sort([](const UListDataObject_Base& A, const UListDataObject_Base& B)
    {
        return A < B;
    });
}

TArray<UListDataObject_Base*> UListDataObject_Collection::GetAllChildListData() const
{
    return ChildListDataArray;
}

bool UListDataObject_Collection::HasAnyChildListData() const
{
    return !ChildListDataArray.IsEmpty();
}