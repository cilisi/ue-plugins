#pragma once

#include "PFRollInterpType.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class  EPFRollInterpType : uint8
{
	Constant UMETA(DisplayName = "Constant"),
	Linear UMETA(DisplayName = "Linear"),
	LinearStable UMETA(DisplayName = "Linear Stable"),
	Cubic UMETA(DisplayName = "Cubic"),
	CubicClamped UMETA(DisplayName = "Cubic Clamped")
};
