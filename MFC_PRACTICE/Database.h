#pragma once
#import "C:\Program Files\Common Files\System\ado\msado15.dll" rename("EOF", "adoEOF") no_namespace
//typedef ADODB::_RecordsetPtr RecPtr;
//typedef ADODB::_ConnectionPtr CnnPtr;


class Database
{
public:
	void* SQLExcute(char *szSQL);
	BOOL SQLDelete(char *szTableName, char *szWhere);
	BOOL SQLUpdate(LPCTSTR szTableName, LPCTSTR date, LPCTSTR OH_KEY);
	BOOL SQLREADYNUpdate(LPCTSTR szTableName, LPCTSTR PK, int choice);
	_RecordsetPtr SQLSelect(char* szTableName);
	CString SQLGetKey(LPCTSTR szTableName, LPCTSTR value, LPCTSTR szAccessNo);
	CString SQLGetKey2(LPCTSTR szTableName, LPCTSTR OH_OKEY);
	BOOL SQLInsert(char* szTableName, char* szValues);
	BOOL SQLPatientInsert(LPCTSTR szTableName, LPCTSTR szID, LPCTSTR szName, LPCTSTR szSex, LPCTSTR szBirth);
	BOOL SQLOrderInsert(LPCTSTR szTableName, LPCTSTR szAccessNo);
	BOOL SQLDepartmentInsert(LPCTSTR szTableName, LPCTSTR szDepartCode, LPCTSTR szName);
	BOOL SQLExamCodeInsert(LPCTSTR szTableName, LPCTSTR szExamCode, LPCTSTR szDescription);
	BOOL SQLOrderHistoryInsert(LPCTSTR szTableName, LPCTSTR timeDate, LPCTSTR okey, LPCTSTR deptcode, LPCTSTR examcode, LPCTSTR patid, LPCTSTR publish, LPCTSTR registration);
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



