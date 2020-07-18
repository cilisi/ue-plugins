#pragma once

#include "Constants.h"

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Functions.generated.h"

#define MIN_COLOR_NUM CB_ZERO
#define MAX_COLOR_NUM CB_MAX_BYTE_NUM

/**
 *
 */
UCLASS()
class COMLIB_API UFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "CB_Functions")
		/** Get liner point of start and end from PlayerController for example mouse etc **/
		static void GetLinerPointFromMouse(const APlayerController* PlayerController, const float Length, FVector& Start, FVector& End);

	UFUNCTION(BlueprintPure, Category = "CB_Functions")
		/** Get liner point of start and end from PlayerController for example arm etc **/
		static void GetLinerPointFromSceneComponent(const APlayerController* PlayerController, const USceneComponent* SceneComponent, const float Length, FVector& Start, FVector& End);

	UFUNCTION(BlueprintCallable, Category = "CB_Functions")
		/** Build ray line from play controller or scene component attaching charactor to mouse world location convert from screen position**/
		static bool BuildLinerFromMouseOrComponent(
			UObject* WorldContextObject,
			const APlayerController* PlayerController,
			const float Length,
			const ETraceTypeQuery TraceChannel,
			FHitResult& OutHit,
			const TArray<AActor*>& ActorsToIgnore,
			const USceneComponent* SceneComponent = nullptr,
			const EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::Type::None,
			const bool bTraceComplex = true,
			const bool bIgnoreSelf = true,
			const FLinearColor TraceColor = FLinearColor::Red,
			const FLinearColor TraceHitColor = FLinearColor::Green,
			const float DrawTime = 5.0f);

	UFUNCTION(BlueprintPure, Category = "CB_Functions")
		/** Random generate color **/
		static FColor RandomColor();

	UFUNCTION(BlueprintPure, Category = "CB_Functions")
		/** Show mouse cursor when is shadow or shadow when is showed except it is ignored **/
		static bool FlipFlopMouseCursor(APlayerController* const PlayerController, const bool& IsIgnored = false);

public:

	UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = "CB_Functions", meta = (WorldContext = "WorldContextObject"))
		static FVector2D GetScreenSize(UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = "CB_Functions", meta = (WorldContext = "WorldContextObject"))
		static FVector2D GetScreenCenterPoint(UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = "CB_Functions", meta = (WorldContext = "WorldContextObject"))
		static bool GetScreenCenterPointWorldLocationDirection(UObject* WorldContextObject, APlayerController* PlayerController, FVector& WorldLocation, FVector& WorldDirection);

	UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = "CB_Functions", meta = (WorldContext = "WorldContextObject"))
		/** Is Left Haft Screen **/
		static bool IsLeftHalfScreen(UObject* WorldContextObject, const FVector2D& Location);

	UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = "CB_Functions", meta = (WorldContext = "WorldContextObject"))
		/** Is Top Haft Screen **/
		static bool IsTopHalfScreen(UObject* WorldContextObject, const FVector2D& Location);
};
