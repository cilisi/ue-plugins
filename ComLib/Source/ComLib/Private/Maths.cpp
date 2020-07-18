#include "Maths.h"
#include "Kismet/KismetMathLibrary.h"

TArray<FTransform> UMaths::GenerateSolidSquarePointOn2DFlat(const FTransform& CenterPointTemplate, const int32 EdgeVertexAmount, const float Interval)
{
	FVector CenterPoint = CenterPointTemplate.GetLocation();
	TArray<FTransform> Points;
	float HalfEdgeLength = (EdgeVertexAmount - 1) * Interval / 2;
	for (size_t i = 0; i < EdgeVertexAmount; i++)//y
	{
		for (size_t j = 0; j < EdgeVertexAmount; j++)//x
		{
			float NewX = CenterPoint.X + j * Interval - HalfEdgeLength;
			float NewY = CenterPoint.Y + i * Interval - HalfEdgeLength;
			FVector NewLocation = FVector(NewX, NewY, CenterPoint.Z);
			FTransform NewTransform = FTransform(CenterPointTemplate);
			NewTransform.SetLocation(NewLocation);
			Points.Add(NewTransform);
		}
	}
	return Points;
}

TArray<FTransform> UMaths::GenerateHollowSquarePointOn2DFlat(const FTransform& CenterPointTemplate, const int32 EdgeVertexAmount, const float Interval, const EDirection Direction)
{
	FVector CenterPoint = CenterPointTemplate.GetLocation();
	TArray<FTransform> Points;
	int32 MaxIndex = EdgeVertexAmount - 1;
	float HalfEdgeLength = MaxIndex * Interval / 2;
	for (size_t i = 0; i < EdgeVertexAmount; i++)//y
	{
		for (size_t j = 0; j < EdgeVertexAmount; j++)//x
		{
			if (i == 0 || j == 0 || i == MaxIndex || j == MaxIndex) {
				float NewX = CenterPoint.X + j * Interval - HalfEdgeLength;
				float NewY = CenterPoint.Y + i * Interval - HalfEdgeLength;
				FVector NewLocation = FVector(NewX, NewY, CenterPoint.Z);
				FTransform NewTransform = FTransform(CenterPointTemplate);
				NewTransform.SetLocation(NewLocation);
				FRotator Rotator = NewTransform.GetRotation().Rotator();
				switch (Direction)
				{
				case EDirection::INWARD:
				{
					FRotator NewRotator(Rotator);
					if (i == 0)
					{
						if (j == 0)
						{
							NewRotator = UMaths::RotateRotator(Rotator, EAxis::Type::Z, 225.f);
						}
						else if (j == MaxIndex)
						{
							NewRotator = UMaths::RotateRotator(Rotator, EAxis::Type::Z, 315.f);
						}
						else
						{
							//No Ratate
						}
					}
					else if (i == MaxIndex)
					{
						if (j == 0)
						{
							NewRotator = UMaths::RotateRotator(Rotator, EAxis::Type::Z, 135.f);
						}
						else if (j == MaxIndex)
						{
							NewRotator = UMaths::RotateRotator(Rotator, EAxis::Type::Z, 45.f);
						}
						else
						{
							NewRotator = UMaths::RotateRotator(Rotator, EAxis::Type::Z, 180.f);
						}
					}
					else if (j == 0)
					{
						NewRotator = UMaths::RotateRotator(Rotator, EAxis::Type::Z, 270.f);
					}
					else if (i == MaxIndex)
					{
						NewRotator = UMaths::RotateRotator(Rotator, EAxis::Type::Z, 90.f);
					}
					NewTransform.SetRotation(FQuat(NewRotator));
					break;
				}
				case EDirection::OUTWARD:
				{
					FRotator NewRotator(Rotator);
					if (i == 0)
					{
						if (j == 0)
						{
							NewRotator = UMaths::RotateRotator(Rotator, EAxis::Type::Z, 45.f);
						}
						else if (j == MaxIndex)
						{
							NewRotator = UMaths::RotateRotator(Rotator, EAxis::Type::Z, 135.f);
						}
						else
						{
							NewRotator = UMaths::RotateRotator(Rotator, EAxis::Type::Z, 180.f);
						}
					}
					else if (i == MaxIndex)
					{
						if (j == 0)
						{
							NewRotator = UMaths::RotateRotator(Rotator, EAxis::Type::Z, 315.f);
						}
						else if (j == MaxIndex)
						{
							NewRotator = UMaths::RotateRotator(Rotator, EAxis::Type::Z, 225.f);
						}
						else
						{
							//No Ratate
						}
					}
					else if (j == 0)
					{
						NewRotator = UMaths::RotateRotator(Rotator, EAxis::Type::Z, 90.f);
					}
					else if (i == MaxIndex)
					{
						NewRotator = UMaths::RotateRotator(Rotator, EAxis::Type::Z, 270.f);
					}
					NewTransform.SetRotation(FQuat(NewRotator));
					break;
				}
				default:
					break;
				}
				Points.Add(NewTransform);
			}
		}
	}
	return Points;
}

