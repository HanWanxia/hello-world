#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "TableEntity.h"	
#include "RecordEntity.h"	


// UpdateRecordDlg 对话框

class UpdateRecordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(UpdateRecordDlg)

public:
	UpdateRecordDlg(CString title,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~UpdateRecordDlg();

// 对话框数据
	enum { IDD = IDD_UPDATE_RECORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void SetTable(CTableEntity* pTable);
	CListCtrl m_list;
	CEdit m_edit;

private:
	CTableEntity* m_pTableEntity;	// Pointer to the object of table entity
	DWORD m_dwItem;		// Row
	int m_nSubItem;		// Column
	CString mytitle;
	CRecordEntity m_recordEntity;	// Record the object of view


public:
	afx_msg void OnBnClickedOk();
	CRecordEntity GetRecord(void);
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusEdit1();
	virtual BOOL OnInitDialog();
};
