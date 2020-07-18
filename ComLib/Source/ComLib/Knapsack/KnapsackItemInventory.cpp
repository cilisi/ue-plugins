#include "KnapsackItemInventory.h"
#include "Datas.h"
#include "Resources.h"

FInventoryItemInfo::FInventoryItemInfo()
{
	ItemID = FName("ItemID");
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
		bool b = UDatas::FillDataTableFromJSONFile(DataTable, JsonConfigPath);
		if (b)
		{
			UDatas::HandleDataTableRowNameForNumberate(DataTable);
		}
	}
	return false;
}
