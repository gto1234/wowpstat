#include "stdafx.h"
#include "CDBEngenie.h"

typedef char * (WINAPI* call_libver)();

constexpr auto DBDLLNAME = L"sqlite3.dll";

CDBEngenie::CDBEngenie()
{
}


CDBEngenie::~CDBEngenie()
{
	if (this->hLib != NULL)
	{
		::FreeLibrary(this->hLib);
	}
}



const char* CDBEngenie::GetDatabaseVersion()
{
	char *nRetValue = NULL;
	OutputDebugString(_T("GetDatabaseVersion called"));
	if (this->hLib != NULL)
	{
		call_libver pFGetVersion = (call_libver)::GetProcAddress(this->hLib, "sqlite3_libversion");
		if (pFGetVersion != NULL)
		{
			nRetValue = pFGetVersion();
		}
		else
		{
			OutputDebugString(_T("sqlite3_libversion not find"));
		}
	}
	else
	{
		OutputDebugString(_T("Not initialized"));
	}
	return nRetValue;
	
}

int CDBEngenie::InitializeDatabase()
{	
	this->hLib = ::LoadLibrary(DBDLLNAME);
	
	if (this->hLib == NULL)
	{
		OutputDebugString(_T("Unable to load library"));
		return 1;
	}
	
	OutputDebugString(_T("Database Library loaded"));
	return 0;
}