TArray<FTransform> UMaths::GeneratePliesHollowCirclePointOn2DFlat(const FTransform& CenterPointTemplate, const int32 Plies, const int32 PliesVertexAmount, const float Radius, const EDirection Direction)
{
	FVector CenterPoint = CenterPointTemplate.GetLocation();
	TArray<FTransform> Points;
	Points.Add(FTransform(CenterPointTemplate));
	float Interval = 360.f / PliesVertexAmount * DEGREE_TO_RADIAN;
	for (size_t n = 1; n <= Plies; n++)
	{
		float R = Radius * n;
		TArray<FTransform> TempPoints = UMaths::GenerateHollowCirclePointOn2DFlat(CenterPointTemplate, PliesVertexAmount, R, Direction);
		Points.Append(TempPoints);
	}
	return Points;
}

TArray<FTransform> UMaths::GenerateHollowCirclePointOn2DFlat(const FTransform& CenterPointTemplate, const int32 VertexAmount, const float Radius, const EDirection Direction)
{
	FVector CenterPoint = CenterPointTemplate.GetLocation();
	TArray<FTransform> Points;
	float Interval = 360.f / VertexAmount;
	for (size_t i = 0; i < VertexAmount; i++)
	{
		float Degree = Interval * i;
		float Radian = Degree * DEGREE_TO_RADIAN;
		float NewX = CenterPoint.X + Radius * UKismetMathLibrary::Cos(Radian);
		float NewY = CenterPoint.Y + Radius * UKismetMathLibrary::Sin(Radian);
		FVector NewLocation = FVector(NewX, NewY, CenterPoint.Z);
		FTransform NewTransform = FTransform(CenterPointTemplate);
		NewTransform.SetLocation(NewLocation);
		FRotator Rotator = NewTransform.GetRotation().Rotator();
		switch (Direction)
		{
		case EDirection::INWARD:
		{
			float NewDegree = 90.f + Degree;
			FRotator NewRotator = UMaths::RotateRotator(Rotator, EAxis::Type::Z, -NewDegree);
			NewTransform.SetRotation(FQuat(NewRotator));
			break;
		}
		case EDirection::OUTWARD:
		{
			float NewDegree = 90.f - Degree;
			FRotator NewRotator = UMaths::RotateRotator(Rotator, EAxis::Type::Z, -NewDegree);
			NewTransform.SetRotation(FQuat(NewRotator));
			break;
		}
		default:
			break;
		}
		Points.Add(NewTransform);
	}
	return Points;
}

