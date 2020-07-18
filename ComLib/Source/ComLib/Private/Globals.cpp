#include "Globals.h"


FString UGlobals::GetImportantDir(const EPathType PathType)
{
	FString Result;
	switch (PathType)
	{
	case EPathType::ROOT:
	{
		Result = FPaths::RootDir();
		break;
	}
	case EPathType::PROJECT:
	{
		Result = FPaths::ProjectDir();
		break;
	}
	case EPathType::PROJECT_CONTENT:
	{
		Result = FPaths::ProjectContentDir();
		break;
	}
	case EPathType::PROJECT_CONFIG:
	{
		Result = FPaths::ProjectConfigDir();
		break;
	}
	default:
		break;
	}
	return FPaths::ConvertRelativePathToFull(Result);
}

FString UGlobals::MakePathInImportantDir(const EPathType PathType, const FString& Segment)
{
	FString Result = UGlobals::GetImportantDir(PathType);
	FString Temp = Segment;
	if (Temp.Len() > 0)
	{
		return Result + UStrings::TrimPathString(Segment);
	}
	return Result;
}

void UGlobals::Debug(FString Message, float Duration)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Duration, FColor::Yellow, Message);
	}
}
