#pragma once
#include "Globals.h"
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "Systems.generated.h"

/**
 * Scalability Level
 */
UENUM(BlueprintType)
enum class EScalabilityLevel :uint8
{
	LOW UMETA(DisplayName = "Low Quality"),
	MEDIUM UMETA(DisplayName = "Medium Quality"),
	HIGH UMETA(DisplayName = "High Quality"),
	EPIC UMETA(DisplayName = "Epic Quality"),
	//CINEMATIC
};

/**
 * Scalability Setting
 */
USTRUCT(BlueprintType)
struct FScalabilitySettings : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, meta = (ClampMin = "10", ClampMax = "100"))
		/** Resolution Scale **/
		int32 ScreenPercentage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, meta = (ClampMin = "0.4", ClampMax = "1"))
		/** View Distance Scale **/
		float ViewDistanceScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, meta = (ClampMin = "0", ClampMax = "6"))
		/** Anti-Aliasing **/
		int32 PostProcessAAQuality;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, meta = (ClampMin = "0", ClampMax = "3"))
		/** Post Processing **/
		int32 PostProcessQuality;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, meta = (ClampMin = "0", ClampMax = "3"))
		/** Shadows **/
		int32 ShadowQuality;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, meta = (ClampMin = "0", ClampMax = "3"))
		/** Textures **/
		int32 TextureQuality;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, meta = (ClampMin = "0", ClampMax = "3"))
		/** Effects **/
		int32 EffectsQuality;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, meta = (ClampMin = "0", ClampMax = "3"))
		/** Grass and Foliage Scalability **/
		int32 FoliageQuality;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, meta = (ClampMin = "30", ClampMax = "144"))
		/** Max FPS **/
		int32 MaxFPS;
	FScalabilitySettings() {
	}
	FScalabilitySettings(const FScalabilitySettings& Reference) {
		ScreenPercentage = Reference.ScreenPercentage;
		ViewDistanceScale = Reference.ViewDistanceScale;
		PostProcessAAQuality = Reference.PostProcessAAQuality;
		PostProcessQuality = Reference.PostProcessQuality;
		ShadowQuality = Reference.ShadowQuality;
		TextureQuality = Reference.TextureQuality;
		EffectsQuality = Reference.EffectsQuality;
		FoliageQuality = Reference.FoliageQuality;
		MaxFPS = Reference.MaxFPS;
	}
};

/**
 * System Library
 */
UCLASS()
class COMLIB_API USystems : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	//Scalability Setting

	UFUNCTION(BlueprintPure, Category = "CB_Systems|Scalability")
		static FScalabilitySettings GetScalabilitySetting(EScalabilityLevel ScalabilityLevel)
	{
		FScalabilitySettings Result;
		switch (ScalabilityLevel)
		{
		case EScalabilityLevel::LOW:
			Result.ScreenPercentage = 25;
			Result.ViewDistanceScale = 0.4;
			Result.PostProcessAAQuality = 0;
			Result.PostProcessQuality = 0;
			Result.ShadowQuality = 0;
			Result.TextureQuality = 0;
			Result.EffectsQuality = 0;
			Result.FoliageQuality = 0;
			Result.MaxFPS = 30;
			break;
		case EScalabilityLevel::MEDIUM:
			Result.ScreenPercentage = 50;
			Result.ViewDistanceScale = 0.6;
			Result.PostProcessAAQuality = 2;
			Result.PostProcessQuality = 1;
			Result.ShadowQuality = 1;
			Result.TextureQuality = 1;
			Result.EffectsQuality = 1;
			Result.FoliageQuality = 1;
			Result.MaxFPS = 60;
			break;
		case EScalabilityLevel::HIGH:
			Result.ScreenPercentage = 75;
			Result.ViewDistanceScale = 0.8;
			Result.PostProcessAAQuality = 4;
			Result.PostProcessQuality = 2;
			Result.ShadowQuality = 2;
			Result.TextureQuality = 2;
			Result.EffectsQuality = 2;
			Result.FoliageQuality = 2;
			Result.MaxFPS = 90;
			break;
		case EScalabilityLevel::EPIC:
			Result.ScreenPercentage = 100;
			Result.ViewDistanceScale = 1;
			Result.PostProcessAAQuality = 6;
			Result.PostProcessQuality = 3;
			Result.ShadowQuality = 3;
			Result.TextureQuality = 3;
			Result.EffectsQuality = 3;
			Result.FoliageQuality = 3;
			Result.MaxFPS = 144;
			break;
		default:
			break;
		}
		return Result;
	}

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "CB_Systems|Scalability", meta = (WorldContext = "WorldContextObject"))
		static void UpdateScalabilitySetting(UObject* WorldContextObject, FScalabilitySettings ScalabilitySettings, APlayerController* SpecificPlayer = nullptr);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "CB_Systems|Scalability", meta = (WorldContext = "WorldContextObject"))
		static void SetResolutionScale(UObject* WorldContextObject, EScalabilityLevel ScalabilityLevel, APlayerController* SpecificPlayer = nullptr);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "CB_Systems|Scalability", meta = (WorldContext = "WorldContextObject"))
		static void SetViewDistance(UObject* WorldContextObject, EScalabilityLevel ScalabilityLevel, APlayerController* SpecificPlayer = nullptr);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "CB_Systems|Scalability", meta = (WorldContext = "WorldContextObject"))
		static void SetAntiAliasing(UObject* WorldContextObject, EScalabilityLevel ScalabilityLevel, APlayerController* SpecificPlayer = nullptr);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "CB_Systems|Scalability", meta = (WorldContext = "WorldContextObject"))
		static void SetPostProcessQuality(UObject* WorldContextObject, EScalabilityLevel ScalabilityLevel, APlayerController* SpecificPlayer = nullptr);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "CB_Systems|Scalability", meta = (WorldContext = "WorldContextObject"))
		static void SetShadowQuality(UObject* WorldContextObject, EScalabilityLevel ScalabilityLevel, APlayerController* SpecificPlayer = nullptr);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "CB_Systems|Scalability", meta = (WorldContext = "WorldContextObject"))
		static void SetTextureQuality(UObject* WorldContextObject, EScalabilityLevel ScalabilityLevel, APlayerController* SpecificPlayer = nullptr);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "CB_Systems|Scalability", meta = (WorldContext = "WorldContextObject"))
		static void SetEffectsQuality(UObject* WorldContextObject, EScalabilityLevel ScalabilityLevel, APlayerController* SpecificPlayer = nullptr);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "CB_Systems|Scalability", meta = (WorldContext = "WorldContextObject"))
		static void SetGrassAndFoliageQuality(UObject* WorldContextObject, EScalabilityLevel ScalabilityLevel, APlayerController* SpecificPlayer = nullptr);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "CB_Systems|Scalability", meta = (WorldContext = "WorldContextObject"))
		static void SetMaxFPS(UObject* WorldContextObject, EScalabilityLevel ScalabilityLevel, APlayerController* SpecificPlayer = nullptr);

};
