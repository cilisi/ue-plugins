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

FKnapsackItemInfo::FKnapsackItemInfo(FName Id) :FKnapsackItemInfo(Id, EKnapsackItemInfoInitialtion::ONE)
{

}

FKnapsackItemInfo::FKnapsackItemInfo(FName Id, EKnapsackItemInfoInitialtion KnapsackItemInfoInit)
{
	UKnapsackItemInventory* KnapsackItemInventory = UKnapsackItemInventory::GetSingletonInstance();
	if (KnapsackItemInventory)
	{
		FInventoryItemInfo FoundInventoryItemInfo;
		bool b = KnapsackItemInventory->FindInventoryItemInfoById(Id, FoundInventoryItemInfo);
		if (b)
		{
			this->Id = Id;
			this->InventoryItemInfo = &FoundInventoryItemInfo;
			switch (KnapsackItemInfoInit)
			{
			case ZERO:
				this->Amount = 0;
				break;
			case FULL:
				this->Amount = FoundInventoryItemInfo.MaxAmount;
				break;
			default:
				this->Amount = 1;
				break;
			}
			this->TotalWeight = FoundInventoryItemInfo.Weight;
		}
		else
		{
			this->Id = Id;
			this->InventoryItemInfo = &FoundInventoryItemInfo;
			this->TotalWeight = 0;
		}
	}

}

FInventoryItemInfo* FKnapsackItemInfo::Info()
{
	return InventoryItemInfo;
}

int32 FKnapsackItemInfo::GetTotalAmount()
{
	return this->Amount;
}

