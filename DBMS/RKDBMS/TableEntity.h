#pragma once
#include "FieldEntity.h"

/************************************************
[ClassName]	CTableEntity
[Function]	Database table entity class
************************************************/
class CTableEntity : public CObject
{
public:
	// Constructor
	CTableEntity(CString strName);
	CTableEntity::CTableEntity(CTableEntity& te);
	CTableEntity(void);
	// Destructor
	~CTableEntity(void);

	// Class and block conversion function
	TableBlock GetBlock();
	void SetBlock(TableBlock tb);

	// Set function
	void SetName(CString strName);
	void SetRecordNum(int nNum);
	void SetTdfPath(const CString strTdfPath);
	void SetTrdPath(const CString strTrdPath);
	void SetCrTime(SYSTEMTIME tTime);
	void SetMTime(SYSTEMTIME tTime);

	// Get function
	CString GetName();
	int GetRecordNum();
	int GetFieldNum();
	CString GetTdfPath();
	CString GetTrdPath();
	SYSTEMTIME GetCrTime();
	SYSTEMTIME GetMTime();

private:
	// Table basic information
	CString m_strName;		// Table name
	int m_nRecordNum;		// Record number
	CString m_strTdfPath;	// Path of table definition file 
	CString m_strTrdPath;	// Path of record file
	SYSTEMTIME m_tCrTime;	// Table creation time
	SYSTEMTIME m_tMTime;	// Last modification time

public:
	// Add field
	CFieldEntity* AddField(CFieldEntity &fe);
	// Get a field
	CFieldEntity* GetFieldAt(int nIndex);

private:
	FIELDARRAY m_arrFields;	// Field array

};

typedef CTypedPtrArray<CPtrArray, CTableEntity*> TABLEARR;
