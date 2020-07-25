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
		/*����ȡ��Ʒ����*/
		int32 MaxItemCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CB_Knapsack", meta = (ClampMin = "0", UIMin = "0"))
		/*�;ö�*/
		int32 MaxDurability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "CB_Knapsack")
		/*ʶ���*/
		FName Identify;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "CB_Knapsack")
		/*����ʶ���*/
		TSet<FName> IntimateIdentify;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "CB_Knapsack")
		/*����ʶ���*/
		TSet<FName> FriendIdentify;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category = "CB_Knapsack")
		/*�Ƿ�������*/
		bool IsEnableEncryption;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category = "CB_Knapsack", meta = (EditCondition = "IsEnableEncryption"))
		/*�Ƿ�������*/
		FString Password;

	UPROPERTY(BlueprintReadOnly)
		UKnapsackInfo* KnapsackInfo;
};
