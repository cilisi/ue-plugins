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
	FInventoryItemInfo FoundInventoryItemInfo;
	KnapsackItemInventory->FindInventoryItemInfo(Id, FoundInventoryItemInfo);
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
	MaxItemCount = 40;
	MaxDurability = 100;
	CurrentDurability = 100;
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

bool UKnapsackInfo::Info(FName Id, FInventoryItemInfo& result)
{
	UKnapsackItemInventory* KnapsackItemInventory = UKnapsackItemInventory::GetSingletonInstance();
	if (!KnapsackItemInventory->IsExistInventoryItemInfo(Id)) {
		return false;
	}
	FKnapsackItemInfo* KnapsackItemInfo = KnapsackItemInfoSet.Find(Id);
	if (KnapsackItemInfo)
	{
		result = *KnapsackItemInfo->Info();
		return true;
	}
	return false;
}

int32 UKnapsackInfo::Count()
{
	return KnapsackItemInfoSet.Num();
}

bool UKnapsackInfo::Amount(FName Id, int32& Result)
{
	UKnapsackItemInventory* KnapsackItemInventory = UKnapsackItemInventory::GetSingletonInstance();
	if (!KnapsackItemInventory->IsExistInventoryItemInfo(Id)) {
		return false;
	}
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
	UKnapsackItemInventory* KnapsackItemInventory = UKnapsackItemInventory::GetSingletonInstance();
	if (!KnapsackItemInventory->IsExistInventoryItemInfo(Id)) {
		return false;
	}
	FKnapsackItemInfo* KnapsackItemInfo = KnapsackItemInfoSet.Find(Id);
	if (KnapsackItemInfo)
	{
		Result = KnapsackItemInfo->GetTotalWeight();
		return true;
	}
	return false;
}

float UKnapsackInfo::TotalWeigth()
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
	UKnapsackItemInventory* KnapsackItemInventory = UKnapsackItemInventory::GetSingletonInstance();
	if (!KnapsackItemInventory->IsExistInventoryItemInfo(Id)) {
		return false;
	}
	FKnapsackItemInfo* KnapsackItemInfo = KnapsackItemInfoSet.Find(Id);
	if (KnapsackItemInfo == nullptr)
	{
		if (Count() >= MaxItemCount) {
			return false;
		}
		KnapsackItemInfoSet.Add(FKnapsackItemInfo(Id));
		return true;
	}
	else
	{
		return KnapsackItemInfo->IncrementAmount();
	}
}

bool UKnapsackInfo::AddFull(FName Id)
{
	UKnapsackItemInventory* KnapsackItemInventory = UKnapsackItemInventory::GetSingletonInstance();
	if (!KnapsackItemInventory->IsExistInventoryItemInfo(Id)) {
		return false;
	}
	FKnapsackItemInfo* KnapsackItemInfo = KnapsackItemInfoSet.Find(Id);
	if (KnapsackItemInfo == nullptr)
	{
		if (Count() >= MaxItemCount) {
			return false;
		}
		KnapsackItemInfoSet.Add(FKnapsackItemInfo(Id, EKnapsackItemInfoInitialtion::FULL));
		return true;
	}
	else
	{
		KnapsackItemInfo->fill();
		return true;
	}
}

bool UKnapsackInfo::Add(FName Id, int32 Amount, int32& RealAddAmount)
{
	UKnapsackItemInventory* KnapsackItemInventory = UKnapsackItemInventory::GetSingletonInstance();
	if (!KnapsackItemInventory->IsExistInventoryItemInfo(Id)) {
		return false;
	}
	FKnapsackItemInfo* Value = KnapsackItemInfoSet.Find(Id);
	if (Value == nullptr)
	{
		if (Count() >= MaxItemCount) {
			return false;
		}
		FKnapsackItemInfo KnapsackItemInfo = FKnapsackItemInfo(Id);
		RealAddAmount = KnapsackItemInfo.IncreaseAmount(Amount);
		KnapsackItemInfoSet.Add(KnapsackItemInfo);
	}
	else
	{
		RealAddAmount = Value->IncreaseAmount(Amount);
	}
	return true;
}

bool UKnapsackInfo::RemoveOne(FName Id)
{
	UKnapsackItemInventory* KnapsackItemInventory = UKnapsackItemInventory::GetSingletonInstance();
	if (!KnapsackItemInventory->IsExistInventoryItemInfo(Id)) {
		return false;
	}
	FKnapsackItemInfo* Value = KnapsackItemInfoSet.Find(Id);
	if (Value == nullptr)
	{
		return false;
	}
	else
	{
		return Value->DecrementAmount();
	}
}

