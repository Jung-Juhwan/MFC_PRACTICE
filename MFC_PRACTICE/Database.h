#pragma once
#import "C:/Program Files/Common Files/System/ado/msado15.dll" rename("EOF", "EndOfFile") no_namespace
//typedef ADODB::_RecordsetPtr RecPtr;
//typedef ADODB::_ConnectionPtr CnnPtr;


class Database
{
public:
	void* SQLExcute(char *szSQL);
	BOOL SQLDelete(char *szTableName, char *szWhere);
	BOOL SQLUpdate(char* szTableName, char* szSet, char* szWhere);
	_RecordsetPtr SQLSelect(char* szTableName);
	BOOL SQLInsert(char* szTableName, char* szValues);
	BOOL DisConnect();
	BOOL Connect(LPCTSTR lpszUserName, LPCTSTR lpszPassword, LPCTSTR lpszServiceName, CString& strError);
	Database();
	virtual~Database();

private:
	BOOL m_bIsConnected;
    HRESULT m_hresult;
	_ConnectionPtr m_pConn;
	_RecordsetPtr m_pRset;
	
};



