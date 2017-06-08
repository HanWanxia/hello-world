#include "StdAfx.h"
#include "TableDao.h"

/**************************************************
[FunctionName]	Create
[Function]	Create table and save table information
[Argument]	const CString strFilePath: Path of the table description file
		CTableEntity &te: Table information entity
[ReturnedValue]	bool: True if the operation is successful,otherwise false
**************************************************/
bool CTableDao::Create(const CString strFilePath, CTableEntity &te)
{
	try
	{
		CFile file;
		// Open file
		if (file.Open(strFilePath, CFile::modeWrite | CFile::shareDenyWrite) == FALSE)
		{
			return false;
		}
		// Write in the database table information to the file
		file.SeekToEnd();
		file.Write(&te.GetBlock(), sizeof(TableBlock));
		// Close file
		file.Close();
		return true;
	}
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("Failed to add table information!"));
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to add table information!"));
	}

	return false;
}

/**************************************************
[FunctionName]	AddField
[Function]	Add table field
[Argument]	const CString strFilePath: Path of the table definition file
		CFieldEntity &te: Field information entity
[ReturnedValue]	bool: True if the operation is successful, otherwise false.
**************************************************/
bool CTableDao::AddField(const CString strFilePath, CFieldEntity &fe)
{
	try
	{
		CFile file;
		// Open file
		if (file.Open(strFilePath, CFile::modeWrite | CFile::shareDenyWrite) == FALSE)
		{
			return false;
		}

		// Add field informaiton
		file.SeekToEnd();
		FieldBlock fb = fe.GetBlock();
		file.Write(&fb, sizeof(FieldBlock));

		// Close file
		file.Close();
		return true;
	}
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("Failed to add field!"));
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to add field!"));
	}
	return false;
}

/**************************************************
[FunctionName]	GetTables
[Function]	Read the table information from the table definition file. With this information,
			you can find the table structure definition file.
[Argument]	const CString strFilePath: Path of the table definition file
		TABLEARR &arrTables: Table information array, This is an output parameter, used to save the queried table information.
[ReturnedValue]	int: The number of the queried table.
**************************************************/
int CTableDao::GetTables(const CString strFilepath, TABLEARR &arr )
{
	try
	{
		CFile file;
		// Open file
		if (file.Open(strFilepath, CFile::modeRead | CFile::shareDenyNone) == FALSE)
		{
			return false;
		}
		file.SeekToBegin();
		
		TableBlock tb;
		int nCount = 0;
		// Read table information
		while(file.Read(&tb, sizeof(TableBlock)) > 0)
		{
			CTableEntity* pTable = new CTableEntity();
			pTable->SetBlock(tb);
			arr.Add(pTable);
			nCount++;
		}
		// Close file
		file.Close();
		return nCount;
	}
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("Failed to query table information!"));
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to query table information!"));
	}

	return 0;
}

/**************************************************
[FunctionName]	GetFields
[Function]	Read fields information from the table definition file.
[Argument]	const CString strFilePath: Path of the table definition file
		CTableEntity &te: Table information entities.this is an output parameter.
[ReturnedValue]	bool: True if the operation is successful, otherwise false.
**************************************************/
bool CTableDao::GetFields(const CString strFilepath, CTableEntity &te)
{
	try
	{
		CFile file;
		// Open file
		if (file.Open(strFilepath, CFile::modeRead | CFile::shareDenyNone) == FALSE)
		{
			return false;
		}
		file.SeekToBegin();
		
		// Read field information
		FieldBlock fb;
		while(file.Read(&fb, sizeof(FieldBlock)) > 0)
		{
			CFieldEntity fe;
			fe.SetBlock(fb);
			te.AddField(fe);// Add field
		}

		// Close file
		file.Close();
		return true;
	}
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("Failed to read field information!"));
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to read field information!"));
	}

	return false;
}

/**************************************************
[FunctionName]	AlterTable
[Function]	Alter the table information
[Argument]	const CString strFilePath: Path of the table definition file
		CTableEntity &te: Table information entity
[ReturnedValue]	bool: True if the operation is successful, otherwise false
**************************************************/
bool CTableDao::AlterTable(const CString strFilePath, CTableEntity &te)
{
	try
	{
		CFile file;
		// Open file
		if (file.Open(strFilePath, CFile::modeReadWrite | CFile::shareDenyWrite) == FALSE)
		{
			return false;
		}

		file.SeekToBegin();
		long lOffset = file.GetPosition();

		// Query table information according to the table name, then alter the it
		bool flag = false;
		TableBlock tb;
		CString strName;// Table name
		while(file.Read(&tb, sizeof(TableBlock)) > 0)
		{
			strName = CCharHelper::ToString(tb.name, sizeof(VARCHAR));
			// Compare the table name
			if (te.GetName().Compare(strName) == 0)
			{
				file.Seek(lOffset, CFile::begin);// The file pointer points to the position of the previous record
				file.Write(&te.GetBlock(), sizeof(TableBlock));// Alter the table information
				flag = true;
				break;
			}
			lOffset = file.GetPosition();
		}

		// Close file
		file.Close();
		return flag;
	}
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("Failed to alert table!"));
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to alert table!"));
	}
	return false;
}
