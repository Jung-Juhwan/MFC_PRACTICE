#include "pch.h"
#include "Database.h"


Database::Database()
{
	m_Con = NULL;
}



//bool Database::Open(char* UserName, char* Pwd, char* CnnPtr, char* ErrStr)
//{
//	try
//	{
//		
//		//if (m_Con == NULL)
//		//	return 0;	
//		hr = m_Con.CreateInstance(__uuidof(ADODB::Connection));
//		m_Con->Open(CnnPtr, UserName, Pwd, NULL);
//	}
//	catch (_com_error& e)
//	{
//		// ���� ó��
//		return 0;
//	}
//	return 1;
//}

BOOL Database::Open(LPCTSTR lpszUserName, LPCTSTR lpszPassword, LPCTSTR lpszServiceName,CString& strError)

{
	try
	{
		CString lpszConnText = ("Provider = OraOLEDB.Oracle.1; PLSQLRSet = 1; Data Source = % s; User ID = % s; Password = % s", lpszServiceName, lpszUserName, lpszPassword);
		m_Con.CreateInstance(__uuidof(ADODB::Connection));
		m_Con->Open(_bstr_t(lpszConnText), _T(""), _T(""), ADODB::adConnectUnspecified);
	}
	catch (_com_error& e)
	{		
		return FALSE;
	}

	return TRUE;
}

RecPtr Database::Execute(char* CmdStr)
{
	try
	{
		if (m_Con == NULL)
			return NULL;
		return m_Con->Execute(CmdStr, NULL, 1);
	}
	catch (_com_error& e)
	{
		// ���� ó��
		return NULL;

	}
}

bool Database::Close()
{
	// ������ �ִ°�?
	// ���ٸ� return 0
	if (m_Con == NULL)
		return 0;
	// ������ �ִٸ� ���´�.
	try
	{
		m_Con->Close();
		m_Con = NULL;
	}
	catch (_com_error& e)
	{
		// ���� ó��
		return 0;
	}
	return hr == S_OK;
}

Database::~Database()
{
	try
	{
		// ���� ������ ������ �ʾҴٸ� ������ ���´�.
		if (m_Con)
		{
			m_Con->Close();
			m_Con = NULL;
		}
	}
	catch (_com_error& e)
	{
		// ���� ó��
	}
}