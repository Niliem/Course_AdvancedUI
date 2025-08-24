// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Components/FrontendTabListWidgetBase.h"
#include "Editor/WidgetCompilerLog.h"
#include "Widgets/Components/FrontendCommonButtonBase.h"


void UFrontendTabListWidgetBase::RequestRegisterTab(const FName& InTabId, const FText& InTabDisplayName)
{
    RegisterTab(InTabId, TabButtonEntryWidgetClass, nullptr);

    if (UFrontendCommonButtonBase* FoundButton = Cast<UFrontendCommonButtonBase>(GetTabButtonBaseByID(InTabId)))
    {
        FoundButton->SetButtonText(InTabDisplayName);
    }
}

#if WITH_EDITOR
void UFrontendTabListWidgetBase::ValidateCompiledDefaults(class IWidgetCompilerLog& CompileLog) const
{
    Super::ValidateCompiledDefaults(CompileLog);

    if (!TabButtonEntryWidgetClass)
    {
        CompileLog.Error(FText::FromString(TEXT("The variable TabButtonEntryWidgetClass has no valid entry specified. ")
            + GetClass()->GetName()
            + " needs a valid entry widget class to functional properly"));
    }
}
#endif
