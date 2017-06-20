
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "RKDBMS.h"

#include "MainFrm.h"
#include "DBView.h"
#include "RKDBMSView.h"
#include "RKDBMSDoc.h"
#include "NewTableDlg.h"
#include "FieldDlg.h"
#include "Global.h"
#include "TableView.h"
#include "RecordsView.h"
#include "UpdateRecordDlg.h"
#include "CreateDatabase.h"
#include "ModifyField.h"
#include "EditTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(IDM_NEW_TABLE, &CMainFrame::OnNewTable)
	ON_COMMAND(IDM_ADD_FIELD, &CMainFrame::OnAddField)
	ON_COMMAND(IDM_OPEN_DATABASE, &CMainFrame::OnOpenDatabase)
	ON_UPDATE_COMMAND_UI(IDM_OPEN_DATABASE, &CMainFrame::OnUpdateOpenDatabase)
	ON_COMMAND(IDM_MODIFY_TABLE, &CMainFrame::OnEditTable)
	ON_COMMAND(IDM_OPEN_TABLE, &CMainFrame::OnOpenTable)
	ON_COMMAND(IDM_ADD_RECORD, &CMainFrame::OnInsertRecord)
	ON_COMMAND(IDM_CREATE_DATABASE, &CMainFrame::OnCreateDatabase)
	ON_COMMAND(IDM_MODIFY_RECORD, &CMainFrame::OnModifyRecord)
	ON_COMMAND(IDM_DELETE_RECORD, &CMainFrame::OnDeleteRecord)
	ON_COMMAND(IDM_MODIFY_FIELD, &CMainFrame::OnModifyField)
	ON_COMMAND(IDM_DELETE_FIELD, &CMainFrame::OnDeleteField)
	ON_COMMAND(IDM_DELETE_TABLE, &CMainFrame::OnDeleteTable)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_RUANKO_TITLE,        // The author information pane
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// View type
#define DEFAULT 0	// Default view
#define TABLE   1	// Table structure view
#define RECORDS 2	// Record view
#define DATABASE 3	// Record view

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	CFile file;
	
	file.Open(_T("table.txt"), CFile::modeReadWrite | CFile::shareDenyWrite);
	file.SeekToBegin();
	char* bopen=new char[1];
	CString dbname;
	int h;
	if(file.GetLength()<1)
	{
		open[0]=0;
	}else{
		for(int i=0;i<file.GetLength();i++)
		{
			file.Read(bopen,1);
			h=atoi(bopen);
			open[i]=h;
		}
	}
	
	//m_bOpenDatabase=false;
	file.Close();
}

CMainFrame::~CMainFrame()
{
}

/************************************************************************
[FunctionName]	OnCreate
[Function]	The function of creating framework, called by the system, which is used to initialize the menu bar, toolbar bar and status bar
[Argument]	LPCREATESTRUCT lpCreateStruct: Create a framework of information structure
[ReturnedValue] int: Zero if the operation is successful; otherwise non-zero.
************************************************************************/
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// Set window text
	this->SetTitle(_T("DBMS"));
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

/***************************************************************
[FunctionName]	OnCreateClient
[Function]	Split window
[Argument]	LPCREATESTRUCT lpcs: A pointer to a Windows CREATESTRUCT structure.
		CCreateContext* pContext:A pointer to a CCreateContext structure.
[ReturnedValue] BOOL: TRUE if successful; otherwise FALSE
***************************************************************/
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// Create a static split window, the view can be divided into two columns
	if (!m_wndSpliter.CreateStatic(this, 1, 2))
	{
		AfxMessageBox(_T("Failed to  split window!"));
		return FALSE;
	}

	// Add view to the separated window
	if(!m_wndSpliter.CreateView(0, 0, RUNTIME_CLASS(CDBView), CSize(200, 0), pContext))
	{
		return FALSE;
	}
	if (!m_wndSpliter.CreateView(0, 1, RUNTIME_CLASS(CRKDBMSView), CSize(0,0), pContext))
	{
		return FALSE;
	}


	return TRUE;

