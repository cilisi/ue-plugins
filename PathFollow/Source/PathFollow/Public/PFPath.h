#pragma once

#include "GameFramework/Actor.h"
#include "PFPath.generated.h"

UCLASS()
class PATHFOLLOW_API APFPath : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APFPath();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = PathFollow)
		class UPFPathComponent* PathToFollow;
};

