#pragma once
#include "DBEntity.h"
#include "DBDao.h"
#include "FileLogic.h"

/**************************************************
[ClassName]	CDBLogic
[Function]	Database definition business logic class
**************************************************/
class CDBLogic
{
public:
	// Create database
	bool CreateDatabase(CDBEntity *db);
	// Query database
	bool GetDatabase(CDBEntity *db);
	CDBLogic(CString name);

private:
	CDBDao m_daoDB;			// The database data operation object
	CFileLogic m_fileLogic;	// The logical object of the database file
	CString mydb;
};