int32 FKnapsackItemInfo::GetTotalWeight()
{
	return this->TotalWeight;
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

int32 FKnapsackItemInfo::IncreaseAmount(int32 InAmount)
{
	if (this->Amount <= 0)
	{
		return 0;
	}
	int32 TotalAmount = this->Amount + InAmount;
	if (TotalAmount > InventoryItemInfo->MaxAmount)
	{
		int32 Diff = InventoryItemInfo->MaxAmount - this->Amount;
		this->Amount = InventoryItemInfo->MaxAmount;
		return Diff;
	}
	this->Amount = TotalAmount;
	return InAmount;
}

int32 FKnapsackItemInfo::DecreaseAmount(int32 InAmount)
{
	if (this->Amount <= 0)
	{
		return 0;
	}
	int32 TotalAmount = this->Amount - InAmount;
	if (TotalAmount < 0)
	{
		int32 Diff = this->Amount;
		this->Amount = 0;
		return Diff;
	}
	this->Amount = TotalAmount;
	return InAmount;
}

int32 FKnapsackItemInfo::ChangeAmount(int32 InAmount)
{
	if (this->Amount < 0 || this->Amount > InventoryItemInfo->MaxAmount)
	{
		return 0;
	}
	int32 Diff = InAmount - this->Amount;
	this->Amount = InAmount;
	this->TotalWeight = InAmount * InventoryItemInfo->Weight;
	return Diff;
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

UKnapsackInfo::UKnapsackInfo()
{
	KnapsackItemInfoSet = TSet<FKnapsackItemInfo, TKnapsackItemInfoKeyFuncs>();
}

TArray<FName> UKnapsackInfo::Ids()
{
	TArray<FName> Ids;
	for (TSet<FKnapsackItemInfo, TKnapsackItemInfoKeyFuncs>::TIterator It = KnapsackItemInfoSet.CreateIterator(); It; ++It) {
		Ids.Add((*It).Id);
	}
	return Ids;
}

TArray<FInventoryItemInfo> UKnapsackInfo::Infos()
{
	TArray<FInventoryItemInfo> Infos;
	for (TSet<FKnapsackItemInfo, TKnapsackItemInfoKeyFuncs>::TIterator It = KnapsackItemInfoSet.CreateIterator(); It; ++It) {
		Infos.Add(FInventoryItemInfo(*(*It).Info()));
	}
	return Infos;
}

FInventoryItemInfo UKnapsackInfo::Info(FName Id)
{
	FKnapsackItemInfo* KnapsackItemInfo = KnapsackItemInfoSet.Find(Id);
	if (KnapsackItemInfo)
	{
		return FInventoryItemInfo(*KnapsackItemInfo->Info());
	}
	throw FString("Don't exit Id for") + Id.ToString();
}

bool UKnapsackInfo::Amount(FName Id, int32& Result)
{
	FKnapsackItemInfo* KnapsackItemInfo = KnapsackItemInfoSet.Find(Id);
	if (KnapsackItemInfo)
	{
		Result = KnapsackItemInfo->GetTotalAmount();
		return true;
	}
	return false;
}

bool UKnapsackInfo::Weight(FName Id, float& Result)
{
	FKnapsackItemInfo* KnapsackItemInfo = KnapsackItemInfoSet.Find(Id);
	if (KnapsackItemInfo)
	{
		Result = KnapsackItemInfo->GetTotalWeight();
		return true;
	}
	return false;
}

float UKnapsackInfo::TotalWeigth(FName Id)
{
	float TotalWeight = 0.f;
	float TempWeight = 0.f;
	for (TSet<FKnapsackItemInfo, TKnapsackItemInfoKeyFuncs>::TIterator It = KnapsackItemInfoSet.CreateIterator(); It; ++It) {
		TempWeight = (*It).GetTotalWeight();
		TotalWeight += TempWeight;
	}
	return TotalWeight;
}

bool UKnapsackInfo::AddOne(FName Id)
{
	FKnapsackItemInfo* KnapsackItemInfo = KnapsackItemInfoSet.Find(Id);
	if (KnapsackItemInfo == nullptr)
	{
		KnapsackItemInfoSet.Add(FKnapsackItemInfo(Id));
		return true;
	}
	else
	{
		return KnapsackItemInfo->IncrementAmount();
	}
}

void UKnapsackInfo::AddFull(FName Id)
{
	FKnapsackItemInfo* KnapsackItemInfo = KnapsackItemInfoSet.Find(Id);
	if (KnapsackItemInfo == nullptr)
	{
		KnapsackItemInfoSet.Add(FKnapsackItemInfo(Id, EKnapsackItemInfoInitialtion::FULL));
	}
	else
	{
		KnapsackItemInfo->fill();
	}
}

int32 UKnapsackInfo::Add(FName Id, int32 Amount)
{
	FKnapsackItemInfo* Value = KnapsackItemInfoSet.Find(Id);
	if (Value == nullptr)
	{
		FKnapsackItemInfo KnapsackItemInfo = FKnapsackItemInfo(Id);
		int32 Result = KnapsackItemInfo.IncreaseAmount(Amount);
		KnapsackItemInfoSet.Add(KnapsackItemInfo);
		return Result;
	}
	else
	{
		return Value->IncreaseAmount(Amount);
	}
}

bool UKnapsackInfo::RemoveOne(FName Id)
{
	FKnapsackItemInfo* Value = KnapsackItemInfoSet.Find(Id);
	if (Value == nullptr)
	{
		KnapsackItemInfoSet.Add(FKnapsackItemInfo(Id, EKnapsackItemInfoInitialtion::ZERO));
		return true;
	}
	else
	{
		return Value->DecrementAmount();
	}
}

void UKnapsackInfo::RemoveAll(FName Id)
{
	FKnapsackItemInfo* Value = KnapsackItemInfoSet.Find(Id);
	if (Value == nullptr)
	{
		KnapsackItemInfoSet.Add(FKnapsackItemInfo(Id, EKnapsackItemInfoInitialtion::ZERO));
	}
	else
	{
		return Value->clear();
	}
}

int32 UKnapsackInfo::Remove(FName Id, int32 Amount)
{
	FKnapsackItemInfo* Value = KnapsackItemInfoSet.Find(Id);
	if (Value == nullptr)
	{
		FKnapsackItemInfo KnapsackItemInfo = FKnapsackItemInfo(Id);
		int32 Result = KnapsackItemInfo.IncreaseAmount(Amount);
		KnapsackItemInfoSet.Add(*Value);
		return Result;
	}
	else
	{
		return Value->DecreaseAmount(Amount);
	}
}

void UKnapsackInfo::TransferOneFrom(UKnapsackInfo* Other, FName Id, int32 Amount)
{
	int32 RealRemove = Other->Remove(Id, Amount);
	int32 RealAdd = this->Add(Id, RealRemove);
	if (RealAdd != RealRemove)
	{
		Other->Add(Id, RealRemove - RealAdd);
	}
}

void UKnapsackInfo::TransferOneAllFrom(UKnapsackInfo* Other, FName Id)
{
	int32 Amount;
	bool b = Other->Amount(Id, Amount);
	if (b)
	{
		int32 RealAdd = this->Add(Id, Amount);
		if (RealAdd != Amount)
		{
			Other->Remove(Id, RealAdd);
		}
	}
}

void UKnapsackInfo::TransferAllFrom(UKnapsackInfo* Other)
{
	TArray<FName> Ids = Other->Ids();
	for (TArray<FName>::TConstIterator It = Ids.CreateConstIterator(); It; It++)
	{
		TransferOneAllFrom(Other, *It);
	}
}

void UKnapsackInfo::TransferOneTo(UKnapsackInfo* Other, FName Id, int32 Amount)
{
	int32 RealRemove = this->Remove(Id, Amount);
	int32 RealAdd = Other->Add(Id, RealRemove);
	if (RealAdd != RealRemove)
	{
		this->Add(Id, RealRemove - RealAdd);
	}
}

void UKnapsackInfo::TransferOneAllTo(UKnapsackInfo* Other, FName Id)
{
	int32 Amount;
	bool b = this->Amount(Id, Amount);
	if (b)
	{
		int32 RealAdd = Other->Add(Id, Amount);
		if (RealAdd != Amount)
		{
			this->Remove(Id, RealAdd);
		}
	}
}

void UKnapsackInfo::TransferAllTo(UKnapsackInfo* Other)
{
	TArray<FName> Ids = Other->Ids();
	for (TArray<FName>::TConstIterator It = Ids.CreateConstIterator(); It; It++)
	{
		TransferOneAllTo(Other, *It);
	}
}

void UKnapsackItemInventory::Init(UDataTable* InDataTable)
{
	this->DataTable = InDataTable;
}

bool UKnapsackItemInventory::FindInventoryItemInfoById(const FName Id, FInventoryItemInfo& Result)
{
	if (DataTable)
	{
		FString Content;
		FInventoryItemInfo* Value = DataTable->FindRow<FInventoryItemInfo>(Id, Content);
		if (Value)
		{
			Result = *Value;
			return true;
		}
	}
	return false;
}
