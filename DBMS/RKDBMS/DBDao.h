#pragma once
#include "DBEntity.h"

/**************************************************
[ClassName]	CDBDao
[Function]	Database operation class
**************************************************/
class CDBDao
{
public:
	// Create database
	bool Create(const CString strFilepath, CDBEntity* db, bool bAppend = true);
	// Read the database information
	bool GetDatabase(const CString strFilepath, CDBEntity* db);
};
