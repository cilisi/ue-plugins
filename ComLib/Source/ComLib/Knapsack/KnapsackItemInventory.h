#pragma once
#include "Constants.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "KnapsackItemInventory.generated.h"

/**
 * The Inventory Info of Item
 */
USTRUCT(BlueprintType)
struct FInventoryItemInfo :public FTableRowBase
{
	GENERATED_BODY()

public:

	FInventoryItemInfo();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		/*The unique ID of the item*/
		FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		/*The name of item*/
		FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		/*The activated text message of item*/
		FText Action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		/*The description of item*/
		FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		/*The picture of item*/
		UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		/*The weight of item*/
		float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		/*Whether the item can be used*/
		bool bCanUsed;

	/*Whether the both inventory item info is equal*/
	bool operator==(const FInventoryItemInfo& InventoryItemInfo)const
	{
		return ItemID == InventoryItemInfo.ItemID;
	}

	/*Whether the inventory item info and ItemID is equal for find it*/
	bool operator==(const FName& OtherItemID)const
	{
		return ItemID == OtherItemID;
	}

private:
	static uint32 ItemIndex;
};
uint32 FInventoryItemInfo::ItemIndex = 0;

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

};
