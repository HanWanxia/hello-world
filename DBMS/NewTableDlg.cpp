// NewTableDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RKDBMS.h"
#include "NewTableDlg.h"
#include "afxdialogex.h"


// CNewTableDlg dialog

IMPLEMENT_DYNAMIC(CNewTableDlg, CDialogEx)

CNewTableDlg::CNewTableDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNewTableDlg::IDD, pParent)
{

	m_strName = _T("");
}

CNewTableDlg::~CNewTableDlg()
{
}

void CNewTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
}


BEGIN_MESSAGE_MAP(CNewTableDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CNewTableDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CNewTableDlg message handlers

/************************************************
[FunctionName]	OnBnClickedOk
[Function]	BN_CLICKED message response function of OK button, get the input table name
[Argument]	void
[ReturnedValue]	void
************************************************/
void CNewTableDlg::OnBnClickedOk()
{
	// Get the input table name
	UpdateData();

	// Eliminate the blank space in the string
	m_strName.TrimLeft();	
	m_strName.TrimRight();	

	// If the length of the table name is greater than zero, Confirm the name of the table is correct
	if (m_strName.GetLength() > 0)
	{
		CDialogEx::OnOK();
	}

}
