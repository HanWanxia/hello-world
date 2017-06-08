// UpdateRecordDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RKDBMS.h"
#include "UpdateRecordDlg.h"
#include "afxdialogex.h"


// UpdateRecordDlg 对话框

IMPLEMENT_DYNAMIC(UpdateRecordDlg, CDialogEx)

UpdateRecordDlg::UpdateRecordDlg(CString title,CWnd* pParent /*=NULL*/)
	: CDialogEx(UpdateRecordDlg::IDD, pParent)
{
	mytitle = title;
	m_pTableEntity = NULL;
}

UpdateRecordDlg::~UpdateRecordDlg()
{
}

void UpdateRecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
}


BEGIN_MESSAGE_MAP(UpdateRecordDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &UpdateRecordDlg::OnBnClickedOk)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &UpdateRecordDlg::OnNMClickList1)
	ON_EN_KILLFOCUS(IDC_EDIT1, &UpdateRecordDlg::OnEnKillfocusEdit1)
END_MESSAGE_MAP()


// UpdateRecordDlg 消息处理程序


void UpdateRecordDlg::OnBnClickedOk()
{
	int nCount = m_list.GetItemCount();

	CString strField;
	CString strValue;
	// Get the value of each row in the list
	for (int i = 0; i < nCount; i++)
	{
		// Field name
		strField = m_list.GetItemText(i, 0);

		// Value
		strValue = m_list.GetItemText(i, 2);

		m_recordEntity.Put(strField, strValue);
	}

	CDialogEx::OnOK();
}


void UpdateRecordDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	m_dwItem = pNMListView->iItem;  // The selected row
	m_nSubItem = pNMListView->iSubItem;  // The selected column
	DWORD dwCount = m_list.GetItemCount();  // The number of the data item in the list

	// If the selected line number greater than 0, the column number greater than 1,
	// and no more than the number of data items in the list, respond to the events
	if (m_dwItem >= 0 && m_nSubItem == 2 && m_dwItem <= dwCount)
	{
		CFieldEntity* pField = m_pTableEntity->GetFieldAt(m_dwItem);

		// Get the size of the selected cell
		CRect rtEdit, rtClient;
		m_list.GetWindowRect(rtClient);
		ScreenToClient(rtClient);
		m_list.GetSubItemRect(m_dwItem, m_nSubItem, LVIR_LABEL, rtEdit);
		rtEdit.MoveToX(rtEdit.left + rtClient.left + 2);
		rtEdit.MoveToY(rtEdit.top + rtClient.top);
		rtEdit.bottom += 4;

		// Get the content of the selected cells
		CString strItemText = m_list.GetItemText(m_dwItem, m_nSubItem);
		int nLength = strItemText.GetLength();
		// Set the content of the edit control
		m_edit.SetWindowText(strItemText);
		m_edit.SetWindowPos(&wndTop, rtEdit.left, rtEdit.top, rtEdit.Width(), rtEdit.Height(), SWP_SHOWWINDOW);
		m_edit.SetSel(nLength, nLength);
		m_edit.SetFocus();
	}
}


void UpdateRecordDlg::OnEnKillfocusEdit1()
{
	// Get the value of the edit control
	CString strValue;
	m_edit.GetWindowText(strValue);

	// Assign the value of the edit control to list item
	m_list.SetItemText(m_dwItem, m_nSubItem, strValue);

	// Hide the edit control
	m_edit.ShowWindow(SW_HIDE);
}

CRecordEntity UpdateRecordDlg::GetRecord(void)
{
	return m_recordEntity;
}

BOOL UpdateRecordDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetDlgItemTextW(IDC_TITLE,mytitle);
	// Set the style of report
	DWORD dwStyle= ::GetWindowLong(m_list.m_hWnd ,GWL_STYLE);
	dwStyle |= LVS_REPORT;// Set style
	::SetWindowLong (m_list.m_hWnd ,GWL_STYLE, dwStyle);
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	// List header
	m_list.InsertColumn(0, _T("Field Name"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(1, _T("Field Type"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(3, _T("Value"), LVCFMT_LEFT, 150);

	// Load the table information
	if (m_pTableEntity != NULL)
	{
		// Get the numbet of field
		int nFieldNum = m_pTableEntity->GetFieldNum();
		for (int i = 0; i < nFieldNum; i++)
		{
			// Get field
			CFieldEntity* pField = m_pTableEntity->GetFieldAt(i);

			// Insert field name
			int nItem = m_list.InsertItem(i, pField->GetName());

			// Get the field type 
			int nDataType = pField->GetDataType();
			CString strTypeName = pField->GetTypeName(nDataType);
			// Insert the field type
			m_list.SetItemText(i, 1, strTypeName);
			m_list.SetItemData(i, nDataType);
		}
	}

	// Hide the edit control
	m_edit.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void UpdateRecordDlg::SetTable(CTableEntity* pTable)
{
	m_pTableEntity = pTable;
}
