#pragma once
#include "TableEntity.h"
#include "TableDao.h"
#include "FileLogic.h"

/**************************************************
[ClassName]	CTableLogic
[Function]	Table definition business logic class
**************************************************/
class CTableLogic
{
public:
	// Create a table
	bool CreateTable(const CString strDBName, CTableEntity &te);
	// Add field
	bool AddField(const CString strDBName, CTableEntity &te, CFieldEntity &fe);
	// Query table information
	int GetTables(const CString strDBName, TABLEARR &arrTables);

private:
	CTableDao m_daoTable;	// The database table operation object
	CFileLogic m_fileLogic;	// The database file logic object
};