//FVector
float UMaths::CalculateDistanceLength(const FVector& Head, const FVector& Tail, const float Scale)
{
	const float Quadratic = 2.f;
	FVector Vector = Head - Tail;
	float QuadraticSum = powf(Vector.X, Quadratic) + powf(Vector.Y, Quadratic) + powf(Vector.Z, Quadratic);
	return sqrtf(QuadraticSum) * Scale;
}
FVector UMaths::CalculateUnitVector(const FVector& Head, const FVector& Tail)
{
	FVector Vector = Head - Tail;
	float Distance = UMaths::CalculateDistanceLength(Vector);
	Vector.X /= Distance;
	Vector.Y /= Distance;
	Vector.Z /= Distance;
	return Vector;
}
FVector UMaths::CalculateLinearEnd(const FVector& Start, const FVector& Direction, const float Length)
{
	FVector Result;
	if (Length != 0) {
		FVector Vector = Direction * Length;
		Result = Start + Vector;
	}
	return Result;
}
FVector UMaths::OperateVector(const FVector& Vector, const float& value, const EAxis::Type Axis, const EArithmeticOperatorType SimpleOperator)
{
	FVector Result(Vector);
	switch (SimpleOperator)
	{
	case EArithmeticOperatorType::PLUS:
	{
		switch (Axis)
		{
		case EAxis::Type::X:
		{
			Result.X += value;
			break;
		}
		case EAxis::Type::Y:
		{
			Result.Y += value;
			break;
		}
		case EAxis::Type::Z:
		{
			Result.Z += value;
			break;
		}
		default:
			break;
		}
	}
	case EArithmeticOperatorType::MINUS:
	{
		switch (Axis)
		{
		case EAxis::Type::X:
		{
			Result.X -= value;
			break;
		}
		case EAxis::Type::Y:
		{
			Result.Y -= value;
			break;
		}
		case EAxis::Type::Z:
		{
			Result.Z -= value;
			break;
		}
		default:
			break;
		}
	}
	case EArithmeticOperatorType::MUL:
	{
		switch (Axis)
		{
		case EAxis::Type::X:
		{
			Result.X *= value;
			break;
		}
		case EAxis::Type::Y:
		{
			Result.Y *= value;
			break;
		}
		case EAxis::Type::Z:
		{
			Result.Z *= value;
			break;
		}
		default:
			break;
		}
	}
	case EArithmeticOperatorType::DIV:
	{
		switch (Axis)
		{
		case EAxis::Type::X:
		{
			Result.X /= value;
			break;
		}
		case EAxis::Type::Y:
		{
			Result.Y /= value;
			break;
		}
		case EAxis::Type::Z:
		{
			Result.Z /= value;
			break;
		}
		default:
			break;
		}
	}
	default:
		break;
	}
	return Result;
}
FVector UMaths::SetAxisValue(const FVector& Vector, const EAxis::Type Axis, const float value)
{
	FVector Result(Vector);
	if (&Axis != nullptr)
	{
		switch (Axis)
		{
		case EAxis::Type::X:
		{
			Result.X = value;
			break;
		}
		case EAxis::Type::Y:
		{
			Result.Y = value;
			break;
		}
		case EAxis::Type::Z:
		{
			Result.Z = value;
			break;
		}
		default:
			break;
		}
	}
	return Result;
}
FVector UMaths::RemoveAxis(const FVector& Vector, const EAxis::Type RemoveAxis)
{
	return UMaths::SetAxisValue(Vector, RemoveAxis, CB_ZERO_F);
}
FVector UMaths::RemainAxis(const FVector& Vector, const EAxis::Type RemainAxis)
{
	FVector Result;
	if (&RemainAxis != nullptr)
	{
		switch (RemainAxis)
		{
		case EAxis::Type::X:
		{
			Result.X = Vector.X;
			break;
		}
		case EAxis::Type::Y:
		{
			Result.Y = Vector.Y;
			break;
		}
		case EAxis::Type::Z:
		{
			Result.Z = Vector.Z;
			break;
		}
		default:
			break;
		}
	}
	Result = Vector;
	return Result;
}
FVector UMaths::CalculateLocationOnSurface(const FVector& Location, const FVector& Direction, const EAxis::Type Surface)
{
	return Location + UMaths::RemoveAxis(Direction, Surface);
}
FVector UMaths::CalculateDirectionOnSurface(const FVector& OriginLocation, const FVector& TargetLocation, const  EAxis::Type Surface)
{
	return UMaths::CalculateUnitVector(UMaths::RemoveAxis(TargetLocation, Surface), UMaths::RemoveAxis(OriginLocation, Surface));
}
//FVector2D
FVector2D UMaths::CalculateUnitVector2D(const FVector2D& Head, const FVector2D& Tail)
{
	const float Quadratic = 2.f;
	FVector2D Vector2D = Head - Tail;
	float QuadraticSum = powf(Vector2D.X, Quadratic) + powf(Vector2D.Y, Quadratic);
	float Distance = sqrtf(QuadraticSum);
	Vector2D.X /= Distance;
	Vector2D.Y /= Distance;
	return Vector2D;
}
FVector2D UMaths::CalculateLinearEnd2D(const FVector2D& Start, const FVector2D& Direction, const float Length)
{
	FVector2D Result;
	if (Length != 0) {
		FVector2D Vector2D = Direction * Length;
		Result = Start + Vector2D;
	}
	return Result;
}
FVector2D UMaths::OperateVector2D(const FVector2D& Vector2D, const float value, const EAxis::Type Axis, const EArithmeticOperatorType SimpleOperator)
{
	FVector2D Result(Vector2D);
	switch (SimpleOperator)
	{
	case EArithmeticOperatorType::PLUS:
	{
		switch (Axis)
		{
		case EAxis::Type::X:
		{
			Result.X += value;
			break;
		}
		case EAxis::Type::Y:
		{
			Result.Y += value;
			break;
		}
		default:
			break;
		}
	}
	case EArithmeticOperatorType::MINUS:
	{
		switch (Axis)
		{
		case EAxis::Type::X:
		{
			Result.X -= value;
			break;
		}
		case EAxis::Type::Y:
		{
			Result.Y -= value;
			break;
		}
		default:
			break;
		}
	}
	case EArithmeticOperatorType::MUL:
	{
		switch (Axis)
		{
		case EAxis::Type::X:
		{
			Result.X *= value;
			break;
		}
		case EAxis::Type::Y:
		{
			Result.Y *= value;
			break;
		}
		default:
			break;
		}
	}
	case EArithmeticOperatorType::DIV:
	{
		switch (Axis)
		{
		case EAxis::Type::X:
		{
			Result.X /= value;
			break;
		}
		case EAxis::Type::Y:
		{
			Result.Y /= value;
			break;
		}
		default:
			break;
		}
	}
	default:
		break;
	}
	return Result;
}
FVector2D UMaths::SetAxisValue2D(const FVector2D& Vector2D, const EAxis::Type Axis, const float value)
{
	FVector2D Result(Vector2D);
	if (&Axis != nullptr)
	{
		switch (Axis)
		{
		case EAxis::Type::X:
		{
			Result.X = value;
			break;
		}
		case EAxis::Type::Y:
		{
			Result.Y = value;
			break;
		}
		default:
			break;
		}
	}
	return Result;
}
FVector2D UMaths::RemoveAxis2D(const FVector2D& Vector2D, const EAxis::Type RemoveAxis)
{
	return UMaths::SetAxisValue2D(Vector2D, RemoveAxis, CB_ZERO_F);
}
FVector2D UMaths::RemainAxis2D(const FVector2D& Vector2D, const EAxis::Type RemainAxis)
{
	FVector2D Result;
	if (&RemainAxis != nullptr)
	{
		switch (RemainAxis)
		{
		case EAxis::Type::X:
		{
			Result.X = Vector2D.X;
			break;
		}
		case EAxis::Type::Y:
		{
			Result.Y = Vector2D.Y;
			break;
		}
		default:
			break;
		}
	}
	Result = Vector2D;
	return Result;
}
//FRotator
FRotator UMaths::OperateRotator(const FRotator& Rotator, const float value, const EAxis::Type Axis, const EArithmeticOperatorType SimpleOperator)
{
	FRotator Result(Rotator);
	switch (SimpleOperator)
	{
	case EArithmeticOperatorType::PLUS:
	{
		switch (Axis)
		{
		case EAxis::Type::X:
		{
			Result.Roll += value;
			break;
		}
		case EAxis::Type::Y:
		{
			Result.Pitch += value;
			break;
		}
		case EAxis::Type::Z:
		{
			Result.Yaw += value;
			break;
		}
		default:
			break;
		}
	}
	case EArithmeticOperatorType::MINUS:
	{
		switch (Axis)
		{
		case EAxis::Type::X:
		{
			Result.Roll -= value;
			break;
		}
		case EAxis::Type::Y:
		{
			Result.Pitch -= value;
			break;
		}
		case EAxis::Type::Z:
		{
			Result.Yaw -= value;
			break;
		}
		default:
			break;
		}
	}
	case EArithmeticOperatorType::MUL:
	{
		switch (Axis)
		{
		case EAxis::Type::X:
		{
			Result.Roll *= value;
			break;
		}
		case EAxis::Type::Y:
		{
			Result.Pitch *= value;
			break;
		}
		case EAxis::Type::Z:
		{
			Result.Yaw *= value;
			break;
		}
		default:
			break;
		}
	}
	case EArithmeticOperatorType::DIV:
	{
		switch (Axis)
		{
		case EAxis::Type::X:
		{
			Result.Roll /= value;
			break;
		}
		case EAxis::Type::Y:
		{
			Result.Pitch /= value;
			break;
		}
		case EAxis::Type::Z:
		{
			Result.Yaw /= value;
			break;
		}
		default:
			break;
		}
	}
	default:
		break;
	}
	return Result;
}
FRotator UMaths::SetRotatorAxisValue(const FRotator& Rotator, const EAxis::Type Axis, const float value)
{
	FRotator Result(Rotator);
	if (&Axis != nullptr)
	{
		switch (Axis)
		{
		case EAxis::Type::X:
		{
			Result.Roll = value;
			break;
		}
		case EAxis::Type::Y:
		{
			Result.Pitch = value;
			break;
		}
		case EAxis::Type::Z:
		{
			Result.Yaw = value;
			break;
		}
		default:
			break;
		}
	}
	return Result;
}
FRotator UMaths::RemoveRotatorAxis(const FRotator& Rotator, const EAxis::Type RemoveRotatorAxis)
{
	return UMaths::SetRotatorAxisValue(Rotator, RemoveRotatorAxis, CB_ZERO_F);
}
FRotator UMaths::RemainRotatorAxis(const FRotator& Rotator, const EAxis::Type RemainRotatorAxis)
{
	FRotator Result;
	if (&RemainRotatorAxis != nullptr)
	{
		switch (RemainRotatorAxis)
		{
		case EAxis::Type::X:
		{
			Result.Roll = Rotator.Roll;
			break;
		}
		case EAxis::Type::Y:
		{
			Result.Pitch = Rotator.Pitch;
			break;
		}
		case EAxis::Type::Z:
		{
			Result.Yaw = Rotator.Yaw;
			break;
		}
		default:
			break;
		}
	}
	Result = Rotator;
	return Result;
}
FRotator UMaths::ReverseRotator(const FRotator& Rotator, const EAxis::Type RotatorAxis)
{
	return UMaths::RotateRotator(Rotator, RotatorAxis, 180.f);
}
FRotator UMaths::RotateRotator(const FRotator& Rotator, const EAxis::Type RotatorAxis, float Angle)
{
	FRotator Result(Rotator);
	switch (RotatorAxis)
	{
	case EAxis::Type::X:
	{
		Result.Roll += Angle;
		break;
	}
	case EAxis::Type::Y:
	{
		Result.Pitch += Angle;
		break;
	}
	default:
		Result.Yaw += Angle;
		break;
	}
	return Result;
}
void UMaths::ResolveRotator(const FRotator& Rotator, FVector& Forward, FVector& Right, FVector& Up)
{
	Forward = UKismetMathLibrary::GetForwardVector(Rotator);
	Right = UKismetMathLibrary::GetRightVector(Rotator);
	Up = UKismetMathLibrary::GetUpVector(Rotator);
}
FRotator UMaths::CalculateRotatorOnSurface(const FRotator& Rotator, const EAxis::Type Surface, const float Coefficient, FVector& Forward, FVector& Right, FVector& Up)
{
	FRotator Result(Rotator);
	UMaths::RemainRotatorAxis(Result, Surface);
	UMaths::ResolveRotator(Result, Forward, Right, Up);
	Forward *= Coefficient;
	Right *= Coefficient;
	Up *= Coefficient;
	return Result;
}

