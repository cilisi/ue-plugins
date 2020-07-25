// Fill out your copyright notice in the Description page of Project Settings.


#include "KnapsackComponent.h"

// Sets default values for this component's properties
UKnapsackComponent::UKnapsackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	KnapsackInfo = NewObject<UKnapsackInfo>();
	KnapsackInfo->MaxItemCount = MaxItemCount = 60;
	KnapsackInfo->MaxDurability = MaxDurability = 100;
	Identify = FName();
	IntimateIdentify = TSet<FName>();
	FriendIdentify = TSet<FName>();
	IsEnableEncryption = false;
	Password = FString();
	// ...
}

void UKnapsackComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

// Called when the game starts
void UKnapsackComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...

}


// Called every frame
void UKnapsackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

