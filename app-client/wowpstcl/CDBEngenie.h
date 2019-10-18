#pragma once
class CDBEngenie
{
public:
	static CDBEngenie &getInstance()
	{
		static CDBEngenie engne;
		return engne;
	}

	const char *GetDatabaseVersion();
	int InitializeDatabase();
	
	
private:
	HMODULE hLib;
	~CDBEngenie();
	CDBEngenie();
	

	CDBEngenie(CDBEngenie const&) = delete;
	CDBEngenie& operator= (CDBEngenie const&) = delete;
};

