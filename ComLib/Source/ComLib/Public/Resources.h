#pragma once
#include "Constants.h"

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/Texture2D.h"
#include "IImageWrapper.h"
#include "Resources.generated.h"
/**
 *
 */
UCLASS()
class COMLIB_API UResources : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "")
		static void CopyMessageToClipboard(FString text);

	UFUNCTION(BlueprintCallable, Category = "")
		static FString PasteMessageFromClipboard();

	UFUNCTION(BlueprintCallable, Category = "CB_Resources")
		static bool LoadFileToString(const FString& FileAbsolutePath, FString& Content);

	UFUNCTION(BlueprintCallable, Category = "CB_Resources")

		static bool SaveStringToFile(const FString& FileAbsolutePath, const FString& Content);
	UFUNCTION(BlueprintCallable, Category = "CB_Resources")
		static void FindFiles(const FString& Directory, TArray<FString>& Result, const FString& RegExp = "");

	UFUNCTION(BlueprintCallable, Category = "CB_Resources")
		static UTexture2D* LoadTexture2D(const FString& FilePath, bool& IsValid, int32& Width, int32& Height);
public:

	/** Is support image format **/
	static bool IsSupportImageResource(const FString& PathOrFilename);

	/** Create ImageWrapperPtr by file extention **/
	static TSharedPtr<IImageWrapper> CreateImageWrapperPtrByExtention(const FString& Path);

};