#pragma once


// CreateDatabase 对话框

class CreateDatabase : public CDialogEx
{
	DECLARE_DYNAMIC(CreateDatabase)

public:
	CreateDatabase(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CreateDatabase();

// 对话框数据
	enum { IDD = IDD_CREATEDATABASE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString dbname;
};
