#pragma once

#include "afxwin.h"
#include "FEM.h"
// CFEADlg dialog

class CFEADlg : public CDialog
{
public:
	CFEADlg();
	~CFEADlg();

	FEM * pFEM; 

	// Dialog Data
	enum { IDD = IDD_FEA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
														// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	// Memory allocations and management functions
	//void createFEM();
	//void deleteFEM();

	// Message handlers
	afx_msg void OnBnClickedSelectbcs();
	afx_msg void OnBnClickedSetprops();

	afx_msg void OnBnClickedAnalyze();
	afx_msg void OnBnClickedButton4();

	CButton m_buttonAnalyze;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
};

