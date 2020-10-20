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


	m_hresult = m_pConn.CreateInstance((__uuidof(Connection)));
	if (FAILED(m_hresult))
	{
		printf("Error instantiating Connection object\n");
		CoUninitialize();
		return FALSE;
	}

	m_hresult = m_pConn->Open(_bstr_t(lpszConnText),"","", 0);
	if (FAILED(m_hresult))
	{
		printf("Error Opening Database object using ADO _ConnectionPtr \n");
		CoUninitialize();
		return FALSE;
	}

	m_bIsConnected = TRUE;
	return TRUE;
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
//Insert �ϴ¹��
//Insert into szTableName Values(szValues) �� ���·� ���
//��) Insert into dbo.Test values(1, 'hell world!') �� ����
//    SQLInsert("dbo.Test", "1, 'hell world!'"); ó�� ����ϸ� �˴ϴ�.
//
//�����Ͱ� �ùٸ��� ����Ǹ� TRUE ����, ���� ���н� FALSE ����
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
		//sprintf(szSQL, "Insert into %s Values(%s)", szTableName, szValues);

		//Execute the insert statement
		m_pConn->Execute(szSQL, NULL, 1);
	}
	catch (...)
	{
		return FALSE;
	}
	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////////
//Select �ϴ¹��
//Select * from szTableName �� ���·� ���
//��) Select * from dbo.Test �� ����
//    rs = SQLSelect("dbo.Test"); ó�� ����ϸ� �˴ϴ�.
//
// Select�� �����ϸ� _RecordsetPtr ����, ���н� 0 ����
//
//
//��) int��, varchar���� �÷��� ������ ���̺��� ��� �����͸� �д� ��
//_bstr_t bKeyContents;
//while(!pRs->EndOfFile)
//{
//	szNum[count]=pRs->GetCollect("nNum").intVal;  //������ �϶� 
//	bKeyContents=pRs->Fields->GetItem("szString")->Value;  //������ �϶� 
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
		//sprintf(szSQL, "select * from %s", szTableName);

		m_pRset = m_pConn->Execute(szSQL, NULL, 1);
	}
	catch (...)
	{
		return 0;
	}
	return m_pRset;
}

////////////////////////////////////////////////////////////////////////////////////
//Update �ϴ¹��
//UPDATE szTableName set szSet where szWhere �� ���·� ���
//��) UPDATE dbo.Test set szString='stupid' where nNum=2 �� ����
//    SQLUpdate("dbo.Test", "szString='stupid'", "nNum=2"); ó�� ����ϸ� �˴ϴ�.
//
//�����Ͱ� �ùٸ��� ����Ǹ� TRUE ����, ���н� FALSE ����
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
		//sprintf(szSQL, "UPDATE %s set %s where %s", szTableName, szSet, szWhere);

		//		m_pConn->BeginTrans();
		m_pConn->Execute(szSQL, NULL, 1);
		//		m_pConn->CommitTrans();
	}
	catch (...)
	{
		return FALSE;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////
//Delete �ϴ¹��
//Delete from szTableName where szWhere �� ���·� ���
//��) Delete from dbo.Test where nNum=2 �� ����
//    SQLDelete("dbo.Test", "nNum=2"); ó�� ����ϸ� �˴ϴ�.
//
//�����Ͱ� �ùٸ��� �����Ǹ� TRUE ����, ���н� FALSE ����
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
		m_pConn->Execute(szSQL, NULL, 1);
		//		m_pConn->CommitTrans();
	}
	catch (...)
	{
		return FALSE;
	}
	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////////
//Excute �ϴ¹�� (�������� ���� �ۼ��Ͽ� ����)
// Excute�� �����ϸ� NULL ����, �����Ұ�� NULL �̿��� ��(Select �� ��� (_Recordset*) ����)
void* Database::SQLExcute(char* szSQL)
{
	if (!m_bIsConnected)
	{
		printf("DB is disconnected!\n");
		return 0;
	}

	try
	{
		m_pRset = m_pConn->Execute(szSQL, NULL, 1);
	}
	catch (...)
	{
		return 0;
	}
	return m_pRset;
}

