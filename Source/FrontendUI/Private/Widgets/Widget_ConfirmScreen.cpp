// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Widget_ConfirmScreen.h"

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateOkScreen(const FText& ScreenTitle, const FText& ScreenMessage)
{
    UConfirmScreenInfoObject* ConfirmScreenInfoObject = NewObject<UConfirmScreenInfoObject>();
    ConfirmScreenInfoObject->ScreenTitle = ScreenTitle;
    ConfirmScreenInfoObject->ScreenMessage = ScreenMessage;

    FConfirmScreenButtonInfo OkButtonInfo;
    OkButtonInfo.ButtonType = EConfirmScreenButtonType::Closed;
    OkButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("OK"));

    ConfirmScreenInfoObject->ScreenButtons.Add(OkButtonInfo);

    return ConfirmScreenInfoObject;
}

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateYesNoScreen(const FText& ScreenTitle, const FText& ScreenMessage)
{
    UConfirmScreenInfoObject* ConfirmScreenInfoObject = NewObject<UConfirmScreenInfoObject>();
    ConfirmScreenInfoObject->ScreenTitle = ScreenTitle;
    ConfirmScreenInfoObject->ScreenMessage = ScreenMessage;

    FConfirmScreenButtonInfo YesButtonInfo;
    YesButtonInfo.ButtonType = EConfirmScreenButtonType::Confirmed;
    YesButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("Yes"));

    FConfirmScreenButtonInfo NoButtonInfo;
    NoButtonInfo.ButtonType = EConfirmScreenButtonType::Cancelled;
    NoButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("No"));

    ConfirmScreenInfoObject->ScreenButtons.Add(YesButtonInfo);
    ConfirmScreenInfoObject->ScreenButtons.Add(NoButtonInfo);

    return ConfirmScreenInfoObject;
}

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateOkCancelScreen(const FText& ScreenTitle, const FText& ScreenMessage)
{
    UConfirmScreenInfoObject* ConfirmScreenInfoObject = NewObject<UConfirmScreenInfoObject>();
    ConfirmScreenInfoObject->ScreenTitle = ScreenTitle;
    ConfirmScreenInfoObject->ScreenMessage = ScreenMessage;

    FConfirmScreenButtonInfo OkButtonInfo;
    OkButtonInfo.ButtonType = EConfirmScreenButtonType::Confirmed;
    OkButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("OK"));

    FConfirmScreenButtonInfo CancelButtonInfo;
    CancelButtonInfo.ButtonType = EConfirmScreenButtonType::Closed;
    CancelButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("Cancel"));

    ConfirmScreenInfoObject->ScreenButtons.Add(OkButtonInfo);
    ConfirmScreenInfoObject->ScreenButtons.Add(CancelButtonInfo);

    return ConfirmScreenInfoObject;
}