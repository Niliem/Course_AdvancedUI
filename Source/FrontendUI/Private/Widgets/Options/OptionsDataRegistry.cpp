// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Options/OptionsDataRegistry.h"

#include "FrontendFunctionLibrary.h"
#include "FrontendGameplayTags.h"
#include "Settings/FrontendGameUserSettings.h"
#include "Widgets/Options/OptionsDataInteractionHelper.h"
#include "Widgets/Options/DataObjects/ListDataObject_Collection.h"
#include "Widgets/Options/DataObjects/ListDataObject_Scalar.h"
#include "Widgets/Options/DataObjects/ListDataObject_String.h"
#include "Widgets/Options/DataObjects/ListDataObject_StringResolution.h"

#define MAKE_OPTIONS_DATA_CONTROL(SetterOrGetterFuncName) \
    MakeShared<FOptionsDataInteractionHelper>(GET_FUNCTION_NAME_STRING_CHECKED(UFrontendGameUserSettings, SetterOrGetterFuncName))
    

void UOptionsDataRegistry::InitOptionsDataRegistry(ULocalPlayer* InOwningLocalPlayer)
{
    InitGameplayCollectionTab();
    InitAudioCollectionTab();
    InitVideoCollectionTab();
    InitControlCollectionTab();
}

TArray<UListDataObject_Base*> UOptionsDataRegistry::GetListSourceItemsBySelectedTabId(const FName& InSelectedTabId) const
{
    UListDataObject_Collection* const* FoundTabCollectionPointer = RegisteredOptionsTabCollections.FindByPredicate([InSelectedTabId](UListDataObject_Collection* AvailableTabCollection) -> bool
    {
        return AvailableTabCollection->GetDataId() == InSelectedTabId;
    });

    checkf(FoundTabCollectionPointer,TEXT("No valid tab found under the ID %s"),*InSelectedTabId.ToString());

    UListDataObject_Collection* FoundTabCollection = *FoundTabCollectionPointer;

    TArray<UListDataObject_Base*> AllChildListItems;
    FindAllChildListItems(FoundTabCollection, AllChildListItems);
    
    return AllChildListItems;
}

void UOptionsDataRegistry::FindAllChildListItems(const UListDataObject_Base* InParent, TArray<UListDataObject_Base*>& OutFoundChildren) const
{
    if (!InParent)
        return;
    
    for (const auto Child : InParent->GetAllChildListData())
    {
        if (!Child)
            continue;
    
        OutFoundChildren.Add(Child);
    
        if (Child->HasAnyChildListData())
        {
            FindAllChildListItems(Child, OutFoundChildren);
        }
    }
}

void UOptionsDataRegistry::InitGameplayCollectionTab()
{
    UListDataObject_Collection* GameplayTabCollection = NewObject<UListDataObject_Collection>();
    GameplayTabCollection->SetDataId(FName("GameplayTabCollection"));
    GameplayTabCollection->SetDataDisplayName(FText::FromString(TEXT("Gameplay")));
    
    // Game Difficulty
    {
        UListDataObject_String* GameDifficulty = NewObject<UListDataObject_String>();
        GameDifficulty->SetDataId(FName("GameDifficulty"));
        GameDifficulty->SetDataDisplayName(FText::FromString(TEXT("Difficulty")));
        GameDifficulty->SetDescriptionRichText(FText::FromString(TEXT("Adjusts the difficulty of the game experience.\n\n<Bold>Easy:</> Focuses on the story experience. Provides the most relaxing combat.\n\n<Bold>Normal:</> Offers slightly harder combat experience\n\n<Bold>Hard:</> Offers a much more challenging combat experience\n\n<Bold>Very Hard:</> Provides the most challenging combat experience. Not recommended for first play through.")));
        GameDifficulty->AddDynamicOption(TEXT("Easy"), FText::FromString(TEXT("Easy")));
        GameDifficulty->AddDynamicOption(TEXT("Normal"), FText::FromString(TEXT("Normal")));
        GameDifficulty->AddDynamicOption(TEXT("Hard"), FText::FromString(TEXT("Hard")));
        GameDifficulty->AddDynamicOption(TEXT("Very Hard"), FText::FromString(TEXT("Very Hard")));
        GameDifficulty->SetDefaultValueFromString(TEXT("Normal"));
        GameDifficulty->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetGameDifficulty));
        GameDifficulty->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetGameDifficulty));
        GameDifficulty->SetShouldApplyChangesImmediately(true);
        
        GameplayTabCollection->AddChildListData(GameDifficulty);
    }

    // Test Item
    {
        UListDataObject_String* TestItem = NewObject<UListDataObject_String>();
        TestItem->SetDataId(FName("TestItem"));
        TestItem->SetDataDisplayName(FText::FromString(TEXT("Test Image Item")));
        TestItem->SetSoftDescriptionImage(UFrontendFunctionLibrary::GetOptionsSoftImageByTag(OptionsImageGameplayTags::Options_Image_Gameplay_TestImage));
        TestItem->SetDescriptionRichText(FText::FromString(TEXT("The image to display can be specified in the project settings. It can be anything the developer assigned in there")));

        GameplayTabCollection->AddChildListData(TestItem);
    }
    
    RegisteredOptionsTabCollections.Add(GameplayTabCollection);
}

