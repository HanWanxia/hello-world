#pragma once
#include "afx.h"

/************************************************
[ClassName]	CAppException
[Function]	A custom exception class, the exception handler
************************************************/
class CAppException
{
public:
	//	Non-argument constructor
	CAppException(void);
	//	Overloaded constructor
	CAppException(CString strError);
	//	Destructor
	~CAppException(void);

public:
	//	Overload GetErrorMessage() function，Get error message
	CString GetErrorMessage();

private:
	CString m_strError;	//	Error message
	int m_nCode;		//	Error number
};

