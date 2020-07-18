#include "Datas.h"
#include "Resources.h"
#include "Asserts.h"
#include "JsonObjectConverter.h"
#include "Misc/FileHelper.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "UObject/UnrealType.h"
#include "UObject/EnumProperty.h"
#include "DataTableUtils.h"
#include "Engine/DataTable.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/FileHelper.h"
#include "DataTableUtils.h"
#include "Engine/UserDefinedStruct.h"

bool UDatas::FillDataTableFromCSVString(UDataTable* DataTable, const FString& CSVString)
{
	if (!DataTable || (CSVString.Len() == 0))
	{
		return false;
	}
	// Call bulit-in function
	TArray<FString> Errors = DataTable->CreateTableFromCSVString(CSVString);

	if (Errors.Num())
	{
		return false;
	}

	return true;
}

bool UDatas::FillDataTableFromCSVFile(UDataTable* DataTable, const FString& CSVFilePath)
{
	FString CSVString;
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*CSVFilePath))
	{
		FFileHelper::LoadFileToString(CSVString, *CSVFilePath);
		return UDatas::FillDataTableFromCSVString(DataTable, CSVString);
	}
	return false;
}

bool UDatas::FillDataTableFromJSONString(UDataTable* DataTable, const FString& JSONString)
{
	if (!DataTable || (JSONString.Len() == 0))
	{
		return false;
	}
	// Call bulit-in function
	TArray<FString> Errors = DataTable->CreateTableFromJSONString(JSONString);

	if (Errors.Num())
	{
		return false;
	}

	return true;
}

bool UDatas::FillDataTableFromJSONFile(UDataTable* DataTable, const FString& JSONFilePath)
{
	FString JSONString;
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*JSONFilePath))
	{
		FFileHelper::LoadFileToString(JSONString, *JSONFilePath);
		return UDatas::FillDataTableFromJSONString(DataTable, JSONString);
	}
	return false;
}

UDataTable* UDatas::ParseJsonToDataTable(const FString& JsonData, UScriptStruct* TableType)
{
	if (JsonData.IsEmpty() || !TableType) return nullptr;
	FString newJsonData = JsonData;
	UDataTable* OutDataTable = NewObject<UDataTable>(GWorld, FName(TEXT("NewDataTable")));
	if (!OutDataTable) return nullptr;
	OutDataTable->RowStruct = TableType;
	TArray<FString> OutError = OutDataTable->CreateTableFromJSONString(newJsonData);
	if (OutError.Num() != 0)
	{
		newJsonData.InsertAt(newJsonData.Find("{") + 1, "\r\n\t\t\"Name\": \"_MyTempName\",");
		newJsonData = "[" + newJsonData + "]";
		OutError = OutDataTable->CreateTableFromJSONString(newJsonData);
	}
	if (OutError.Num() != 0) return nullptr;
	return OutDataTable;
}

bool UDatas::ParseDataTableToJson(UDataTable* DataTable, FString& Json)
{
	if (!FDataTableExporterJSON(EDataTableExportFlags::UseJsonObjectsForStructs, Json).WriteTable(*DataTable))
	{
		Json = TEXT("Missing RowStruct!\n");
		return false;
	}
	return true;
}

UDataTable* UDatas::ParseCsvToDataTable(const FString& JsonData, UScriptStruct* TableType)
{
	if (JsonData.IsEmpty() || !TableType) return nullptr;
	FString newJsonData = JsonData;
#if !WITH_EDITOR
	auto* ptr = TableType->Children;
	FString LName, DisplayName, TFrom, TTo, Lstr, Rstr;
	JsonData.Split("\n", &Lstr, &Rstr);
	while (ptr)
	{
		LName = ptr->GetName();
		DisplayName = ptr->GetAuthoredName();
		TFrom = ("," + DisplayName + ",");
		TTo = ("," + LName + ",");
		if (!Lstr.Contains(TFrom))
		{
			TFrom = ("," + DisplayName + '\n');
			TTo = ("," + LName + '\n');
		}
		Lstr = Lstr.Replace(*TFrom, *TTo);
		ptr = ptr->Next;
	}
	Lstr.AppendChar('\n');
	newJsonData = Lstr.Append(Rstr);
#endif //WITH_EDITOR
	UDataTable* OutDataTable = NewObject<UDataTable>(GWorld, FName(TEXT("NewDataTable")));
	if (!OutDataTable) return nullptr;
	OutDataTable->RowStruct = TableType;
	TArray<FString> OutError = OutDataTable->CreateTableFromCSVString(newJsonData);
	if (OutError.Num() != 0) return nullptr;
	return OutDataTable;
}