//	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

/************************************************
[FunctionName]	OnNewTable
[Function]	COMMAND message response function of new table menu , response to the functionality of creating talbe 
[Argument]	void
[ReturnedValue]	void
************************************************/
void CMainFrame::OnNewTable()
{
	
	CFile file;
	file.Open(_T("table.txt"), CFile::modeWrite | CFile::shareDenyWrite);
	CRKDBMSDoc* pDoc = (CRKDBMSDoc*)this->GetActiveDocument();
	CDBEntity* pDB = pDoc->GetEditDB();
	file.Seek(pDoc->getDBAt(),CFile::begin);
	file.Write("1",1);
	open[pDoc->getDBAt()]=0;
	file.Close();
	if (pDB != NULL)
	{	
		// Create and display the new table dialog
		CNewTableDlg dlg;
		int nRes = dlg.DoModal();
				// nRes==IDOK，Confirm the name of the table
		if (nRes == IDOK)
		{
			// Get the existed table
			int nCount = pDoc->GetTableNum();
			for (int i = 0; i < nCount; i++)
			{
				CString strName = pDoc->GetTable(i)->GetName();
				if (dlg.m_strName == strName)
				{
					AfxMessageBox(_T("The table has been existed！"));
					return;
				}
			}
			// Create the table according to the input table name
			CTableEntity* pTable = pDoc->CreateTable(dlg.m_strName);
			// Get the exception information
			CString strError = pDoc->GetError();
			// If there has exception information, prompt exception
			if (strError.GetLength() != 0)
			{
				AfxMessageBox(strError);
				pDoc->SetError(_T(""));
				return;
			}
			// If the added table is not empty, update the view
			if (pTable != NULL)
			{
				// Switch to the table view
				SwitchView(TABLE);

				// Update view
				pDoc->UpdateAllViews(NULL, UPDATE_CREATE_TABLE, pTable);
			}
		}
	}

}

/************************************************
[FunctionName]	OnAddField
[Function]	COMMAND message response function of adding filed menu , response to the functionality of adding field 
[Argument]	void
[ReturnedValue]	void
************************************************/
void CMainFrame::OnAddField()
{
	// Get the object of document
	CRKDBMSDoc* pDoc = (CRKDBMSDoc*)this->GetActiveDocument();
	CTableEntity* pTable = pDoc->GetEditTable();
	if (pTable != NULL)
	{	
		// Create and display the fields dialog box
		CFieldDlg dlg;
		int nRes = dlg.DoModal();

		if (nRes == IDOK)
		{
			CFieldEntity field = dlg.GetField();
			// Decide whether the field exists
			int nCount = pTable->GetFieldNum();
			for (int i = 0; i < nCount; i++)
			{
				if (field.GetName() == pTable->GetFieldAt(i)->GetName())
				{
					AfxMessageBox(_T("The field has been existed！"));
					return;
				}
			}
			// Add field
			CFieldEntity* pField = pDoc->AddField(dlg.GetField());

			// If there has exception information, prompt exception
			CString strError = pDoc->GetError();
			if (strError.GetLength() != 0)
			{
				AfxMessageBox(strError);
				pDoc->SetError(_T(""));
				return;
			}

			// If the added field is not empty, update the view
			if (pField != NULL)
			{
				pDoc->UpdateAllViews(NULL, UPDATE_ADD_FIELD, pField);
			}
		}
	}
}


