// DBView.cpp : implementation file
//

#include "stdafx.h"
#include "RKDBMS.h"
#include "DBView.h"

#include "RKDBMSDoc.h"
#include "Global.h"


// CDBView

IMPLEMENT_DYNCREATE(CDBView, CTreeView)

CDBView::CDBView()
{
	m_pTreeCtrl = NULL;
	selectDB = NULL;
}

CDBView::~CDBView()
{
}

BEGIN_MESSAGE_MAP(CDBView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CDBView::OnTvnSelchanged)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CDBView::OnNMRClick)
END_MESSAGE_MAP()


// CDBView diagnostics

#ifdef _DEBUG
void CDBView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CDBView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDBView message handlers

/***********************************************
[FunctionName]	OnInitialUpdate
[Function]	View initialization function, initialize tree view
[Argument]	void
[ReturnedValue]	void
***********************************************/
void CDBView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
	CFile file;
	
	file.Open(_T("F:\\Liwenjie\\数据库实践课\\finalDBMS\\RKDBMS\\Output\\database.txt"), CFile::modeReadWrite | CFile::shareDenyWrite);
	
	file.SeekToBegin();
	

	//	Get the document object
	CRKDBMSDoc* pDoc = (CRKDBMSDoc*)this->GetDocument();
	pDoc->name = n;
	//	Get the exceptionl information
	CString strError = pDoc->GetError();

	//	Decide whether there are exceptions
	if (strError.GetLength() != 0)
	{
		//	Prompt exception information
		AfxMessageBox(strError);

		//	Set the exception information to empty
		pDoc->SetError(_T(""));
		return;
	}
	
	//	Delete images from the list
	m_imageList.DeleteImageList();

	// Ccreate icon in the list
	m_imageList.Create(16, 16, ILC_COLOR16 | ILC_MASK, 0, 4); 

	// Add images to the list
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_DATABASE));
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_TABLE));
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_CHILD));

	//	Get tree control
	m_pTreeCtrl = &this->GetTreeCtrl();
	selectDB = m_pTreeCtrl->GetRootItem();

	// Get the style of the tree control
	DWORD dwStyle = ::GetWindowLong(m_pTreeCtrl->m_hWnd, GWL_STYLE);

	// Set the style of the tree control
	dwStyle |= TVS_HASBUTTONS	// Expand or collapse the child items
			|TVS_HASLINES		// Draw lines linked child items to their corresponding parent item
			|TVS_LINESATROOT;	// Draw lines linked child items to the root item
	::SetWindowLong (m_pTreeCtrl->m_hWnd ,GWL_STYLE,dwStyle);

	// Assigns an image list to a list view control
	m_pTreeCtrl->SetImageList(&m_imageList, TVSIL_NORMAL);

	//	Get the database name
	CString strDBName = pDoc->GetDBEntity()->GetName();

	//	Add root item
	HTREEITEM hRoot;
	char* name=new char[100];
	for(int i=0;i<file.GetLength();i+=100)
	{
		file.Read(name,100);
		strDBName=name;
		hRoot = m_pTreeCtrl->InsertItem(strDBName, 0, 0, NULL);
		m_pTreeCtrl->SetItemData(hRoot, MENU_DATABASE);
		m_pTreeCtrl->Expand(hRoot, TVE_EXPAND);
	}
	file.Close();
}

