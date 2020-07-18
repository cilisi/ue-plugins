#pragma once
#include "Globals.h"

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "Policies/PrettyJsonPrintPolicy.h"
#include "Dom/JsonValue.h"
#include "Dom/JsonObject.h"
#include "Datas.generated.h"

UCLASS()
class COMLIB_API UDatas : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "CB_Datas")
		/** Read JSON string to DataTable **/
		static UDataTable* ParseJsonToDataTable(const FString& InData, UScriptStruct* TableType);

	UFUNCTION(BlueprintCallable, Category = "CB_Datas")
		/** Read CSV string to DataTable **/
		static UDataTable* ParseCsvToDataTable(const FString& InData, UScriptStruct* TableType);

	UFUNCTION(BlueprintCallable, Category = "CB_Datas")
		/** Write DataTable to CSV **/
		static bool ParseDataTableToCsv(UDataTable* DataTable, FString& ExportedText);

	UFUNCTION(BlueprintCallable, Category = "CB_Datas")
		/** Write DataTable to JSON **/
		static bool ParseDataTableToJson(UDataTable* DataTable, FString& ExportedText);

	UFUNCTION(BlueprintCallable, Category = "CB_Datas", CustomThunk, meta = (CustomStructureParam = "OutRow"))
		/** Get first row from DataTable **/
		static bool GetDataTableFirstRow(UDataTable* DataTable, FTableRowBase& OutRow) { check(0);return false; }
	static bool Generic_GetDataTableFirstRow(UDataTable* DataTable, UScriptStruct* StructDefinition, void* OutRowStructDataPtr);
	DECLARE_FUNCTION(execGetDataTableFirstRow) {
		P_GET_OBJECT(UDataTable, DataTable);

		Stack.StepCompiledIn<UStructProperty>(NULL);
		void* OutRowStructDataPtr = Stack.MostRecentPropertyAddress;

		P_FINISH;
		bool bSuccess = false;

		UStructProperty* StructProp = Cast<UStructProperty>(Stack.MostRecentProperty);
		if (StructProp && OutRowStructDataPtr)
		{
			UScriptStruct* OutputType = StructProp->Struct;

			P_NATIVE_BEGIN;
			bSuccess = Generic_GetDataTableFirstRow(DataTable, OutputType, OutRowStructDataPtr);
			P_NATIVE_END;
		}
		*(bool*)RESULT_PARAM = bSuccess;
	}

	UFUNCTION(BlueprintCallable, Category = "CB_Datas", CustomThunk, meta = (CustomStructureParam = "OutRow"))
		/** Get first row from DataTable **/
		static bool GetDataTableLastRow(UDataTable* DataTable, FTableRowBase& OutRow) { check(0);return false; }
	static bool Generic_GetDataTableLastRow(UDataTable* DataTable, UScriptStruct* TableType, void* OutRowStructDataPtr);
	DECLARE_FUNCTION(execGetDataTableLastRow) {
		P_GET_OBJECT(UDataTable, DataTable);

		Stack.StepCompiledIn<UStructProperty>(NULL);
		void* OutRowStructDataPtr = Stack.MostRecentPropertyAddress;

		P_FINISH;
		bool bSuccess = false;

		UStructProperty* StructProp = Cast<UStructProperty>(Stack.MostRecentProperty);
		if (StructProp && OutRowStructDataPtr)
		{
			UScriptStruct* OutputType = StructProp->Struct;

			P_NATIVE_BEGIN;
			bSuccess = Generic_GetDataTableLastRow(DataTable, OutputType, OutRowStructDataPtr);
			P_NATIVE_END;
		}
		*(bool*)RESULT_PARAM = bSuccess;
	}

	UFUNCTION(BlueprintCallable, Category = "CB_Datas", CustomThunk, meta = (CustomStructureParam = "OutRow"))
		/** Get first row from DataTable **/
		static bool GetDataTableRow(UDataTable* DataTable, int32 Row, FTableRowBase& OutRow) { check(0);return false; }
	static bool Generic_GetDataTableRow(UDataTable* DataTable, int32 Row, UScriptStruct* TableType, void* OutRowStructDataPtr);
	DECLARE_FUNCTION(execGetDataTableRow) {
		P_GET_OBJECT(UDataTable, DataTable);
		P_GET_SOFTOBJECT(int32, Row);
		Stack.StepCompiledIn<UStructProperty>(NULL);
		void* OutRowStructDataPtr = Stack.MostRecentPropertyAddress;

		P_FINISH;
		bool bSuccess = false;

		UStructProperty* StructProp = Cast<UStructProperty>(Stack.MostRecentProperty);
		if (StructProp && OutRowStructDataPtr)
		{
			UScriptStruct* OutputType = StructProp->Struct;

			P_NATIVE_BEGIN;
			bSuccess = Generic_GetDataTableRow(DataTable, Row, OutputType, OutRowStructDataPtr);
			P_NATIVE_END;
		}
		*(bool*)RESULT_PARAM = bSuccess;
	}

	UFUNCTION(BlueprintCallable, Category = "CB_Datas", CustomThunk, meta = (CustomStructureParam = "OutStruct"))
		/** Convert from JSON to struct **/
		static bool JsonToStruct(const FString& Json, FTableRowBase& OutStruct) { check(0);return false; }
	DECLARE_FUNCTION(execJsonToStruct) {
		P_GET_PROPERTY(UStrProperty, Json);

		Stack.StepCompiledIn<UStructProperty>(NULL);
		void* OutStructPtr = Stack.MostRecentPropertyAddress;

		P_FINISH;
		bool bSuccess = false;

		UStructProperty* StructProp = Cast<UStructProperty>(Stack.MostRecentProperty);
		if (StructProp && OutStructPtr)
		{
			UScriptStruct* OutputType = StructProp->Struct;

			P_NATIVE_BEGIN;
			bSuccess = Generic_JsonToStruct(Json, OutputType, OutStructPtr);
			P_NATIVE_END;
		}
		*(bool*)RESULT_PARAM = bSuccess;
	}
	static bool Generic_JsonToStruct(const FString& Json, UScriptStruct* StructDefinition, void* OutStructPtr);

	UFUNCTION(BlueprintCallable, Category = "CB_Datas", CustomThunk, meta = (CustomStructureParam = "InStruct"))
		/** Convert from struct to JSON **/
		static bool StructToJson(FString& Json, UScriptStruct* InStruct) { check(0);return false; }
	DECLARE_FUNCTION(execStructToJson) {
		P_GET_PROPERTY_REF(UStrProperty, Json);

		Stack.StepCompiledIn<UStructProperty>(NULL);
		void* InStruct = Stack.MostRecentPropertyAddress;

		P_FINISH;
		bool bSuccess = false;

		UStructProperty* StructProp = Cast<UStructProperty>(Stack.MostRecentProperty);
		if (StructProp && InStruct)
		{
			UScriptStruct* StructType = StructProp->Struct;

			P_NATIVE_BEGIN;
			bSuccess = Generic_StructToJson(Json, StructType, InStruct);
			P_NATIVE_END;
		}
		*(bool*)RESULT_PARAM = bSuccess;
	}
	static bool Generic_StructToJson(FString& Json, UScriptStruct* StructDefinition, void* InStruct);