/************************************************
[FunctionName]	SwitchView
[Function]	Switch view
[Argument]	int nViewType: view type
[ReturnedValue]	void
************************************************/
void CMainFrame::SwitchView(int nViewType)
{
	// Get the size of the original window
	CRect rt;
	CView* pOldView = (CView*)m_wndSpliter.GetPane(0, 1);	
	pOldView->GetClientRect(&rt);

	// Get the context
	CCreateContext context;
	context.m_pCurrentDoc = pOldView->GetDocument();
	context.m_pCurrentFrame = this;

	// Delete the original view
	m_wndSpliter.DeleteView(0, 1);

	// Depending on the type of view, create a new view
	switch(nViewType)
	{
	case TABLE:	// Table structure view
		{
			// Add a new view
			context.m_pNewViewClass = RUNTIME_CLASS(CTableView);
			m_wndSpliter.CreateView(0, 1, RUNTIME_CLASS(CTableView), rt.Size(), &context);
		}
		break;
	case DATABASE:	// Table structure view
		{
			// Add a new view
			context.m_pNewViewClass = RUNTIME_CLASS(CDBView); 
			m_wndSpliter.CreateView(0, 1, RUNTIME_CLASS(CDBView), rt.Size(), &context);
		}
		break;
	case RECORDS:	// Record view
		{
			// Add new view
			context.m_pNewViewClass = RUNTIME_CLASS(CRecordsView);
			m_wndSpliter.CreateView(0, 1, RUNTIME_CLASS(CRecordsView), rt.Size(), &context);
		}
		break;
	case DEFAULT:	// Default view
		{
			// Add new view
			context.m_pNewViewClass = RUNTIME_CLASS(CTableView);
			m_wndSpliter.CreateView(0, 1, RUNTIME_CLASS(CRKDBMSView), rt.Size(), &context);
		}
		break;
	default:
		break;
	}

	// Update view
	CView* pCurView = (CView*)m_wndSpliter.GetPane(0, 1);
	pCurView->OnInitialUpdate();

	// Update window
	m_wndSpliter.RecalcLayout();
}

/************************************************
[FunctionName]	OnOpenDatabase
[Function]	COMMAND message response function of opening database menu , response to the functionality of opening database
[Argument]	int nViewType: View type
[ReturnedValue]	void
************************************************/
void CMainFrame::OnOpenDatabase()
{
	// Get the pointer to the document
	CRKDBMSDoc* pDoc = (CRKDBMSDoc*)this->GetActiveDocument();

	// Read table
	pDoc->LoadTables();

	// Decide whether has exception
	CString strError = pDoc->GetError();
	if(strError.GetLength() > 0)
	{
		AfxMessageBox(strError);
		pDoc->SetError(_T(""));
	}
	
	// The database has been opened
	open[pDoc->getDBAt()] = 0;

	// Update view
	pDoc->UpdateAllViews(NULL, UPDATE_OPEN_DATABASE, NULL);
}

/************************************************
[FunctionName]	OnUpdateOpenDatabase
[Function]	Change the display status of menu item
[Argument]	CCmdUI *pCmdUI: The object to receive command
[ReturnedValue]	void
************************************************/
void CMainFrame::OnUpdateOpenDatabase(CCmdUI *pCmdUI)
{
	CRKDBMSDoc* pDoc = (CRKDBMSDoc*)this->GetActiveDocument();
	pCmdUI->Enable(open[pDoc->getDBAt()]);
}

/************************************************
[FunctionName]	OnEditTable
[Function]	COMMAND message response function of altering table menu , display the table structure
[Argument]	void
[ReturnedValue]	void
************************************************/
void CMainFrame::OnEditTable()
{
	CRKDBMSDoc* pDoc = (CRKDBMSDoc*)this->GetActiveDocument();
	if (open[pDoc->getDBAt()] == FALSE)
	{

		// Create new table
		CDBEntity* pDB=pDoc->GetEditDB();
		EditTable editTable;
		int judge=editTable.DoModal();
		CTableEntity* pTable=pDoc->GetEditTable();
		
		if(judge==IDOK)
		{
			
			int nCount = pDoc->GetTableNum();
			
			for (int i = 0; i < nCount; i++)
			{
				if (editTable.getTableName() == pDoc->GetTable(i)->GetName())
				{
					AfxMessageBox(_T("The table has been existed！"));
					return;
				}
			}
			pTable->SetName(editTable.getTableName());
		}
		if (pTable != NULL)
		{
			// Switch window
			SwitchView(TABLE);	
			pDoc->EditTable(pTable);

			pDoc->UpdateAllViews(NULL, UPDATE_EDIT_TABLE,  pTable);
		}
	}
	
}

