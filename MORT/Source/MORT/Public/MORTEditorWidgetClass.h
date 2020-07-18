#pragma once

#include "CoreMinimal.h"
#include "Editor/Blutility/Classes/EditorUtilityWidget.h"

#include "MORTEditorWidgetClass.generated.h"

/**
 *
 */
UENUM()
enum class EMORTAction : uint8
{
	ToLowerCase,
	ToUpperCase,
	RemoveFromStart,
	RemoveFromEnd,
	Prefix,
	Suffix,
	RenameAndNumerate,
	FindAndReplace,
	FindRegexAndReplace
};

UCLASS(BlueprintType)
class MORT_API UMORTEditorWidgetClass : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
	UMORTEditorWidgetClass();
	~UMORTEditorWidgetClass();

	UFUNCTION(BlueprintCallable, Category = Values)
		void Setup(EMORTAction action, TArray<AActor*> actors, TArray<UObject*> assets, bool renameProjectAssets, bool renameWorldActors, FString textToFind, FString targetText, FString RegexPattern, int32 CapturingGroupNumber, int32 startNumber, int32 charsToRemove);

	UFUNCTION()
		void OnEachSelectedAssetDelegate(UObject* asset, int32 index);

	UFUNCTION()
		void OnEachSelectedActorDelegate(AActor* actor, int32 index);

	//UPROPERTY(EditAnywhere, Category = Values) bool renameWorldActors;
	//UPROPERTY(EditAnywhere, Category = Values) bool renameProjectAssets;
protected:
	//UPROPERTY(EditAnywhere, Category = Values) FString textToFind;
	//UPROPERTY(EditAnywhere, Category = Values) FString targetText;
	//UPROPERTY(EditAnywhere, Category = Values) FString RegexPattern;
	//UPROPERTY(EditAnywhere, Category = Values) int32 CapturingGroupNumber;
	//UPROPERTY(EditAnywhere, Category = Values) int32 startNumber;
	//UPROPERTY(EditAnywhere, Category = Values) int32 charsToRemove;

private:
	EMORTAction m_action;
	TArray<AActor*> m_actors;
	TArray<UObject*> m_assets;
	bool m_renameProjectAssets;
	bool m_renameWorldActors;
	FString m_textToFind;
	FString m_targetText;
	FString m_RegexPattern;
	int32 m_CapturingGroupNumber;
	int32 m_startNumber;
	int32 m_charsToRemove;
};
