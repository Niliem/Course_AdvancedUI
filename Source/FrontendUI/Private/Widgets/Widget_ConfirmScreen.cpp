// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Widget_ConfirmScreen.h"
#include "CommonTextBlock.h"
#include "Components/DynamicEntryBox.h"
#include "Widgets/Components/FrontendCommonButtonBase.h"
#include "ICommonInputModule.h"

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

void UWidget_ConfirmScreen::InitConfirmScreen(UConfirmScreenInfoObject* ScreenInfoObject, TFunction<void(EConfirmScreenButtonType)> ClickedButtonCallback)
{
    check(ScreenInfoObject && CommonTextBlock_Title && CommonTextBlock_Message && DynamicEntryBox_Buttons);

    CommonTextBlock_Title->SetText(ScreenInfoObject->ScreenTitle);
    CommonTextBlock_Message->SetText(ScreenInfoObject->ScreenMessage);

    if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
    {
        DynamicEntryBox_Buttons->Reset<UFrontendCommonButtonBase>(
            [](UFrontendCommonButtonBase& ExistingButton)
            {
                ExistingButton.OnClicked().Clear();
            }
            );
    }

    check(!ScreenInfoObject->ScreenButtons.IsEmpty());

    for (const FConfirmScreenButtonInfo& ButtonInfo : ScreenInfoObject->ScreenButtons)
    {
        FDataTableRowHandle ActionRow;
        switch (ButtonInfo.ButtonType)
        {
            case EConfirmScreenButtonType::Cancelled:
                ActionRow = ICommonInputModule::GetSettings().GetDefaultBackAction();
                break;
            case EConfirmScreenButtonType::Closed:
                ActionRow = ICommonInputModule::GetSettings().GetDefaultClickAction();
                break;
            case EConfirmScreenButtonType::Unknown:
                break;
        }

        UFrontendCommonButtonBase* AddedButton = DynamicEntryBox_Buttons->CreateEntry<UFrontendCommonButtonBase>();
        AddedButton->SetButtonText(ButtonInfo.ButtonTextToDisplay);
        AddedButton->SetTriggeringInputAction(ActionRow);
        AddedButton->OnClicked().AddLambda(
            [ClickedButtonCallback, ButtonInfo, this]()
            {
                ClickedButtonCallback(ButtonInfo.ButtonType);
                DeactivateWidget();
            });
    }

    if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
    {
        DynamicEntryBox_Buttons->GetAllEntries().Last()->SetFocus();
    }
}