
// PledgeDistributionDlg.h : header file
//

#pragma once


// CPledgeDistributionDlg dialog
class CPledgeDistributionDlg : public CDialogEx
{
// Construction
public:
	CStatusBar m_bar;
	CPledgeDistributionDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PLEDGEDISTRIBUTION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	double m_double_amount_pledged;
//	double m_double_school1;
//	double m_double_school2;
//	double m_double_school3;
	CSpinButtonCtrl m_ctr_spin_per1;
	CSpinButtonCtrl m_ctr_spin_per2;
	CSpinButtonCtrl m_ctr_spin_per3;
	double m_double_amount_rec1;
	double m_double_amount_rec_2;
	double m_double_amount_rec3;
	CString m_str_school1;
	CEdit m_ctr_school1;
	CEdit m_ctr_school2;
	CEdit m_ctr_school3;
	CEdit m_ctr_remaining;
	afx_msg void OnDeltaposSpinper1(NMHDR *pNMHDR, LRESULT *pResult);
	int fisrt_selection;
	int second_selection;
	int third_selection;
	afx_msg void OnDeltaposSpinper2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinper3(NMHDR *pNMHDR, LRESULT *pResult);
	CProgressCtrl m_ctr_Progressbar1;
	CProgressCtrl m_ctr_Progressbar2;
	CProgressCtrl m_ctr_Progressbar3;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
