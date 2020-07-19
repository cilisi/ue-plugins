#pragma once
#include "Constants.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "KnapsackItemInventory.generated.h"

/**
 * The Inventory Compound Info of Item
 */
USTRUCT(BlueprintType)
struct FInventoryItemCompoundInfo :public FTableRowBase
{
	GENERATED_BODY()

public:

	FInventoryItemCompoundInfo();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		/*The unique ID of the item*/
		FName Id;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", UIMin = "0"))
		/*The amount of needed item*/
		int32 Amount;

	FORCEINLINE friend bool operator==(const FInventoryItemCompoundInfo& L, const FInventoryItemCompoundInfo& R)
	{
		return L.Id == R.Id;
	}

	/*Whether the inventory item info and Item ID is equal for find it*/
	bool operator==(const FName& OtherId)const
	{
		return Id == OtherId;
	}
};

/** Case insensitive string hash function. */
FORCEINLINE uint32 GetTypeHash(const FInventoryItemCompoundInfo& InventoryItemCompoundInfo)
{
	return GetTypeHash(InventoryItemCompoundInfo.Id);
}

/**
 * The Inventory Info of Item
 */
USTRUCT(BlueprintType)
struct FInventoryItemInfo :public FTableRowBase
{
	GENERATED_BODY()

public:

	FInventoryItemInfo();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		/*Whether the item can be used*/
		bool bCanUsed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		/*The unique ID of the item*/
		FName Id;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		/*The name of item*/
		FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		/*The category of item*/
		FName Category;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		/*The activated text message of item*/
		FText Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		/*The description of item*/
		FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		/*The picture of item*/
		UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", UIMin = "0"))
		/*The weight of item*/
		float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		/*Whether the item can be compounded*/
		bool bCanCompound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bCanCompound"))
		/*The articles needed for synthesize the item*/
		TSet<FInventoryItemCompoundInfo> CompoundInfos;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		/*Whether the item can be merged*/
		bool bCanMerged;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bCanMerged"))
		FInventoryItemCompoundInfo MergedInfo;

	/*Whether the both inventory item info is equal*/
	FORCEINLINE friend bool operator==(const FInventoryItemInfo& L, const FInventoryItemInfo& R)
	{
		return L.Id == R.Id;
	}

	/*Whether the inventory item info and Item ID is equal for find it*/
	bool operator==(const FName& OtherId)const
	{
		return Id == OtherId;
	}

private:

};

/** Case insensitive string hash function. */
FORCEINLINE uint32 GetTypeHash(const FInventoryItemInfo& InventoryItemInfo)
{
	return GetTypeHash(InventoryItemInfo.Id);
}

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class COMLIB_API UKnapsackItemInventory : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackItemInventory")
		static bool ReadConfig(const FString JsonConfigPath, UDataTable* DataTable);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CB_KnapsackItemInventory", meta = (AllowPrivateAccess = "true"))
		UDataTable* DataTable;
};
