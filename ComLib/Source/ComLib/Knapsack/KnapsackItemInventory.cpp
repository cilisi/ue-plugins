#include "KnapsackItemInventory.h"
#include "Datas.h"
#include "Resources.h"
FInventoryItemCompoundInfo::FInventoryItemCompoundInfo()
{
	Id = FName("Id");
	Amount = 1;
}
FInventoryItemInfo::FInventoryItemInfo()
{
	bCanUsed = true;
	Id = FName("Id");
	Name = FName("Name");
	Action = FText::FromString("The Item Action Text");
	Description = FText::FromString("The Item Description Text");
	Thumbnail = nullptr;
	Weight = 0.f;
	bCanCompound = false;
	CompoundInfos = TSet<FInventoryItemCompoundInfo>();
	bCanMerged = false;
	MergedInfo = FInventoryItemCompoundInfo();
}



FKnapsackItemInfo::FKnapsackItemInfo(FName Id)
{
	UKnapsackItemInventory* KnapsackItemInventory = UKnapsackItemInventory::GetSingletonInstance();
	if (KnapsackItemInventory)
	{
		FInventoryItemInfo* InventoryItemInfo = KnapsackItemInventory->FindInventoryItemInfoById(Id);
		if (InventoryItemInfo)
		{
			this->Id = Id;
			this->InventoryItemInfo = InventoryItemInfo;
			this->Amount = 1;
			this->TotalWeight = InventoryItemInfo->Weight;
			return;
		}
		else
		{
			throw FString("Don't exist FInventoryItem Info by Id ") + Id.ToString();
		}
	}
	else
	{
		throw FString("Don't exist KnapsackItemInventory");
	}
}

FInventoryItemInfo* FKnapsackItemInfo::Info()
{
	return InventoryItemInfo;
}

bool FKnapsackItemInfo::IncrementAmount()
{
	if (this->Amount >= InventoryItemInfo->MaxAmount)
	{
		return false;
	}
	++this->Amount;
	this->TotalWeight = this->Amount * InventoryItemInfo->Weight;
	return true;
}

bool FKnapsackItemInfo::DecrementAmount()
{
	if (this->Amount <= 0)
	{
		return false;
	}
	--this->Amount;
	this->TotalWeight = this->Amount * InventoryItemInfo->Weight;
	return true;
}

bool FKnapsackItemInfo::ChangeAmount(int32 Amount)
{
	if (this->Amount <= 0 || this->Amount > InventoryItemInfo->MaxAmount)
	{
		return false;
	}
	this->Amount = Amount;
	this->TotalWeight = this->Amount * InventoryItemInfo->Weight;
	return true;
}

void FKnapsackItemInfo::clear()
{
	this->Amount = 0;
	this->TotalWeight = 0.f;
}

void FKnapsackItemInfo::fill()
{
	this->Amount = InventoryItemInfo->MaxAmount;
	this->TotalWeight = this->Amount * InventoryItemInfo->MaxAmount;
}

FInventoryItemInfo* UKnapsackItemInventory::FindInventoryItemInfoById(const FName Id)
{
	if (DataTable)
	{
		FString Content;
		FInventoryItemInfo* Value = DataTable->FindRow<FInventoryItemInfo>(Id, Content);
		if (Value)
		{
			return Value;
		}
	}
	return nullptr;
}

bool UKnapsackItemInventory::ReadConfig(const FString JsonConfigPath, UDataTable* DataTable)
{
	FString JsonConfig;
	if (JsonConfigPath.Len() != 0) {
		bool b = UDatas::FillDataTableFromJSONFile(DataTable, JsonConfigPath);
		if (b)
		{
			UDatas::HandleDataTableRowNameForNumberate(DataTable);
		}
	}
	return false;
}

FKnapsackInfo::FKnapsackInfo()
{
	KnapsackItemInfoSet = TSet<FKnapsackItemInfo, TKnapsackItemInfoKeyFuncs>();
}
TArray<FInventoryItemInfo> FKnapsackInfo::Infos()
{
	TArray<FInventoryItemInfo> Infos;
	for (TSet<FKnapsackItemInfo, TKnapsackItemInfoKeyFuncs>::TIterator It = KnapsackItemInfoSet.CreateIterator(); it; ++it) {
		Infos.Add(*(*It).Info());
	}
	return Infos;
}

bool FKnapsackInfo::AddOne(FName Id)
{
	FKnapsackItemInfo* KnapsackItemInfo = KnapsackItemInfoSet.Find(Id);
	if (KnapsackItemInfo == nullptr)
	{
		KnapsackItemInfoSet.Add(FKnapsackItemInfo(Id));
	}
	else
	{
		return KnapsackItemInfo->IncrementAmount();
	}
}

bool FKnapsackInfo::AddFull(FName Id)
{
	FKnapsackItemInfo* KnapsackItemInfo = KnapsackItemInfoSet.Find(Id);
	if (KnapsackItemInfo == nullptr)
	{
		KnapsackItemInfo = &FKnapsackItemInfo(Id);
		KnapsackItemInfo->fill();
		KnapsackItemInfoSet.Add(*KnapsackItemInfo);
	}
	else
	{
		KnapsackItemInfo->fill();
	}
	return true;
}

bool FKnapsackInfo::Add(FName Id, int32 Amount)
{
	FKnapsackItemInfo* KnapsackItemInfo = KnapsackItemInfoSet.Find(Id);
	if (KnapsackItemInfo == nullptr)
	{
		KnapsackItemInfo = &FKnapsackItemInfo(Id);
		KnapsackItemInfo->ChangeAmount(Amount);
		KnapsackItemInfoSet.Add(*KnapsackItemInfo);
	}
	else
	{
		KnapsackItemInfo->fill();
	}
	return false;
}

bool FKnapsackInfo::RemoveOne(FName Id)
{
	return false;
}

bool FKnapsackInfo::RemoveAll(FName Id)
{
	return false;
}

bool FKnapsackInfo::Remove(FName Id, int32 Amount)
{
	return false;
}

bool FKnapsackInfo::Transform(const FKnapsackInfo& Other, FName Id, int32 Amount)
{
	return false;
}

bool FKnapsackInfo::TransformOneAll(const FKnapsackInfo& Other, FName Id)
{
	return false;
}

bool FKnapsackInfo::TransformAll(const FKnapsackInfo& Other, FName Id)
{
	return false;
}
