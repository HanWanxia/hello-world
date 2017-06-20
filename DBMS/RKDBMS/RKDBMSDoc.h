
// RKDBMSDoc.h : interface of the CRKDBMSDoc class
//


#pragma once

#include "DBEntity.h"		
#include "TableEntity.h"
#include "DBEntity.h"
#include "FieldEntity.h"	
#include "RecordEntity.h"

/*****************************************************
[ClassName] CRKDBMSDoc
[Function] Document class, implement procedures logic operation related to the interface, and maintain and manage data.
*****************************************************/
class CRKDBMSDoc : public CDocument
{
protected: // create from serialization only
	CRKDBMSDoc();
	DECLARE_DYNCREATE(CRKDBMSDoc)

// Attributes
public:
	
// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();       // Create new docunment.
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();		// Close document.
#ifdef SHARED_HANDLERS
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CRKDBMSDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	CDBEntity m_dbEntity;	// Database entity object
	CString m_strError;		// Exception information
	TABLEARR m_arrTable;	// Table array
	CTableEntity* m_pEditTable;	// Current edit form
	CDBEntity* m_pEditDB;
	CDBEntity* m_pEditDB1;
	DBARR mydb;

	RECORDARR m_arrRecord;	// Record information

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
#endif // SHARED_HANDLERS


public:
	CDBEntity* GetDBEntity();			//	Get the database entities
	CString GetError();					//	Get exception information
	void SetError(CString strError);	//	Set exception information

	CDBEntity* CreateDB(CString strName);
	CTableEntity* CreateTable(CString strName);		// Create table
	CTableEntity* GetEditTable();					// Get current form
	CDBEntity* GetEditDB();
	CFieldEntity* AddField(CFieldEntity &field);	// Add field
	CFieldEntity* ModifyField(CFieldEntity &field,CTableEntity* pTable);     //Modify field
	CFieldEntity* DeleteField(CFieldEntity &field,CTableEntity* pTable);     //Delete field
	void SetEditTable(CTableEntity* pTable);		// Set the current form
	void SetEditTable(CString strTableName);		// Set the current form
	void SetEditDB(CString strDBName);
	CTableEntity* GetTable(int nIndex);				// Get table
	CDBEntity* GetDB(int nIndex);
	int GetTableNum();								// Get the number of table information
	int GetDBNum();
	void LoadTables(void);							// Load tables
	void selectRecord(CRecordEntity &selectRecord);                            //select records
	void UpdateRecord(CRecordEntity &selectRecord,CRecordEntity &modifyRecord);
	void DeleteRecord(CRecordEntity &selectRecord); //delete record
	CRecordEntity* InsertRecord(CRecordEntity &record);	// Insert a record
	int GetRecordNum();								// Get the number of records
	CRecordEntity* GetRecord(int nIndex);			// Get a record
	CRKDBMSDoc(CString n);
	CString name;
	int getDBAt();
	bool EditTable(CTableEntity* pTable);
	CTableEntity* DeleteTable(CTableEntity* pTable);     //Delete field
};
