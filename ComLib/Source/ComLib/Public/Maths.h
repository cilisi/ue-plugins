#pragma once
#include "Constants.h"

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Maths.generated.h"

/** PI/180 **/
#define DEGREE_TO_RADIAN (0.017453292519943296f);

UENUM(BlueprintType)
enum class EArithmeticOperatorType :uint8
{
	PLUS UMETA(DisplayName = "+"),
	MINUS UMETA(DisplayName = "-"),
	MUL UMETA(DisplayName = "*"),
	DIV UMETA(DisplayName = "/"),
};
UENUM(BlueprintType)
enum class EDirection :uint8
{
	DEFAULT UMETA(DisplayName = "Default"),
	INWARD UMETA(DisplayName = "Inward"),
	OUTWARD UMETA(DisplayName = "Outward"),
};
/**
 *
 */
UCLASS()
class COMLIB_API UMaths : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "CB_Maths|Shaps")
		/** Generate per point of shape of solid square on 2d flat **/
		static TArray<FTransform> GenerateSolidSquarePointOn2DFlat(const FTransform& CenterPointTemplate, const int32 EdgeVertexAmount, const float Interval);

	UFUNCTION(BlueprintCallable, Category = "CB_Maths|Shaps")
		/** Generate per point of shape of hollow square on 2d flat **/
		static TArray<FTransform> GenerateHollowSquarePointOn2DFlat(const FTransform& CenterPointTemplate, const int32 EdgeVertexAmount, const float Interval, const EDirection Direction = EDirection::DEFAULT);

	UFUNCTION(BlueprintCallable, Category = "CB_Maths|Shaps")
		/** Generate per point of shape of hollow circle on 2d flat **/
		static TArray<FTransform> GeneratePliesHollowCirclePointOn2DFlat(const FTransform& CenterPointTemplate, const int32 Plies, const int32 PliesVertexAmount, const float Radius, const EDirection Direction = EDirection::DEFAULT);

	UFUNCTION(BlueprintCallable, Category = "CB_Maths|Shaps")
		/** Generate per point of shape of hollow circle on 2d flat **/
		static TArray<FTransform> GenerateHollowCirclePointOn2DFlat(const FTransform& CenterPointTemplate, const int32 VertexAmount, const float Radius, const EDirection Direction = EDirection::DEFAULT);

	//FVector

	UFUNCTION(BlueprintPure, Category = "CB_Maths|Vectors")
		/** Calculate unit vecotr with the distance sum is 1 **/
		static float CalculateDistanceLength(const FVector& Head, const FVector& Tail = FVector::ZeroVector, const float Scale = 1.f);

	UFUNCTION(BlueprintPure, Category = "CB_Maths|Vectors")
		/** Calculate unit vecotr with the distance sum is 1 **/
		static FVector CalculateUnitVector(const FVector& Head, const FVector& Tail = FVector::ZeroVector);

	UFUNCTION(BlueprintPure, Category = "CB_Maths|Vectors")
		/** Calculate liner end from start point with direction of several times **/
		static FVector CalculateLinearEnd(const FVector& Start, const FVector& Direction, const float Length);

	UFUNCTION(BlueprintPure, Category = "CB_Maths|Vectors")
		/** Arithmetic for Vector **/
		static FVector OperateVector(const FVector& Vector, const float& value, const EAxis::Type Axis, const EArithmeticOperatorType SimpleOperator);

	UFUNCTION(BlueprintPure, Category = "CB_Maths|Vectors")
		/** set axis value **/
		static FVector SetAxisValue(const FVector& Vector, const EAxis::Type Axis, const float value);

	UFUNCTION(BlueprintPure, Category = "CB_Maths|Vectors")
		/** remove axis value and set 0 **/
		static FVector RemoveAxis(const FVector& Vector, const EAxis::Type RemoveAxis);

	UFUNCTION(BlueprintPure, Category = "CB_Maths|Vectors")
		/** remove axis value and set 0 except assgin axis **/
		static FVector RemainAxis(const FVector& Vector, const EAxis::Type RemainAxis);

	UFUNCTION(BlueprintPure, Category = "CB_Maths|Vectors")
		/** Calculate new location by location and direction with size for specified Surface that Z is XY surface,Y is XZ surface and X is YZ surface **/
		static FVector CalculateLocationOnSurface(const FVector& Location, const FVector& Direction, const EAxis::Type Surface);

	UFUNCTION(BlueprintPure, Category = "CB_Maths|Vectors")
		/** Calculate direction by location with origin and target for specified Surface that Z is XY surface,Y is XZ surface and X is YZ surface **/
		static FVector CalculateDirectionOnSurface(const FVector& OriginLocation, const FVector& TargetLocation, const EAxis::Type Surface);

	//FVector2D

	UFUNCTION(BlueprintPure, Category = "CB_Maths|Vectors")
		/** Calculate unit Vector2D with the distance sum is 1 **/
		static FVector2D CalculateUnitVector2D(const FVector2D& Head, const FVector2D& Tail = FVector2D(0.f, 0.f));

	UFUNCTION(BlueprintPure, Category = "CB_Maths|Vectors")
		/** Calculate liner end from start point with direction of several times **/
		static FVector2D CalculateLinearEnd2D(const FVector2D& Start, const FVector2D& Direction, const float Length);

	UFUNCTION(BlueprintPure, Category = "CB_Maths|Vectors")
		/** Arithmetic for Vector2D **/
		static FVector2D OperateVector2D(const FVector2D& Vector2D, const float value, const EAxis::Type Axis, const EArithmeticOperatorType SimpleOperator);

	UFUNCTION(BlueprintPure, Category = "CB_Maths|Vectors")
		/** set axis value **/
		static FVector2D SetAxisValue2D(const FVector2D& Vector2D, const EAxis::Type Axis, const float value);

	UFUNCTION(BlueprintPure, Category = "CB_Maths|Vectors")
		/** remove axis value and set 0 **/
		static FVector2D RemoveAxis2D(const FVector2D& Vector2D, const EAxis::Type RemoveAxis);

	UFUNCTION(BlueprintPure, Category = "CB_Maths|Vectors")
		/** remove axis value and set 0 except assgin axis **/
		static FVector2D RemainAxis2D(const FVector2D& Vector2D, const EAxis::Type RemainAxis);

	//FRotator
	UFUNCTION(BlueprintPure, Category = "CB_Maths|Vectors")
		/** Arithmetic for Rotator **/
		static FRotator OperateRotator(const FRotator& Vector, const float value, const EAxis::Type Axis, const EArithmeticOperatorType SimpleOperator);

	UFUNCTION(BlueprintPure, Category = "CB_Maths|Rotators")
		/** set rotator axis value **/
		static FRotator SetRotatorAxisValue(const FRotator& Rotator, const EAxis::Type Axis, const float value);

	UFUNCTION(BlueprintPure, Category = "CB_Maths|Rotators")
		/** remove rotator axis value and set 0 **/
		static FRotator RemoveRotatorAxis(const FRotator& Rotator, const EAxis::Type RemoveRotatorAxis);

	UFUNCTION(BlueprintPure, Category = "CB_Maths|Rotators")
		/** remove rotator axis value and set 0 except assgin axis **/
		static FRotator RemainRotatorAxis(const FRotator& Rotator, const EAxis::Type RemainRotatorAxis);

	UFUNCTION(BlueprintPure, Category = "CB_Maths|Rotators")
		/** reverse rotator axis with 180 **/
		static FRotator ReverseRotator(const FRotator& Rotator, const EAxis::Type RotatorAxis);

	UFUNCTION(BlueprintPure, Category = "CB_Maths|Rotators")
		/** reverse rotator axis with angle **/
		static FRotator RotateRotator(const FRotator& Rotator, const EAxis::Type RotatorAxis, float Angle);

	UFUNCTION(BlueprintPure, Category = "CB_Functions")
		/** Resolve rotator as forward,right and up vector **/
		static void ResolveRotator(const FRotator& Rotator, FVector& Forward, FVector& Right, FVector& Up);

	UFUNCTION(BlueprintPure, Category = "CB_Maths|Rotators")
		/** Calculate new rotator by Coefficient for specified Surface that Z is XY surface,Y is XZ surface and X is YZ surface **/
		static FRotator CalculateRotatorOnSurface(const FRotator& Rotator, const EAxis::Type Surface, const float Coefficient, FVector& Forward, FVector& Right, FVector& Up);

	UFUNCTION(BlueprintPure, Category = "CB_Maths|Transforms")
		/** Calculate transform where face to it on suitable place **/
		static FTransform CalculateTransformBySuitableFaceToFace(const FTransform& Transform, const EAxis::Type Surface, const float Distance);

	UFUNCTION(BlueprintPure, Category = "CB_Maths|Transforms")
		/** Calculate transform of display **/
		static void CalculateDisplayTransform(const FTransform& Transform, const float Distance, const float AbsoluteOrRelativeHeight, FTransform& Absolute, FTransform& Relative);
};
