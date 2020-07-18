#include "Systems.h"
#include "Kismet/KismetSystemLibrary.h"

#define SET_SCALABILITY_SETTING(WorldContextName,PlayerControllerName,ScalabilityLevelName,Cmd,LowValue,MediumValue,HighValue,EpicValue) \
	FString CmdString = CB_FS_CONCAT(Cmd, " ");\
	switch (ScalabilityLevelName)\
	{\
	case EScalabilityLevel::LOW:UKismetSystemLibrary::ExecuteConsoleCommand(WorldContextName, CB_FS_CONCAT(CmdString,LowValue), PlayerControllerName);break;\
	case EScalabilityLevel::MEDIUM:UKismetSystemLibrary::ExecuteConsoleCommand(WorldContextName, CB_FS_CONCAT(CmdString,MediumValue), PlayerControllerName);break;\
	case EScalabilityLevel::HIGH:UKismetSystemLibrary::ExecuteConsoleCommand(WorldContextName, CB_FS_CONCAT(CmdString,HighValue), PlayerControllerName);break;\
	case EScalabilityLevel::EPIC:UKismetSystemLibrary::ExecuteConsoleCommand(WorldContextName, CB_FS_CONCAT(CmdString,EpicValue), PlayerControllerName);break;\
	default:break;\
	}

#define SET_ALL_SCALABILITY_SETTINGS(WorldContextName,PlayerControllerName,Cmd,VariableName,LowerBound,UpperBound) \
	if (ScalabilitySettings.VariableName >= LowerBound && ScalabilitySettings.VariableName <= UpperBound)\
	{\
		UKismetSystemLibrary::ExecuteConsoleCommand(WorldContextName, CB_FS_CONCAT_3(Cmd," ", ScalabilitySettings.VariableName), PlayerControllerName);\
	}

void USystems::UpdateScalabilitySetting(UObject* WorldContextObject, FScalabilitySettings ScalabilitySettings, APlayerController* SpecificPlayer)
{
	SET_ALL_SCALABILITY_SETTINGS(WorldContextObject, SpecificPlayer, "r.ScreenPercentage", ScreenPercentage, 10, 100);
	SET_ALL_SCALABILITY_SETTINGS(WorldContextObject, SpecificPlayer, "r.ViewDistanceScale", ViewDistanceScale, 0.4, 1);
	SET_ALL_SCALABILITY_SETTINGS(WorldContextObject, SpecificPlayer, "r.PostProcessAAQuality", PostProcessAAQuality, 0, 6);
	SET_ALL_SCALABILITY_SETTINGS(WorldContextObject, SpecificPlayer, "sg.PostProcessQuality", PostProcessQuality, 0, 3);
	SET_ALL_SCALABILITY_SETTINGS(WorldContextObject, SpecificPlayer, "sg.ShadowQuality", ShadowQuality, 0, 3);
	SET_ALL_SCALABILITY_SETTINGS(WorldContextObject, SpecificPlayer, "sg.TextureQuality", TextureQuality, 0, 3);
	SET_ALL_SCALABILITY_SETTINGS(WorldContextObject, SpecificPlayer, "sg.EffectsQuality", EffectsQuality, 0, 3);
	SET_ALL_SCALABILITY_SETTINGS(WorldContextObject, SpecificPlayer, "FoliageQuality", FoliageQuality, 0, 3);
	SET_ALL_SCALABILITY_SETTINGS(WorldContextObject, SpecificPlayer, "t.MaxFPS", FoliageQuality, 30, 144);
}

void USystems::SetResolutionScale(UObject* WorldContextObject, EScalabilityLevel ScalabilityLevel, APlayerController* SpecificPlayer)
{
	SET_SCALABILITY_SETTING(WorldContextObject, SpecificPlayer, ScalabilityLevel, "r.ScreenPercentage", 30, 50, 80, 100);
}

void USystems::SetViewDistance(UObject* WorldContextObject, EScalabilityLevel ScalabilityLevel, APlayerController* SpecificPlayer)
{
	SET_SCALABILITY_SETTING(WorldContextObject, SpecificPlayer, ScalabilityLevel, "r.ViewDistanceScale", 0.4f, 0.6f, 0.8f, 1.f);
}

void USystems::SetAntiAliasing(UObject* WorldContextObject, EScalabilityLevel ScalabilityLevel, APlayerController* SpecificPlayer)
{
	SET_SCALABILITY_SETTING(WorldContextObject, SpecificPlayer, ScalabilityLevel, "r.PostProcessAAQuality", 0, 2, 4, 6);
}

void USystems::SetPostProcessQuality(UObject* WorldContextObject, EScalabilityLevel ScalabilityLevel, APlayerController* SpecificPlayer)
{
	SET_SCALABILITY_SETTING(WorldContextObject, SpecificPlayer, ScalabilityLevel, "sg.PostProcessQuality", 0, 1, 2, 3);
}

void USystems::SetShadowQuality(UObject* WorldContextObject, EScalabilityLevel ScalabilityLevel, APlayerController* SpecificPlayer)
{
	SET_SCALABILITY_SETTING(WorldContextObject, SpecificPlayer, ScalabilityLevel, "sg.ShadowQuality", 0, 1, 2, 3);
}

void USystems::SetTextureQuality(UObject* WorldContextObject, EScalabilityLevel ScalabilityLevel, APlayerController* SpecificPlayer)
{
	SET_SCALABILITY_SETTING(WorldContextObject, SpecificPlayer, ScalabilityLevel, "sg.TextureQuality", 0, 1, 2, 3);
}

void USystems::SetEffectsQuality(UObject* WorldContextObject, EScalabilityLevel ScalabilityLevel, APlayerController* SpecificPlayer)
{
	SET_SCALABILITY_SETTING(WorldContextObject, SpecificPlayer, ScalabilityLevel, "sg.EffectsQuality", 0, 1, 2, 3);
}

void USystems::SetGrassAndFoliageQuality(UObject* WorldContextObject, EScalabilityLevel ScalabilityLevel, APlayerController* SpecificPlayer)
{
	SET_SCALABILITY_SETTING(WorldContextObject, SpecificPlayer, ScalabilityLevel, "FoliageQuality", 0, 1, 2, 3);
}

void USystems::SetMaxFPS(UObject* WorldContextObject, EScalabilityLevel ScalabilityLevel, APlayerController* SpecificPlayer)
{
	SET_SCALABILITY_SETTING(WorldContextObject, SpecificPlayer, ScalabilityLevel, "t.MaxFPS", 30, 60, 90, 144);
}