/************************************************
[FunctionName]	OnOpenTable
[Function]	COMMAND message response function of opening table menu,display the record, select records.
[Argument]	void
[ReturnedValue]	void
************************************************/
void CMainFrame::OnOpenTable()
{
	CRKDBMSDoc* pDoc = (CRKDBMSDoc*)this->GetActiveDocument();
	if (open[pDoc->getDBAt()] == FALSE)
	{
		// Get the pointer to the object of docunment
		

		// Gets the current edit table
		CTableEntity* pTable = pDoc->GetEditTable();

		// Decide whether the current edit table is null
		if (pTable != NULL)
		{

			UpdateRecordDlg* dlg = new UpdateRecordDlg(_T("Select record:"));
			// Set the table editor
			dlg->SetTable(pTable);

			// Create a record and display the dialog box
			int nRes = dlg->DoModal();

			if (nRes == IDOK)
			{
				CRecordEntity record = dlg->GetRecord();
				pDoc->selectRecord(record);
			}

			// If not null, query record
			//pDoc->LoadRecord();

			// Decide whether has exception
			CString strError = pDoc->GetError();
			if (strError.GetLength() > 0)
			{
				AfxMessageBox(strError);
				pDoc->SetError(_T(""));
				return;
			}
			// Switch window
			SwitchView(RECORDS);

			// Update view
			pDoc->UpdateAllViews(NULL, UPDATE_OPEN_TABLE, pTable);
		}
	}
}

/************************************************
[FunctionName]	OnInsertRecord
[Function]	COMMAND message response function of adding record menu,insert record into the table. 
[Argument]	void
[ReturnedValue]	void
************************************************/
void CMainFrame::OnInsertRecord()
{
	CRKDBMSDoc* pDoc = (CRKDBMSDoc*)this->GetActiveDocument();
	if (1)
	{
		// Get the object of the document
		
		// Gets the current edit table
		CTableEntity* pTable = pDoc->GetEditTable();
		if (pTable != NULL)
		{
			UpdateRecordDlg* dlg = new UpdateRecordDlg(_T("Insert record:"));
			// Set the table editor
			dlg->SetTable(pTable);

			// Create a record and display the dialog box
			int nRes = dlg->DoModal();

			if (nRes == IDOK)
			{
				// Get the record
				CRecordEntity record = dlg->GetRecord();

				// Insert record
				CRecordEntity* pRecord = pDoc->InsertRecord(record);

				// Decide whether has exception
				CString strError = pDoc->GetError();
				if (strError.GetLength() > 0)
				{
					AfxMessageBox(strError);
					pDoc->SetError(_T(""));
				}
				if (pRecord != NULL)
				{
					// Update view
					pDoc->UpdateAllViews(NULL, UPDATE_INSERT_RECORD, pRecord);
				}
			}
		}
	}
}

