#pragma once
#include <typeinfo>
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

//Is enable debug
#define CB_ENABLE_DEBUG  !(UE_BUILD_SHIPPING || UE_BUILD_TEST)

//Log

#define CB_CUR_CLASS_FUNC (FString(__FUNCTION__))
#define CB_CUR_LINE (FString::FromInt(__LINE__))

#define CB_PF_LOG_DIS(LogCat, FormatString, ...)                                                         \
	UE_LOG(LogCat, Display, TEXT("%s(%s): %s"), *CB_CUR_CLASS_FUNC, *CB_CUR_LINE, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__))

#define CB_PF_LOG_WARN(LogCat, FormatString, ...)                                                        \
	UE_LOG(LogCat, Warning, TEXT("%s(%s): %s"), *CB_CUR_CLASS_FUNC, *CB_CUR_LINE, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__))

#define CB_PF_LOG_ERR(LogCat, FormatString, ...)                                                         \
	UE_LOG(LogCat, Error, TEXT("%s(%s): %s"), *CB_CUR_CLASS_FUNC, *CB_CUR_LINE, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__))

#define CB_PF_LOG_VERB(LogCat, FormatString, ...)                                                        \
	UE_LOG(LogCat, Verbose, TEXT("%s(%s): %s"), *CB_CUR_CLASS_FUNC, *CB_CUR_LINE, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__))

#define CB_PF_LOG_VERYVERB(LogCat, FormatString, ...)                                                    \
	UE_LOG(LogCat, VeryVerbose, TEXT("%s(%s): %s"), *CB_CUR_CLASS_FUNC, *CB_CUR_LINE, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__))

/** Define Global Log**/
DEFINE_LOG_CATEGORY_STATIC(ComLibPlugin, Display, Display);

#define CB_EOF -1
#define CB_ERROR CB_EOF
#define CB_ZERO 0
#define CB_ZERO_F 0.f

#define CB_MIN_BYTE_NUM CB_ZERO
#define CB_MAX_BYTE_NUM 255

#define CB_MIN_INT8 0x80
#define CB_MAX_INT8 0x7F
#define CB_MIN_INT16 0x8000
#define CB_MAX_INT16 0x7FFF
#define CB_MIN_INT32 0x80000000
#define CB_MAX_INT32 0x7FFFFFFF
#define CB_MIN_INT64 0x8000000000000000
#define CB_MAX_INT64 0x7FFFFFFFFFFFFFFF
#define CB_MAX_UINT8 0xFF
#define CB_MAX_UINT16 0xFFFF
#define CB_MAX_UINT32 0xFFFFFFFF
#define CB_MAX_UINT64 0xFFFFFFFFFFFFFFFF

/** Allow occurence char **/
#define CB_DOLLAR 36
#define CB_UNDERLINE 95
#define CB_NUM_LOWER_BOUND 48
#define CB_NUM_UPPER_BOUND 59
#define CB_UPPERCASE_LOWER_BOUND 65
#define CB_UPPERCASE_UPPER_BOUND 90
#define CB_LOWERCASE_LOWER_BOUND 97
#define CB_LOWERCASE_UPPER_BOUND 122

#define CB_TO_UPPERCASE(x) (x)-32
#define CB_TO_LOWERCASE(x) (x)+32


#define CB_S_TRUE TEXT("true")
#define CB_S_FALSE TEXT("false")

#define CB_S_IE_PNG TEXT("png")
#define CB_S_IE_JPG TEXT("jpg")
#define CB_S_IE_JPEG TEXT("jpeg")
#define CB_S_IE_BMP TEXT("bmp")
#define CB_S_IE_ICO TEXT("ico")
#define CB_S_IE_EXR TEXT("exr")
#define CB_S_IE_ICNS TEXT("icns")
#define CB_S_DOT TEXT(".")
#define CB_S_SLASH TEXT("/")
#define CB_S_BI_SLASH TEXT("//")
#define CB_S_BSLASH TEXT("\\")
//ToString
#define CB_FS_TOSTRING(x) UEObjectInterface::ToFString(x)

#define CB_FS_C(x) FString().AppendChar(x)
#define CB_FS(x) CB_FS_TOSTRING(x)
#define CB_FS_CONCAT(a,b) CB_FS(a).Append(CB_FS_TOSTRING(b))
#define CB_FS_CONCAT_3(a,b,c) CB_FS_CONCAT(a,b).Append(CB_FS_TOSTRING(c))
#define CB_FS_CONCAT_4(a,b,c,d) CB_FS_CONCAT_3(a,b,c).Append(CB_FS_TOSTRING(d))
#define CB_FS_CONCAT_5(a,b,c,d,e) CB_FS_CONCAT_4(a,b,c,d).Append(CB_FS_TOSTRING(e))
#define CB_FS_CONCAT_6(a,b,c,d,e,f) CB_FS_CONCAT_4(a,b,c,d,e).Append(CB_FS_TOSTRING(f))


class UEObjectInterface {

public:
	virtual FString ToString() {
		return FString();
	};
	virtual int32 HashCode() {
		return 0;
	}
	virtual bool Equal(const UEObjectInterface* const Other) {
		return this == Other;
	}

	static FString ToFString(int32 Value) {
		return FString::FromInt(Value);
	}
	static FString ToFString(double Value) {
		return FString::SanitizeFloat(Value);
	}
	static FString ToFString(TCHAR Value) {
		return FString().AppendChar(Value);
	}
	static FString ToFString(FString Value) {
		return Value;
	}
};
class Constants
{
public:
	static TArray<FString> SupportImageExtensionName();
};