/**************************************************************
[FunctionName]	OnUpdate
[Function]	View update function
[Argument]	CView* pSender: Pointer to the view
		LPARAM lHint: Include the information need to be modified
		CObject* pHint: Pointer to the modified object
[ReturnedValue]	void
**************************************************************/
void CDBView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CRKDBMSDoc* pDoc = (CRKDBMSDoc*)this->GetDocument();
	CString log;
	CString strTime;
	SYSTEMTIME t;
	GetLocalTime(&t);
	CString time=CTimeHelper::ToDatetimeString(t);
	CStdioFile file;
	file.Open(_T("F:\\Liwenjie\\数据库实践课\\finalDBMS\\RKDBMS\\Output\\Log.txt"), CFile::modeWrite | CFile::shareDenyWrite);

	char* logmess=new char[100];
	if (pSender == NULL)
	{
		switch (lHint)
		{
		case UPDATE_CREATE_TABLE:	//Create table
			{
				// Get table object pointer
				CTableEntity* pTable = (CTableEntity*)pHint;
				// Add item
				HTREEITEM hTableNode = AddTableNode(pTable);

				m_pTreeCtrl->SelectItem(hTableNode);
				file.SeekToEnd();
				log=time+_T(" CreateTable ")+pTable->GetName()+_T(" in ")+pDoc->GetEditDB()->GetName()+_T(";");
				file.Write(log,2*log.GetLength());
				
				file.Close();
			}
			break;
		case UPDATE_CREATEDATABASE:	//Create table
			{
				

				CDBEntity* pDB = (CDBEntity*)pHint;
				CRKDBMSDoc* pDoc = (CRKDBMSDoc*)this->GetDocument();
				//CDBEntity* pDB = pDoc->GetEditDB();
 				HTREEITEM hDBItem = GetDBItem(pDB->GetName());
				HTREEITEM hRoot = m_pTreeCtrl->InsertItem (pDB->GetName(),TVI_ROOT,TVI_LAST);
				m_pTreeCtrl->SetItemData(hRoot, MENU_DATABASE);
				//HTREEITEM hNewDBItem = AddDBNode(pNewDB, hDBItem);
				m_pTreeCtrl->SelectItem(hDBItem);
				file.SeekToEnd();
				log=time+_T(" CreateDatabase ")+pDB->GetName()+_T(";");
				file.Write(log,2*log.GetLength());
				file.Close();
			}
			break;
		case UPDATE_ADD_FIELD:		// Add field
			{
				CFieldEntity* pField = (CFieldEntity*)pHint;
				CTableEntity* pTable = pDoc->GetEditTable();
 				HTREEITEM hTableItem = GetTableItem(pTable->GetName());
				HTREEITEM hFieldItem = AddFieldNode(pField, hTableItem);
				m_pTreeCtrl->SelectItem(hFieldItem);
				file.SeekToEnd();
				log=time+_T(" AddField ")+pField->GetName()+_T(" in ")+pDoc->GetEditDB()->GetName()+_T(" ")+pTable->GetName()+_T(";");
				file.Write(log,2*log.GetLength());
				file.Close();
			}
			break;
		case UPDATE_OPEN_DATABASE:	// Open database
			{
				// Get table
				
				if(pDoc->GetDBEntity()->GetName()==m_pTreeCtrl->GetItemText(m_pTreeCtrl->GetSelectedItem()))
				{
					int nCount = pDoc->GetTableNum();
					for (int i = 0; i < nCount; i++)
					{
						CTableEntity* pTableEntity = pDoc->GetTable(i);
						AddTableNode(pTableEntity);
					
					}
					m_pTreeCtrl->SelectItem(m_pTreeCtrl->GetRootItem());
				}
				file.SeekToEnd();
				log=time+_T("  OpenDatabase  ")+pDoc->GetEditDB()->GetName()+_T(";");
				file.Write(log,2*log.GetLength());
				file.Close();
				
			}
			break;
		case UPDATE_Modify_Field:    //Modify field
			{
				CFieldEntity* pField = (CFieldEntity*)pHint;
				
				CTableEntity* pTable = pDoc->GetEditTable();
 				HTREEITEM hTableItem = GetTableItem(pTable->GetName());

				HTREEITEM hFieldItem = ModifyFieldNode(pField, hTableItem,pTable);
				m_pTreeCtrl->SelectItem(hFieldItem);
				file.SeekToEnd();
				log=time+_T(" ModifyField ")+m_pTreeCtrl->GetItemText(m_pTreeCtrl->GetSelectedItem())+_T("to")+_T(" ")+pField->GetName()+_T(" in ")+pDoc->GetEditDB()->GetName()+_T(" ")+pTable->GetName()+_T(";");
				file.Write(log,2*log.GetLength());
				file.Close();
			}
			break;
		case UPDATE_Delete_Field:
			{
				CFieldEntity* pField = (CFieldEntity*)pHint;
			
				CTableEntity* pTable = pDoc->GetEditTable();
 				HTREEITEM hTableItem = GetTableItem(pTable->GetName());

				HTREEITEM hFieldItem = DeleteFieldNode(pField, hTableItem,pTable);
				file.SeekToEnd();
				log=time+_T("  DeleteField  ")+pField->GetName()+_T(" in ")+pDoc->GetEditDB()->GetName()+_T(" ")+pTable->GetName();
				file.Write(log,2*log.GetLength());
				file.Close();
			}
			break;
		default:
			break;
		}

	}
}

