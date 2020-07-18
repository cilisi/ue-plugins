#pragma once

#include "Modules/ModuleManager.h"
#include "Runtime/Launch/Resources/Version.h"

DECLARE_LOG_CATEGORY_EXTERN(PathFollowModuleLog, NoLogging, NoLogging);

class PATHFOLLOW_API FPathFollowModule : public IModuleInterface
{
private:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

#if WITH_EDITORONLY_DATA
  void RegisterDetailsCustomization();
  void RegisterVisualizer();
  void OnSelectObject(UObject*);
  void SetFollowerActor(class AActor* FollowerActor);

	TSharedPtr<class FUICommandList> _Commands;
#endif
};
