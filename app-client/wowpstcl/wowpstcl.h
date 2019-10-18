
// wowpstcl.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CwowpstclApp:
// Сведения о реализации этого класса: wowpstcl.cpp
//

class CwowpstclApp : public CWinApp
{
public:
	CwowpstclApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CwowpstclApp theApp;
