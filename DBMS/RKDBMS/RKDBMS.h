
// RKDBMS.h : main header file for the RKDBMS application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CRKDBMSApp:
// See RKDBMS.cpp for the implementation of this class
//

/************************************************************************
[ClassName] CRKDBMSApp
[Function] Applacation class，achieve the function of the application of creation and cancellation
************************************************************************/
class CRKDBMSApp : public CWinApp
{
public:
	CRKDBMSApp();


// Overrides
public:
	virtual BOOL InitInstance();   // Initialize the application instance function
	virtual int ExitInstance();    // Exit the application instance function

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRKDBMSApp theApp;
