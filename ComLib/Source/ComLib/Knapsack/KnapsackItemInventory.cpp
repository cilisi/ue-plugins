#include "KnapsackItemInventory.h"
#include "Datas.h"
#include "Resources.h"
FInventoryItemCompoundInfo::FInventoryItemCompoundInfo()
{
	Id = FName("Id");
	Amount = 0;
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
