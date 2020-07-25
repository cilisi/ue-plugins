#pragma once
#include "Constants.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "Kismet/KismetMathLibrary.h"
#include "KnapsackItemInventory.generated.h"

////////////////////////////////////////////////////////////////////////////////////////////
//The Inventory Item Information Configuration
////////////////////////////////////////////////////////////////////////////////////////////

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

	FInventoryItemCompoundInfo& operator=(const FInventoryItemCompoundInfo& Other)
	{
		Id = Other.Id;
		Amount = Other.Amount;
		return *this;
	}

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

	FInventoryItemInfo& operator=(const FInventoryItemInfo& Other)
	{
		bCanUsed = Other.bCanUsed;
		Id = Other.Id;
		Name = Other.Name;
		Category = Other.Category;
		Action = Other.Action;
		Description = Other.Description;
		Thumbnail = Other.Thumbnail;
		Weight = Other.Weight;
		MaxAmount = Other.MaxAmount;
		bCanCompound = Other.bCanCompound;
		CompoundInfos = Other.CompoundInfos;
		bCanMerged = Other.bCanMerged;
		MergedInfo = Other.MergedInfo;
		return *this;
	}

	/*Whether the inventory item info and Item ID is equal for find it*/
	bool operator==(const FName& OtherId)const
	{
		return Id == OtherId;
	}

private:

};

FORCEINLINE uint32 GetTypeHash(const FInventoryItemInfo& InventoryItemInfo)
{
	return GetTypeHash(InventoryItemInfo.Id);
}

////////////////////////////////////////////////////////////////////////////////////////////
//END The Inventory Item Information Configuration
////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////
//The Knapsack Item Information
////////////////////////////////////////////////////////////////////////////////////////////

/**
 * The Knapsack Item Info Initialtion Opetion
 */
enum EKnapsackItemInfoInitialtion {
	ZERO,
	ONE,
	FULL
};

/**
 * The Knapsack Item Info
 */
struct FKnapsackItemInfo {

	FKnapsackItemInfo(FName Id);

	FKnapsackItemInfo(FName Id, EKnapsackItemInfoInitialtion KnapsackItemInfoInit);

	bool IncrementAmount();

	bool DecrementAmount();

	int32 IncreaseAmount(int32 Amount);

	int32 DecreaseAmount(int32 Amount);

	int32 ChangeAmount(int32 Amount);

	void clear();

	void fill();

	FInventoryItemInfo* Info();

	int32 GetTotalAmount();

	int32 GetTotalWeight();

	FKnapsackItemInfo& operator=(const FKnapsackItemInfo* Other)
	{
		Id = Other->Id;
		InventoryItemInfo = Other->InventoryItemInfo;
		Amount = Other->Amount;
		TotalWeight = Other->TotalWeight;
		return *this;
	}

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

FORCEINLINE uint32 GetTypeHash(const FKnapsackItemInfo& KnapsackItemInfo)
{
	return GetTypeHash(KnapsackItemInfo.Id);
}

/**
 * The Knapsack Item Info KeyFuncs
 */
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
UCLASS(ClassGroup = (Knapsack))
class COMLIB_API UKnapsackInfo : public UObject
{
	GENERATED_BODY()

public:

	UKnapsackInfo();

	UFUNCTION(BlueprintPure, Category = "CB_KnapsackInfo")
		TArray<FName> Ids();

	UFUNCTION(BlueprintPure, Category = "CB_KnapsackInfo")
		TArray<FInventoryItemInfo> Infos();

	UFUNCTION(BlueprintPure, Category = "CB_KnapsackInfo")
		bool Info(FName Id, FInventoryItemInfo& result);

	UFUNCTION(BlueprintPure, Category = "CB_KnapsackInfo")
		int32 Count();

	UFUNCTION(BlueprintPure, Category = "CB_KnapsackInfo")
		bool Amount(FName Id, int32& Result);

	UFUNCTION(BlueprintPure, Category = "CB_KnapsackInfo")
		bool Weight(FName Id, float& Result);

	UFUNCTION(BlueprintPure, Category = "CB_KnapsackInfo")
		float TotalWeigth();

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackInfo")
		bool AddOne(FName Id);

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackInfo")
		bool AddFull(FName Id);

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackInfo")
		bool Add(FName Id, int32 Amount, int32& RealAddAmount);

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackInfo")
		bool RemoveOne(FName Id);

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackInfo")
		bool RemoveAll(FName Id);

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackInfo")
		bool Remove(FName Id, int32 Amount, int32& RealRemoveAmount);

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackInfo")
		void TransferOneFrom(UKnapsackInfo* Other, FName Id, int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackInfo")
		void TransferOneAllFrom(UKnapsackInfo* Other, FName Id);

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackInfo")
		void TransferAllFrom(UKnapsackInfo* Other);

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackInfo")
		void TransferOneTo(UKnapsackInfo* Other, FName Id, int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackInfo")
		void TransferOneAllTo(UKnapsackInfo* Other, FName Id);

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackInfo")
		void TransferAllTo(UKnapsackInfo* Other);

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackInfo")
		void IncreaseDurability(int32 Durability);

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackInfo")
		void DecreaseDurability(int32 Durability);

	UFUNCTION(BlueprintPure, Category = "CB_KnapsackInfo")
		bool IsDamage();

	//背包属性设置
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CB_KnapsackInfo", meta = (ClampMin = "0", UIMin = "0"))
		//最大存取物品数量
		int32 MaxItemCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category = "CB_KnapsackInfo", meta = (ClampMin = "0", UIMin = "0"))
		//耐久度
		int32 MaxDurability;

private:
	TSet<FKnapsackItemInfo, TKnapsackItemInfoKeyFuncs> KnapsackItemInfoSet;
	int32 CurrentDurability;
};

////////////////////////////////////////////////////////////////////////////////////////////
//END The Knapsack Item Information
////////////////////////////////////////////////////////////////////////////////////////////
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

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackItemInventory")
		static bool ReadConfig(const FString JsonConfigPath, UDataTable* DataTable);

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackItemInventory")
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
		/*Init DataTable*/
		void Init(UDataTable* DataTable);

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackItemInventory")
		/*Is Exist Inventory Item Info*/
		bool IsExistInventoryItemInfo(const FName Id);

	UFUNCTION(BlueprintCallable, Category = "CB_KnapsackItemInventory")
		/*Find Inventory Item Info By Id*/
		void FindInventoryItemInfo(const FName Id, FInventoryItemInfo& Result);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CB_KnapsackItemInventory", meta = (AllowPrivateAccess = "true"))
		/*The meta data of  Inventory Item Info*/
		UDataTable* DataTable;
};
UKnapsackItemInventory* UKnapsackItemInventory::SingletonInstance = nullptr;