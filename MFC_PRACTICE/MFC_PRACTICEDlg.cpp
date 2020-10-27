
// MFC_PRACTICEDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFC_PRACTICE.h"
#include "MFC_PRACTICEDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CMFCPRACTICEDlg 대화 상자



CMFCPRACTICEDlg::CMFCPRACTICEDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_PRACTICE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCPRACTICEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOG, logList);
}

void CMFCPRACTICEDlg::GetData(CString& a,CString& b)
{
	a = m_id;
	b = m_pwd;
}


BEGIN_MESSAGE_MAP(CMFCPRACTICEDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_ID, &CMFCPRACTICEDlg::OnEnChangeId)
	ON_EN_CHANGE(IDC_PWD, &CMFCPRACTICEDlg::OnEnChangePwd)
	ON_BN_CLICKED(IDC_CONNECTION, &CMFCPRACTICEDlg::OnBnClickedConnection)
	ON_BN_CLICKED(IDOK, &CMFCPRACTICEDlg::OnBnClickedOk)
	ON_LBN_SELCHANGE(IDC_LOG, &CMFCPRACTICEDlg::OnLbnSelchangeLog)
END_MESSAGE_MAP()


// CMFCPRACTICEDlg 메시지 처리기

BOOL CMFCPRACTICEDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	CString id = _T("cis");
	CString password = _T("infinitt");
	CString error;

	if (!CISDB.Connect(id, password, _T("orcl"), error))
	{
		MessageBox(_T("해당 ID와 PWD가 정확하지 않습니다"), _T("DB CONNECTION 오류"), MB_OK | MB_ICONSTOP);
		SetDlgItemText(IDC_ID, _T(""));
		SetDlgItemText(IDC_PWD, _T(""));
	}
	else {
		logList.InsertString(-1,id + "/" + password);
		//CISDB.SQLInsert((LPSTR)(LPCTSTR)("T_ORDER"), (LPSTR)(LPCTSTR)("1,'aaa'"));
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCPRACTICEDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCPRACTICEDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCPRACTICEDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCPRACTICEDlg::OnEnChangeId()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCPRACTICEDlg::OnEnChangePwd()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCPRACTICEDlg::OnBnClickedConnection()
{
	CString selectQuery = _T("");
	int sqlCount = 0;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItemText(IDC_ID, m_id);
	GetDlgItemText(IDC_PWD, m_pwd);

	m_id = "test1";
	m_pwd = "infinitt";
	//provider = "Provider=OraOLEDB.Oracle.1;PLSQLRSet=1; Data Source=localhost\\SQLEXPRESS; Trusted_Connection=yes; Database=orcl;";
	
	CString strError;
	CStringArray patient;
	CStringArray department;
	CStringArray examcode;
	CStringArray order;

	CStringArray patName;
	CStringArray patBirth;
	CStringArray patID;
	CStringArray patSex;
	CStringArray patREADYN;

	CStringArray examCD;
	CStringArray examName;
	CStringArray examTYP;
	CStringArray examTYPName;
	CStringArray eqipREADYN;
	
	CStringArray ordDate;
	CStringArray ordSeqNo;
	CStringArray acptTime;
	CStringArray workREADYN;

	int index;
	int c=0,a=0,b=0;
	if (!DB.Connect(m_id,m_pwd,_T("cistest"),strError)) 
	{
		MessageBox(_T("해당 ID와 PWD가 정확하지 않습니다"), _T("DB CONNECTION 오류"), MB_OK | MB_ICONSTOP);
		SetDlgItemText(IDC_ID, _T(""));
		SetDlgItemText(IDC_PWD, _T(""));
	}		
	else {
		index=logList.InsertString(-1, m_id + "/" + m_pwd);

		pat = DB.SQLSelect("TBLLINK_PATIENT");
		eqip = DB.SQLSelect("TBLLINK_EQIPINFO");
		work = DB.SQLSelect("TBLLINK_WORKLIST");
		while (!pat->adoEOF)
		{
			patREADYN.Add(pat->Fields->GetItem("READYN")->Value);

			if (patREADYN.GetAt(c)==(_T("N"))) {
				patID.Add(pat->Fields->GetItem("PATID")->Value);
				patName.Add(pat->Fields->GetItem("PATNAME")->Value);
				patBirth.Add(pat->Fields->GetItem("BIRTH")->Value);
				patSex.Add(pat->Fields->GetItem("PSEX")->Value);
				patient.Add(patID.GetAt(c) + "\\" + patName.GetAt(c) + "\\" + patBirth.GetAt(c) + "\\" + patSex.GetAt(c));

				DB.SQLREADYNUpdate(_T("TBLLINK_PATIENT"), patID.GetAt(c), 2);
			}

			pat->MoveNext();
			c++;
		}
		while (!eqip->adoEOF) {

			eqipREADYN.Add(eqip->Fields->GetItem("READYN")->Value);

			if (eqipREADYN.GetAt(a)==(_T("N"))) {
				examCD.Add(eqip->Fields->GetItem("EXAMCD")->Value);
				examName.Add(eqip->Fields->GetItem("EXAMNAME")->Value);
				examTYP.Add(eqip->Fields->GetItem("EXAMTYP")->Value);
				examTYPName.Add(eqip->Fields->GetItem("EXAMTYPNAME")->Value);
				examcode.Add(examCD.GetAt(a) + "\\" + examName.GetAt(a));
				department.Add(examTYP.GetAt(a) + "\\" + examTYPName.GetAt(a));

				DB.SQLREADYNUpdate(_T("TBLLINK_EQIPINFO"), examCD.GetAt(a), 1);
			}

			eqip->MoveNext();
			a++;
		}
		while (!work->adoEOF) {

			workREADYN.Add(work->Fields->GetItem("READYN")->Value);

			if (workREADYN.GetAt(b)==(_T("N"))) {
				ordDate.Add(work->Fields->GetItem("ORDDATE")->Value);
				ordSeqNo.Add(work->Fields->GetItem("ORDSEQNO")->Value);
				acptTime.Add(work->Fields->GetItem("ACPTTIME")->Value);
				order.Add(ordSeqNo.GetAt(b));
				
				DB.SQLREADYNUpdate(_T("TBLLINK_WORKLIST"), ordSeqNo.GetAt(b),3);
			}

			work->MoveNext();
			b++;
		}
		for (int i = 0; i < patient.GetCount(); i++) {
			index=logList.InsertString(-1, patient.GetAt(i));
			CISDB.SQLPatientInsert(_T("T_PATIENT"), patID.GetAt(i),patName.GetAt(i),patSex.GetAt(i),patBirth.GetAt(i));
		}

		for (int i = 0; i < order.GetCount(); i++) {
			index = logList.InsertString(-1, order.GetAt(i));
			CISDB.SQLOrderInsert(_T("T_ORDER"), ordSeqNo.GetAt(i));
		}
		for (int i = 0; i < department.GetCount(); i++) {
			index = logList.InsertString(-1, department.GetAt(i));
			CISDB.SQLDepartmentInsert(_T("T_DEPARTMENT"), examTYP.GetAt(i), examTYPName.GetAt(i));
		}
		for (int i = 0; i < examcode.GetCount(); i++) {
			index = logList.InsertString(-1, examcode.GetAt(i));
			CISDB.SQLExamCodeInsert(_T("T_EXAMCODE"), examCD.GetAt(i), examName.GetAt(i));
		}
		logList.SetCurSel(index);

		/*
		sqlCount=DB.SQLCount("TBLLINK_EQIPINFO");
		str.Format(_T("%d"), sqlCount);
		SetDlgItemText(IDC_LOG, str);
		*/

		//CISDB.SQLInsert((LPSTR)(LPCTSTR)("T_ORDER"), (LPSTR)(LPCTSTR)("1,'aaa'"));
	

	}

		
}


void CMFCPRACTICEDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void CMFCPRACTICEDlg::OnLbnSelchangeLog()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