/**************************************************************
[FunctionName]	AddTableNode
[Function]	Add table node in the tree control
[Argument]	CTableEntity* pTable: Pointer to the object of table entity
[ReturnedValue]	HTREEITEM: The added item
**************************************************************/
HTREEITEM CDBView::AddTableNode(CTableEntity* pTable)
{
	// Get root item
	HTREEITEM hRootNode = m_pTreeCtrl->GetSelectedItem();

	if (hRootNode != NULL)
	{
		// Add child item
		HTREEITEM hTableNode = m_pTreeCtrl->InsertItem(pTable->GetName(), 1, 1, hRootNode);

		if (hTableNode != NULL)
		{
			// Add number to the table item
			m_pTreeCtrl->SetItemData(hTableNode, MENU_TABLE);

			// Add leaf item
			HTREEITEM hColNode = m_pTreeCtrl->InsertItem(_T("Column"), 2, 2, hTableNode);       // Column

			// Add number to the column item
			m_pTreeCtrl->SetItemData(hColNode, MENU_OTHER);

			// Show field
			int nFieldNum = pTable->GetFieldNum();
			for (int i = 0; i < nFieldNum; i++)
			{
				CFieldEntity* pField = pTable->GetFieldAt(i);
				AddFieldNode(pField, hTableNode);
			}

			// Expand table item
			m_pTreeCtrl->Expand(hTableNode, TVE_EXPAND);
			// Expand database item
			m_pTreeCtrl->Expand(hRootNode, TVE_EXPAND);

			return hTableNode;
		}
	}
	return NULL;
}

/**************************************************************
[FunctionName]	AddFieldNode
[Function]	Add field item to the tree control
[Argument]	CFieldEntity* pField: Pointer to the object of table entity
		HTREEITEM hTableItem: Table item
[ReturnedValue]	HTREEITEM: The added item
**************************************************************/
HTREEITEM CDBView::AddFieldNode(CFieldEntity* pField, HTREEITEM hTableItem)
{
	// Get the child item of the table item
	//HTREEITEM hItem = m_pTreeCtrl->GetSelectedItem();
	
	HTREEITEM hItem = m_pTreeCtrl->GetChildItem(hTableItem);

	if (hItem != NULL)
	{
		// Traverse the child items of the table item
		do 
		{
			// Get column item
			if (m_pTreeCtrl->GetItemText(hItem).CompareNoCase(_T("Column")) == 0)
			{
				break;
			}
		}while ((hItem = m_pTreeCtrl->GetNextSiblingItem(hItem)) != NULL);
	}

	HTREEITEM hFieldNode = m_pTreeCtrl->InsertItem(pField->GetName(), 1, 1, hItem);       // Field
	
	// Add a number to the field item
	m_pTreeCtrl->SetItemData(hFieldNode, MENU_FIELD);
	
	return hFieldNode;
}
/***********************************************************/
HTREEITEM CDBView::ModifyFieldNode(CFieldEntity* pField, HTREEITEM hTableItem,CTableEntity* pTable)
{
	// Get the child item of the table item
	HTREEITEM hItem = m_pTreeCtrl->GetSelectedItem();
	
	
	m_pTreeCtrl->SetItemText(hItem,pField->GetName());
	return hItem;
}
/***************************************************/
HTREEITEM CDBView::DeleteFieldNode(CFieldEntity* pField, HTREEITEM hTableItem,CTableEntity* pTable)
{
	// Get the child item of the table item
	HTREEITEM hItem = m_pTreeCtrl->GetSelectedItem();
	
	

	m_pTreeCtrl->DeleteItem(hItem);
	return hItem;
}

