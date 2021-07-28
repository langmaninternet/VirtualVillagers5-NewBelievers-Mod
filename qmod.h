// qmod.h : main header file for the QMOD application
//

#if !defined(AFX_QMOD_H__B2D7B0FA_6509_4BFA_8DD2_AF7AFBC6401E__INCLUDED_)
#define AFX_QMOD_H__B2D7B0FA_6509_4BFA_8DD2_AF7AFBC6401E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CQmodApp:
// See qmod.cpp for the implementation of this class
//

class CQmodApp : public CWinApp
{
public:
	CQmodApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQmodApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CQmodApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QMOD_H__B2D7B0FA_6509_4BFA_8DD2_AF7AFBC6401E__INCLUDED_)
