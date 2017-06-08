#include "StdAfx.h"
#include "RecordDao.h"

/**************************************************
[FunctionName]	Insert
[Function]	Create new rows in a table
[Argument]	CTableEntity &te: Table structure information
		CRecordEntity &re: Record information entity
[ReturnedValue]	bool: True if the operation is successful; otherwise false.
**************************************************/
bool CRecordDao::Insert(CTableEntity &te, CRecordEntity &re)
{
	try
	{
		CFile file;
		// Open file
		if (file.Open(te.GetTrdPath(), CFile::modeWrite | CFile::shareDenyWrite) == FALSE)
		{
			return false;
		}
		// The cursor to the end of the file
		file.SeekToEnd();

		// Save record
		Write(file, te, re);

		// Close file
		file.Close();
		return true;
	}
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("Failed to save record!"));
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to save record!"));
	}

	return false;	
}

/**************************************************
[FunctionName]	JudgeSame
[Function]	Judge if the current record is the record user select
[Argument]	CTableEntity &te,CRecordEntity &select,CRecordEntity &now
[ReturnedValue]	bool: True if the operation is successful; otherwise false.
**************************************************/
 bool CRecordDao::JudgeSame(CTableEntity &te,CRecordEntity &select,CRecordEntity &now)
{
	int nCount = te.GetFieldNum();

	if (nCount > 0)
	{
		//compare the record value of each field
		for (int i = 0; i < nCount; i++)
		{
			CFieldEntity* pField = te.GetFieldAt(i);
			CString strValue = now. Get(pField->GetName());
			CString selectValue = select.Get(pField->GetName());
			if(!selectValue.IsEmpty() && strValue!=selectValue)
				return false;
		}
	}
	return true;
}

 bool CRecordDao::JudgeAll(CTableEntity &te,CRecordEntity &select)
 {
	int nCount = te.GetFieldNum();

	if (nCount > 0)
	{
		//compare the record value of each field
		for (int i = 0; i < nCount; i++)
		{
			CFieldEntity* pField = te.GetFieldAt(i);
			CString selectValue = select.Get(pField->GetName());
			if(!selectValue.IsEmpty())
				return false;
		}
	}
	return true;
}

/**************************************************
[FunctionName]	UpdateRecord
[Function]	Update the record
[Argument]	CTableEntity &te, RECORDARR &data,CRecordEntity &select,CRecordEntity & modify
[ReturnedValue]	int: The total number of the records
**************************************************/
int CRecordDao::UpdateRecord(CTableEntity &te, RECORDARR &data,CRecordEntity &select,CRecordEntity & modify)
{
			
		CFile file;
		// Open file
		if (file.Open(te.GetTrdPath(), CFile::modeReadWrite | CFile::shareDenyNone) == FALSE)
		{
			return 0;
		}
		// The cursor to the end of the file
		file.SeekToBegin();
		long lOffset = file.GetPosition();
		int nCount = 0;
		while (true)
		{
			CRecordEntity* pRecordEntity = new CRecordEntity();
			if (Read(file, te, *pRecordEntity) == true)
			{
				//find the record user select
				if(JudgeSame(te,select,*pRecordEntity))
				{
					CRecordEntity* m_recordEntity = new CRecordEntity();
					int nCount = te.GetFieldNum();

					if (nCount > 0)
					{
						// Insert the record into the list control
						for (int i = 0; i < nCount; i++)
						{
							CFieldEntity* pField = te.GetFieldAt(i);
							CString strValue = pRecordEntity->Get(pField->GetName());
							CString modifyValue = modify.Get(pField->GetName());
							if(!modifyValue.IsEmpty() && strValue!=modifyValue)
								m_recordEntity->Put(pField->GetName(), modifyValue);
							else
								m_recordEntity->Put(pField->GetName(), strValue);
						}
					}
					//add the record to records array
					data.Add(m_recordEntity);
					nCount++;
					//write the new record into file
					file.Seek(lOffset,CFile::begin);  
					Write(file,te,*m_recordEntity);
				}
				else
				{
					data.Add(pRecordEntity);
					nCount++;
				}
				//find the current file pointer position
				lOffset = file.GetPosition();
			}
			else
			{
				delete pRecordEntity;
				pRecordEntity = NULL;
				break;
			}
		}
		// Close file
		file.Close();

		return nCount;		
}


