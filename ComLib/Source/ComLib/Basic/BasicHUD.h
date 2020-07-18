#pragma once
#include "Components.h"
#include "Engine/DirectionalLight.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Texture.h"
#include "BasicHUD.generated.h"

/**
 *
 */
UCLASS()
class COMLIB_API ABasicHUD : public AHUD
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = "SightBead")
		bool EnableSigthBead;
	UPROPERTY(EditAnywhere, BlueprintSetter = SetSigthBeadTexture, Category = "SightBead", meta = (DisplayName = "Texture", EditCondition = "EnableSigthBead"))
		UTexture* SigthBeadTexture;
	UPROPERTY(EditAnywhere, BlueprintSetter = SetSigthBeadLinearColor, AdvancedDisplay, Category = "SightBead", meta = (DisplayName = "LinearColor", EditCondition = "EnableSigthBead"))
		FLinearColor SigthBeadLinearColor;
	UPROPERTY(EditAnywhere, BlueprintSetter = SetSigthBeadScale, AdvancedDisplay, Category = "SightBead", meta = (ClampMin = "1", ClampMax = "2", DisplayName = "Scale", EditCondition = "EnableSigthBead"))
		float SigthBeadScale;
	UPROPERTY(EditAnywhere, BlueprintSetter = SetSigthBeadRotator, AdvancedDisplay, Category = "SightBead", meta = (ClampMin = "-180", ClampMax = "180", DisplayName = "Rotator", EditCondition = "EnableSigthBead"))
		float SigthBeadRotator;
	UPROPERTY(EditAnywhere, BlueprintSetter = SetSigthBeadRotPivot, AdvancedDisplay, Category = "SightBead", meta = (DisplayName = "RotPivot", EditCondition = "EnableSigthBead"))
		FVector2D SigthBeadRotPivot;

	EBlendMode SigthBeadBlendMode;

public:

	UFUNCTION(BlueprintSetter, Category = "CB_BasicHUD_SightBead")
		virtual void SetSigthBeadTexture(UTexture* Texture);

	UFUNCTION(BlueprintSetter, Category = "CB_BasicHUD_SightBead")
		virtual void SetSigthBeadLinearColor(FLinearColor LinearColor);

	UFUNCTION(BlueprintSetter, Category = "CB_BasicHUD_SightBead")
		virtual void SetSigthBeadScale(float Scale);

	UFUNCTION(BlueprintSetter, Category = "CB_BasicHUD_SightBead")
		virtual void SetSigthBeadRotator(float Rotator);

	UFUNCTION(BlueprintSetter, Category = "CB_BasicHUD_SightBead")
		virtual void SetSigthBeadRotPivot(FVector2D RotPivot);

	UFUNCTION(BlueprintCallable, Category = "CB_BasicHUD_SightBead")
		virtual void SetSigthBeadBlendMode(EBlendMode BlendMode);

	ABasicHUD();

	virtual void PostInitProperties()override;

	virtual void Tick(float DeltaSeconds)
	{
		PreTick(DeltaSeconds);
		DoTick(DeltaSeconds);
		PostTick(DeltaSeconds);
	}

protected:

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "CB_BasicHUD")
		void DoReceiveDrawHUD(int32 SizeX, int32 SizeY);

	UFUNCTION(BlueprintImplementableEvent, Category = "CB_Event")
		void PreBeginPlay();

	UFUNCTION(BlueprintImplementableEvent, Category = "CB_Event")
		void PostBeginPlay();

	UFUNCTION(BlueprintImplementableEvent, Category = "CB_Event")
		void PreTick(float DeltaSeconds);

	UFUNCTION(BlueprintImplementableEvent, Category = "CB_Event")
		void PostTick(float DeltaSeconds);

	virtual void DoBeginPlay() {};

	virtual void DoTick(float DeltaSeconds) {};

	virtual void BeginPlay()override {
		PreBeginPlay();
		DoBeginPlay();
		PostBeginPlay();
	}
};