//Transform
FTransform UMaths::CalculateTransformBySuitableFaceToFace(const FTransform& Transform, const EAxis::Type Surface, const float Distance)
{
	FVector Translation;
	FRotator Rotator;
	FVector Scale;
	UKismetMathLibrary::BreakTransform(Transform, Translation, Rotator, Scale);
	FRotator NewRotator = UMaths::ReverseRotator(UMaths::RemainRotatorAxis(Rotator, Surface), Surface);
	FVector Forward, Right, Up;
	UMaths::CalculateRotatorOnSurface(Rotator, Surface, Distance, Forward, Right, Up);
	FVector NewLocation = UMaths::CalculateLocationOnSurface(Transform.GetLocation(), Forward, Surface);
	return UKismetMathLibrary::MakeTransform(NewLocation, NewRotator, Scale);
}

void UMaths::CalculateDisplayTransform(const FTransform& Transform, const float Distance, const float AbsoluteOrRelativeHeight, FTransform& Absolute, FTransform& Relative)
{
	FTransform NewFransform = UMaths::CalculateTransformBySuitableFaceToFace(Transform, EAxis::Type::Z, Distance);
	FVector Location;
	FRotator Rotator;
	FVector Scale;
	UKismetMathLibrary::BreakTransform(NewFransform, Location, Rotator, Scale);
	FVector AbsoluteVector = UMaths::SetAxisValue(Location, EAxis::Type::Z, AbsoluteOrRelativeHeight);
	FVector RelativeVector = UMaths::SetAxisValue(
		UMaths::OperateVector(Location, AbsoluteOrRelativeHeight, EAxis::Type::Z, EArithmeticOperatorType::PLUS),
		EAxis::Type::Z,
		AbsoluteOrRelativeHeight);
	Absolute = UKismetMathLibrary::MakeTransform(AbsoluteVector, Rotator, Scale);
	Relative = UKismetMathLibrary::MakeTransform(RelativeVector, Rotator, Scale);
}