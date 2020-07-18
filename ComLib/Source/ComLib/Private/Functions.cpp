#include "Functions.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "Maths.h"

void UFunctions::GetLinerPointFromMouse(const APlayerController* PlayerController, const float Length, FVector& Start, FVector& End)
{
	FVector Location, Direction;
	if (PlayerController->DeprojectMousePositionToWorld(Location, Direction)) {
		End = UMaths::CalculateLinearEnd(Location, Direction, Length);
	}
}
void UFunctions::GetLinerPointFromSceneComponent(const APlayerController* PlayerController, const USceneComponent* SceneComponent, const float Length, FVector& Start, FVector& End)
{
	FVector Location, Direction;
	if (PlayerController->DeprojectMousePositionToWorld(Location, Direction)) {
		Location = SceneComponent->GetComponentLocation();
		End = UMaths::CalculateLinearEnd(Location, Direction, Length);
	}
}

bool UFunctions::BuildLinerFromMouseOrComponent(UObject* WorldContextObject,
	const APlayerController* PlayerController,
	const float Length,
	const ETraceTypeQuery TraceChannel,
	FHitResult& OutHit,
	const TArray<AActor*>& ActorsToIgnore,
	const USceneComponent* SceneComponent,
	const EDrawDebugTrace::Type DrawDebugType,
	const bool bTraceComplex,
	const bool bIgnoreSelf,
	const FLinearColor TraceColor,
	const FLinearColor TraceHitColor,
	const float DrawTime)
{
	FVector Start, End;
	if (SceneComponent != nullptr) {
		UFunctions::GetLinerPointFromSceneComponent(PlayerController, SceneComponent, Length, Start, End);
	}
	else {
		UFunctions::GetLinerPointFromMouse(PlayerController, Length, Start, End);
	}
	return UKismetSystemLibrary::LineTraceSingle(WorldContextObject, Start, End, TraceChannel, bTraceComplex, ActorsToIgnore, DrawDebugType, OutHit, bIgnoreSelf, TraceColor, TraceHitColor, DrawTime);
}

FColor UFunctions::RandomColor()
{
	uint8 R = FMath::RandRange(MIN_COLOR_NUM, MAX_COLOR_NUM);
	uint8 G = FMath::RandRange(MIN_COLOR_NUM, MAX_COLOR_NUM);
	uint8 B = FMath::RandRange(MIN_COLOR_NUM, MAX_COLOR_NUM);
	uint8 A = FMath::RandRange(MIN_COLOR_NUM, MAX_COLOR_NUM);
	return FColor(R, G, B, A);
}

bool UFunctions::FlipFlopMouseCursor(APlayerController* const PlayerController, const bool& IsIgnored)
{
	if (!IsIgnored) {
		bool Status = PlayerController->bShowMouseCursor;
		PlayerController->bShowMouseCursor = Status;
	}
	return PlayerController->bShowMouseCursor;
}

FVector2D UFunctions::GetScreenSize(UObject* WorldContextObject)
{
	return UWidgetLayoutLibrary::GetViewportSize(WorldContextObject);
}

FVector2D UFunctions::GetScreenCenterPoint(UObject* WorldContextObject)
{
	return UFunctions::GetScreenSize(WorldContextObject) / 2;
}

bool UFunctions::GetScreenCenterPointWorldLocationDirection(UObject* WorldContextObject, APlayerController* PlayerController, FVector& WorldLocation, FVector& WorldDirection)
{
	FVector2D Center = UFunctions::GetScreenCenterPoint(WorldContextObject);
	return PlayerController->DeprojectScreenPositionToWorld(Center.X, Center.Y, WorldLocation, WorldDirection);
}

bool UFunctions::IsLeftHalfScreen(UObject* WorldContextObject, const FVector2D& Location)
{
	FVector2D Center = UFunctions::GetScreenCenterPoint(WorldContextObject);
	return Location.X < Center.X;
}

bool UFunctions::IsTopHalfScreen(UObject* WorldContextObject, const FVector2D& Location)
{
	FVector2D Center = UFunctions::GetScreenCenterPoint(WorldContextObject);
	return Location.Y > Center.Y;
}