bool UDatas::ParseDataTableToCsv(UDataTable* DataTable, FString& Json)
{
	if (!DataTable->RowStruct)
	{
		return false;
	}
	Json.Empty();
	// Write the header (column titles)
	FString ImportKeyField;
	if (!DataTable->ImportKeyField.IsEmpty())
	{
		// Write actual name if we have it
		ImportKeyField = DataTable->ImportKeyField;
		Json += ImportKeyField;
	}
	else
	{
		Json += TEXT("---");
	}
	UProperty* SkipProperty = nullptr;
	for (TFieldIterator<UProperty> It(DataTable->RowStruct); It; ++It)
	{
		UProperty* BaseProp = *It;
		check(BaseProp);
		FString ColumnHeader = DataTableUtils::GetPropertyExportName(BaseProp);
		if (ColumnHeader == ImportKeyField)
		{
			// Don't write header again if this is the name field, and save for skipping later
			SkipProperty = BaseProp;
			continue;
		}
		Json += TEXT(",");
		Json += ColumnHeader;
	}
	Json += TEXT("\n");
	// Write each row
	for (auto RowIt = DataTable->GetRowMap().CreateConstIterator(); RowIt; ++RowIt)
	{
		FName RowName = RowIt.Key();
		Json += RowName.ToString();
		uint8* RowData = RowIt.Value();
		//WriteRow(DataTable.RowStruct, RowData);
		{
			if (!DataTable->RowStruct)
			{
				return false;
			}
			for (TFieldIterator<UProperty> It(DataTable->RowStruct); It; ++It)
			{
				UProperty* BaseProp = *It;
				check(BaseProp);
				if (BaseProp == SkipProperty)
				{
					continue;
				}
				const void* Data = BaseProp->ContainerPtrToValuePtr<void>(RowData, 0);
				//WriteStructEntry(InRowData, BaseProp, Data);
				{
					Json += TEXT(",");
					const FString PropertyValue = DataTableUtils::GetPropertyValueAsString(BaseProp, (uint8*)RowData, EDataTableExportFlags::None);
					Json += TEXT("\"");
					Json += PropertyValue.Replace(TEXT("\""), TEXT("\"\""));
					Json += TEXT("\"");
				}
			}
		}
		Json += TEXT("\n");
	}
	return true;
}

bool UDatas::Generic_GetDataTableFirstRow(UDataTable* DataTable, UScriptStruct* TableType, void* OutRowStructDataPtr)
{
	return UDatas::GetStructDataFromDataTable(DataTable, OutRowStructDataPtr, 0);
}

bool UDatas::Generic_GetDataTableLastRow(UDataTable* DataTable, UScriptStruct* TableType, void* OutRowStructDataPtr)
{
	return UDatas::GetStructDataFromDataTable(DataTable, OutRowStructDataPtr, CB_MAX_INT32);
}

bool UDatas::Generic_GetDataTableRow(UDataTable* DataTable, int32 Row, UScriptStruct* TableType, void* OutRowStructDataPtr)
{
	return UDatas::GetStructDataFromDataTable(DataTable, OutRowStructDataPtr, Row);
}