/**************************************************
[FunctionName]	DeleteRecord
[Function]	Delete the record
[Argument]	CTableEntity &te, RECORDARR &data,CRecordEntity &select
[ReturnedValue]	int: The total number of the records
**************************************************/
int CRecordDao::DeleteRecord(CTableEntity &te, RECORDARR &data,CRecordEntity &select)
{
			
		CFile file;
		// Open file
		if (file.Open(te.GetTrdPath(), CFile::modeReadWrite | CFile::shareDenyNone) == FALSE)
		{
			return 0;
		}
		// The cursor to the end of the file
		file.SeekToBegin();
		int nCount = 0;
		while (true)
		{
			CRecordEntity* pRecordEntity = new CRecordEntity();
			//find the current file pointer position
			if (Read(file, te, *pRecordEntity) == true)
			{
				//find the record user select
				if(!JudgeSame(te,select,*pRecordEntity))
				{
					data.Add(pRecordEntity);
					nCount++;
				}
			}
			else
			{
				delete pRecordEntity;
				pRecordEntity = NULL;
				break;
			}
		}
		// Close file
		file.Close();
		writeRecord(te, data);
		return nCount;		
}

/**************************************************
[FunctionName]	selectRecord
[Function]	Delete the record
[Argument]	CTableEntity &te, RECORDARR &data,CRecordEntity &select
[ReturnedValue]	int: The total number of the records
**************************************************/
int CRecordDao::selectRecord(CTableEntity &te, RECORDARR &data,CRecordEntity &select)
{
			
		CFile file;
		// Open file
		if (file.Open(te.GetTrdPath(), CFile::modeReadWrite | CFile::shareDenyNone) == FALSE)
		{
			return 0;
		}
		// The cursor to the end of the file
		file.SeekToBegin();
		int nCount = 0;
		if(JudgeAll(te,select))
		{
			return SelectAll(te,data);
		}
		while (true)
		{
			CRecordEntity* pRecordEntity = new CRecordEntity();
			//find the current file pointer position
			if (Read(file, te, *pRecordEntity) == true)
			{
				//find the record user select
				if(JudgeAll(te,select) && JudgeSame(te,select,*pRecordEntity))
				{
					data.Add(pRecordEntity);
					nCount++;
				}
			}
			else
			{
				delete pRecordEntity;
				pRecordEntity = NULL;
				break;
			}
		}
		// Close file
		file.Close();
		return nCount;		
}

/**************************************************
[FunctionName]	SelectAll
[Function]	Retrieve all records from a specified table
[Argument]	CTableEntity &te: Table structure information
		RECORDARR &data: Recordset
[ReturnedValue]	int: The total number of the records
**************************************************/
int CRecordDao::SelectAll(CTableEntity &te, RECORDARR &data)
{
	try
	{		
		CFile file;
		// Open file
		if (file.Open(te.GetTrdPath(), CFile::modeRead | CFile::shareDenyNone) == FALSE)
		{
			return 0;
		}
		// The cursor to the end of the file
		file.SeekToBegin();

		int nCount = 0;
		while (true)
		{
			// Get the value to write
			CRecordEntity* pRecordEntity = new CRecordEntity();
			if (Read(file, te, *pRecordEntity) == true)
			{
				data.Add(pRecordEntity);
				nCount++;
			}
			else
			{
				delete pRecordEntity;
				pRecordEntity = NULL;
				break;// Exit the while loop
			}
		}
		// Close file
		file.Close();

		return nCount;
	}
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("Failed to query record!"));
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to query record!"));
	}

	return 0;	
}

