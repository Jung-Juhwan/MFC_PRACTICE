#pragma once


// TEST 대화 상자

class TEST : public CDialogEx
{
	DECLARE_DYNAMIC(TEST)

public:
	TEST(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~TEST();

	void GetData(CString& a);
	CString m_data;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
