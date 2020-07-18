#include "Strings.h"

int UStrings::FindFirstPrefixFromStrings(const TArray<FString>& Preifxs, const FString& String, const ESearchCase::Type Case)
{
	int index = CB_EOF;
	auto Result = Preifxs.FindByPredicate([&](FString Preifx) {index++;return String.StartsWith(Preifx, Case);});
	return Result == nullptr ? CB_EOF : index;
}

int UStrings::FindFirstStringFromPrefixs(const TArray<FString>& Strings, const FString& Preifx, const ESearchCase::Type Case)
{
	int index = CB_EOF;
	auto Result = Strings.FindByPredicate([&](FString String) {index++;return String.StartsWith(Preifx, Case);});
	return Result == nullptr ? CB_EOF : index;
}

int UStrings::FindFirstSuffixFromStrings(const TArray<FString>& Suffixs, const FString& String, const ESearchCase::Type Case)
{
	int index = CB_EOF;
	auto Result = Suffixs.FindByPredicate([&](FString Suffix) {index++;return String.EndsWith(Suffix, Case);});
	return Result == nullptr ? CB_EOF : index;
}

int UStrings::FindFirstStringFromSuffixs(const TArray<FString>& Strings, const FString& Suffix, const ESearchCase::Type Case)
{
	int index = CB_EOF;
	auto Result = Strings.FindByPredicate([&](FString String) {index++;return String.EndsWith(Suffix, Case);});
	return Result == nullptr ? CB_EOF : index;
}

int UStrings::FindFirstSubstringFromStrings(const TArray<FString>& Substrings, const FString& String, const ESearchCase::Type Case)
{
	int index = CB_EOF;
	auto Result = Substrings.FindByPredicate([&](FString Substring) {index++;return String.Contains(Substring, Case);});
	return Result == nullptr ? CB_EOF : index;
}

int UStrings::FindFirstStringFromSubstrings(const TArray<FString>& Strings, const FString& Substring, const ESearchCase::Type Case)
{
	int index = CB_EOF;
	auto Result = Strings.FindByPredicate([&](FString String) {index++;return String.Contains(Substring, Case);});
	return Result == nullptr ? CB_EOF : index;
}

bool UStrings::IsExistPrefixFromStrings(const TArray<FString>& Preifxs, const FString& String, const ESearchCase::Type Case)
{
	return UStrings::FindFirstPrefixFromStrings(Preifxs, String, Case) != CB_EOF;
}

bool UStrings::IsExistStringFromPrefixs(const TArray<FString>& Strings, const FString& Preifx, const ESearchCase::Type Case)
{
	return UStrings::FindFirstStringFromPrefixs(Strings, Preifx, Case) != CB_EOF;
}

bool UStrings::IsExistSuffixFromStrings(const TArray<FString>& Suffixs, const FString& String, const ESearchCase::Type Case)
{
	return UStrings::FindFirstSuffixFromStrings(Suffixs, String, Case) != CB_EOF;
}

bool UStrings::IsExistStringFromSuffixs(const TArray<FString>& Strings, const FString& Suffix, const ESearchCase::Type Case)
{
	return UStrings::FindFirstStringFromSuffixs(Strings, Suffix, Case) != CB_EOF;
}

bool UStrings::IsExistSubstringFromStrings(const TArray<FString>& Substrings, const FString& String, const ESearchCase::Type Case)
{
	return UStrings::FindFirstSubstringFromStrings(Substrings, String, Case) != CB_EOF;
}

bool UStrings::IsExistStringFromSubstrings(const TArray<FString>& Strings, const FString& Substring, const ESearchCase::Type Case)
{
	return UStrings::FindFirstStringFromSubstrings(Strings, Substring, Case) != CB_EOF;
}

FString UStrings::TrimString(const FString& String, const FString& Prefix, const FString& Suffix, const ESearchCase::Type Case)
{
	FString Result = String.TrimStartAndEnd();
	if (Prefix.Len() != 0) {
		while (Result.StartsWith(Prefix, Case))
		{
			Result = Result.RightChop(Prefix.Len());
		}
	}
	if (Suffix.Len() != 0)
	{
		while (Result.EndsWith(Suffix, Case))
		{
			Result = Result.LeftChop(Suffix.Len());
		}
	}
	return Result;
}