/**************************************************
[FunctionName]	Write
[Function]	To save a record to a file
[Argument]	CFile &file: Open file of data record
		CTableEntity &te: Table structure information
		CRecordEntity &re: Record information entity
[ReturnedValue]	bool: True if the operation is successful;otherwise false.
**************************************************/
bool CRecordDao::Write(CFile &file, CTableEntity &te, CRecordEntity &re)
{
	try
	{
		// Get field number and save the value of each field  one by one.
		int nFieldNum = te.GetFieldNum();
		for(int i = 0; i < nFieldNum; i++)
		{
			// Get field information.
			CFieldEntity* pField = te.GetFieldAt(i);

			// Get the value of the field, the data type is CString. Before you save the need for type conversion
			CString strFieldName = pField->GetName();
			CString strVal = re.Get(strFieldName);

			// Get to the data type of the field.
			// To convert the value of the field to the actual data types, and write in the file.
			switch (pField->GetDataType())
			{
			case CFieldEntity::DT_INTEGER : // Integer
				{
					int nVal = _wtoi(strVal);
					file.Write(&nVal, sizeof(int));
					break; 
				}
			case CFieldEntity::DT_BOOL : // Boolean type
				{
					int nVal = _wtoi(strVal);
					file.Write(&nVal, sizeof(bool));
					break;
				}
			case CFieldEntity::DT_DOUBLE : // Floating-point number
				{
					double dbVal = _wtof(strVal);
					file.Write(&dbVal, sizeof(double));
					break;
				}
			case CFieldEntity::DT_DATETIME : // Time type
				{
					SYSTEMTIME st = CTimeHelper::ToSystemTime(strVal);
					file.Write(&st, sizeof(SYSTEMTIME));
					break;
				}
			case CFieldEntity::DT_VARCHAR : // String type
				{
					// The length of the string
					int nSize = sizeof(char) * pField->GetParam();
					// Create a cache to save the string
					char* pBuf = new char[nSize];
					CCharHelper::ToChars(pBuf, strVal, nSize);
					// Write in file
					file.Write(pBuf, nSize);
					// Release the cache
					delete[] pBuf;
					break;
				}
			default: // Other data types
				{
					throw new CAppException(_T("Field data type is unusual, save record failed!"));
				}
			}// end switch

		}// end for
		return true;
	}
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("Failed to save record!"));
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to save record!"));
	}

	return false;
}

bool CRecordDao::writeRecord(CTableEntity &te, RECORDARR &data)
{
	int nCount = data.GetCount();
	CFile file;
	// Open file
	CRecordEntity* current = new CRecordEntity();
	if (file.Open(te.GetTrdPath(), CFile::modeWrite|CFile::modeCreate) == FALSE)
	{
		return false;
	}
	current = data.GetAt(0);
	Write(file,te,*current);
	file.Close();
	if (file.Open(te.GetTrdPath(), CFile::modeWrite | CFile::shareDenyWrite) == FALSE)
	{
		return false;
	}
	file.SeekToEnd();
	for(int i = 1;i<nCount;i++)
	{
		current = data.GetAt(i);
		Write(file,te,*current);
	}
}

/**************************************************
[FunctionName]	Read
[Function]	Read a record from the file
[Argument]	CFile &file: Open file of data record
			CTableEntity &te: Table structure information
			CRecordEntity &re: Record information entity
[ReturnedValue]	bool: True if the operation is successful;otherwise false.
**************************************************/
bool CRecordDao::Read(CFile &file, CTableEntity &te, CRecordEntity &re)
{
	try
	{
		// Get field number and read the value of each field  one by one.
		int nFieldNum = te.GetFieldNum();
		for(int i = 0; i < nFieldNum; i++)
		{
			// Get field information.
			CFieldEntity* pField = te.GetFieldAt(i);
			CString strFieldName = pField->GetName();// Field name

			switch (pField->GetDataType())
			{
			case CFieldEntity::DT_INTEGER: // Integer
				{
					int nVal;
					if(file.Read(&nVal, sizeof(int)) == 0)
					{
						return false;
					}
					re.Put(strFieldName, nVal);
					break;
				}
			case CFieldEntity::DT_BOOL : // Boolean
				{
					bool bVal;
					if(file.Read(&bVal, sizeof(bool)) == 0)
					{
						return false;
					}
					re.Put(strFieldName, bVal);
					break;
				}
			case CFieldEntity::DT_DOUBLE : // Floating-point number
				{
					double dbVal;
					if(file.Read(&dbVal, sizeof(double)) == 0)
					{
						return false;
					}
					re.Put(strFieldName, dbVal);
					break;
				}
			case CFieldEntity::DT_DATETIME : // Time type
				{
					SYSTEMTIME st;
					if(file.Read(&st, sizeof(SYSTEMTIME)) == 0)
					{
						return false;
					}
					re.Put(strFieldName, st);
					break;					
				}
			case CFieldEntity::DT_VARCHAR : // String type
				{
					int nSize = sizeof(char) * pField->GetParam();
					char* pBuf = new char[nSize];
					if(file.Read(pBuf, nSize) == 0)
					{
						return false;
					}
					re.Put(strFieldName, CCharHelper::ToString(pBuf, nSize));					
					// Release cache
					delete[] pBuf;
					break;
				}
			default : // Other data types
				{
					throw new CAppException(_T("Field data type is unusual, read record failed!"));
				}
			}// end switch
		}// end for
		return true;
	}
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("Failed to read record!"));
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to read record!"));
	}

	return false;
}
