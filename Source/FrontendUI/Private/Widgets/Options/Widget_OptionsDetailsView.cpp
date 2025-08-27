// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Options/Widget_OptionsDetailsView.h"

#include "CommonTextBlock.h"
#include "CommonLazyImage.h"
#include "CommonRichTextBlock.h"
#include "Widgets/Options/DataObjects/ListDataObject_Base.h"

void UWidget_OptionsDetailsView::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    ClearDetailsViewInfo();
}

void UWidget_OptionsDetailsView::UpdateDetailsViewInfo(UListDataObject_Base* InDataObject, const FString& InEntryWidgetClassName)
{
    ClearDetailsViewInfo();
    
    if (!InDataObject)
        return;
    
    CommonTextBlock_Title->SetText(InDataObject->GetDataDisplayName());

    if (!InDataObject->GetSoftDescriptionImage().IsNull())
    {
        CommonLazyImage_DescriptionImage->SetBrushFromLazyTexture(InDataObject->GetSoftDescriptionImage());
        CommonLazyImage_DescriptionImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
    }

    CommonRichTextBlock_Description->SetText(InDataObject->GetDescriptionRichText());

    const FString DynamicDetails = FString::Printf(
        TEXT("Data Object Class: <Bold>%s</>\n\nEntry Widget Class: <Bold>%s</>"),
        *InDataObject->GetClass()->GetName(), *InEntryWidgetClassName
        );
    CommonRichTextBlock_DynamicDetails->SetText(FText::FromString(DynamicDetails));
    
    CommonRichTextBlock_DisabledReason->SetText(InDataObject->GetDisabledRichText());
}

void UWidget_OptionsDetailsView::ClearDetailsViewInfo()
{
    CommonTextBlock_Title->SetText(FText::GetEmpty());
    CommonLazyImage_DescriptionImage->SetVisibility(ESlateVisibility::Collapsed);
    CommonRichTextBlock_Description->SetText(FText::GetEmpty());
    CommonRichTextBlock_DynamicDetails->SetText(FText::GetEmpty());    
    CommonRichTextBlock_DisabledReason->SetText(FText::GetEmpty());
}