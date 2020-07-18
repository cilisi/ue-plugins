#include "PathFollowPrivatePCH.h"
#include "PFPath.h"
#include "Components/PFPathComponent.h"


APFPath::APFPath()
{
	PrimaryActorTick.bCanEverTick = false;
	PathToFollow = CreateDefaultSubobject<UPFPathComponent>(TEXT("PathToFollow"));
	RootComponent = PathToFollow;
	SetHidden(true);
}
