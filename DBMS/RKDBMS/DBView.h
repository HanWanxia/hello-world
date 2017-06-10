#pragma once

#include "TableEntity.h"
#include "DBEntity.h"
#include "FieldEntity.h"	
// CDBView view
/****************************************************
[ClassName] CDBView
[Function] Shows the database structure view class, inherit from CTreeView
****************************************************/
class CDBView : public CTreeView
{
	DECLARE_DYNCREATE(CDBView)

protected:
	CDBView();           // protected constructor used by dynamic creation
	virtual ~CDBView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnInitialUpdate();	//	View initialization function
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);

protected:
	CTreeCtrl* m_pTreeCtrl;	// Tree control
	int number;

private:
	HTREEITEM AddTableNode(CTableEntity* pTable);	// Add a table item
	HTREEITEM selectDB;
	HTREEITEM AddFieldNode(CFieldEntity* pField, HTREEITEM hTableItem); // Add the field item
	HTREEITEM ModifyFieldNode(CFieldEntity* pField, HTREEITEM hTableItem,CTableEntity* pTable); // Modify the field item
	HTREEITEM DeleteFieldNode(CFieldEntity* pField, HTREEITEM hTableItem,CTableEntity* pTable); // Modify the field item
	HTREEITEM GetTableItem(CString strTableName);	// Get to table item
	HTREEITEM GetDBItem(CString strDBName);
private:
	CImageList m_imageList;	//	Tree image list

public:
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
	CString n;
};