/************************************************
[FunctionName]	OnCreateDatabase
[Function]	COMMAND message response function of create database menu,create a database. 
[Argument]	void
[ReturnedValue]	void
************************************************/ 
void CMainFrame::OnCreateDatabase()
{
	
	// Create and display the new table dialog
	CreateDatabase dlg;
	int nRes = dlg.DoModal();

	// nRes==IDOK，Confirm the name of the table
	if (nRes == IDOK)
	{
		//	Get the object of document
		CRKDBMSDoc* pDoc = (CRKDBMSDoc*)this->GetActiveDocument();
		name = dlg.dbname;
		// Get the existed database
		int nCount = pDoc->GetDBNum();
		for (int i = 0; i < nCount; i++)
		{
			CString strName = pDoc->GetDB(i)->GetName();
			if (dlg.dbname == strName)
			{
				AfxMessageBox(_T("The table has been existed！"));
				return;
			}
		}
		open[pDoc->GetDBNum()]=0;
		// Create the database according to the input database name
		CDBEntity* db = pDoc->CreateDB(dlg.dbname);
		// Get the exception information
		CString strError = pDoc->GetError();
		// If there has exception information, prompt exception
		if (strError.GetLength() != 0)
		{
			AfxMessageBox(strError);
			pDoc->SetError(_T(""));
			return;
		}
		// If the added database is not empty, update the view
		if (db != NULL)
		{
			// Switch to the database view
			SwitchView(DATABASE);
				// Update view
			pDoc->UpdateAllViews(NULL, UPDATE_CREATEDATABASE, (CObject*)db);
		}
	}
}

/************************************************
[FunctionName]	OnModifyRecord
[Function]	COMMAND message response function of modify record menu,update the record value. 
[Argument]	void
[ReturnedValue]	void
************************************************/ 
void CMainFrame::OnModifyRecord()
{
	CRKDBMSDoc* pDoc = (CRKDBMSDoc*)this->GetActiveDocument();
	if (open[pDoc->getDBAt()] == FALSE)
	{
		// Get the object of the document
		
		// Gets the current edit table
		CTableEntity* pTable = pDoc->GetEditTable();
		if (pTable != NULL)
		{
			UpdateRecordDlg* dlg = new UpdateRecordDlg(_T("Select record:"));
			// Set the table editor
			dlg->SetTable(pTable);

			// Create a record and display the dialog box
			int nRes = dlg->DoModal();

			if (nRes == IDOK)
			{
				// Get the record
				CRecordEntity selectRecord = dlg->GetRecord();
				CRecordEntity modifyRecord;
				UpdateRecordDlg* modify = new UpdateRecordDlg(_T("Modify value:"));
				modify->SetTable(pTable);
				int res = modify->DoModal();
				if(res == IDOK)
					modifyRecord = modify->GetRecord();
				

				// If not null, update record
				pDoc->UpdateRecord(selectRecord,modifyRecord);

				// Decide whether has exception
				CString strError = pDoc->GetError();
				if (strError.GetLength() > 0)
				{
					AfxMessageBox(strError);
					pDoc->SetError(_T(""));
					return;
				}
				SwitchView(RECORDS);

			// Update view
			pDoc->UpdateAllViews(NULL, UPDATE_OPEN_TABLE, pTable);
			}
		}
	}
}


void CMainFrame::OnDeleteRecord()
{
	CRKDBMSDoc* pDoc = (CRKDBMSDoc*)this->GetActiveDocument();
	if (open[pDoc->getDBAt()] == FALSE)
	{
		// Get the object of the document
		
		// Gets the current edit table
		CTableEntity* pTable = pDoc->GetEditTable();
		if (pTable != NULL)
		{
			UpdateRecordDlg* dlg = new UpdateRecordDlg(_T("Select record:"));
			// Set the table editor
			dlg->SetTable(pTable);

			// Create a record and display the dialog box
			int nRes = dlg->DoModal();

			if (nRes == IDOK)
			{
				// Get the record
				CRecordEntity selectRecord = dlg->GetRecord();
				
				// If not null, update record
				pDoc->DeleteRecord(selectRecord);

				// Decide whether has exception
				CString strError = pDoc->GetError();
				if (strError.GetLength() > 0)
				{
					AfxMessageBox(strError);
					pDoc->SetError(_T(""));
					return;
				}
				SwitchView(RECORDS);

			// Update view
			pDoc->UpdateAllViews(NULL, UPDATE_OPEN_TABLE, pTable);
			}
		}
	}
}


