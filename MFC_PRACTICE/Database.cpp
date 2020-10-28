#include "pch.h"
#include "Database.h"

Database::Database()
{
	m_pConn = NULL;
	m_bIsConnected = NULL;
	m_pRset = NULL;
	m_hresult = S_OK;
}

Database::~Database()
{
	if (m_bIsConnected)
	{
		m_pConn->Close();
		CoInitialize(NULL);
	}
}

BOOL Database::Connect(LPCTSTR lpszUserName, LPCTSTR lpszPassword, LPCTSTR lpszServiceName, CString& strError)
{
	if (m_bIsConnected)
	{
		printf("DB is already connected!\n");
		return TRUE;
	}
	CString lpszConnText = _T("Provider = OraOLEDB.Oracle.1; PLSQLRSet = 1; Data Source = ");
	lpszConnText.Append(lpszServiceName);
	lpszConnText.Append(_T(";"));
	CString UserID = _T(" User ID = ");
	UserID.Append(lpszUserName);
	UserID.Append(_T(";"));
	CString PWD = _T(" Password = ");
	PWD.Append(lpszPassword);
	PWD.Append(_T(";"));
	lpszConnText.Append(UserID);
	lpszConnText.Append(PWD);

	/*char szCon[256];

	memset(szCon, 0x00, sizeof(szCon));

	sprintf(szCon, "Provider=SQLOLEDB;Data Source=%s; Initial catalog=%s;User ID=%s;Password=%s;", szDBServerIP, szDBName, szUserID, szUserPW);*/

	//Initialize the COM Library
	CoInitialize(NULL);

	try {
		m_hresult = m_pConn.CreateInstance(__uuidof(Connection));
		if (FAILED(m_hresult))
		{
			printf("Error instantiating Connection object\n");
			CoUninitialize();
			return FALSE;
		}

		//m_pConn->Provider = "OraOLEDB.Oracle.1";
		//m_pConn->ConnectionString = lpszConnText.GetBuffer(0); //접속스트링설정

		m_hresult = m_pConn->Open(_bstr_t(lpszConnText), "", "", adConnectUnspecified);
		if (FAILED(m_hresult))
		{
			printf("Error Opening Database object using ADO _ConnectionPtr \n");
			CoUninitialize();
			return FALSE;
		}
		m_bIsConnected = TRUE;
		return TRUE;
	}
	catch (_com_error& err) {
		TRACE(_T("com error:%s"), err.Description());

	}



}

int Database::SQLCount(char* szTableName)
{
	int count = 0;

	if (!m_bIsConnected)
	{
		printf("DB is disconnected!\n");
		return 0;
	}

	try
	{
		char szSQL[256];
		memset(szSQL, 0x00, sizeof(szSQL));
		sprintf(szSQL, "Select * from %s", szTableName);
		
		//Execute the insert statement
		m_pRset = m_pConn->Execute(szSQL, NULL, adCmdText);

		if (m_pRset->adoEOF) {
			return 0;
		}

		while (!m_pRset->adoEOF)
		{
			m_pRset->MoveNext();
			count++;
		}
	}
	catch (...)
	{
		return 0;
	}
	return count;
}

BOOL Database::DisConnect()
{
	if (!m_bIsConnected)
	{
		printf("DB is already disconnected!\n");
		return TRUE;
	}
	m_pConn->Close();
	CoUninitialize();
	m_bIsConnected = FALSE;
	return TRUE;
}



