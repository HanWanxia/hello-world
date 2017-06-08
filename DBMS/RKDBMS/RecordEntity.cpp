#include "StdAfx.h"
#include "RecordEntity.h"

// Constructor
CRecordEntity::CRecordEntity(void)
{
}

// Copy constructor
CRecordEntity::CRecordEntity(CRecordEntity &e)
{
	POSITION pos = e.m_mapData.GetStartPosition();
	CString strFieldName, strValue;
	while(pos)
	{
		e.m_mapData.GetNextAssoc(pos, strFieldName, strValue);
		m_mapData.SetAt(strFieldName, strValue);
	}
}

// Destructor
CRecordEntity::~CRecordEntity(void)
{
}

// Overload "=" operator
CRecordEntity &CRecordEntity::operator =(const CRecordEntity &e)
{
	CString strFieldName, strValue;
	POSITION ipos = e.m_mapData.GetStartPosition();
	while(ipos!=NULL)
	{
		e.m_mapData.GetNextAssoc(ipos, strFieldName, strValue);
		m_mapData.SetAt(strFieldName, strValue);
	}

	return *this;
}

// Add record
void CRecordEntity::Put(CString strFieldName, CString strValue)
{
	m_mapData.SetAt(strFieldName, strValue);
}

void CRecordEntity::Put(CString strFieldName, int nValue)
{
	CString strValue;
	strValue.Format(_T("%d"), nValue);
	m_mapData.SetAt(strFieldName, strValue);
}
void CRecordEntity::Put(CString strFieldName, double dbValue)
{
	CString strValue;
	strValue.Format(_T("%f"), dbValue);
	m_mapData.SetAt(strFieldName, strValue);
}

void CRecordEntity::Put(CString strFieldName, SYSTEMTIME t)
{
	m_mapData.SetAt(strFieldName, CTimeHelper::ToLDatetimeString(t));
}

// Get the value of the field.After removed, needs to be transformed according to the data type of the field.
CString CRecordEntity::Get(CString strFieldName)
{
	CString strVal;
	if(m_mapData.Lookup(strFieldName, strVal) == FALSE)
	{
		// Get the default value
		strVal = _T("");
	}
	return strVal;
}