bool UDatas::GetStructDataFromDataTable(UDataTable* DataTable, void* OutRowStructDataPtr, int32 Index)
{
	if (DataTable)
	{
		TArray<FName> Names = DataTable->GetRowNames();
		if (Names.Num() != 0)
		{
			UScriptStruct* StructType = DataTable->RowStruct;
			if (Index < 0)
			{
				Index = 0;
			}
			if (Index > Names.Num() - 1)
			{
				Index = Names.Num() - 1;
			}
			void* RowPtr = DataTable->FindRowUnchecked(Names[Index]);
			if (StructType && RowPtr)
			{
				StructType->CopyScriptStruct(OutRowStructDataPtr, RowPtr);
				return true;
			}
		}
	}
	return false;
}

bool UDatas::Generic_StructToJson(FString& Json, UScriptStruct* StructDefinition, void* InStruct)
{
	if (FJsonObjectConverter::UStructToJsonObjectString(StructDefinition, InStruct, Json, 0, 0))
	{
		UDataTable* tempDT = ParseJsonToDataTable(Json, StructDefinition);
		if (tempDT)
		{
			ParseDataTableToJson(tempDT, Json);
			FString Lstr, Rstr;
			Json.Split(",", &Lstr, &Rstr);
			Json = "{" + Rstr.Left(Rstr.Len() - 1);
			return true;
		}
	}
	return false;
}

bool UDatas::Generic_JsonToStruct(const FString& Json, UScriptStruct* StructDefinition, void* OutStructPtr)
{
	if (!Json.IsEmpty())
	{
		UDataTable* InDataTable = NewObject<UDataTable>(GWorld);
		if (InDataTable)
		{
			InDataTable->RowStruct = StructDefinition;
			TArray<FString> OutError = InDataTable->CreateTableFromJSONString(Json);
			if (OutError.Num() == 0)
			{
				void* RowPtr = InDataTable->FindRowUnchecked(InDataTable->GetRowNames()[0]);
				UScriptStruct* StructType = InDataTable->RowStruct;
				if (RowPtr && StructType)
				{
					StructType->CopyScriptStruct(OutStructPtr, RowPtr);
					return true;
				}
			}
		}
	}
	return false;
}

