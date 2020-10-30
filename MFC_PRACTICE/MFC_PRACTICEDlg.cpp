
// MFC_PRACTICEDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFC_PRACTICE.h"
#include "MFC_PRACTICEDlg.h"
#include "afxdialogex.h"
#include <time.h>

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
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCPRACTICEDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCPRACTICEDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCPRACTICEDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCPRACTICEDlg::OnBnClickedButton4)
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



	if (!DB.Connect(m_id,m_pwd,_T("cistest"),strError)) 
	{
		MessageBox(_T("해당 ID와 PWD가 정확하지 않습니다"), _T("DB CONNECTION 오류"), MB_OK | MB_ICONSTOP);
		SetDlgItemText(IDC_ID, _T(""));
		SetDlgItemText(IDC_PWD, _T(""));
	}		
	else {
		index=logList.InsertString(-1, m_id + "/" + m_pwd);


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


void CMFCPRACTICEDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	eqip = DB.SQLSelect("TBLLINK_EQIPINFO");


	CString word;
	int a;

	a = 0;
	while (!eqip->adoEOF) {
		word = _T("");
		
		eqipCD.Add(eqip->Fields->GetItem("EQIPCD")->Value);
		examCD.Add(eqip->Fields->GetItem("EXAMCD")->Value);
		examName.Add(eqip->Fields->GetItem("EXAMNAME")->Value);
		examTYP.Add(eqip->Fields->GetItem("EXAMTYP")->Value);
		examTYPName.Add(eqip->Fields->GetItem("EXAMTYPNAME")->Value);

		CISDB.SQLDepartmentInsert(_T("T_DEPARTMENT"), examTYP.GetAt(a), examTYPName.GetAt(a));
		CISDB.SQLExamCodeInsert(_T("T_EXAMCODE"), examCD.GetAt(a), examName.GetAt(a));

		word += eqipCD.GetAt(a) + "/" + examCD.GetAt(a) + "/" + examTYP.GetAt(a);
		DB.SQLREADYNUpdate(_T("TBLLINK_EQIPINFO"), word, 1);

		eqip->MoveNext();
		a++;
	}
	index = logList.InsertString(-1, _T("1번 완료"));

	logList.SetCurSel(index);
}

void CMFCPRACTICEDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pat = DB.SQLSelect("TBLLINK_PATIENT");

	CString word;
	
	int b;

	b = 0;
	while (!pat->adoEOF)
	{
		patID.Add(pat->Fields->GetItem("PATID")->Value);
		patName.Add(pat->Fields->GetItem("PATNAME")->Value);
		patBirth.Add(pat->Fields->GetItem("BIRTH")->Value);
		patSex.Add(pat->Fields->GetItem("PSEX")->Value);

		CISDB.SQLPatientInsert(_T("T_PATIENT"), patID.GetAt(b), patName.GetAt(b), patSex.GetAt(b), patBirth.GetAt(b));

		DB.SQLREADYNUpdate(_T("TBLLINK_PATIENT"), patID.GetAt(b), 2);

		pat->MoveNext();
		b++;
	}
	index = logList.InsertString(-1, _T("2번 완료"));

	logList.SetCurSel(index);
}

void CMFCPRACTICEDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	work = DB.SQLSelect("TBLLINK_WORKLIST");

	CString word;
	int c;

	c = 0;
	while (!work->adoEOF) {

		getDate = work->Fields->GetItem("ORDDATE")->Value;

		strYear = getDate.Left(4);
		strMonth = getDate.Mid(4, 2);
		strDay = getDate.Right(2);

		putDate += strYear + "-" + strMonth + "-" + strDay;
		ordDate.Add(putDate);
		workExamCD.Add(work->Fields->GetItem("EXAMCD")->Value);
		workExamTYP.Add(work->Fields->GetItem("EXAMTYP")->Value);
		ordSeqNo.Add(work->Fields->GetItem("ORDSEQNO")->Value);
		acptTime.Add(work->Fields->GetItem("ACPTTIME")->Value);
		workPatID.Add(work->Fields->GetItem("PATID")->Value);

		CISDB.SQLOrderInsert(_T("T_ORDER"), ordSeqNo.GetAt(c));
		DB.SQLREADYNUpdate(_T("TBLLINK_WORKLIST"), ordSeqNo.GetAt(c), 3);

		work->MoveNext();
		c++;
	}

	index = logList.InsertString(-1, _T("3번 완료"));

	logList.SetCurSel(index);
}


void CMFCPRACTICEDlg::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	time_t curTime = time(NULL);
	struct tm* pLocal = NULL;

#if defined(_WIN32) || defined(_WIN64) 
	pLocal = localtime(&curTime);
#else 
	localtime_r(&curTime, pLocal);
#endif 
	if (pLocal == NULL)
	{
		// Failed to convert the current time 
		return;
	}
	CString timeDate;
	CString year;
	year.Format(_T("%d"), pLocal->tm_year + 1900);
	CString mon;
	mon.Format(_T("%d"), pLocal->tm_mon + 1);
	CString day;
	day.Format(_T("%d"), pLocal->tm_mday);

	timeDate += year + "-" + mon + "-" + day;

	CString a;
		
	int sqlCount=DB.SQLCount("TBLLINK_WORKLIST");
	for (int i = 0; i < sqlCount; i++) {
		a = CISDB.SQLGetKey(_T("T_ORDER"), _T("O_KEY"), ordSeqNo.GetAt(i));
		CISDB.SQLOrderHistoryInsert(_T("T_ORDERHISTORY"),timeDate, a, (LPCTSTR)workExamTYP.GetAt(i), (LPCTSTR)workExamCD.GetAt(i), (LPCTSTR)workPatID.GetAt(i), (LPCTSTR)ordDate.GetAt(i), (LPCTSTR)acptTime.GetAt(i));
	}
		
}