bool UKnapsackInfo::RemoveAll(FName Id)
{
	UKnapsackItemInventory* KnapsackItemInventory = UKnapsackItemInventory::GetSingletonInstance();
	if (!KnapsackItemInventory->IsExistInventoryItemInfo(Id)) {
		return false;
	}
	FKnapsackItemInfo* Value = KnapsackItemInfoSet.Find(Id);
	if (Value == nullptr)
	{
		return false;
	}
	else
	{
		Value->clear();
		return true;
	}
}

bool UKnapsackInfo::Remove(FName Id, int32 Amount, int32& RealRemoveAmount)
{
	UKnapsackItemInventory* KnapsackItemInventory = UKnapsackItemInventory::GetSingletonInstance();
	if (!KnapsackItemInventory->IsExistInventoryItemInfo(Id)) {
		return false;
	}
	FKnapsackItemInfo* Value = KnapsackItemInfoSet.Find(Id);
	if (Value == nullptr)
	{
		RealRemoveAmount = 0;
		return false;
	}
	else
	{
		RealRemoveAmount = Value->DecreaseAmount(Amount);
		return true;
	}
}

void UKnapsackInfo::TransferOneFrom(UKnapsackInfo* Other, FName Id, int32 Amount)
{
	int32 RealRemove;
	bool IsRmove = Other->Remove(Id, Amount, RealRemove);
	if (IsRmove)
	{
		int32 RealAdd;
		bool IsAdd = this->Add(Id, RealRemove, RealAdd);
		if (IsAdd)
		{
			if (RealAdd != RealRemove)
			{
				int32 Diff;
				Other->Add(Id, RealRemove - RealAdd, Diff);
			}
		}
		else {
			Other->Add(Id, Amount, RealRemove);
		}

	}
}

void UKnapsackInfo::TransferOneAllFrom(UKnapsackInfo* Other, FName Id)
{
	int32 Amount;
	bool b = Other->Amount(Id, Amount);
	if (b)
	{
		int32 RealAdd;
		bool Add = this->Add(Id, Amount, RealAdd);
		if (Add)
		{
			int32 Diff;
			Other->Remove(Id, RealAdd, Diff);
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
	int32 RealRemove;
	bool Remove = this->Remove(Id, Amount, RealRemove);
	if (Remove)
	{
		int32 RealAdd;
		bool Add = Other->Add(Id, RealRemove, RealAdd);
		if (Add && RealAdd != RealRemove)
		{
			int32 Diff;
			this->Add(Id, RealRemove - RealAdd, Diff);
		}
	}

}

void UKnapsackInfo::TransferOneAllTo(UKnapsackInfo* Other, FName Id)
{
	int32 Amount;
	bool b = this->Amount(Id, Amount);
	if (b)
	{
		int32 RealAdd;
		bool Add = Other->Add(Id, Amount, RealAdd);
		if (Add)
		{
			int32 Diff;
			this->Remove(Id, RealAdd, Diff);
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

void UKnapsackInfo::IncreaseDurability(int32 Durability)
{
	if (Durability <= 0)
	{
		DecreaseDurability(-Durability);
	}
	else if (Durability >= MaxDurability)
	{
		CurrentDurability = MaxDurability;
	}
	else {
		CurrentDurability = Durability;
	}
}

void UKnapsackInfo::DecreaseDurability(int32 Durability)
{
	if (Durability <= 0)
	{
		IncreaseDurability(-Durability);
	}
	else if (Durability >= MaxDurability)
	{
		CurrentDurability = 0;
	}
	else {
		CurrentDurability = Durability;
	}
}

bool UKnapsackInfo::IsDamage()
{
	return CurrentDurability == 0;
}

void UKnapsackItemInventory::Init(UDataTable* InDataTable)
{
	this->DataTable = InDataTable;
}

bool UKnapsackItemInventory::IsExistInventoryItemInfo(const FName Id)
{
	if (DataTable)
	{
		return DataTable->FindRow<FInventoryItemInfo>(Id, FString()) != nullptr;
	}
	return false;
}

void UKnapsackItemInventory::FindInventoryItemInfo(const FName Id, FInventoryItemInfo& Result)
{
	if (DataTable)
	{
		FString Content;
		FInventoryItemInfo* Value = DataTable->FindRow<FInventoryItemInfo>(Id, Content);
		if (Value)
		{
			Result = *Value;
		}
	}
}
