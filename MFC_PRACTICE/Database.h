#pragma once
#import "C:\Program Files\Common Files\System\ado\msado15.dll" rename("EOF", "adoEOF") no_namespace
//typedef ADODB::_RecordsetPtr RecPtr;
//typedef ADODB::_ConnectionPtr CnnPtr;


class Database
{
public:
	void* SQLExcute(char *szSQL);
	BOOL SQLDelete(char *szTableName, char *szWhere);
	BOOL SQLUpdate(char* szTableName, char* szSet, char* szWhere);
	BOOL SQLREADYNUpdate(LPCTSTR szTableName, LPCTSTR PK, int choice);
	_RecordsetPtr SQLSelect(char* szTableName);
	BOOL SQLInsert(char* szTableName, char* szValues);
	BOOL SQLPatientInsert(LPCTSTR szTableName, LPCTSTR szID, LPCTSTR szName, LPCTSTR szSex, LPCTSTR szBirth);
	BOOL SQLOrderInsert(LPCTSTR szTableName, LPCTSTR szAccessNo);
	BOOL SQLDepartmentInsert(LPCTSTR szTableName, LPCTSTR szDepartCode, LPCTSTR szName);
	BOOL SQLExamCodeInsert(LPCTSTR szTableName, LPCTSTR szExamCode, LPCTSTR szDescription);
	BOOL SQLOrderHistoryInsert(LPCTSTR szTableName, LPCTSTR szID, LPCTSTR szName);
	BOOL DisConnect();
	BOOL Connect(LPCTSTR lpszUserName, LPCTSTR lpszPassword, LPCTSTR lpszServiceName, CString& strError);
	int SQLCount(char* szTableName);
	Database();
	virtual~Database();

private:
	BOOL m_bIsConnected;
    HRESULT m_hresult;
	_ConnectionPtr m_pConn;
	_RecordsetPtr m_pRset;
	
};



