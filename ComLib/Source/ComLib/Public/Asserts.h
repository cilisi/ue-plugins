#pragma once

#include "CoreMinimal.h"
#include "KIsmet/BlueprintFunctionLibrary.h"
#include "Asserts.generated.h"

/**
 *
 */
UCLASS()
class COMLIB_API UAsserts : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "CB_Asserts")
		static bool IsInRange_int32(int32 Test, int32 Min, int32 Max, bool IsMinCloesd = true, bool IsMaxCloesed = false);

	UFUNCTION(BlueprintPure, Category = "CB_Asserts")
		static bool IsInRange_int64(int64 Test, int64 Min, int64 Max, bool IsMinCloesd = true, bool IsMaxCloesed = false);

	UFUNCTION(BlueprintPure, Category = "CB_Asserts")
		static bool IsInRange_float(float Test, float Min, float Max, bool IsMinCloesd, bool IsMaxCloesed);

	UFUNCTION(BlueprintPure, Category = "CB_Valid")
		static int32 ValidRange_int32(int32 Test, int32 Min, int32 Max, int32 Default, bool IsMinCloesd = true, bool IsMaxCloesed = false);

	UFUNCTION(BlueprintPure, Category = "CB_Valid")
		static int64 ValidRange_int64(int64 Test, int64 Min, int64 Max, int64 Default, bool IsMinCloesd = true, bool IsMaxCloesed = false);

	UFUNCTION(BlueprintPure, Category = "CB_Valid")
		static float ValidRange_float(float Test, float Min, float Max, float Default, bool IsMinCloesd, bool IsMaxCloesed);

};

