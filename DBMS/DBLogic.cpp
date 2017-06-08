#include "StdAfx.h"
#include "DBLogic.h"




CDBLogic::CDBLogic(CString name)
{
	mydb = name;
}

/**************************************************
[FunctionName]	CreateDatabase
[Function]	Create database
[Argument]	CDBEntity &db: Database entity object, contains the name of the database.
[ReturnedValue]	bool: True if the operation is successful, other false.
**************************************************/
bool CDBLogic::CreateDatabase(CDBEntity* db)
{
	try 
	{
		// Decide whether the file exists, if there is no,a file will be created.
		CString strDBFile = m_fileLogic.GetDBFile(mydb+_T(".db"));
		if (CFileHelper::IsValidFile(strDBFile) == false)
		{
			if(CFileHelper::CreateFile(strDBFile) == false)
			{
				return false;
			}
		}

		// Read file, decide whether exists the database of the same name
		if (m_daoDB.GetDatabase(strDBFile, db) == true)
		{
			return false;
		}

		// Create database
		CString strDBFolder = m_fileLogic.GetDBFolder(db->GetName());
		db->SetFilepath(strDBFolder);
		if(m_daoDB.Create(strDBFile, db) == false)
		{
			return false;
		}
	}
	catch (CAppException* e)
	{
		throw e;
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to create database!"));
	}

	return true;
}

/**************************************************
[FunctionName]	GetDatabase
[Function]	Query the database information
[Argument]	CDBEntity &db: Database entity object, contains the name of the database.
		Queried database information will be saved to the object.
[ReturnedValue]	bool: True if exists the database of the same name, otherwise false
**************************************************/
bool CDBLogic::GetDatabase(CDBEntity* db)
{
	try
	{
		return m_daoDB.GetDatabase(m_fileLogic.GetDBFile(mydb+_T(".db")), db);
	}
	catch (CAppException* e)
	{
		throw e;
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to create database!"));
	}
	return false;
}
