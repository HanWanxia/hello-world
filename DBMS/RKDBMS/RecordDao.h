#pragma once
#include "TableEntity.h"
#include "RecordEntity.h"

/**************************************************
[ClassName]	CRecordDao
[Function]	Record data operation class
**************************************************/
class CRecordDao
{
public:
	// Create new rows in a table
	bool Insert(CTableEntity &te, CRecordEntity &re);
	bool JudgeSame(CTableEntity &te,CRecordEntity &select,CRecordEntity &now);
	bool JudgeAll(CTableEntity &te,CRecordEntity &select);
	// Retrieve all records from a specified table
	int SelectAll(CTableEntity &te, RECORDARR &data);
	int UpdateRecord(CTableEntity &te, RECORDARR &data,CRecordEntity &select,CRecordEntity & modify);
	int DeleteRecord(CTableEntity &te, RECORDARR &data,CRecordEntity &select);
	int selectRecord(CTableEntity &te, RECORDARR &data,CRecordEntity &select);

private:
	// Save record
	bool Write(CFile &file, CTableEntity &te, CRecordEntity &re);
	bool writeRecord(CTableEntity &te, RECORDARR &data);
	long getsize(CFieldEntity* fe);
	// Get record
	bool Read(CFile &file, CTableEntity &te, CRecordEntity &re);
};
