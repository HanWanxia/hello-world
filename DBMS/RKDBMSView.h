
// RKDBMSView.h : interface of the CRKDBMSView class
//

#pragma once
class CRKDBMSDoc;  // Declare document class
/************************************************************************
[ClassName] CRKDBMSView
[Function] View class, display the interface, inherit from CView class.
************************************************************************/
class CRKDBMSView : public CView
{
protected: // create from serialization only
	CRKDBMSView();
	DECLARE_DYNCREATE(CRKDBMSView)

// Attributes
public:
	CRKDBMSDoc* GetDocument() const;   // Get the document associated with views

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs); //Modify the view window style
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CRKDBMSView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in RKDBMSView.cpp
inline CRKDBMSDoc* CRKDBMSView::GetDocument() const
   { return reinterpret_cast<CRKDBMSDoc*>(m_pDocument); }
#endif

