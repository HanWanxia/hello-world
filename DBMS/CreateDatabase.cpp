// CreateDatabase.cpp : 实现文件
//

#include "stdafx.h"
#include "RKDBMS.h"
#include "CreateDatabase.h"
#include "afxdialogex.h"


// CreateDatabase 对话框

IMPLEMENT_DYNAMIC(CreateDatabase, CDialogEx)

CreateDatabase::CreateDatabase(CWnd* pParent /*=NULL*/)
	: CDialogEx(CreateDatabase::IDD, pParent)
{
	dbname = _T("");
}

CreateDatabase::~CreateDatabase()
{
}

void CreateDatabase::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, dbname);
}


BEGIN_MESSAGE_MAP(CreateDatabase, CDialogEx)
	ON_BN_CLICKED(IDOK, &CreateDatabase::OnBnClickedOk)
END_MESSAGE_MAP()


// CreateDatabase 消息处理程序


void CreateDatabase::OnBnClickedOk()
{
	// Get the input table name
	UpdateData();

	// Eliminate the blank space in the string
	dbname.TrimLeft();	
	dbname.TrimRight();	

	// If the length of the table name is greater than zero, Confirm the name of the table is correct
	if (dbname.GetLength() > 0)
	{
		CDialogEx::OnOK();
	}
}