FString UStrings::TrimPathString(const FString& PathString, bool HasStartSlash)
{
	FString Result = PathString;
	Result = UStrings::TrimString(*Result, CB_S_SLASH);
	Result = UStrings::TrimString(*Result, CB_S_BSLASH);
	if (Result.Contains(CB_S_BSLASH))
	{
		Result = Result.Replace(CB_S_BSLASH, CB_S_SLASH);
	}
	while (Result.Contains(CB_S_BI_SLASH))
	{
		Result = Result.Replace(CB_S_BI_SLASH, CB_S_SLASH);
	}
	return HasStartSlash ? FString(CB_S_DOT).Append(Result) : Result;
}
bool UStrings::IsLetter(const TCHAR& Char)
{
	if (CB_LOWERCASE_LOWER_BOUND <= Char && Char <= CB_LOWERCASE_UPPER_BOUND)
	{
		return true;
	}
	if (CB_UPPERCASE_LOWER_BOUND <= Char && Char <= CB_UPPERCASE_UPPER_BOUND)
	{
		return true;
	}
	return false;
}
bool UStrings::IsNumber(const TCHAR& Char)
{
	if (CB_NUM_LOWER_BOUND <= Char && Char <= CB_NUM_UPPER_BOUND)
	{
		return true;
	}
	return false;
}
bool UStrings::IsAllowedProgrammeChar(const TCHAR& Char)
{
	if (UStrings::IsLetter(Char))
	{
		return true;
	}
	if (UStrings::IsNumber(Char))
	{
		return true;
	}
	if (Char == CB_UNDERLINE || Char == CB_DOLLAR)
	{
		return true;
	}
	return false;

}
bool UStrings::IsUpperCase(const TCHAR& Char)
{
	return CB_UPPERCASE_LOWER_BOUND <= Char && Char <= CB_UPPERCASE_UPPER_BOUND;
}
bool UStrings::IsoLowerCase(const TCHAR& Char)
{
	return CB_LOWERCASE_LOWER_BOUND <= Char && Char <= CB_LOWERCASE_UPPER_BOUND;
}
TCHAR UStrings::ToUpperCase(const TCHAR& Char)
{
	int Value = Char;
	if (CB_LOWERCASE_LOWER_BOUND <= Value && Value <= CB_LOWERCASE_UPPER_BOUND)
	{
		Value = CB_TO_UPPERCASE(Value);
		return Value;
	}
	return Char;
}
TCHAR UStrings::ToLowerCase(const TCHAR& Char)
{
	int Value = Char;
	if (CB_UPPERCASE_LOWER_BOUND <= Value && Value <= CB_UPPERCASE_UPPER_BOUND)
	{
		Value = CB_TO_LOWERCASE(Value);
		return Value;
	}
	return Char;
}
FString UStrings::HeadUpperCase(const FString& String)
{
	if (String.Len() > 0) {
		TCHAR Head = String[0];
		Head = UStrings::ToUpperCase(Head);
		return FString().AppendChar(Head).Append(*String + 1, String.Len() - 1);
	}
	return FString();
}
FString UStrings::HeadLowerCase(const FString& String)
{
	if (String.Len() > 0) {
		TCHAR Head = String[0];
		Head = UStrings::ToLowerCase(Head);
		return FString().AppendChar(Head).Append(*String + 1, String.Len() - 1);
	}
	return FString();
}
FString UStrings::ConvertToSlash(const FString& String, const FString& Prefix, const FString& Suffix, const bool IsUpperCase)
{
	FString Temp(String);
	if (Prefix.Len() != 0)
	{
		if (String.StartsWith(Prefix))
		{
			Temp = String.LeftChop(Prefix.Len());
		}
	}
	if (Suffix.Len() != 0)
	{
		if (String.EndsWith(Suffix))
		{
			Temp = String.RightChop(Suffix.Len());
		}
	}
	bool LastIsLetterOrNum = false;
	bool IsAddUnderLine = false;
	FString Result;
	for (int i = 0;i < String.Len();i++)
	{
		TCHAR C = String[i];
		if (UStrings::IsAllowedProgrammeChar(C))
		{
			if (Result.Len() == 0)
			{
				LastIsLetterOrNum = false;
				IsAddUnderLine = false;
			}
			else
			{
				TCHAR Last = Result[Result.Len() - 1];
				LastIsLetterOrNum = UStrings::IsLetter(Last) || UStrings::IsNumber(Last);
				IsAddUnderLine = LastIsLetterOrNum && (UStrings::IsUpperCase(C) || C == CB_DOLLAR);
			}
			if (IsAddUnderLine)
			{
				Result.AppendChar(CB_UNDERLINE);
			}
			Result.AppendChar(C);
			LastIsLetterOrNum = false;
			IsAddUnderLine = false;
		}
	}
	return Result.ToUpper();
}
FString UStrings::ConvertToCamel(const FString& String, const bool IsUpperCase)
{
	return FString();
}