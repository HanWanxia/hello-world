#pragma once


// CNewTableDlg dialog
/************************************************
[ClassName]	CNewTableDlg
[Function]	New table dialog class
************************************************/
class CNewTableDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNewTableDlg)

public:
	CNewTableDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewTableDlg();

// Dialog Data
	enum { IDD = IDD_NEW_TABLE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strName;	// Table name

};