void CMainFrame::OnModifyField()
{
	// TODO: 在此添加命令处理程序代码
	CRKDBMSDoc* pDoc = (CRKDBMSDoc*)this->GetActiveDocument();
	CTableEntity* pTable = pDoc->GetEditTable();
	if (pTable != NULL)
	{	
		// Create and display the fields dialog box
		ModifyField dlg;
		int nRes = dlg.DoModal();

		if (nRes == IDOK)
		{
			//CFieldEntity field = dlg.GetField();
			// Decide whether the field exists
			int nCount = pTable->GetFieldNum();
			CFieldEntity* pField=pTable->GetEditField();
			CString s=pField->GetName();
			for (int i = 0; i < nCount; i++)
			{
				if (dlg.getFieldName() == pTable->GetFieldAt(i)->GetName())
				{
					AfxMessageBox(_T("The field has been existed！"));
					return;
				}
			}
			pField->SetName(dlg.getFieldName());
			
			
			// Add field
			CFieldEntity* field = pDoc->ModifyField(*pField,pDoc->GetEditTable());

			// If there has exception information, prompt exception
			CString strError = pDoc->GetError();
			if (strError.GetLength() != 0)
			{
				AfxMessageBox(strError);
				pDoc->SetError(_T(""));
				return;
			}

			// If the added field is not empty, update the view
			if (pField != NULL)
			{
				//pDoc->UpdateAllViews(NULL, UPDATE_OPEN_TABLE, pTable);
				pDoc->UpdateAllViews(NULL, UPDATE_Modify_Field, pField);
			}
		}
	}
	
}


void CMainFrame::OnDeleteField()
{
	// TODO: 在此添加命令处理程序代码
	CRKDBMSDoc* pDoc = (CRKDBMSDoc*)this->GetActiveDocument();
	CTableEntity* pTable = pDoc->GetEditTable();
	if (pTable != NULL)
	{	
		// Create and display the fields dialog box
		

		
			//CFieldEntity field = dlg.GetField();
			// Decide whether the field exists
			
			CFieldEntity* pField=pTable->GetEditField();
			
			
			
			// Add field
			CFieldEntity* field = pDoc->DeleteField(*pField,pDoc->GetEditTable());

			// If there has exception information, prompt exception
			CString strError = pDoc->GetError();
			if (strError.GetLength() != 0)
			{
				AfxMessageBox(strError);
				pDoc->SetError(_T(""));
				return;
			}

			// If the added field is not empty, update the view
			if (pField != NULL)
			{
				//pDoc->UpdateAllViews(NULL, UPDATE_OPEN_TABLE, pTable);
				pDoc->UpdateAllViews(NULL, UPDATE_Delete_Field, pField);
			}
		
	}
}



void CMainFrame::OnDeleteTable()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: 在此添加命令处理程序代码
	CRKDBMSDoc* pDoc = (CRKDBMSDoc*)this->GetActiveDocument();
	
	CDBEntity* pDB = pDoc->GetEditDB();
	if (pDB != NULL)
	{	
		// Create and display the fields dialog box
		

		
			//CFieldEntity field = dlg.GetField();
			// Decide whether the field exists
			
			CTableEntity* pTable = pDoc->GetEditTable();
			
			
			
			// Add field
			pDoc->DeleteTable(pTable);

			// If there has exception information, prompt exception
			CString strError = pDoc->GetError();
			if (strError.GetLength() != 0)
			{
				AfxMessageBox(strError);
				pDoc->SetError(_T(""));
				return;
			}

			// If the added field is not empty, update the view
			if (pTable != NULL)
			{
				//pDoc->UpdateAllViews(NULL, UPDATE_OPEN_TABLE, pTable);
				pDoc->UpdateAllViews(NULL, UPDATE_Delete_Table, pTable);
			}
		
	}
}
