#pragma once
#import "C:\Program Files\Common Files\System\ado\msado15.dll" rename("EOF", "EndOfFile")
typedef ADODB::_RecordsetPtr RecPtr;
typedef ADODB::_ConnectionPtr CnnPtr;


class Database
{
public:

	CnnPtr m_Con;
	Database();
	~Database();
	bool Open(char* UserName, char* Pwd, char* CnnPtr, char* ErrStr);
	RecPtr Execute(char* CmdStr);
	bool Close();

	
};