private:
	static bool GetStructDataFromDataTable(UDataTable* DataTable, void* OutStructDataPtr, int32 Index);

};

class UDataTable;
enum class EDataTableExportFlags : uint8;

template <class CharType>
struct TPrettyJsonPrintPolicy;

// forward declare JSON writer
template <class CharType>
struct TPrettyJsonPrintPolicy;

template <class CharType, class PrintPolicy>
class TJsonWriter;

class FDataTableExporterJSON
{
public:
	typedef TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>> FDataTableJsonWriter;

	FDataTableExporterJSON(const EDataTableExportFlags InDTExportFlags, FString& OutExportText);

	FDataTableExporterJSON(const EDataTableExportFlags InDTExportFlags, TSharedRef<FDataTableJsonWriter> InJsonWriter);

	~FDataTableExporterJSON();

	/** Returns what string is used as the key/name field for a data table */
	FString GetKeyFieldName(const UDataTable& DataTable);

	/** Writes the data table out as an array of objects */
	bool WriteTable(const UDataTable& DataTable);

	/** Writes the data table out as a named object with each row being a sub value on that object */
	bool WriteTableAsObject(const UDataTable& DataTable);

	/** Writes out a single row */
	bool WriteRow(const UScriptStruct* InRowStruct, const void* InRowData, const FString* FieldToSkip = nullptr);

	/** Writes the contents of a single row */
	bool WriteStruct(const UScriptStruct* InStruct, const void* InStructData, const FString* FieldToSkip = nullptr);

private:
	bool WriteStructEntry(const void* InRowData, const UProperty* InProperty, const void* InPropertyData);

	bool WriteContainerEntry(const UProperty* InProperty, const void* InPropertyData, const FString* InIdentifier = nullptr);

	EDataTableExportFlags DTExportFlags;
	TSharedRef<FDataTableJsonWriter> JsonWriter;
	bool bJsonWriterNeedsClose;
};

bool GetStructDataFromDataTable(UDataTable* DataTable, void* OutRowStructDataPtr);
