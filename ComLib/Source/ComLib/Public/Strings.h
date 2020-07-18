#pragma once

#include "Constants.h"
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Strings.generated.h"

/**
 *
 */
UCLASS()
class COMLIB_API UStrings : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "CB_Strings")
		/*Find first index from prefix array with string compare*/
		static int FindFirstPrefixFromStrings(const TArray<FString>& Preifxs, const FString& String, const ESearchCase::Type Case = ESearchCase::Type::IgnoreCase);

	UFUNCTION(BlueprintPure, Category = "CB_Strings")
		/*Find first index from string array with prefix compare*/
		static int FindFirstStringFromPrefixs(const TArray<FString>& Strings, const FString& Preifx, const ESearchCase::Type Case = ESearchCase::Type::IgnoreCase);

	UFUNCTION(BlueprintPure, Category = "CB_Strings")
		/*Find first index from suffixs array with string compare*/
		static int FindFirstSuffixFromStrings(const TArray<FString>& Suffixs, const FString& String, const ESearchCase::Type Case = ESearchCase::Type::IgnoreCase);

	UFUNCTION(BlueprintPure, Category = "CB_Strings")
		/*Find first index from suffix array with string compare*/
		static int FindFirstStringFromSuffixs(const TArray<FString>& Strings, const FString& Suffix, const ESearchCase::Type Case = ESearchCase::Type::IgnoreCase);

	UFUNCTION(BlueprintPure, Category = "CB_Strings")
		/*Find first index from suffix array with string compare*/
		static int FindFirstSubstringFromStrings(const TArray<FString>& Substrings, const FString& String, const ESearchCase::Type Case = ESearchCase::Type::IgnoreCase);

	UFUNCTION(BlueprintPure, Category = "CB_Strings")
		/*Find first index from substring array with string compare*/
		static int FindFirstStringFromSubstrings(const TArray<FString>& Strings, const FString& Substring, const ESearchCase::Type Case = ESearchCase::Type::IgnoreCase);

	UFUNCTION(BlueprintPure, Category = "CB_Strings")
		static bool IsExistPrefixFromStrings(const TArray<FString>& Preifxs, const FString& String, const ESearchCase::Type Case = ESearchCase::Type::IgnoreCase);

	UFUNCTION(BlueprintPure, Category = "CB_Strings")
		static bool IsExistStringFromPrefixs(const TArray<FString>& Strings, const FString& Preifx, const ESearchCase::Type Case = ESearchCase::Type::IgnoreCase);

	UFUNCTION(BlueprintPure, Category = "CB_Strings")
		static bool IsExistSuffixFromStrings(const TArray<FString>& Suffixs, const FString& String, const ESearchCase::Type Case = ESearchCase::Type::IgnoreCase);

	UFUNCTION(BlueprintPure, Category = "CB_Strings")
		static bool IsExistStringFromSuffixs(const TArray<FString>& Strings, const FString& Suffix, const ESearchCase::Type Case = ESearchCase::Type::IgnoreCase);

	UFUNCTION(BlueprintPure, Category = "CB_Strings")
		static bool IsExistSubstringFromStrings(const TArray<FString>& Substrings, const FString& String, const ESearchCase::Type Case = ESearchCase::Type::IgnoreCase);

	UFUNCTION(BlueprintPure, Category = "CB_Strings")
		static bool IsExistStringFromSubstrings(const TArray<FString>& Strings, const FString& Substring, const ESearchCase::Type Case = ESearchCase::Type::IgnoreCase);

	UFUNCTION(BlueprintPure, Category = "CB_Strings")
		static FString TrimString(const FString& String, const FString& Prefix = "", const FString& Suffix = "", const ESearchCase::Type Case = ESearchCase::Type::IgnoreCase);

	UFUNCTION(BlueprintPure, Category = "CB_Strings")
		static FString TrimPathString(const FString& PathString, bool HasStartSlash = false);

	UFUNCTION(BlueprintPure, Category = "CB_Strings")
		static FString ConvertToSlash(const FString& String, const FString& Prefix = "", const FString& Suffix = "", const bool IsUpperCase = true);

	UFUNCTION(BlueprintPure, Category = "CB_Strings")
		static FString ConvertToCamel(const FString& String, const bool IsHeadUpperCase = true);
public:
	static bool IsLetter(const TCHAR& Char);
	static bool IsNumber(const TCHAR& Char);
	static bool IsAllowedProgrammeChar(const TCHAR& Char);
	static bool IsUpperCase(const TCHAR& Char);
	static bool IsoLowerCase(const TCHAR& Char);
	static TCHAR ToUpperCase(const TCHAR& Char);
	static TCHAR ToLowerCase(const TCHAR& Char);
	static FString HeadUpperCase(const FString& String);
	static FString HeadLowerCase(const FString& String);
};
