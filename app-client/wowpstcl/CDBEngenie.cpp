#include "stdafx.h"
#include "CDBEngenie.h"
#include <vector>

	

constexpr auto DBDLLNAME = L"sqlite3.dll";

CDBEngenie::CDBEngenie()
{
	this->hLib = 0;
	this->pF_dbclose = 0;
	this->pF_dbexec = 0;
	this->pF_dbopen = 0;
	this->pF_libver = 0;
	this->db = 0;
	m_isInitialized = false;
	m_result_query.clear();
}


CDBEngenie::~CDBEngenie()
{
	if (this->db != 0)
	{
		pF_dbclose(this->db);
	}
	if (this->hLib != 0)
	{
		::FreeLibrary(this->hLib);
	}

	this->hLib = 0;
	this->pF_dbclose = 0;
	this->pF_dbexec = 0;
	this->pF_dbopen = 0;
	this->pF_libver = 0;
	this->db = 0;
	m_isInitialized = false;
}
/*04  static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
	05    int i;
	06    for (i = 0; i < argc; i++) {
		07      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		08
	}
	09    printf("\n");
	10    return 0;
	11
}
12
13  int main(int argc, char** argv) {
	14    sqlite3 * db;
	15    char* zErrMsg = 0;
	16    int rc;
	17
		18    if (argc != 3) {
		19      fprintf(stderr, "Usage: %s DATABASE SQL-STATEMENT\n", argv[0]);
		20      return(1);
		21
	}
	22    rc = sqlite3_open(argv[1], &db);
	23    if (rc) {
		24      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		25      sqlite3_close(db);
		26      return(1);
		27
	}
	28    rc = sqlite3_exec(db, argv[2], callback, 0, &zErrMsg);
	29    if (rc != SQLITE_OK) {
		30      fprintf(stderr, "SQL error: %s\n", zErrMsg);
		31      sqlite3_free(zErrMsg);
		32
	}
	33    sqlite3_close(db);
	34    return 0;
	35
}*/

int CDBEngenie::callback(void* context, int argc, char** argv, char** azColName)
{
	OutputDebugString(_T(__FUNCSIG__" called"));
	if (context != 0)
	{
		CDBEngenie* DBEngenie = reinterpret_cast<CDBEngenie*>(context);
		if (DBEngenie != 0)
		{
			std::vector<std::string> TableRecord;
			for (int i = 0; i < argc; i++)
			{
				TableRecord.emplace_back(argv[i]);
			}
			DBEngenie->AddResultRecord(TableRecord);
		}
	}
	

	return 0;
}
void CDBEngenie::AddResultRecord(const std::vector<std::string>& TableRecord)
{
	m_result_query.emplace_back(TableRecord);
}

void CDBEngenie::Query(const std::string& query)
{
	char* zErrMsg = 0;
	OutputDebugString(_T(__FUNCSIG__" called\n"));
	if (m_isInitialized == true)
	{
		int rc = this->pF_dbexec(this->db, query.c_str(), &callback, this, &zErrMsg);
	}
	else
	{

	}
}

void CDBEngenie::Query(const std::string &query,  std::vector<std::vector<std::string>> &result)
{
	char* zErrMsg = 0;
	OutputDebugString(_T(__FUNCSIG__" called\n"));
	if (m_isInitialized == true)
	{
		m_result_query.clear();
		int rc = this->pF_dbexec(this->db, query.c_str(), &callback, this, &zErrMsg);
		result.assign(m_result_query.begin(), m_result_query.end());
	}
	else
	{

	}
	
}

const char* CDBEngenie::GetDatabaseVersion()
{
	char *nRetValue = 0;
	OutputDebugString(_T("GetDatabaseVersion called\n"));
	if (m_isInitialized != 0)
	{
		nRetValue = this->pF_libver();
	}
	else
	{
		OutputDebugString(_T("Not initialized\n"));
	}
	return nRetValue;
	
}

int CDBEngenie::InitializeDatabase()
{	
	if (this->hLib != 0)
	{
		OutputDebugString(_T("Already initialized\n"));
		return 1;
	}

	this->hLib = ::LoadLibrary(DBDLLNAME);
	
	if (this->hLib == 0)
	{
		OutputDebugString(_T("Unable to load library\n"));
		return 1;
	}
	
	this->pF_dbopen = (call_dbopen)::GetProcAddress(this->hLib, "sqlite3_open");
	this->pF_dbclose = (call_dbclose)::GetProcAddress(this->hLib, "sqlite3_close");
	this->pF_libver = (call_libver)::GetProcAddress(this->hLib, "sqlite3_libversion");
	this->pF_dbexec = (call_dbexec)::GetProcAddress(this->hLib, "sqlite3_exec");
	
	if ((this->pF_dbopen == 0)  ||
	    (this->pF_dbclose == 0) || 
		(this->pF_libver == 0)  || 
		(this->pF_dbexec == 0) )
	{
		OutputDebugString(_T("Some libfunction not mapped\n"));
		return 1;
	}

	int rc = pF_dbopen("wowpstat.db", &db);
	if (rc)
	{
		OutputDebugString(_T("SimpleSelect can not open"));
		return 1;
	}

	m_isInitialized = true;
	OutputDebugString(_T("Database Library loaded\n"));
	return 0;
}
