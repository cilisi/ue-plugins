#include "Resources.h"
#include "IImageWrapperModule.h"
#include "Misc/FileHelper.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformFilemanager.h"
#include "Modules/ModuleManager.h"
#include "Internationalization/Regex.h"
#include "Serialization/JsonSerializer.h"

#if PLATFORM_MAC
#include "Mac/MacPlatformApplicationMisc.h"
#elif PLATFORM_WINDOWS
#include "Windows/WindowsPlatformApplicationMisc.h"
#elif PLATFORM_LINUX
#include "Linux/LinuxPlatformApplicationMisc.h"
#elif PLATFORM_ANDROID
#include "Android/AndroidPlatformApplicationMisc.h"
#elif PLATFORM_IOS
#include "IOS/IOSPlatformApplicationMisc.h"
#endif 


void UResources::CopyMessageToClipboard(FString text)
{
	FPlatformApplicationMisc::ClipboardCopy(*text);
}

FString UResources::PasteMessageFromClipboard()
{
	FString ClipboardContent;
	FPlatformApplicationMisc::ClipboardPaste(ClipboardContent);
	return ClipboardContent;
}

bool UResources::LoadFileToString(const FString& FileAbsolutePath, FString& Content)
{
	return FFileHelper::LoadFileToString(Content, *FileAbsolutePath);
}

bool UResources::SaveStringToFile(const FString& FileAbsolutePath, const FString& Content)
{
	return FFileHelper::SaveStringToFile(Content, *FileAbsolutePath);
}

void UResources::FindFiles(const FString& Directory, TArray<FString>& Result, const FString& RegExp)
{
	TArray<FString> FoundFiles;
	IFileManager::Get().FindFiles(FoundFiles, *Directory);
	if (RegExp == "")
	{
		Result.Append(FoundFiles);
	}
	else
	{
		FString AbsolutePath = "";
		FRegexPattern Pattern(*RegExp);
		for (TArray<FString>::TConstIterator It = Result.CreateConstIterator();It;++It)
		{
			FRegexMatcher Matcher(Pattern, *It);
			Matcher.SetLimits(0, It->Len());
			if (Matcher.FindNext()) {
				AbsolutePath = Directory + *It;
				Result.Add(AbsolutePath);
			}
		}
	}
}
UTexture2D* UResources::LoadTexture2D(const FString& FilePath, bool& IsValid, int32& Width, int32& Height)
{
	bool IsCanReadData = UResources::IsSupportImageResource(FilePath) && IFileManager::Get().FileExists(*FilePath);
	//To do
	IsValid = false;
	Width = CB_ERROR;
	Height = CB_ERROR;
	return nullptr;
}
bool UResources::IsSupportImageResource(const FString& PathOrFilename) {
	TArray<FString> Array = Constants::SupportImageExtensionName();
	for (int32 i = 0;i < Array.Num();i++)
	{
		if (PathOrFilename.EndsWith(CB_FS_CONCAT(CB_S_DOT, Array[i])))
		{
			return true;
		}
	}
	return false;
}
TSharedPtr<IImageWrapper> UResources::CreateImageWrapperPtrByExtention(const FString& Path)
{
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));

	if (Path.EndsWith(CB_FS_CONCAT(CB_S_DOT, CB_S_IE_PNG)))
	{
		return ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);
	}
	else if (Path.EndsWith(CB_FS_CONCAT(CB_S_DOT, CB_S_IE_JPG)) || Path.EndsWith(CB_FS_CONCAT(CB_S_DOT, CB_S_IE_JPEG)))
	{
		return ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);
	}
	else if (Path.EndsWith(CB_FS_CONCAT(CB_S_DOT, CB_S_IE_BMP)))
	{
		return ImageWrapperModule.CreateImageWrapper(EImageFormat::BMP);
	}
	else if (Path.EndsWith(CB_FS_CONCAT(CB_S_DOT, CB_S_IE_ICO)))
	{
		return ImageWrapperModule.CreateImageWrapper(EImageFormat::ICO);
	}
	else if (Path.EndsWith(CB_FS_CONCAT(CB_S_DOT, CB_S_IE_EXR)))
	{
		return ImageWrapperModule.CreateImageWrapper(EImageFormat::EXR);
	}
	else if (Path.EndsWith(CB_FS_CONCAT(CB_S_DOT, CB_S_IE_ICNS)))
	{
		return ImageWrapperModule.CreateImageWrapper(EImageFormat::ICNS);
	}
	return nullptr;
}
