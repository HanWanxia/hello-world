#pragma once
#include "TableEntity.h"
#include "FieldEntity.h"

/**************************************************
[ClassName]	CTableDao
[Function]	Table data operation class
**************************************************/
class CTableDao
{
public:
	// Create table and save table information
	bool Create(const CString strFilePath, CTableEntity &te);
	// Add a table field
	bool AddField(const CString strFilePath, CFieldEntity &fe);
	// Get table information
	int GetTables(const CString strFilepath, TABLEARR &arr);
	// Get field information
	bool GetFields(const CString strFilepath, CTableEntity &te);
	// Alert table
	bool AlterTable(const CString strFilePath, CTableEntity &te);
};
