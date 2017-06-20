#pragma once


// EditTable 对话框

class EditTable : public CDialogEx
{
	DECLARE_DYNAMIC(EditTable)

public:
	EditTable(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~EditTable();
	CString getTableName();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CString tname;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
