#include "PathFollow.h"
#include "Engine.h"
#if WITH_EDITOR
#include "UnrealEd.h"
#endif

#define CUR_CLASS_FUNC (FString(__FUNCTION__))
#define CUR_LINE (FString::FromInt(__LINE__))

#define PF_LOG_DIS(LogCat, FormatString, ...)                                                         \
	UE_LOG(LogCat, Display, TEXT("%s(%s): %s"), *CUR_CLASS_FUNC, *CUR_LINE, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__))

#define PF_LOG_WARN(LogCat, FormatString, ...)                                                        \
	UE_LOG(LogCat, Warning, TEXT("%s(%s): %s"), *CUR_CLASS_FUNC, *CUR_LINE, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__))

#define PF_LOG_ERR(LogCat, FormatString, ...)                                                         \
	UE_LOG(LogCat, Error, TEXT("%s(%s): %s"), *CUR_CLASS_FUNC, *CUR_LINE, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__))

#define PF_LOG_VERB(LogCat, FormatString, ...)                                                        \
	UE_LOG(LogCat, Verbose, TEXT("%s(%s): %s"), *CUR_CLASS_FUNC, *CUR_LINE, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__))

#define PF_LOG_VERYVERB(LogCat, FormatString, ...)                                                    \
	UE_LOG(LogCat, VeryVerbose, TEXT("%s(%s): %s"), *CUR_CLASS_FUNC, *CUR_LINE, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__))

// You should place include statements to your module's private header files here.  You only need to
// add includes for headers that are used in most of your module's source files though.
