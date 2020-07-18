#pragma once
#include "Constants.h"
#include "Strings.h"

#include "CoreMinimal.h"
#include "EngineMinimal.h"
#include "Engine/Engine.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameFramework/PlayerController.h"
#include "Misc/Paths.h"
#include "Globals.generated.h"

UENUM(BlueprintType)
enum class EPathType :uint8
{
	ROOT UMETA(DispalyName = "Engine Or Package Path"),
	PROJECT UMETA(DispalyName = "Project Path"),
	PROJECT_CONTENT UMETA(DispalyName = "Project Content Path"),
	PROJECT_CONFIG UMETA(DispalyName = "Project Config Path"),
};

/**
 *
 */
UCLASS()
class COMLIB_API UGlobals : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "CB_Globals")
		static FString GetImportantDir(const EPathType PathType);

	UFUNCTION(BlueprintPure, Category = "CB_Globals")
		static FString MakePathInImportantDir(const EPathType PathType, const FString& Segment);

	UFUNCTION(BlueprintCallable, Category = "CB_Globals")
		static void Debug(FString Message, float Duration = 0.f);
};
