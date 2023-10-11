
// PledgeDistributionDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "PledgeDistribution.h"
#include "PledgeDistributionDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define MY_TIMER 3000
static UINT BASED_CODE indicators[] = {
	ID_INDICATOR_TIME,
ID_INDICATOR_POINT
};


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPledgeDistributionDlg dialog



CPledgeDistributionDlg::CPledgeDistributionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PLEDGEDISTRIBUTION_DIALOG, pParent)
	, m_double_amount_pledged(0)
	, m_double_amount_rec1(0)
	, m_double_amount_rec_2(0)
	, m_double_amount_rec3(0)
	, m_str_school1(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPledgeDistributionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_double_amount_pledged);
	//  DDX_Text(pDX, IDC_EDIT_school1, m_double_school1);
	//  DDX_Text(pDX, IDC_EDIT_school2, m_double_school2);
	//  DDX_Text(pDX, IDC_EDIT_school3, m_double_school3);
	DDX_Control(pDX, IDC_SPIN_per1, m_ctr_spin_per1);
	DDX_Control(pDX, IDC_SPIN_per2, m_ctr_spin_per2);
	DDX_Control(pDX, IDC_SPIN_per3, m_ctr_spin_per3);
	DDX_Text(pDX, IDC_EDIT_amount_rec1, m_double_amount_rec1);
	DDX_Text(pDX, IDC_EDIT_amount_rec2, m_double_amount_rec_2);
	DDX_Text(pDX, IDC_EDIT_amount_rec3, m_double_amount_rec3);
	DDX_Text(pDX, IDC_EDIT_school1, m_str_school1);
	DDX_Control(pDX, IDC_EDIT_school1, m_ctr_school1);
	DDX_Control(pDX, IDC_EDIT_school2, m_ctr_school2);
	DDX_Control(pDX, IDC_EDIT_school3, m_ctr_school3);
	DDX_Control(pDX, IDC_EDIT_remaining, m_ctr_remaining);
	DDX_Control(pDX, IDC_PROGRESS1, m_ctr_Progressbar1);
	DDX_Control(pDX, IDC_PROGRESS2, m_ctr_Progressbar2);
	DDX_Control(pDX, IDC_PROGRESS3, m_ctr_Progressbar3);
}

BEGIN_MESSAGE_MAP(CPledgeDistributionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_per1, &CPledgeDistributionDlg::OnDeltaposSpinper1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_per2, &CPledgeDistributionDlg::OnDeltaposSpinper2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_per3, &CPledgeDistributionDlg::OnDeltaposSpinper3)
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CPledgeDistributionDlg message handlers

BOOL CPledgeDistributionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_bar.Create(this);
	m_bar.SetIndicators(indicators, 2);

	CRect rect;
	GetClientRect(&rect);
	m_bar.SetPaneInfo(0, ID_INDICATOR_POINT, SBPS_NORMAL, rect.Width() - 150);
	m_bar.SetPaneInfo(1, ID_INDICATOR_TIME, SBPS_NORMAL, rect.Width() - 0);
	m_bar.GetStatusBarCtrl().SetBkColor(RGB(192, 192, 192));
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, ID_INDICATOR_TIME);

	SetTimer(MY_TIMER, 1000, NULL);
	


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPledgeDistributionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPledgeDistributionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPledgeDistributionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPledgeDistributionDlg::OnDeltaposSpinper1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	UpdateData(TRUE);
	
	
	int rest;
	rest = 0;
	if ( rest>0)
	{
		AfxMessageBox(_T(" still to be used"),rest);
	}
	else 


	m_ctr_spin_per1.SetRange(0, 100);
	m_ctr_Progressbar1.SetPos(fisrt_selection);
	fisrt_selection = m_ctr_spin_per1.GetPos();
	double Rec;
	Rec = m_double_amount_pledged * fisrt_selection / 100;
	m_double_amount_rec1 = Rec;
	/*if (fisrt_selection == 100)
	{
		rec = (m_double_amount_pledged*(fisrt_selection) / 100));
	}*/
	
	//AfxMessageBox(_T("If the whole amount has been distributed, don't display a message"));
	//AfxMessageBox(_T(""));


	UpdateData(FALSE);
	*pResult = 0;
		//m_ctr_Progressbar1.SetBkColor(RGB(255,255,255));

}



void CPledgeDistributionDlg::OnDeltaposSpinper2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	UpdateData(TRUE);
	m_ctr_spin_per2.SetRange(0, (100 - fisrt_selection));
	
	m_ctr_Progressbar2.SetPos(second_selection);
	second_selection = m_ctr_spin_per2.GetPos();
	double amount_Rec; 
	 amount_Rec  = (m_double_amount_pledged * (second_selection)) / 100;
	 m_double_amount_rec_2 = amount_Rec;

	m_ctr_Progressbar1.SetBkColor(RGB(255, 255, 255));
	UpdateData(FALSE);
	*pResult = 0;

	

}


void CPledgeDistributionDlg::OnDeltaposSpinper3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	m_ctr_spin_per3.SetRange(0, (100 - (fisrt_selection+second_selection)));
	
	m_ctr_Progressbar3.SetPos(third_selection);
	third_selection = m_ctr_spin_per3.GetPos();
	m_ctr_Progressbar1.SetBkColor(RGB(255, 255, 255));
	double amount_Rec1;
	amount_Rec1 = (m_double_amount_pledged * (third_selection)) / 100;
	m_double_amount_rec3 = amount_Rec1;
	UpdateData(FALSE);
	*pResult = 0;
	

}


void CPledgeDistributionDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CTime t1;

	t1 = CTime::GetCurrentTime();
	m_bar.SetPaneText(1, t1.Format("%H:%M:%S, %D"));


	CDialogEx::OnTimer(nIDEvent);
}


void CPledgeDistributionDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CString str;
	str.Format(_T("x = %d y = %d"), point.x, point.y);
	m_bar.SetPaneText(0, str);


	CDialogEx::OnMouseMove(nFlags, point);
}
