// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Widget_ConfirmScreen.h"
#include "CommonTextBlock.h"
#include "Components/DynamicEntryBox.h"
#include "Widgets/Components/FrontendCommonButtonBase.h"
#include "ICommonInputModule.h"

UWidget_ConfirmScreen::FConfirmScreenInfo UWidget_ConfirmScreen::CreateOkScreen(const FText& ScreenTitle, const FText& ScreenMessage)
{
    FConfirmScreenInfo ConfirmScreenInfo;
    ConfirmScreenInfo.Title = ScreenTitle;
    ConfirmScreenInfo.Message = ScreenMessage;

    FConfirmScreenButtonInfo OkButtonInfo;
    OkButtonInfo.Type = EConfirmScreenButtonType::Closed;
    OkButtonInfo.TextToDisplay = FText::FromString(TEXT("OK"));

    ConfirmScreenInfo.AvailableButtons.Add(OkButtonInfo);

    return ConfirmScreenInfo;
}

UWidget_ConfirmScreen::FConfirmScreenInfo UWidget_ConfirmScreen::CreateYesNoScreen(const FText& ScreenTitle, const FText& ScreenMessage)
{
    FConfirmScreenInfo ConfirmScreenInfo;
    ConfirmScreenInfo.Title = ScreenTitle;
    ConfirmScreenInfo.Message = ScreenMessage;

    FConfirmScreenButtonInfo YesButtonInfo;
    YesButtonInfo.Type = EConfirmScreenButtonType::Confirmed;
    YesButtonInfo.TextToDisplay = FText::FromString(TEXT("Yes"));

    FConfirmScreenButtonInfo NoButtonInfo;
    NoButtonInfo.Type = EConfirmScreenButtonType::Cancelled;
    NoButtonInfo.TextToDisplay = FText::FromString(TEXT("No"));

    ConfirmScreenInfo.AvailableButtons.Add(YesButtonInfo);
    ConfirmScreenInfo.AvailableButtons.Add(NoButtonInfo);

    return ConfirmScreenInfo;
}

UWidget_ConfirmScreen::FConfirmScreenInfo UWidget_ConfirmScreen::CreateOkCancelScreen(const FText& ScreenTitle, const FText& ScreenMessage)
{
    FConfirmScreenInfo ConfirmScreenInfo;
    ConfirmScreenInfo.Title = ScreenTitle;
    ConfirmScreenInfo.Message = ScreenMessage;

    FConfirmScreenButtonInfo OkButtonInfo;
    OkButtonInfo.Type = EConfirmScreenButtonType::Confirmed;
    OkButtonInfo.TextToDisplay = FText::FromString(TEXT("OK"));

    FConfirmScreenButtonInfo CancelButtonInfo;
    CancelButtonInfo.Type = EConfirmScreenButtonType::Closed;
    CancelButtonInfo.TextToDisplay = FText::FromString(TEXT("Cancel"));

    ConfirmScreenInfo.AvailableButtons.Add(OkButtonInfo);
    ConfirmScreenInfo.AvailableButtons.Add(CancelButtonInfo);

    return ConfirmScreenInfo;
}

UWidget_ConfirmScreen::FConfirmScreenInfo UWidget_ConfirmScreen::CreateYesNoCancelScreen(const FText& ScreenTitle, const FText& ScreenMessage)
{
    FConfirmScreenInfo ConfirmScreenInfo;
    ConfirmScreenInfo.Title = ScreenTitle;
    ConfirmScreenInfo.Message = ScreenMessage;

    FConfirmScreenButtonInfo YesButtonInfo;
    YesButtonInfo.Type = EConfirmScreenButtonType::Confirmed;
    YesButtonInfo.TextToDisplay = FText::FromString(TEXT("Yes"));

    FConfirmScreenButtonInfo NoButtonInfo;
    NoButtonInfo.Type = EConfirmScreenButtonType::Cancelled;
    NoButtonInfo.TextToDisplay = FText::FromString(TEXT("No"));

    FConfirmScreenButtonInfo CancelButtonInfo;
    CancelButtonInfo.Type = EConfirmScreenButtonType::Closed;
    CancelButtonInfo.TextToDisplay = FText::FromString(TEXT("Cancel"));

    ConfirmScreenInfo.AvailableButtons.Add(YesButtonInfo);
    ConfirmScreenInfo.AvailableButtons.Add(NoButtonInfo);
    ConfirmScreenInfo.AvailableButtons.Add(CancelButtonInfo);

    return ConfirmScreenInfo;
}

void UWidget_ConfirmScreen::InitConfirmScreen(const FConfirmScreenInfo& ConfirmScreenInfo, TFunction<void(EConfirmScreenButtonType)> ClickedButtonCallback)
{
    check(CommonTextBlock_Title && CommonTextBlock_Message && DynamicEntryBox_Buttons);

    CommonTextBlock_Title->SetText(ConfirmScreenInfo.Title);
    CommonTextBlock_Message->SetText(ConfirmScreenInfo.Message);

    if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
    {
        DynamicEntryBox_Buttons->Reset<UFrontendCommonButtonBase>(
            [](const UFrontendCommonButtonBase& ExistingButton)
            {
                ExistingButton.OnClicked().Clear();
            }
            );
    }

    for (const FConfirmScreenButtonInfo& ButtonInfo : ConfirmScreenInfo.AvailableButtons)
    {
        UFrontendCommonButtonBase* AddedButton = DynamicEntryBox_Buttons->CreateEntry<UFrontendCommonButtonBase>();
        AddedButton->SetButtonText(ButtonInfo.TextToDisplay);
        AddedButton->OnClicked().AddLambda(
            [ClickedButtonCallback, ButtonInfo, this]()
            {
                ClickedButtonCallback(ButtonInfo.Type);
                DeactivateWidget();
            });
    }

    if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
    {
        DynamicEntryBox_Buttons->GetAllEntries().Last()->SetFocus();
    }
}