#include "StdAfx.h"
#include "RecordLogic.h"

/**************************************************
[FunctionName]	Insert
[Function]	Create new rows in a table
[Argument]	CString strDBName: Database name
			CTableEntity &te: Table information entity
			CRecordEntity &re: Record information entity
[ReturnedValue]	bool: True if the operation is successful, otherwise false.
**************************************************/
bool CRecordLogic::Insert(const CString strDBName, CTableEntity &te, CRecordEntity &re)
{
	try
	{
		// Decide whether the file exists, if there is no,a file will be created.
		CString strTrdPath = te.GetTrdPath();
		if (CFileHelper::IsValidFile(strTrdPath) == false)
		{
			if(CFileHelper::CreateFile(strTrdPath) == false)
			{
				return false;
			}
		}

		// Insert a record
		if (m_daoRecord.Insert(te, re) == false)
		{
			return false;
		}

		// Modify record number
		int nRecordNum = te.GetRecordNum()+1;
		te.SetRecordNum(nRecordNum);

		// Alert table information
		CString strTableFile = m_fileLogic.GetTableFile(strDBName);
		if(m_daoTable.AlterTable(strTableFile, te) == false)
		{
			return false;
		}

		return true;
	}
	catch (CAppException *e)
	{
		throw e;
	}

	return false;
}

/**************************************************
[FunctionName]	UpdateRecord
[Function]	Update the record use select in a table
[Argument]	CTableEntity &te, RECORDARR &data,CRecordEntity &select,CRecordEntity &modify
[ReturnedValue]	bool: True if the operation is successful, otherwise false.
**************************************************/
bool CRecordLogic::UpdateRecord(CTableEntity &te, RECORDARR &data,CRecordEntity &select,CRecordEntity &modify)
{
	try
	{
		// Read record
		if (m_daoRecord.UpdateRecord(te, data,select,modify) == false)
		{
			return false;
		}

		return true;
	}
	catch (CAppException *e)
	{
		throw e;
	}

	return false;
}

/**************************************************
[FunctionName]	DeleteRecord
[Function]	Update the record use select in a table
[Argument]	CTableEntity &te, RECORDARR &data,CRecordEntity &select
[ReturnedValue]	bool: True if the operation is successful, otherwise false.
**************************************************/
bool CRecordLogic::DeleteRecord(CTableEntity &te, RECORDARR &data,CRecordEntity &select)
{
	try
	{
		// Read record
		if (m_daoRecord.DeleteRecord(te, data,select) == false)
		{
			return false;
		}

		return true;
	}
	catch (CAppException *e)
	{
		throw e;
	}

	return false;
}

/**************************************************
[FunctionName]	selectRecord
[Function]	Show the record user select in a table
[Argument]	CTableEntity &te, RECORDARR &data,CRecordEntity &select
[ReturnedValue]	bool: True if the operation is successful, otherwise false.
**************************************************/
bool CRecordLogic::selectRecord(CTableEntity &te, RECORDARR &data,CRecordEntity &select)
{
	try
	{
		// Read record
		if (m_daoRecord.selectRecord(te, data,select) == false)
		{
			return false;
		}

		return true;
	}
	catch (CAppException *e)
	{
		throw e;
	}

	return false;
}
