#pragma once

/************************************************
[ClassName]	CRecordEntity
[Function]	Record entity class
************************************************/
class CRecordEntity : public CObject
{
public:
	// Constructor
	CRecordEntity();
	// Copy constructor
	CRecordEntity(CRecordEntity &e);
	// Destructor
	~CRecordEntity();

	// Overload "=" operator
	CRecordEntity &operator =(const CRecordEntity &);

public:
	// Save the value of the field
	void Put(CString strFieldName, CString strValue);
	void Put(CString strFieldName, int nValue);
	void Put(CString strFieldName, double dbValue);
	void Put(CString strFieldName, SYSTEMTIME t);

	// Get the value of the field.
	CString Get(CString strFieldName);

private: 
	CMapStringToString m_mapData; // Data
};

// Record collection definition
typedef CTypedPtrArray<CPtrArray, CRecordEntity*> RECORDARR;
