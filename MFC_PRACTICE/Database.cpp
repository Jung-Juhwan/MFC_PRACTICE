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
		// ���� ó��
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
