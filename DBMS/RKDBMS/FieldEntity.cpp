#include "StdAfx.h"
#include "FieldEntity.h"

// Constructor
CFieldEntity::CFieldEntity(void)
{
	m_strName = _T("");			// Field name
	m_nType = DT_NONE;			// Field type
	m_nParam = -1;				// Field parameter
	::GetLocalTime(&m_tMTime);	// Last modification time
	m_nIntegrities = 0;			// Type of integrity constraints
}

// Constructor
CFieldEntity::CFieldEntity(CString strName, int nType, int nParam, int nIntegrities)
{
	m_strName = strName;
	m_nType = nType;
	m_nParam = nParam;
	m_nIntegrities = nIntegrities;
	::GetLocalTime(&m_tMTime);
}

// Copy constructor
CFieldEntity::CFieldEntity(CFieldEntity& fe)
{
	m_strName = fe.m_strName;
	m_nType = fe.m_nType;
	m_nParam = fe.m_nParam;
	m_tMTime = fe.m_tMTime;
	m_nIntegrities = fe.m_nIntegrities;
}

// Destructor
CFieldEntity::~CFieldEntity(void)
{
}

/**************************************************
[FunctionName]	GetTypeName
[Function]	Get the name of the data type
[Argument]	int nDataType: Data type
[ReturnedValue]	CString: Type name
**************************************************/
CString CFieldEntity::GetTypeName(int nDataType)
{
	CString strName = _T("");
	switch(nDataType)
	{
	case CFieldEntity::DT_INTEGER:	// INT type
		{
			strName = _T("INT");
			break;
		}
	case CFieldEntity::DT_BOOL:		// BOOL type
		{
			strName = _T("BOOL");
			break;
		}
	case CFieldEntity::DT_DOUBLE:	// DOUBLE type
		{
			strName = _T("DOUBLE");
			break;
		}
	case CFieldEntity::DT_VARCHAR:	// VRACHAR type
		{
			strName = _T("VARCHAR");
			break;
		}
	case CFieldEntity::DT_DATETIME:	// DATETIME type
		{
			strName = _T("DATATIME");
			break;
		}
	default:
		break;
	}
	return strName;
}

//////////////////////////////////////////////////////////////////////////
// Class and block conversion function
void CFieldEntity::SetBlock(FieldBlock fb)
{
	m_strName = CCharHelper::ToString(fb.name, sizeof(VARCHAR));
	m_tMTime = fb.mtime;
	m_nType = fb.type;
	m_nParam = fb.param;
	m_nIntegrities = fb.integrities;
}

FieldBlock CFieldEntity::GetBlock()
{
	FieldBlock fb;
	memset(&fb, 0, sizeof(FieldBlock));

	CCharHelper::ToChars(fb.name, m_strName, sizeof(VARCHAR));
	fb.mtime = m_tMTime;
	fb.type = m_nType;
	fb.param = m_nParam;
	fb.integrities = m_nIntegrities;
	return fb;
}

//////////////////////////////////////////////////////////////////////////
// Set function
void CFieldEntity::SetName(CString strName)
{
	m_strName = strName;
}

void CFieldEntity::SetDataType(int nType)
{
	m_nType = nType;
}

void CFieldEntity::SetParam(int nParam)
{
	m_nParam = nParam;
}

void CFieldEntity::SetMTime(SYSTEMTIME t)
{
	m_tMTime = t;
}

//////////////////////////////////////////////////////////////////////////
// Get function
CString CFieldEntity::GetName()
{
	return m_strName;
}

int CFieldEntity::GetDataType()
{
	return m_nType;
}

int CFieldEntity::GetParam()
{
	return m_nParam;
}

SYSTEMTIME CFieldEntity::GetMTime()
{
	return m_tMTime;
}
