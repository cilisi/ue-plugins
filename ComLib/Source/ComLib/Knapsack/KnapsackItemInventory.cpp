#include "KnapsackItemInventory.h"
#include "Datas.h"
#include "Resources.h"

FInventoryItemInfo::FInventoryItemInfo()
{
	ItemIndex++;
	ItemID = FName("ItemID", ItemIndex);
	Name = FName("Item");
	Action = FText::FromString("The Item Action Text");
	Description = FText::FromString("The Item Description Text");
	Thumbnail = nullptr;
	Weight = 0.f;
	bCanUsed = true;
}

bool UKnapsackItemInventory::ReadConfig(const FString JsonConfigPath, UDataTable* DataTable)
{
	FString JsonConfig;
	if (JsonConfigPath.Len() != 0) {
		return UDatas::FillDataTableFromJSONFile(DataTable, JsonConfigPath);
	}
	return false;
}
