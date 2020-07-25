// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KnapsackItemInventory.h"
#include "KnapsackComponent.generated.h"


UCLASS(ClassGroup = (Knapsack), meta = (BlueprintSpawnableComponent))
class COMLIB_API UKnapsackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UKnapsackComponent();

	virtual void InitializeComponent() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CB_Knapsack", meta = (ClampMin = "0", UIMin = "0"))
		/*最大存取物品数量*/
		int32 MaxItemCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CB_Knapsack", meta = (ClampMin = "0", UIMin = "0"))
		/*耐久度*/
		int32 MaxDurability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "CB_Knapsack")
		/*识别号*/
		FName Identify;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "CB_Knapsack")
		/*亲密识别号*/
		TSet<FName> IntimateIdentify;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "CB_Knapsack")
		/*好友识别号*/
		TSet<FName> FriendIdentify;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category = "CB_Knapsack")
		/*是否开启加密*/
		bool IsEnableEncryption;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category = "CB_Knapsack", meta = (EditCondition = "IsEnableEncryption"))
		/*是否开启加密*/
		FString Password;

	UPROPERTY(BlueprintReadOnly)
		UKnapsackInfo* KnapsackInfo;
};
