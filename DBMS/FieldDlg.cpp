// FieldDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RKDBMS.h"
#include "FieldDlg.h"
#include "afxdialogex.h"


// CFieldDlg dialog

IMPLEMENT_DYNAMIC(CFieldDlg, CDialogEx)

CFieldDlg::CFieldDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFieldDlg::IDD, pParent)
{

	m_strName = _T("");
	m_strDefault = _T("");
	m_strType = _T("");
	m_bNull = FALSE;
	m_bPrimary = FALSE;
}

CFieldDlg::~CFieldDlg()
{
}

void CFieldDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cbType);
	DDX_Text(pDX, IDC_EDIT_DEFAULT, m_strDefault);
	DDX_Check(pDX, IDC_CHECK_NULL, m_bNull);
	DDX_Check(pDX, IDC_CHECK_PRIMARY, m_bPrimary);
	DDX_CBString(pDX, IDC_COMBO_TYPE, m_strType);
}


BEGIN_MESSAGE_MAP(CFieldDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFieldDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CFieldDlg message handlers

/*****************************************************
[FunctionName]	OnInitDialog
[Function]	Dialog initialization function
[Argument]	void
[ReturnedValue]	BOOL:TRUE if the operation is successful, otherwise FALSE
*****************************************************/
BOOL CFieldDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Initializes the combo box
	m_cbType.InsertString(0, _T("INT"));
	m_cbType.InsertString(1, _T("VARCHAR"));
	m_cbType.InsertString(2, _T("BOOL"));
	m_cbType.InsertString(3, _T("DOUBLE"));
	m_cbType.InsertString(4, _T("DATATIME"));
	m_cbType.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/*****************************************************
[FunctionName]	OnBnClickedOk
[Function]	OK button BN_CLICKED message response function, save the input field information to the field entity object
[Argument]	void
[ReturnedValue]	void
*****************************************************/
void CFieldDlg::OnBnClickedOk()
{
	// Get the input data
	UpdateData();

	// Remove  the blank spaces in the field name
	m_strName.TrimLeft();
	m_strName.TrimRight();

	// The length of the field name must be greater than zero
	if (m_strName.GetLength() > 0)
	{
		m_fieldEntity.SetName(m_strName);
		
		if(m_strType.CollateNoCase(_T("INT")) == 0)
		{
			m_fieldEntity.SetDataType(CFieldEntity::DT_INTEGER);
		}
		else if(m_strType.CollateNoCase(_T("BOOL")) == 0)
		{
			m_fieldEntity.SetDataType(CFieldEntity::DT_BOOL);
		}
		else if(m_strType.CollateNoCase(_T("DOUBLE")) == 0)
		{
			m_fieldEntity.SetDataType(CFieldEntity::DT_DOUBLE);
		}
		else if(m_strType.CollateNoCase(_T("VARCHAR")) == 0)
		{
			m_fieldEntity.SetDataType(CFieldEntity::DT_VARCHAR);
			m_fieldEntity.SetParam(256);
		}
		else if(m_strType.CollateNoCase(_T("DATATIME")) == 0)
		{
			m_fieldEntity.SetDataType(CFieldEntity::DT_DATETIME);
		}
		CDialogEx::OnOK();
	}
}

/*****************************************************
[FunctionName]	GetField
[Function]	Get the object of field information entity
[Argument]	void
[ReturnedValue]	CFieldEntity: Field information entity
*****************************************************/
CFieldEntity CFieldDlg::GetField()
{
	return m_fieldEntity;
}
