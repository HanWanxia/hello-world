#pragma once
#include "FieldEntity.h"	

// CFieldDlg dialog
/*******************************************
[ClassName]	CFieldDlg
[Function]	Field properties dialog box class, inherit from CDialogEx
*******************************************/
class CFieldDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFieldDlg)

public:
	CFieldDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFieldDlg();

public:
	CFieldEntity GetField();
// Dialog Data
	enum { IDD = IDD_FIELD_DIALOG };
	virtual BOOL OnInitDialog();	// Dialog initialization function
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
public:
	CString m_strName;		// Field name
	CComboBox m_cbType;		// Type
	CString m_strDefault;	// Defult value
	BOOL m_bNull;			// Whether is null
	BOOL m_bPrimary;		// Whether is primary key

private:
	CFieldEntity m_fieldEntity;	// Field information entity

public:
	CString m_strType;
};