/**************************************************************
[FunctionName]	OnTvnSelchanged
[Function]	The selected tree item message response function
[ReturnedValue]	void
**************************************************************/
void CDBView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// Get the object of the document
	CRKDBMSDoc* pDoc = (CRKDBMSDoc*)this->GetDocument();

	// Get the selected item
	HTREEITEM hSelectedItem = m_pTreeCtrl->GetSelectedItem();

	if (hSelectedItem != NULL)
	{
		DWORD dwVal = m_pTreeCtrl->GetItemData(hSelectedItem);
		if (dwVal == MENU_DATABASE)
		{
			HTREEITEM P;
			CString dbname;
			pDoc->SetEditTable(_T(""));
			P = m_pTreeCtrl->GetSelectedItem();
			dbname = m_pTreeCtrl->GetItemText(P);
			if(dbname != "")
			{
				pDoc->SetEditDB(dbname);
			}
			selectDB = P;
			//GetDlgItem(IDM_OPEN_DATABASE)->EnableWindow(true);
		}
		else if(dwVal == MENU_TABLE)
		{
			HTREEITEM hItem = hSelectedItem; 
			while (dwVal != MENU_TABLE)
			{
				hItem = m_pTreeCtrl->GetParentItem(hItem);
				dwVal = m_pTreeCtrl->GetItemData(hItem);
			}
			CString name = m_pTreeCtrl->GetItemText(hItem);
			pDoc->SetEditTable(m_pTreeCtrl->GetItemText(hItem));
		}
		else if(dwVal == MENU_FIELD)
		{
			CString fname;
			fname=m_pTreeCtrl->GetItemText(hSelectedItem);
			pDoc->GetEditTable()->SetEditField(fname);
		}
		else
		{}
	}
	*pResult = 0;
}

/**************************************************************
[FunctionName]	GetTableItem
[Function]	Get table item according to the table name
[Argument]	CString strTableName: Table name
[ReturnedValue]	HTREEITEM: Item
**************************************************************/
HTREEITEM CDBView::GetTableItem(CString strTableName)
{
	// Get root item
	HTREEITEM hRootNode = selectDB;

	// Get table item
	HTREEITEM hTableNode = m_pTreeCtrl->GetChildItem(hRootNode);

	if (hTableNode != NULL)
	{
		do 
		{
			if (m_pTreeCtrl->GetItemText(hTableNode).CompareNoCase(strTableName) == 0)
			{
				return hTableNode;
			}
		} while ((hTableNode = m_pTreeCtrl->GetNextSiblingItem(hTableNode)) != NULL);
	}
	return NULL;
}


HTREEITEM CDBView::GetDBItem(CString strDBName)
{
	// Get root item
	HTREEITEM hRootNode = m_pTreeCtrl->GetRootItem();

	// Get table item
	HTREEITEM hDBNode = m_pTreeCtrl->GetChildItem(hRootNode);

	if (hDBNode != NULL)
	{
		do 
		{
			if (m_pTreeCtrl->GetItemText(hDBNode).CompareNoCase(strDBName) == 0)
			{
				return hDBNode;
			}
		} while ((hDBNode = m_pTreeCtrl->GetNextSiblingItem(hDBNode)) != NULL);
	}
	return NULL;
}

/**************************************************************
[FunctionName]	OnNMRClick
[Function]	The right mouse button click event, when click on the root item, it will display the database operation menu.
[ReturnedValue]	void
**************************************************************/
void CDBView::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// Get the clicked position
	CPoint point;
	GetCursorPos(&point);
	// Convert the location of the cursor to client coordinates
	m_pTreeCtrl->ScreenToClient(&point); 
	// Decide whether the clicked location is on the tree control
	UINT nFlag = TVHT_ONITEM;   
	HTREEITEM hSelectedItem = m_pTreeCtrl->HitTest(point, &nFlag);

	if(NULL != hSelectedItem)	// Uncheck the new node, to return
	{	
		DWORD dwVal = m_pTreeCtrl->GetItemData(hSelectedItem);
		if (dwVal != MENU_OTHER)
		{
			// Convert the selected coordinates into the coordinates relative to screen
			m_pTreeCtrl->ClientToScreen(&point);
			// Load the menu resource
			CMenu* pMenu = this->GetParentFrame()->GetMenu()->GetSubMenu(dwVal);
			// Show the menu on the clicked position
			pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, point.x, point.y, AfxGetMainWnd());
		}

	}	

	*pResult = 0;
}
