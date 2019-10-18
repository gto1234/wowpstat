﻿
// wowpstclDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "wowpstcl.h"
#include "wowpstclDlg.h"
#include "afxdialogex.h"
#include "CDBEngenie.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CwowpstclDlg



CwowpstclDlg::CwowpstclDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WOWPSTCL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CwowpstclDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_AircraftList);
	DDX_Control(pDX, IDC_AIRCRAFTINFO, m_AircraftInfo);
}

BEGIN_MESSAGE_MAP(CwowpstclDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZING()
END_MESSAGE_MAP()


// Обработчики сообщений CwowpstclDlg

BOOL CwowpstclDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	CDBEngenie::getInstance().InitializeDatabase(); //Init database engenie
	const char *dbvername = CDBEngenie::getInstance().GetDatabaseVersion();
	if (dbvername != NULL)
	{
		OutputDebugString(_T("Get version"));
		this->m_AircraftInfo.SetWindowText(CString(dbvername));
	}
	else
	{
		OutputDebugString(_T("Unable to get version"));
	}

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CwowpstclDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CwowpstclDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CwowpstclDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CwowpstclDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnSizing(fwSide, pRect);
	LPRECT oldlistrect = new RECT();
	LPRECT oldinforect = new RECT();
	m_AircraftList.GetWindowRect(oldlistrect);
	m_AircraftInfo.GetWindowRect(oldinforect);

	m_AircraftList.SetWindowPos(NULL, 10, 30, oldlistrect->right - oldlistrect->left , pRect->bottom - pRect->top - 70, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_AircraftInfo.SetWindowPos(NULL, 10, 30, pRect->right - oldinforect->left - 20, pRect->bottom - pRect->top - 70, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);

	// TODO: добавьте свой код обработчика сообщений
	delete oldlistrect;
	delete oldinforect;
	

	this->RefreshAircraftList();
}



void CwowpstclDlg::RefreshAircraftList()
{
	// TODO: Добавьте сюда код реализации.

	m_AircraftList.ResetContent();
	
	//TODO: Perform request to database 

}