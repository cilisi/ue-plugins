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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", UIMin = "0"))
		/*The max amount of item*/
		int32 MaxAmount;

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

USTRUCT(BlueprintType)
struct FKnapsackItemInfo {

	GENERATED_BODY()

public:
	FKnapsackItemInfo(FName Id);

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackItemInfo")
		bool IncrementAmount();

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackItemInfo")
		bool DecrementAmount();

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackItemInfo")
		bool ChangeAmount(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackItemInfo")
		void clear();

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackItemInfo")
		void fill();

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackItemInfo")
		FInventoryItemInfo* Info();

	FORCEINLINE friend bool operator==(const FKnapsackItemInfo& L, const FKnapsackItemInfo& R)
	{
		return L.Id == R.Id;
	}

	bool operator==(const FName& OtherId)const
	{
		return Id == OtherId;
	}

public:

	FName Id;

private:

	FInventoryItemInfo* InventoryItemInfo;

	int32 Amount;

	float TotalWeight;
};

/** Case insensitive string hash function. */
FORCEINLINE uint32 GetTypeHash(const FKnapsackItemInfo& KnapsackItemInfo)
{
	return GetTypeHash(KnapsackItemInfo.Id);
}

struct TKnapsackItemInfoKeyFuncs :BaseKeyFuncs<FKnapsackItemInfo, FName> {
	//Init KnapsackItemInfo Key Funcs
	typedef BaseKeyFuncs<FKnapsackItemInfo, FName> Super;
	typedef typename Super::ElementInitType ElementInitType;
	typedef typename Super::KeyInitType     KeyInitType;
	static KeyInitType GetSetKey(ElementInitType Element)
	{
		return Element.Id;
	}
	static  bool Matches(KeyInitType A, KeyInitType B)
	{
		return A.Compare(B) == 0;
	}
	static uint32 GetKeyHash(KeyInitType Key)
	{
		return GetTypeHash(Key);
	}
};

/**
 * The Knapsack Info
 */
USTRUCT(BlueprintType)
struct FKnapsackInfo {

	GENERATED_BODY()

public:

	FKnapsackInfo();

	TSet<FKnapsackItemInfo, TKnapsackItemInfoKeyFuncs> KnapsackItemInfoSet;

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackInfo")
		TArray<FInventoryItemInfo> Infos();

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackInfo")
		bool AddOne(FName Id);

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackInfo")
		bool AddFull(FName Id);

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackInfo")
		bool Add(FName Id, int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackInfo")
		bool RemoveOne(FName Id);

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackInfo")
		bool RemoveAll(FName Id);

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackInfo")
		bool Remove(FName Id, int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackInfo")
		bool Transform(const FKnapsackInfo& Other, FName Id, int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackInfo")
		bool TransformOneAll(const FKnapsackInfo& Other, FName Id);

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackInfo")
		bool TransformAll(const FKnapsackInfo& Other, FName Id);
};

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class COMLIB_API UKnapsackItemInventory : public UObject
{
	GENERATED_BODY()

public:
	UKnapsackItemInventory(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
	{

	}

	static UKnapsackItemInventory* GetSingletonInstance() {
		if (SingletonInstance == nullptr)
		{
			SingletonInstance = NewObject<UKnapsackItemInventory>();
		}
		return SingletonInstance;
	};

private:
	static UKnapsackItemInventory* SingletonInstance;

public:

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackItemInventory")
		static bool ReadConfig(const FString JsonConfigPath, UDataTable* DataTable);

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackItemInventory")
		FInventoryItemInfo* FindInventoryItemInfoById(const FName Id);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CB_KnapsackItemInventory", meta = (AllowPrivateAccess = "true"))
		UDataTable* DataTable;
};
UKnapsackItemInventory* UKnapsackItemInventory::SingletonInstance = nullptr;