void UOptionsDataRegistry::InitAudioCollectionTab()
{
    UListDataObject_Collection* AudioTabCollection = NewObject<UListDataObject_Collection>();
    AudioTabCollection->SetDataId(FName("AudioTabCollection"));
    AudioTabCollection->SetDataDisplayName(FText::FromString(TEXT("Audio")));

    // Volume Category
    {
        UListDataObject_Collection* VolumeCategoryCollection = NewObject<UListDataObject_Collection>();
        VolumeCategoryCollection->SetDataId(FName("VolumeCategoryCollection"));
        VolumeCategoryCollection->SetDataDisplayName(FText::FromString(TEXT("Volume")));
        
        AudioTabCollection->AddChildListData(VolumeCategoryCollection);

        // Overall Volume
        {
            UListDataObject_Scalar* OverallVolume = NewObject<UListDataObject_Scalar>();
            OverallVolume->SetDataId(FName("OverallVolume"));
            OverallVolume->SetDataDisplayName(FText::FromString(TEXT("Overall Volume")));
            OverallVolume->SetDescriptionRichText(FText::FromString(TEXT("This is description for Overall Volume")));
            OverallVolume->SetDisplayValueRange(TRange<float>(0.0f, 1.0f));
            OverallVolume->SetOutputValueRange(TRange<float>(0.0f, 2.0f));
            OverallVolume->SetSliderStepSize(0.01f);
            OverallVolume->SetDefaultValueFromString(LexToString(1.0f));
            OverallVolume->SetDisplayNumericType(ECommonNumericType::Percentage);
            OverallVolume->SetNumberFormattingOptions(UListDataObject_Scalar::NoDecimal());
            OverallVolume->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetOverallVolume));
            OverallVolume->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetOverallVolume));
            OverallVolume->SetShouldApplyChangesImmediately(true);
            
            VolumeCategoryCollection->AddChildListData(OverallVolume);
        }

        // Music Volume
        {
            UListDataObject_Scalar* MusicVolume = NewObject<UListDataObject_Scalar>();
            MusicVolume->SetDataId(FName("MusicVolume"));
            MusicVolume->SetDataDisplayName(FText::FromString(TEXT("Music Volume")));
            MusicVolume->SetDescriptionRichText(FText::FromString(TEXT("This is description for Music Volume")));
            MusicVolume->SetDisplayValueRange(TRange<float>(0.0f, 1.0f));
            MusicVolume->SetOutputValueRange(TRange<float>(0.0f, 2.0f));
            MusicVolume->SetSliderStepSize(0.01f);
            MusicVolume->SetDefaultValueFromString(LexToString(1.0f));
            MusicVolume->SetDisplayNumericType(ECommonNumericType::Percentage);
            MusicVolume->SetNumberFormattingOptions(UListDataObject_Scalar::NoDecimal());
            MusicVolume->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetMusicVolume));
            MusicVolume->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetMusicVolume));
            MusicVolume->SetShouldApplyChangesImmediately(true);
            
            VolumeCategoryCollection->AddChildListData(MusicVolume);
        }

        // Music Volume
        {
            UListDataObject_Scalar* SFXVolume = NewObject<UListDataObject_Scalar>();
            SFXVolume->SetDataId(FName("SFXVolume"));
            SFXVolume->SetDataDisplayName(FText::FromString(TEXT("SFX Volume")));
            SFXVolume->SetDescriptionRichText(FText::FromString(TEXT("This is description for SFX Volume")));
            SFXVolume->SetDisplayValueRange(TRange<float>(0.0f, 1.0f));
            SFXVolume->SetOutputValueRange(TRange<float>(0.0f, 2.0f));
            SFXVolume->SetSliderStepSize(0.01f);
            SFXVolume->SetDefaultValueFromString(LexToString(1.0f));
            SFXVolume->SetDisplayNumericType(ECommonNumericType::Percentage);
            SFXVolume->SetNumberFormattingOptions(UListDataObject_Scalar::NoDecimal());
            SFXVolume->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetSFXVolume));
            SFXVolume->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetSFXVolume));
            SFXVolume->SetShouldApplyChangesImmediately(true);
            
            VolumeCategoryCollection->AddChildListData(SFXVolume);
        }
    }

    // Sound Category
    {
        UListDataObject_Collection* SoundCategoryCollection = NewObject<UListDataObject_Collection>();
        SoundCategoryCollection->SetDataId(FName("SoundCategoryCollection"));
        SoundCategoryCollection->SetDataDisplayName(FText::FromString(TEXT("Sound")));
        
        AudioTabCollection->AddChildListData(SoundCategoryCollection);

        // Allow Background Audio
        {
            UListDataObject_StringBool* AllowBackgroundAudio = NewObject<UListDataObject_StringBool>();
            AllowBackgroundAudio->SetDataId(FName("AllowBackgroundAudio"));
            AllowBackgroundAudio->SetDataDisplayName(FText::FromString(TEXT("Allow Background Audio")));
            AllowBackgroundAudio->SetDescriptionRichText(FText::FromString(TEXT("This is description for Allow Background Audio")));
            AllowBackgroundAudio->OverrideTrueDisplayText(FText::FromString(TEXT("Enabled")));
            AllowBackgroundAudio->OverrideFalseDisplayText(FText::FromString(TEXT("Disabled")));
            AllowBackgroundAudio->SetFalseAsDefaultValue();
            AllowBackgroundAudio->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetAllowBackgroundAudio));
            AllowBackgroundAudio->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetAllowBackgroundAudio));
            AllowBackgroundAudio->SetShouldApplyChangesImmediately(true);
            
            SoundCategoryCollection->AddChildListData(AllowBackgroundAudio);
        }
        
        // Use HDR Audio
        {
            UListDataObject_StringBool* UseHDRAudio = NewObject<UListDataObject_StringBool>();
            UseHDRAudio->SetDataId(FName("UseHDRAudio"));
            UseHDRAudio->SetDataDisplayName(FText::FromString(TEXT("Use HDR Audio")));
            UseHDRAudio->SetDescriptionRichText(FText::FromString(TEXT("This is description for Use HDR Audio")));
            UseHDRAudio->OverrideTrueDisplayText(FText::FromString(TEXT("Enabled")));
            UseHDRAudio->OverrideFalseDisplayText(FText::FromString(TEXT("Disabled")));
            UseHDRAudio->SetFalseAsDefaultValue();
            UseHDRAudio->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetUseHDRAudio));
            UseHDRAudio->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetUseHDRAudio));
            UseHDRAudio->SetShouldApplyChangesImmediately(true);
            
            SoundCategoryCollection->AddChildListData(UseHDRAudio);
        }
    }
    
    RegisteredOptionsTabCollections.Add(AudioTabCollection);
}

