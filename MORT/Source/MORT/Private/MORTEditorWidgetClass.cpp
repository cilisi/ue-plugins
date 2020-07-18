#include "MORTEditorWidgetClass.h"
#include "MORTPrivatePCH.h"

#define DEBUG_MSG(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT(x), __VA_ARGS__));}

UMORTEditorWidgetClass::UMORTEditorWidgetClass()
{
	//m_renameProjectAssets = true;
	//m_renameProjectAssets = true;
}

UMORTEditorWidgetClass::~UMORTEditorWidgetClass()
{
}

void UMORTEditorWidgetClass::Setup(EMORTAction action, TArray<AActor*> actors, TArray<UObject*> assets, bool renameProjectAssets, bool renameWorldActors, FString textToFind, FString targetText, FString RegexPattern, int32 CapturingGroupNumber, int32 startNumber, int32 charsToRemove)
{
	m_renameProjectAssets = renameProjectAssets;
	m_renameWorldActors = renameWorldActors;
	m_textToFind = textToFind;
	m_targetText = targetText;
	m_RegexPattern = RegexPattern;
	m_CapturingGroupNumber = CapturingGroupNumber;
	m_startNumber = startNumber;
	m_charsToRemove = charsToRemove;
	m_action = action;
	m_actors = actors;
	m_assets = assets;

	if (renameProjectAssets)
	{
		for (int i = 0; i < assets.Num(); i++)
		{
			OnEachSelectedAssetDelegate(assets[i], i);
		}
	}

	if (renameWorldActors)
	{
		for (int i = 0; i < actors.Num(); i++)
		{
			OnEachSelectedActorDelegate(actors[i], i);
		}
	}

}

void UMORTEditorWidgetClass::OnEachSelectedAssetDelegate(UObject* asset, int32 index)
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::GetModuleChecked<FAssetRegistryModule>("AssetRegistry");
	FAssetData XAssetData = AssetRegistryModule.Get().GetAssetByObjectPath(TEXT("/MORT/MORT.MORT"));
	UObject* MORTasset = XAssetData.GetAsset();

	FString newName;

	switch (m_action)
	{
	case EMORTAction::FindAndReplace:
	{
		newName = asset->GetName().Replace(*m_textToFind, *m_targetText);
	} break;

	case EMORTAction::Prefix:
	{
		newName = m_targetText + asset->GetName();
	} break;

	case EMORTAction::Suffix:
	{
		newName = asset->GetName() + m_targetText;
	} break;

	case EMORTAction::RenameAndNumerate:
	{
		newName = m_targetText + FString::FromInt(m_startNumber + index);
	} break;

	case EMORTAction::ToLowerCase:
	{
		newName = asset->GetName().ToLower();
	} break;

	case EMORTAction::ToUpperCase:
	{
		newName = asset->GetName().ToUpper();
	} break;

	case EMORTAction::RemoveFromStart:
	{
		newName = asset->GetName();
		if (newName.Len() > m_charsToRemove)
		{
			newName.RemoveAt(0, m_charsToRemove);
		}
	} break;

	case EMORTAction::RemoveFromEnd:
	{
		newName = asset->GetName();
		if (newName.Len() > m_charsToRemove)
		{
			newName.RemoveAt(newName.Len() - m_charsToRemove, m_charsToRemove);
		}
	} break;

	case EMORTAction::FindRegexAndReplace:
	{
		newName = asset->GetName();
		const FRegexPattern myPattern(m_RegexPattern);
		FRegexMatcher myMatcher(myPattern, newName);
		if (myMatcher.FindNext())
		{
			FString x = myMatcher.GetCaptureGroup(m_CapturingGroupNumber);
			newName = asset->GetName().Replace(*x, *m_targetText);
		}
	} break;

	}

	FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
	TArray<FAssetRenameData> AssetsAndNames;
	const FString PackagePath = FPackageName::GetLongPackagePath(asset->GetOutermost()->GetName());
	new(AssetsAndNames) FAssetRenameData(asset, PackagePath, newName);
	if (asset != MORTasset)
	{
		AssetToolsModule.Get().RenameAssets(AssetsAndNames);
	}
}

void UMORTEditorWidgetClass::OnEachSelectedActorDelegate(AActor* actor, int32 index)
{
	FString newName;


	switch (m_action)
	{
	case EMORTAction::FindAndReplace:
	{
		newName = actor->GetActorLabel().Replace(*m_textToFind, *m_targetText);
		newName = TEXT(" ") + newName;
	} break;

	case EMORTAction::Prefix:
	{
		newName = m_targetText + actor->GetActorLabel();
	} break;

	case EMORTAction::Suffix:
	{
		newName = actor->GetActorLabel() + m_targetText;
	} break;

	case EMORTAction::RenameAndNumerate:
	{
		newName = m_targetText + FString::FromInt(m_startNumber + index);
		newName = TEXT(" ") + newName;
	} break;

	case EMORTAction::ToLowerCase:
	{
		newName = actor->GetActorLabel().ToLower();
	} break;

	case EMORTAction::ToUpperCase:
	{
		newName = actor->GetActorLabel().ToUpper();
	} break;

	case EMORTAction::RemoveFromStart:
	{
		newName = actor->GetActorLabel();
		if (newName.Len() > m_charsToRemove)
		{
			newName.RemoveAt(0, m_charsToRemove);
			newName = TEXT(" ") + newName;
		}
	} break;

	case EMORTAction::RemoveFromEnd:
	{
		newName = actor->GetActorLabel();
		if (newName.Len() > m_charsToRemove)
		{
			newName.RemoveAt(newName.Len() - m_charsToRemove, m_charsToRemove);
			newName = TEXT(" ") + newName;
		}
	} break;

	case EMORTAction::FindRegexAndReplace:
	{
		newName = actor->GetActorLabel();
		const FRegexPattern myPattern(m_RegexPattern);
		FRegexMatcher myMatcher(myPattern, newName);
		if (myMatcher.FindNext())
		{
			FString x = myMatcher.GetCaptureGroup(m_CapturingGroupNumber);
			newName = actor->GetActorLabel().Replace(*x, *m_targetText);
			newName = TEXT(" ") + newName;
		}
	} break;
	}

	actor->Rename(*newName);
	actor->SetActorLabel(newName);
}
