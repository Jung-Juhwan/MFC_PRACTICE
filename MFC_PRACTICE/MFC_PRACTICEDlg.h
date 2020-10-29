
// MFC_PRACTICEDlg.h: 헤더 파일
//

#pragma once


// CMFCPRACTICEDlg 대화 상자
class CMFCPRACTICEDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCPRACTICEDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_PRACTICE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

	Database DB;
	Database CISDB;
	_RecordsetPtr eqip;
	_RecordsetPtr pat;
	_RecordsetPtr work;
	_RecordsetPtr orderT;
	void GetData(CString& a, CString& b);
	CString m_id;
	CString m_pwd;
	CString provider;

	CStringArray patient;
	CStringArray department;
	CStringArray examcode;
	CStringArray order;

	CStringArray patName;
	CStringArray patBirth;
	CStringArray patID, workPatID;
	CStringArray patSex;

	CStringArray eqipCD;
	CStringArray examCD, workExamCD;
	CStringArray examName;
	CStringArray examTYP, workExamTYP;
	CStringArray examTYPName;

	CStringArray ordDate;
	CStringArray ordSeqNo;
	CStringArray acptTime;

	CString getDate;
	CString putDate;
	CString strYear;
	CString strMonth;
	CString strDay;
	int index;

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeId();
	afx_msg void OnEnChangePwd();
	afx_msg void OnBnClickedConnection();
	afx_msg void OnBnClickedOk();
	afx_msg void OnLbnSelchangeLog();
	CListBox logList;

	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