void UOptionsDataRegistry::InitVideoCollectionTab()
{
    UListDataObject_Collection* VideoTabCollection = NewObject<UListDataObject_Collection>();
    VideoTabCollection->SetDataId(FName("VideoTabCollection"));
    VideoTabCollection->SetDataDisplayName(FText::FromString(TEXT("Video")));

    UListDataObject_StringEnum* CachedWindowMode = nullptr;
    UListDataObject_StringInteger* CachedOverallQuality = nullptr;

    // Display Category Collection
    {
        UListDataObject_Collection* DisplayCategoryCollection = NewObject<UListDataObject_Collection>();
        DisplayCategoryCollection->SetDataId(FName("Display Category Collection"));
        DisplayCategoryCollection->SetDataDisplayName(FText::FromString(TEXT("Display")));
        
        VideoTabCollection->AddChildListData(DisplayCategoryCollection);

        FOptionsDataEditConditionDescriptor PackagedBuildOnlyCondition;
        PackagedBuildOnlyCondition.SetEditConditionFunc([]()->bool
        {
            const bool bIsInEditor = GIsEditor || GIsPlayInEditorWorld;
            return !bIsInEditor;
        });
        PackagedBuildOnlyCondition.SetDisabledRichReason(TEXT("\n\n<Disabled>This setting can only be adjusted in a packaged build.</>"));

        // Window Mode
        {
            UListDataObject_StringEnum* WindowMode = NewObject<UListDataObject_StringEnum>();
            WindowMode->SetDataId(FName("WindowMode"));
            WindowMode->SetDataDisplayName(FText::FromString(TEXT("Window Mode")));
            WindowMode->SetDescriptionRichText(FText::FromString(TEXT("This is description for Window Mode")));
            WindowMode->AddEnumOption(EWindowMode::Fullscreen, FText::FromString("Fullscreen Mode"));
            WindowMode->AddEnumOption(EWindowMode::WindowedFullscreen, FText::FromString("Borderless Window"));
            WindowMode->AddEnumOption(EWindowMode::Windowed, FText::FromString("Windowed Mode"));
            WindowMode->SetDefaultValueFromEnumOption(EWindowMode::WindowedFullscreen);
            WindowMode->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetFullscreenMode));
            WindowMode->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetFullscreenMode));
            WindowMode->SetShouldApplyChangesImmediately(true);
            
            WindowMode->AddEditCondition(PackagedBuildOnlyCondition);
            
            CachedWindowMode = WindowMode;
            
            VideoTabCollection->AddChildListData(WindowMode);
        }
        
        // Screen Resolution
        {
            UListDataObject_StringResolution* ScreenResolution = NewObject<UListDataObject_StringResolution>();
            ScreenResolution->SetDataId(FName("ScreenResolution"));
            ScreenResolution->SetDataDisplayName(FText::FromString(TEXT("Screen Resolution")));
            ScreenResolution->SetDescriptionRichText(FText::FromString(TEXT("This is description for Screen Resolution")));
            ScreenResolution->InitResolutionValues();
            ScreenResolution->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetScreenResolution));
            ScreenResolution->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetScreenResolution));
            ScreenResolution->SetShouldApplyChangesImmediately(true);
            
            FOptionsDataEditConditionDescriptor WindowModeEditCondition;
            WindowModeEditCondition.SetEditConditionFunc([CachedWindowMode]()->bool
            {
                if (!CachedWindowMode)
                    return false;

                const bool bIsBorderlessWindow = CachedWindowMode->GetCurrentValueAsEnum<EWindowMode::Type>() == EWindowMode::WindowedFullscreen;
                return !bIsBorderlessWindow;
            });
            WindowModeEditCondition.SetDisabledRichReason(TEXT("\n\n<Disabled>Screen Resolution is not adjustable when the 'Window Mode' is set to Borderless Window.The value must match with the maximum allowed resolution.</>"));
            WindowModeEditCondition.SetDisabledForcedStringValue(ScreenResolution->GetMaximumAllowedResolution());

            ScreenResolution->AddEditCondition(PackagedBuildOnlyCondition);
            ScreenResolution->AddEditCondition(WindowModeEditCondition);

            ScreenResolution->AddEditDependencyData(CachedWindowMode);
            
            VideoTabCollection->AddChildListData(ScreenResolution);
        }
    }

    // Graphics Category Collection
    {
        UListDataObject_Collection* GraphicsCategoryCollection = NewObject<UListDataObject_Collection>();
        GraphicsCategoryCollection->SetDataId(FName("Graphics Category Collection"));
        GraphicsCategoryCollection->SetDataDisplayName(FText::FromString(TEXT("Graphics")));
        
        VideoTabCollection->AddChildListData(GraphicsCategoryCollection);

        // Display Gamma
        {
            UListDataObject_Scalar* DisplayGamma = NewObject<UListDataObject_Scalar>();
            DisplayGamma->SetDataId(FName("DisplayGamma"));
            DisplayGamma->SetDataDisplayName(FText::FromString(TEXT("Brightness")));
            DisplayGamma->SetDescriptionRichText(FText::FromString(TEXT("This is description for Brightness")));
            DisplayGamma->SetDisplayValueRange(TRange<float>(0.0f, 1.0f));
            DisplayGamma->SetOutputValueRange(TRange<float>(1.2f, 3.2f)); // 2.2f is default value
            DisplayGamma->SetSliderStepSize(0.01f);
            DisplayGamma->SetDefaultValueFromString(LexToString(2.2f));
            DisplayGamma->SetDisplayNumericType(ECommonNumericType::Percentage);
            DisplayGamma->SetNumberFormattingOptions(UListDataObject_Scalar::NoDecimal());
            DisplayGamma->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetDisplayGamma));
            DisplayGamma->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetDisplayGamma));

            GraphicsCategoryCollection->AddChildListData(DisplayGamma);
        }

        // Overall Quality
        {
            UListDataObject_StringInteger* OverallQuality = NewObject<UListDataObject_StringInteger>();
            OverallQuality->SetDataId(FName("OverallQuality"));
            OverallQuality->SetDataDisplayName(FText::FromString(TEXT("Overall Quality")));
            OverallQuality->SetDescriptionRichText(FText::FromString(TEXT("This is description for Overall Quality")));
            OverallQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
            OverallQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
            OverallQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
            OverallQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
            OverallQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
            OverallQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetOverallScalabilityLevel));
            OverallQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetOverallScalabilityLevel));
            OverallQuality->SetShouldApplyChangesImmediately(true);

            CachedOverallQuality = OverallQuality;

            GraphicsCategoryCollection->AddChildListData(OverallQuality);
        }

        // Resolution Scale
        {
            UListDataObject_Scalar* ResolutionScale = NewObject<UListDataObject_Scalar>();
            ResolutionScale->SetDataId(FName("ResolutionScale"));
            ResolutionScale->SetDataDisplayName(FText::FromString(TEXT("Resolution Scale")));
            ResolutionScale->SetDescriptionRichText(FText::FromString(TEXT("This is description for Resolution Scale")));
            ResolutionScale->SetDisplayValueRange(TRange<float>(0.0f, 1.0f));
            ResolutionScale->SetOutputValueRange(TRange<float>(0.0f, 1.0f));
            ResolutionScale->SetSliderStepSize(0.01f);
            ResolutionScale->SetDefaultValueFromString(LexToString(1.0f));
            ResolutionScale->SetDisplayNumericType(ECommonNumericType::Percentage);
            ResolutionScale->SetNumberFormattingOptions(UListDataObject_Scalar::NoDecimal());
            ResolutionScale->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetResolutionScaleNormalized));
            ResolutionScale->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetResolutionScaleNormalized));
            ResolutionScale->SetShouldApplyChangesImmediately(true);

            ResolutionScale->AddEditDependencyData(CachedOverallQuality);

            GraphicsCategoryCollection->AddChildListData(ResolutionScale);
        }

        // Global Illumination Quality
        {
            UListDataObject_StringInteger* GlobalIlluminationQuality = NewObject<UListDataObject_StringInteger>();
            GlobalIlluminationQuality->SetDataId(FName("GlobalIlluminationQuality"));
            GlobalIlluminationQuality->SetDataDisplayName(FText::FromString(TEXT("Global Illumination")));
            GlobalIlluminationQuality->SetDescriptionRichText(FText::FromString(TEXT("This is description for Global Illumination")));
            GlobalIlluminationQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
            GlobalIlluminationQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
            GlobalIlluminationQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
            GlobalIlluminationQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
            GlobalIlluminationQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
            GlobalIlluminationQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetGlobalIlluminationQuality));
            GlobalIlluminationQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetGlobalIlluminationQuality));
            GlobalIlluminationQuality->SetShouldApplyChangesImmediately(true);

            GlobalIlluminationQuality->AddEditDependencyData(CachedOverallQuality);
            CachedOverallQuality->AddEditDependencyData(GlobalIlluminationQuality);
            
            GraphicsCategoryCollection->AddChildListData(GlobalIlluminationQuality);
        }

        // Shadow Quality
        {
            UListDataObject_StringInteger* ShadowQuality = NewObject<UListDataObject_StringInteger>();
            ShadowQuality->SetDataId(FName("ShadowQuality"));
            ShadowQuality->SetDataDisplayName(FText::FromString(TEXT("Shadow Quality")));
            ShadowQuality->SetDescriptionRichText(FText::FromString(TEXT("This is description for Shadow Quality")));
            ShadowQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
            ShadowQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
            ShadowQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
            ShadowQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
            ShadowQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
            ShadowQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetShadowQuality));
            ShadowQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetShadowQuality));
            ShadowQuality->SetShouldApplyChangesImmediately(true);

            ShadowQuality->AddEditDependencyData(CachedOverallQuality);
            CachedOverallQuality->AddEditDependencyData(ShadowQuality);
            
            GraphicsCategoryCollection->AddChildListData(ShadowQuality);
        }

        // Anti Aliasing Quality
        {
            UListDataObject_StringInteger* AntiAliasingQuality = NewObject<UListDataObject_StringInteger>();
            AntiAliasingQuality->SetDataId(FName("AntiAliasingQuality"));
            AntiAliasingQuality->SetDataDisplayName(FText::FromString(TEXT("Anti Aliasing")));
            AntiAliasingQuality->SetDescriptionRichText(FText::FromString(TEXT("This is description for Anti Aliasing Quality")));
            AntiAliasingQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
            AntiAliasingQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
            AntiAliasingQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
            AntiAliasingQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
            AntiAliasingQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
            AntiAliasingQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetAntiAliasingQuality));
            AntiAliasingQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetAntiAliasingQuality));
            AntiAliasingQuality->SetShouldApplyChangesImmediately(true);

            AntiAliasingQuality->AddEditDependencyData(CachedOverallQuality);
            CachedOverallQuality->AddEditDependencyData(AntiAliasingQuality);
            
            GraphicsCategoryCollection->AddChildListData(AntiAliasingQuality);
        }

        // View Distance Quality
        {
            UListDataObject_StringInteger* ViewDistanceQuality = NewObject<UListDataObject_StringInteger>();
            ViewDistanceQuality->SetDataId(FName("ViewDistanceQuality"));
            ViewDistanceQuality->SetDataDisplayName(FText::FromString(TEXT("View Distance")));
            ViewDistanceQuality->SetDescriptionRichText(FText::FromString(TEXT("This is description for View Distance Quality")));
            ViewDistanceQuality->AddIntegerOption(0, FText::FromString(TEXT("Near")));
            ViewDistanceQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
            ViewDistanceQuality->AddIntegerOption(2, FText::FromString(TEXT("Far")));
            ViewDistanceQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
            ViewDistanceQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
            ViewDistanceQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetViewDistanceQuality));
            ViewDistanceQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetViewDistanceQuality));
            ViewDistanceQuality->SetShouldApplyChangesImmediately(true);

            ViewDistanceQuality->AddEditDependencyData(CachedOverallQuality);
            CachedOverallQuality->AddEditDependencyData(ViewDistanceQuality);
            
            GraphicsCategoryCollection->AddChildListData(ViewDistanceQuality);
        }

        // Texture Quality
        {
            UListDataObject_StringInteger* TextureQuality = NewObject<UListDataObject_StringInteger>();
            TextureQuality->SetDataId(FName("TextureQuality"));
            TextureQuality->SetDataDisplayName(FText::FromString(TEXT("Texture Quality")));
            TextureQuality->SetDescriptionRichText(FText::FromString(TEXT("This is description for Texture Quality")));
            TextureQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
            TextureQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
            TextureQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
            TextureQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
            TextureQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
            TextureQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetTextureQuality));
            TextureQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetTextureQuality));
            TextureQuality->SetShouldApplyChangesImmediately(true);

            TextureQuality->AddEditDependencyData(CachedOverallQuality);
            CachedOverallQuality->AddEditDependencyData(TextureQuality);
            
            GraphicsCategoryCollection->AddChildListData(TextureQuality);
        }

        // Visual Effects Quality
        {
            UListDataObject_StringInteger* VisualEffectQuality = NewObject<UListDataObject_StringInteger>();
            VisualEffectQuality->SetDataId(FName("VisualEffectQuality"));
            VisualEffectQuality->SetDataDisplayName(FText::FromString(TEXT("Visual Effects Quality")));
            VisualEffectQuality->SetDescriptionRichText(FText::FromString(TEXT("This is description for Visual Effects Quality")));
            VisualEffectQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
            VisualEffectQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
            VisualEffectQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
            VisualEffectQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
            VisualEffectQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
            VisualEffectQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetVisualEffectQuality));
            VisualEffectQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetVisualEffectQuality));
            VisualEffectQuality->SetShouldApplyChangesImmediately(true);

            VisualEffectQuality->AddEditDependencyData(CachedOverallQuality);
            CachedOverallQuality->AddEditDependencyData(VisualEffectQuality);
            
            GraphicsCategoryCollection->AddChildListData(VisualEffectQuality);
        }

        // Reflection Quality
        {
            UListDataObject_StringInteger* ReflectionQuality = NewObject<UListDataObject_StringInteger>();
            ReflectionQuality->SetDataId(FName("ReflectionQuality"));
            ReflectionQuality->SetDataDisplayName(FText::FromString(TEXT("Reflection Quality")));
            ReflectionQuality->SetDescriptionRichText(FText::FromString(TEXT("This is description for Reflection Quality")));
            ReflectionQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
            ReflectionQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
            ReflectionQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
            ReflectionQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
            ReflectionQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
            ReflectionQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetReflectionQuality));
            ReflectionQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetReflectionQuality));
            ReflectionQuality->SetShouldApplyChangesImmediately(true);

            ReflectionQuality->AddEditDependencyData(CachedOverallQuality);
            CachedOverallQuality->AddEditDependencyData(ReflectionQuality);
            
            GraphicsCategoryCollection->AddChildListData(ReflectionQuality);
        }

        // Post Processing Quality
        {
            UListDataObject_StringInteger* PostProcessingQuality = NewObject<UListDataObject_StringInteger>();
            PostProcessingQuality->SetDataId(FName("PostProcessingQuality"));
            PostProcessingQuality->SetDataDisplayName(FText::FromString(TEXT("Post Processing")));
            PostProcessingQuality->SetDescriptionRichText(FText::FromString(TEXT("This is description for Post Processing Quality")));
            PostProcessingQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
            PostProcessingQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
            PostProcessingQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
            PostProcessingQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
            PostProcessingQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
            PostProcessingQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetPostProcessingQuality));
            PostProcessingQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetPostProcessingQuality));
            PostProcessingQuality->SetShouldApplyChangesImmediately(true);

            PostProcessingQuality->AddEditDependencyData(CachedOverallQuality);
            CachedOverallQuality->AddEditDependencyData(PostProcessingQuality);
            
            GraphicsCategoryCollection->AddChildListData(PostProcessingQuality);
        }
    }
    
    RegisteredOptionsTabCollections.Add(VideoTabCollection);
}

void UOptionsDataRegistry::InitControlCollectionTab()
{
    UListDataObject_Collection* ControlTabCollection = NewObject<UListDataObject_Collection>();
    ControlTabCollection->SetDataId(FName("ControlTabCollection"));
    ControlTabCollection->SetDataDisplayName(FText::FromString(TEXT("Control")));
    
    RegisteredOptionsTabCollections.Add(ControlTabCollection);
}

