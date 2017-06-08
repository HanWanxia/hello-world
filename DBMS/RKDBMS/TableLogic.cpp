#include "StdAfx.h"
#include "TableLogic.h"

/**************************************************
[FunctionName]	CreateTable
[Function]	Create a table
[Argument]	const CString strDBName: Database name
		CTableEntity &te: Table data entity
[ReturnedValue]	bool: True if query the database successfully,otherwise false
**************************************************/
bool CTableLogic::CreateTable(const CString strDBName, CTableEntity &te)
{
	try
	{
		// Decide whether the file exists, if there is no,a file will be created.
		CString strTableFile = m_fileLogic.GetTableFile(strDBName);
		if (CFileHelper::IsValidFile(strTableFile) == false)
		{
			if(CFileHelper::CreateFile(strTableFile) == false)
			{
				return false;
			}
		}

		// Set the path of the table definition file
		te.SetTdfPath(m_fileLogic.GetTbDefineFile(strDBName, te.GetName()));
		// Set the path of the record file
		te.SetTrdPath(m_fileLogic.GetTbRecordFile(strDBName, te.GetName()));

		// Create table and save table information
		if(m_daoTable.Create(strTableFile, te) == false)
		{
			return false;
		}

		return true;
	}
	catch (CAppException* e)
	{
		throw e;
	}

	return false;
}

/**************************************************
[FunctionName]	AddField
[Function]	Add table field
[Argument]	const CString strDBName: Database name
CTableEntity &te: Table information entity
		CFieldEntity &fe: Field entity
[ReturnedValue]	bool: True if adds field successfully, otherwise false
**************************************************/
bool CTableLogic::AddField(const CString strDBName, CTableEntity &te, CFieldEntity &fe)
{	
	try
	{
		// Decide whether the file exists, if there is no,a file will be created.
		CString strTdfPath = te.GetTdfPath();
		if (CFileHelper::IsValidFile(strTdfPath) == false)
		{
			if(CFileHelper::CreateFile(strTdfPath) == false)
			{
				return false;
			}
		}

		// Save field information
		if(m_daoTable.AddField(strTdfPath, fe) == false)
		{
			return false;
		}
		// Add field
		te.AddField(fe);

		// Update modify time
		SYSTEMTIME tTime;
		::GetLocalTime(&tTime);
		te.SetMTime(tTime);

		// Alert table information
		CString strTableFile = m_fileLogic.GetTableFile(strDBName);
		if(m_daoTable.AlterTable(strTableFile, te) == false)
		{
			return false;
		}
		return true;
	}
	catch (CAppException* e)
	{
		throw e;
	}

	return false;
}

/**************************************************
[FunctionName]	GetTables
[Function]	Query table information
[Argument]	const CString strDBName: Database name
		TABLEARR &arrTables: Table information list
[ReturnedValue]	int: The number of the queried table
**************************************************/
int CTableLogic::GetTables(const CString strDBName, TABLEARR &arrTables)
{
	int nCount = 0;

	try
	{
		// Get the table description file
		CString strTableFile = m_fileLogic.GetTableFile(strDBName);

		// Query talbe information
		nCount = m_daoTable.GetTables(strTableFile, arrTables);

		// Read the table structure from the table definition file one by one
		for (int i = 0; i < nCount; i++)
		{
			CTableEntity* pTable = arrTables.GetAt(i);
			m_daoTable.GetFields(pTable->GetTdfPath(), *pTable);
		}
	}
	catch (CAppException e)
	{
		throw e;
	}

	return nCount;
}
