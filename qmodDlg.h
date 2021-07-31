// qmodDlg.h : header file
//

#if !defined(AFX_QMODDLG_H__966F688C_2359_47CE_916C_A58F29C90CAE__INCLUDED_)
#define AFX_QMODDLG_H__966F688C_2359_47CE_916C_A58F29C90CAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CQmodDlg dialog

class CQmodDlg : public CDialog
{
// Construction
public:
	CQmodDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CQmodDlg)
	enum { IDD = IDD_QMOD_DIALOG };
	int		m_food;
	int		m_tech;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQmodDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CQmodDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCollection();
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIdEvent);
	int mainTimerID;

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QMODDLG_H__966F688C_2359_47CE_916C_A58F29C90CAE__INCLUDED_)
