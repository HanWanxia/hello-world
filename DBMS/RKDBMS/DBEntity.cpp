#include "StdAfx.h"
#include "DBEntity.h"
#include "TableEntity.h"
#include "FieldEntity.h"

/************************************************************************
[FunctionName]	CDBEntity
[Function]	The constructor to initialize the data members.
[Argument]	void
************************************************************************/
CDBEntity::CDBEntity(void)
{
	m_strName = _T("");
	m_bType = false;
	m_strFilepath = _T("");
	::GetLocalTime(&m_tCtTime);
}

/************************************************************************
[FunctionName]	CDBEntity
[Function]	Use DatabaseBlock structure to initialize the data members
[Argument]	strName: Database name
************************************************************************/
CDBEntity::CDBEntity(const CString strName)
{
	m_strName = strName;
	m_bType = false;
	m_strFilepath = _T("");
	::GetLocalTime(&m_tCtTime);
}

/************************************************************************
[FunctionName]	CDBEntity
[Function]	Use DatabaseBlock structure to initialize the data members
[Argument]	db: Database block structure
************************************************************************/
CDBEntity::CDBEntity(DatabaseBlock &db)
{
	this->SetBlock(db);
}

/************************************************************************
[FunctionName]	~CDBEntity
[Function]	Destructor
[Argument]	db: Database block structure
************************************************************************/
CDBEntity::~CDBEntity(void)
{

}

/************************************************************************
[FunctionName]	GetBlock
[Function]	Save the database information to a DatabaseBlock structure.
[Argument]	void
[ReturnedValue]	DatabaseBlock: Database block structure
************************************************************************/
DatabaseBlock CDBEntity::GetBlock(void)
{
	DatabaseBlock db;
	memset(&db, 0, sizeof(DatabaseBlock));// Initializes the memory space

	CCharHelper::ToChars(db.filepath, m_strFilepath, sizeof(VARCHAR));
	CCharHelper::ToChars(db.name, m_strName, sizeof(VARCHAR));
	db.crtime = m_tCtTime;
	db.type = m_bType;

	return db;
}

/************************************************************************
[FunctionName]	SetBlock
[Function]	Use the data in a database block structure assignment for CDBEntity data members.
[Argument]	db: Database block structure
[ReturnedValue]	void
************************************************************************/
void CDBEntity::SetBlock(DatabaseBlock db)
{
	m_strName = CCharHelper::ToString(db.name, sizeof(VARCHAR));
	m_strFilepath = CCharHelper::ToString(db.filepath, sizeof(VARCHAR));
	m_bType = db.type;
	m_tCtTime = db.crtime;
}

/************************************************************************
[FunctionName]	SetName
[Function]	Set the database name
[Argument]	strName: Database name
[ReturnedValue]	void
************************************************************************/
void CDBEntity::SetName(CString strName)
{
	m_strName = strName;
}

/************************************************************************
[FunctionName]	SetType
[Function]	Set the database type
[Argument]	bType: Database type.true is system database，false is custom database.
[ReturnedValue]	void
************************************************************************/
void CDBEntity::SetType(bool bType)
{
	m_bType = bType;
}

/************************************************************************
[FunctionName]	SetFilepath
[Function]	Set the database file path
[Argument]	strFilepath: The absolute path of the database file on the disk.
[ReturnedValue]	void
************************************************************************/
void CDBEntity::SetFilepath(CString strFilepath)
{
	m_strFilepath = strFilepath;
}

/************************************************************************
[FunctionName]	SetCtTime
[Function]	Set the database creation time
[Argument]	tTime: Database creation time
[ReturnedValue]	void
************************************************************************/
void CDBEntity::SetCtTime(SYSTEMTIME tTime)
{
	m_tCtTime = tTime;
}

/************************************************************************
[FunctionName]	GetName
[Function]	Get the database name
[Argument]	void
[ReturnedValue]	CString: Database name
************************************************************************/
CString CDBEntity::GetName()
{
	return m_strName;
}

/************************************************************************
[FunctionName]	GetType
[Function]	Get the database type
[Argument]	void
[ReturnedValue]	bool: Database type.true is system database，false is custom database.
************************************************************************/
bool CDBEntity::GetType()
{
	return m_bType;
}

/************************************************************************
[FunctionName]	GetFilepath
[Function]	Get the database file path
[Argument]	void
[ReturnedValue]	CString: The absolute path of the database file on the disk.
************************************************************************/
CString CDBEntity::GetFilepath()
{
	return m_strFilepath;
}

/************************************************************************
[FunctionName]	GetCtTime
[Function]	Get the database creation time
[Argument]	void
[ReturnedValue]	SYSTEMTIME: creation time
************************************************************************/
SYSTEMTIME CDBEntity::GetCtTime()
{
	return m_tCtTime;
}

CTableEntity* CDBEntity::AddTable(CTableEntity &te)
{
	// Add field
	CTableEntity* pTable = new CTableEntity(te);
	m_arrTables.Add(pTable);

	return pTable;
}

CTableEntity* CDBEntity::GetTableAt(int nIndex)
{
	return m_arrTables.GetAt(nIndex);
}

int CDBEntity::GetTableNum()
{
	return m_arrTables.GetCount();
}
