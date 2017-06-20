// EditTable.cpp : 实现文件
//

#include "stdafx.h"
#include "RKDBMS.h"
#include "EditTable.h"
#include "afxdialogex.h"


// EditTable 对话框

IMPLEMENT_DYNAMIC(EditTable, CDialogEx)

EditTable::EditTable(CWnd* pParent /*=NULL*/)
	: CDialogEx(EditTable::IDD, pParent)
{

}

EditTable::~EditTable()
{
}

void EditTable::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(EditTable, CDialogEx)
	ON_BN_CLICKED(IDOK, &EditTable::OnBnClickedOk)
END_MESSAGE_MAP()


// EditTable 消息处理程序


void EditTable::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT_Table)->GetWindowText(tname);
	CDialogEx::OnOK();
}

CString EditTable::getTableName()
{
	return tname;
}