namespace
{
	const TCHAR* JSONTypeToString(const EJson InType)
	{
		switch (InType)
		{
		case EJson::None:
			return TEXT("None");
		case EJson::Null:
			return TEXT("Null");
		case EJson::String:
			return TEXT("String");
		case EJson::Number:
			return TEXT("Number");
		case EJson::Boolean:
			return TEXT("Boolean");
		case EJson::Array:
			return TEXT("Array");
		case EJson::Object:
			return TEXT("Object");
		default:
			return TEXT("Unknown");
		}
	}
	void WriteJSONObjectStartWithOptionalIdentifier(FDataTableExporterJSON::FDataTableJsonWriter& InJsonWriter, const FString* InIdentifier)
	{
		if (InIdentifier)
		{
			InJsonWriter.WriteObjectStart(*InIdentifier);
		}
		else
		{
			InJsonWriter.WriteObjectStart();
		}
	}
	template <typename ValueType>
	void WriteJSONValueWithOptionalIdentifier(FDataTableExporterJSON::FDataTableJsonWriter& InJsonWriter, const FString* InIdentifier, const ValueType InValue)
	{
		if (InIdentifier)
		{
			InJsonWriter.WriteValue(*InIdentifier, InValue);
		}
		else
		{
			InJsonWriter.WriteValue(InValue);
		}
	}
}
FString FDataTableExporterJSON::GetKeyFieldName(const UDataTable& DataTable)
{
	FString ExplicitString = DataTable.ImportKeyField;
	if (ExplicitString.IsEmpty())
	{
		return TEXT("Name");
	}
	else
	{
		return ExplicitString;
	}
}
FDataTableExporterJSON::FDataTableExporterJSON(const EDataTableExportFlags InDTExportFlags, FString& OutExportText)
	: DTExportFlags(InDTExportFlags)
	, JsonWriter(TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>::Create(&OutExportText))
	, bJsonWriterNeedsClose(true)
{
}
FDataTableExporterJSON::FDataTableExporterJSON(const EDataTableExportFlags InDTExportFlags, TSharedRef<FDataTableJsonWriter> InJsonWriter)
	: DTExportFlags(InDTExportFlags)
	, JsonWriter(InJsonWriter)
	, bJsonWriterNeedsClose(false)
{
}
FDataTableExporterJSON::~FDataTableExporterJSON()
{
	if (bJsonWriterNeedsClose)
	{
		JsonWriter->Close();
	}
}
bool FDataTableExporterJSON::WriteTable(const UDataTable& DataTable)
{
	if (!DataTable.RowStruct)
	{
		return false;
	}
	FString KeyField = GetKeyFieldName(DataTable);
	JsonWriter->WriteArrayStart();
	// Iterate over rows
	for (auto RowIt = DataTable.GetRowMap().CreateConstIterator(); RowIt; ++RowIt)
	{
		JsonWriter->WriteObjectStart();
		{
			// RowName
			const FName RowName = RowIt.Key();
			JsonWriter->WriteValue(KeyField, RowName.ToString());
			// Now the values
			uint8* RowData = RowIt.Value();
			WriteRow(DataTable.RowStruct, RowData, &KeyField);
		}
		JsonWriter->WriteObjectEnd();
	}
	JsonWriter->WriteArrayEnd();
	return true;
}
bool FDataTableExporterJSON::WriteTableAsObject(const UDataTable& DataTable)
{
	if (!DataTable.RowStruct)
	{
		return false;
	}
	JsonWriter->WriteObjectStart(DataTable.GetName());
	// Iterate over rows
	for (auto RowIt = DataTable.GetRowMap().CreateConstIterator(); RowIt; ++RowIt)
	{
		// RowName
		const FName RowName = RowIt.Key();
		JsonWriter->WriteObjectStart(RowName.ToString());
		{
			// Now the values
			uint8* RowData = RowIt.Value();
			WriteRow(DataTable.RowStruct, RowData);
		}
		JsonWriter->WriteObjectEnd();
	}
	JsonWriter->WriteObjectEnd();
	return true;
}
bool FDataTableExporterJSON::WriteRow(const UScriptStruct* InRowStruct, const void* InRowData, const FString* FieldToSkip)
{
	if (!InRowStruct)
	{
		return false;
	}
	return WriteStruct(InRowStruct, InRowData, FieldToSkip);
}
bool FDataTableExporterJSON::WriteStruct(const UScriptStruct* InStruct, const void* InStructData, const FString* FieldToSkip)
{
	for (TFieldIterator<const UProperty> It(InStruct); It; ++It)
	{
		const UProperty* BaseProp = *It;
		check(BaseProp);
		const FString Identifier = DataTableUtils::GetPropertyExportName(BaseProp, DTExportFlags);
		if (FieldToSkip && *FieldToSkip == Identifier)
		{
			// Skip this field
			continue;
		}
		if (BaseProp->ArrayDim == 1)
		{
			const void* Data = BaseProp->ContainerPtrToValuePtr<void>(InStructData, 0);
			WriteStructEntry(InStructData, BaseProp, Data);
		}
		else
		{
			JsonWriter->WriteArrayStart(Identifier);
			for (int32 ArrayEntryIndex = 0; ArrayEntryIndex < BaseProp->ArrayDim; ++ArrayEntryIndex)
			{
				const void* Data = BaseProp->ContainerPtrToValuePtr<void>(InStructData, ArrayEntryIndex);
				WriteContainerEntry(BaseProp, Data);
			}
			JsonWriter->WriteArrayEnd();
		}
	}
	return true;
}
bool FDataTableExporterJSON::WriteStructEntry(const void* InRowData, const UProperty* InProperty, const void* InPropertyData)
{
	const FString Identifier = DataTableUtils::GetPropertyExportName(InProperty, DTExportFlags);
	if (const UEnumProperty* EnumProp = Cast<const UEnumProperty>(InProperty))
	{
		const FString PropertyValue = DataTableUtils::GetPropertyValueAsString(EnumProp, (uint8*)InRowData, DTExportFlags);
		JsonWriter->WriteValue(Identifier, PropertyValue);
	}
	else if (const UNumericProperty* NumProp = Cast<const UNumericProperty>(InProperty))
	{
		if (NumProp->IsEnum())
		{
			const FString PropertyValue = DataTableUtils::GetPropertyValueAsString(InProperty, (uint8*)InRowData, DTExportFlags);
			JsonWriter->WriteValue(Identifier, PropertyValue);
		}
		else if (NumProp->IsInteger())
		{
			const int64 PropertyValue = NumProp->GetSignedIntPropertyValue(InPropertyData);
			JsonWriter->WriteValue(Identifier, PropertyValue);
		}
		else
		{
			const double PropertyValue = NumProp->GetFloatingPointPropertyValue(InPropertyData);
			JsonWriter->WriteValue(Identifier, PropertyValue);
		}
	}
	else if (const UBoolProperty* BoolProp = Cast<const UBoolProperty>(InProperty))
	{
		const bool PropertyValue = BoolProp->GetPropertyValue(InPropertyData);
		JsonWriter->WriteValue(Identifier, PropertyValue);
	}
	else if (const UArrayProperty* ArrayProp = Cast<const UArrayProperty>(InProperty))
	{
		JsonWriter->WriteArrayStart(Identifier);
		FScriptArrayHelper ArrayHelper(ArrayProp, InPropertyData);
		for (int32 ArrayEntryIndex = 0; ArrayEntryIndex < ArrayHelper.Num(); ++ArrayEntryIndex)
		{
			const uint8* ArrayEntryData = ArrayHelper.GetRawPtr(ArrayEntryIndex);
			WriteContainerEntry(ArrayProp->Inner, ArrayEntryData);
		}
		JsonWriter->WriteArrayEnd();
	}
	else if (const USetProperty* SetProp = Cast<const USetProperty>(InProperty))
	{
		JsonWriter->WriteArrayStart(Identifier);
		FScriptSetHelper SetHelper(SetProp, InPropertyData);
		for (int32 SetSparseIndex = 0; SetSparseIndex < SetHelper.GetMaxIndex(); ++SetSparseIndex)
		{
			if (SetHelper.IsValidIndex(SetSparseIndex))
			{
				const uint8* SetEntryData = SetHelper.GetElementPtr(SetSparseIndex);
				WriteContainerEntry(SetHelper.GetElementProperty(), SetEntryData);
			}
		}
		JsonWriter->WriteArrayEnd();
	}
	else if (const UMapProperty* MapProp = Cast<const UMapProperty>(InProperty))
	{
		JsonWriter->WriteObjectStart(Identifier);
		FScriptMapHelper MapHelper(MapProp, InPropertyData);
		for (int32 MapSparseIndex = 0; MapSparseIndex < MapHelper.GetMaxIndex(); ++MapSparseIndex)
		{
			if (MapHelper.IsValidIndex(MapSparseIndex))
			{
				const uint8* MapKeyData = MapHelper.GetKeyPtr(MapSparseIndex);
				const uint8* MapValueData = MapHelper.GetValuePtr(MapSparseIndex);
				// JSON object keys must always be strings
				const FString KeyValue = DataTableUtils::GetPropertyValueAsStringDirect(MapHelper.GetKeyProperty(), (uint8*)MapKeyData, DTExportFlags);
				WriteContainerEntry(MapHelper.GetValueProperty(), MapValueData, &KeyValue);
			}
		}
		JsonWriter->WriteObjectEnd();
	}
	else if (const UStructProperty* StructProp = Cast<const UStructProperty>(InProperty))
	{
		if (!!(DTExportFlags & EDataTableExportFlags::UseJsonObjectsForStructs))
		{
			JsonWriter->WriteObjectStart(Identifier);
			WriteStruct(StructProp->Struct, InPropertyData);
			JsonWriter->WriteObjectEnd();
		}
		else
		{
			const FString PropertyValue = DataTableUtils::GetPropertyValueAsString(InProperty, (uint8*)InRowData, DTExportFlags);
			JsonWriter->WriteValue(Identifier, PropertyValue);
		}
	}
	else
	{
		const FString PropertyValue = DataTableUtils::GetPropertyValueAsString(InProperty, (uint8*)InRowData, DTExportFlags);
		JsonWriter->WriteValue(Identifier, PropertyValue);
	}
	return true;
}
bool FDataTableExporterJSON::WriteContainerEntry(const UProperty* InProperty, const void* InPropertyData, const FString* InIdentifier)
{
	if (const UEnumProperty* EnumProp = Cast<const UEnumProperty>(InProperty))
	{
		const FString PropertyValue = DataTableUtils::GetPropertyValueAsStringDirect(InProperty, (uint8*)InPropertyData, DTExportFlags);
		WriteJSONValueWithOptionalIdentifier(*JsonWriter, InIdentifier, PropertyValue);
	}
	else if (const UNumericProperty* NumProp = Cast<const UNumericProperty>(InProperty))
	{
		if (NumProp->IsEnum())
		{
			const FString PropertyValue = DataTableUtils::GetPropertyValueAsStringDirect(InProperty, (uint8*)InPropertyData, DTExportFlags);
			WriteJSONValueWithOptionalIdentifier(*JsonWriter, InIdentifier, PropertyValue);
		}
		else if (NumProp->IsInteger())
		{
			const int64 PropertyValue = NumProp->GetSignedIntPropertyValue(InPropertyData);
			WriteJSONValueWithOptionalIdentifier(*JsonWriter, InIdentifier, PropertyValue);
		}
		else
		{
			const double PropertyValue = NumProp->GetFloatingPointPropertyValue(InPropertyData);
			WriteJSONValueWithOptionalIdentifier(*JsonWriter, InIdentifier, PropertyValue);
		}
	}
	else if (const UBoolProperty* BoolProp = Cast<const UBoolProperty>(InProperty))
	{
		const bool PropertyValue = BoolProp->GetPropertyValue(InPropertyData);
		WriteJSONValueWithOptionalIdentifier(*JsonWriter, InIdentifier, PropertyValue);
	}
	else if (const UStructProperty* StructProp = Cast<const UStructProperty>(InProperty))
	{
		if (!!(DTExportFlags & EDataTableExportFlags::UseJsonObjectsForStructs))
		{
			WriteJSONObjectStartWithOptionalIdentifier(*JsonWriter, InIdentifier);
			WriteStruct(StructProp->Struct, InPropertyData);
			JsonWriter->WriteObjectEnd();
		}
		else
		{
			const FString PropertyValue = DataTableUtils::GetPropertyValueAsStringDirect(InProperty, (uint8*)InPropertyData, DTExportFlags);
			WriteJSONValueWithOptionalIdentifier(*JsonWriter, InIdentifier, PropertyValue);
		}
	}
	else if (const UArrayProperty* ArrayProp = Cast<const UArrayProperty>(InProperty))
	{
		// Cannot nest arrays
		return false;
	}
	else if (const USetProperty* SetProp = Cast<const USetProperty>(InProperty))
	{
		// Cannot nest sets
		return false;
	}
	else if (const UMapProperty* MapProp = Cast<const UMapProperty>(InProperty))
	{
		// Cannot nest maps
		return false;
	}
	else
	{
		const FString PropertyValue = DataTableUtils::GetPropertyValueAsStringDirect(InProperty, (uint8*)InPropertyData, DTExportFlags);
		WriteJSONValueWithOptionalIdentifier(*JsonWriter, InIdentifier, PropertyValue);
	}
	return true;
}
