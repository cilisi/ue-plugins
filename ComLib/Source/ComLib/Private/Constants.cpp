#include "Constants.h"

TArray<FString> Constants::SupportImageExtensionName()
{
	TArray<FString> Instance;
	Instance.Add(CB_S_IE_PNG);
	Instance.Add(CB_S_IE_JPEG);
	Instance.Add(CB_S_IE_BMP);
	Instance.Add(CB_S_IE_ICO);
	Instance.Add(CB_S_IE_EXR);
	Instance.Add(CB_S_IE_ICNS);
	return Instance;
}