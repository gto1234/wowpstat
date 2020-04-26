#pragma once

#include "sqlite3/sqlite3.h"
#include <string>
#include "CDictionaryTable.h"
#include <vector>


/*
//With declared WINAPI expands __stdcall x86-32 version will not work properly. Instead this __cdecl works correctly on both architecturies
typedef char* (WINAPI* call_libver)();
typedef int   (WINAPI* call_dbopen)(const char*, sqlite3**);
typedef int   (WINAPI* call_dbclose)(sqlite3*);
typedef int   (WINAPI* call_dbexec)(sqlite3*, const char*, int (*)(void*, int, char**, char**), void*, char**);*/

typedef char* (__cdecl* call_libver)();
typedef int   (__cdecl* call_dbopen)(const char*, sqlite3**);
typedef int   (__cdecl* call_dbclose)(sqlite3*);
typedef int   (__cdecl* call_dbexec)(sqlite3*, const char*, int (*)(void*, int, char**, char**), void*, char**);

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
	void Query(const std::string& query);
	void Query(const std::string &query, std::vector<std::vector<std::string>>& result);
	
	
private:
	HMODULE hLib;
	~CDBEngenie();
	CDBEngenie();
	
	call_libver		pF_libver;
	call_dbopen		pF_dbopen;
	call_dbclose	pF_dbclose;
	call_dbexec		pF_dbexec;

	sqlite3* db;
	bool m_isInitialized;
	static int callback(void*, int, char**, char**);
	std::vector<std::vector<std::string>> m_result_query;
	void AddResultRecord(const std::vector<std::string>&);

	CDBEngenie(CDBEngenie const&) = delete;
	CDBEngenie& operator= (CDBEngenie const&) = delete;
};

