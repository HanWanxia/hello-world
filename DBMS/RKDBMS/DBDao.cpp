#include "StdAfx.h"
#include "DBDao.h"

/**************************************************
[FunctionName] Create
[Function] Create database, insert a record into ruanko.db file.
[Argument]	const CString strFilepath: The database file path
		CDBEntity db: The database entities, including the database name.
		bool bAppend: Whether write file in a additional way.true if additional and false if overwritten
[ReturnedValue]	bool: True if the operation is successful; otherwise false.
**************************************************/
bool CDBDao::Create(const CString strFilepath, CDBEntity* db, bool bAppend)
{
	try
	{
		CFile file;
		if(bAppend == true)
		{
			if (file.Open(strFilepath, CFile::modeWrite | CFile::shareDenyWrite) == FALSE)
			{
				return false;
			}
		}
		else
		{
			if (file.Open(strFilepath, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite) == FALSE)
			{
				return false;
			}
		}

		file.SeekToBegin();
		file.Write(&db->GetBlock(), sizeof(DatabaseBlock));
		file.Close();

		return true;
	}
	catch(CException* e)// Catch exceptions
	{
		// Delete the exception information
		e->Delete();
		// Throw a custom exception
		throw new CAppException(_T("Failed to create the database file!"));
	}
	catch(...)	// Catch other exceptions
	{
		// Throw a custom exception
		throw new CAppException(_T("Failed to create the database file!"));
	}

	return false;
}

/**************************************************
[FunctionName]	GetDatabase
[Function]	Read the database information
[Argument]	const CString strFilepath: The database file path
		CDBEntity db: The database entities, including the database name.
[ReturnedValue]	bool: True if the operation is successful; otherwise false.
**************************************************/
bool CDBDao::GetDatabase(const CString strFilepath, CDBEntity* db)
{
	try
	{
		// Verify the file name
		CString strDBName = db->GetName();
		if (strDBName.GetLength() == 0)
		{
			return false;
		}
		
		// Open the file in a read-only way
		CFile file;
		if (file.Open(strFilepath, CFile::modeRead | CFile::shareDenyNone) == FALSE)
		{
			return false;
		}

		// Read the database information
		bool bExist = false;
		DatabaseBlock sdb;

		file.SeekToBegin();
		while (file.Read(&sdb, sizeof(DatabaseBlock)) > 0)
		{
			CString strName = CCharHelper::ToString(sdb.name, sizeof(VARCHAR));
			if (strName.CompareNoCase(strDBName) == 0)
			{
				db->SetBlock(sdb);
				bExist = true;
				break;
			}
		}
		file.Close();

		return bExist;
	}
	catch(CException* e)// Catch exceptions
	{
		// Delete the exception information
		e->Delete();
		// Throw a custom exception
		throw new CAppException(_T("Failed to create the database file!"));
	}
	catch(...)	// Catch other exceptions
	{
		// Throw a custom exception
		throw new CAppException(_T("Failed to create the database file!"));
	}
	return false;
}