////////////////////////////////////////////////////////////////////////////////////
//Insert 하는방법
//Insert into szTableName Values(szValues) 의 형태로 사용
//예) Insert into dbo.Test values(1, 'hell world!') 의 경우는
//    SQLInsert("dbo.Test", "1, 'hell world!'"); 처럼 사용하면 됩니다.
//
//데이터가 올바르게 저장되면 TRUE 리턴, 저장 실패시 FALSE 리턴
BOOL Database::SQLInsert(char* szTableName, char* szValues)
{
	if (!m_bIsConnected)
	{
		printf("DB is disconnected!\n");
		return FALSE;
	}

	try
	{
		char szSQL[256];
		memset(szSQL, 0x00, sizeof(szSQL));
		sprintf(szSQL, "Insert into %s Values(%s)", szTableName, szValues);

		//Execute the insert statement
		m_pConn->Execute(szSQL, NULL, 1);
	}
	catch (...)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL Database::SQLPatientInsert(LPCTSTR szTableName, LPCTSTR szID, LPCTSTR szName, LPCTSTR szSex, LPCTSTR szBirth)
{

	if (!m_bIsConnected)
	{
		printf("DB is disconnected!\n");
		return FALSE;
	}

	try
	{
		CString query = _T("Insert into ");
		query.Append(szTableName);
		query += " Values('";
		query.Append(szID);
		query += "','";
		query.Append(szName);
		query += "','";
		query.Append(szSex);
		query += "','";
		query.Append(szBirth);
		query += "')";

		//Execute the insert statement
		m_pConn->Execute(_bstr_t(query), NULL, adCmdText);
	}
	catch (...)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL Database::SQLOrderInsert(LPCTSTR szTableName, LPCTSTR szAccessNo)
{
	int i = 0;
	if (!m_bIsConnected)
	{
		printf("DB is disconnected!\n");
		return FALSE;
	}

	try
	{
		CString query = _T("Insert into ");
		query.Append(szTableName);
		query += " Values(";
		query.Append(_T("tmp_seq.NEXTVAL"));
		query += ",'";
		query.Append(szAccessNo);
		query += "')";

		//Execute the insert statement
		m_pConn->Execute(_bstr_t(query), NULL, adCmdText);
	}
	catch (...)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL Database::SQLDepartmentInsert(LPCTSTR szTableName, LPCTSTR szDepartCode, LPCTSTR szName)
{
	if (!m_bIsConnected)
	{
		printf("DB is disconnected!\n");
		return FALSE;
	}

	try
	{
		CString query = _T("Insert into ");
		query.Append(szTableName);
		query += " Values('";
		query.Append(szDepartCode);
		query += "','";
		query.Append(szName);
		query += "')";

		//Execute the insert statement
		m_pConn->Execute(_bstr_t(query), NULL, adCmdText);
	}
	catch (...)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL Database::SQLExamCodeInsert(LPCTSTR szTableName, LPCTSTR szExamCode, LPCTSTR szDescription)
{
	if (!m_bIsConnected)
	{
		printf("DB is disconnected!\n");
		return FALSE;
	}

	try
	{
		CString query = _T("Insert into ");
		query.Append(szTableName);
		query += " Values('";
		query.Append(szExamCode);
		query += "','";
		query.Append(szDescription);
		query += "')";

		//Execute the insert statement
		m_pConn->Execute(_bstr_t(query), NULL, adCmdText);
	}
	catch (...)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL Database::SQLOrderHistoryInsert(LPCTSTR szTableName, LPCTSTR szID, LPCTSTR szName)
{
	/*
	if (!m_bIsConnected)
	{
		printf("DB is disconnected!\n");
		return FALSE;
	}

	try
	{
		CString query = _T("Insert into ");
		query.Append(szTableName);
		query += " Values('";
		query.Append(szID);
		query += "','";
		query.Append(szName);
		query += "','";
		query.Append(szSex);
		query += "','";
		query.Append(szBirth);
		query += "')";

		//Execute the insert statement
		m_pConn->Execute(_bstr_t(query), NULL, adCmdText);
	}
	catch (...)
	{
		return FALSE;
	}
	return TRUE;
	*/
	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////////
//Select 하는방법
//Select * from szTableName 의 형태로 사용
//예) Select * from dbo.Test 의 경우는
//    rs = SQLSelect("dbo.Test"); 처럼 사용하면 됩니다.
//
// Select에 성공하면 _RecordsetPtr 리턴, 실패시 0 리턴
//
//
//예) int형, varchar형의 컬럼을 가지는 테이블의 모든 데이터를 읽는 예
//_bstr_t bKeyContents;
//while(!pRs->EndOfFile)
//{
//	szNum[count]=pRs->GetCollect("nNum").intVal;  //정수형 일때 
//	bKeyContents=pRs->Fields->GetItem("szString")->Value;  //문자형 일때 
// 	szString[count].Format("%s",(LPCSTR)bKeyContents);
//	printf(szNum[count], szString[count]); .........
// 	pRs->MoveNext();
// 	count++;
// }


_RecordsetPtr Database::SQLSelect(char* szTableName)
{
	if (!m_bIsConnected)
	{
		printf("DB is disconnected!\n");
		return 0;
	}

	try
	{
		char szSQL[256];
		memset(szSQL, 0x00, sizeof(szSQL));
		sprintf(szSQL, "select * from %s", szTableName);

		m_pRset = m_pConn->Execute(szSQL, NULL, adCmdText);
	}
	catch (...)
	{
		return 0;
	}
	return m_pRset;
}

////////////////////////////////////////////////////////////////////////////////////
//Update 하는방법
//UPDATE szTableName set szSet where szWhere 의 형태로 사용
//예) UPDATE dbo.Test set szString='stupid' where nNum=2 의 경우는
//    SQLUpdate("dbo.Test", "szString='stupid'", "nNum=2"); 처럼 사용하면 됩니다.
//
//데이터가 올바르게 저장되면 TRUE 리턴, 실패시 FALSE 리턴
BOOL Database::SQLUpdate(char* szTableName, char* szSet, char* szWhere)
{
	if (!m_bIsConnected)
	{
		printf("DB is disconnected!\n");
		return FALSE;
	}

	try
	{
		char szSQL[256];
		memset(szSQL, 0x00, sizeof(szSQL));
		sprintf(szSQL, "UPDATE %s set %s where %s", szTableName, szSet, szWhere);

		//		m_pConn->BeginTrans();
		m_pConn->Execute(szSQL, NULL, adExecuteNoRecords);
		//		m_pConn->CommitTrans();
	}
	catch (...)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL Database::SQLREADYNUpdate(LPCTSTR szTableName, LPCTSTR PK, int choice)
{
	if (!m_bIsConnected)
	{
		printf("DB is disconnected!\n");
		return FALSE;
	}

	try
	{
		CString query = _T("Update ");
		query.Append(szTableName);
		query += " set READYN='Y' where ";
		switch (choice)
		{
			case 1: //EQIPINFO 테이블
				query += "EQIPCD = ";
				query.Append(PK);
				break;
			case 2: //PATIENT 테이블
				query += "PATID = ";
				query.Append(PK);
				break;
			case 3: //worklist 테이블
				query += "ORDSEQNO = ";
				query.Append(PK);
				break;

		default:
			break;
		}


		//		m_pConn->BeginTrans();
		m_pConn->Execute(_bstr_t(query), NULL, adExecuteNoRecords);
		//		m_pConn->CommitTrans();
	}
	catch (...)
	{
		return FALSE;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////
//Delete 하는방법
//Delete from szTableName where szWhere 의 형태로 사용
//예) Delete from dbo.Test where nNum=2 의 경우는
//    SQLDelete("dbo.Test", "nNum=2"); 처럼 사용하면 됩니다.
//
//데이터가 올바르게 삭제되면 TRUE 리턴, 실패시 FALSE 리턴
BOOL Database::SQLDelete(char* szTableName, char* szWhere)
{
	if (!m_bIsConnected)
	{
		printf("DB is disconnected!\n");
		return FALSE;
	}

	try
	{
		char szSQL[256];
		memset(szSQL, 0x00, sizeof(szSQL));
		//sprintf(szSQL, "DELETE from %s where %s", szTableName, szWhere);

		//		m_pConn->BeginTrans();
		m_pConn->Execute(szSQL, NULL, adExecuteNoRecords);
		//		m_pConn->CommitTrans();
	}
	catch (...)
	{
		return FALSE;
	}
	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////////
//Excute 하는방법 (쿼리문을 직접 작성하여 실행)
// Excute에 실패하면 NULL 리턴, 성공할경우 NULL 이외의 값(Select 의 경우 (_Recordset*) 리턴)
void* Database::SQLExcute(char* szSQL)
{
	if (!m_bIsConnected)
	{
		printf("DB is disconnected!\n");
		return 0;
	}

	try
	{
		m_pRset = m_pConn->Execute(szSQL, NULL, adCmdText);
	}
	catch (...)
	{
		return 0;
	}
	return m_pRset;
}

