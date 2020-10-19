#include "pch.h"
#include "Database.h"

HRESULT hr;

Database::Database()
{
	m_Con = NULL;
}

Database::~Database()
{
	try
	{
		// 아직 연결이 끊기지 않았다면 연결을 끊는다.
		if (m_Con)
		{
			m_Con->Close();
			m_Con = NULL;
		}
	}
	catch (_com_error& e)
	{
		// 오류 처리
	}
}

bool Database::Open(char* UserName, char* Pwd, char* CnnPtr, char* ErrStr)
{
	try
	{
		if (m_Con == NULL)
			return 0;
		hr = m_Con.CreateInstance(__uuidof(ADODB::Connection));
		m_Con->Open(CnnPtr, UserName, Pwd, NULL);
	}
	catch (_com_error& e)
	{
		// 오류 처리
		return 0;
	}
	return 1;
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
		// 오류 처리
		return NULL;

	}
}

bool Database::Close()
{
	// 연결이 있는가?
	// 없다면 return 0
	if (m_Con == NULL)
		return 0;
	// 연결이 있다면 끊는다.
	try
	{
		m_Con->Close();
		m_Con = NULL;
	}
	catch (_com_error& e)
	{
		// 오류 처리
		return 0;
	}
	return hr == S_OK;
}
