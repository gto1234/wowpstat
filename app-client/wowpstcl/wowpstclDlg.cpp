
// wowpstclDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "wowpstcl.h"
#include "wowpstclDlg.h"
#include "afxdialogex.h"
#include "CDBEngenie.h"
#include "CAircraftTable.h"


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
	: CDialogEx(IDD_MAIN, pParent)
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
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_BUTTON_FILTER, &CwowpstclDlg::OnButtonFilter)
	ON_COMMAND(ID_BUTTON_ADD, &CwowpstclDlg::OnButtonAdd)
	ON_LBN_SELCHANGE(IDC_LIST1, &CwowpstclDlg::OnAircraftListChangeSelectedItem)
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

	m_Toolbar.Create(this);
	m_Toolbar.LoadToolBar(IDR_TOOLBAR_MAIN);
	m_Toolbar.ShowWindow(SW_SHOW);
	//m_Toolbar.SetBarStyle(CBRS_ALIGN_TOP | CBRS_TOOLTIPS | CBRS_FLYBY);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию	
	CDBEngenie::getInstance().InitializeDatabase(); //Init database engenie
	m_DlgAddAirplane.LoadDictionaries();
	RefreshAircraftList();
	OnAircraftListChangeSelectedItem();



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

	m_AircraftList.SetWindowPos(NULL, 10, 30, oldlistrect->right - oldlistrect->left , pRect->bottom - pRect->top - 110, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_AircraftInfo.SetWindowPos(NULL, 10, 30, pRect->right - oldinforect->left - 20, pRect->bottom - pRect->top - 110, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);

	// TODO: добавьте свой код обработчика сообщений
	delete oldlistrect;
	delete oldinforect;
	


}



void CwowpstclDlg::RefreshAircraftList()
{
	// TODO: Добавьте сюда код реализации.

	m_AircraftTable.SelectAll();
	m_AircraftTable.AssociateWithVisualComponent(m_AircraftList);
	
	//TODO: Perform request to database 

}


void CwowpstclDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
}


void CwowpstclDlg::OnButtonFilter()
{
	// TODO: добавьте свой код обработчика команд
	OutputDebugString(_T("OnButtonFilter\n"));

}


void CwowpstclDlg::OnButtonAdd()
{
	// TODO: добавьте свой код обработчика команд	
	m_DlgAddAirplane.DoModal();
	RefreshAircraftList();
}


void CwowpstclDlg::OnAircraftListChangeSelectedItem()
{	
	int nListBoxIndex = m_AircraftList.GetCurSel();

	if (nListBoxIndex == LB_ERR) 
		return;

	/*CString ItemSelected;
	m_AircraftList.GetText(nListBoxIndex, ItemSelected);
	AfxMessageBox(ItemSelected);*/

	CAircraftTable::TableContent CurrentAircraft;

	if (m_AircraftTable.GetAircraft(nListBoxIndex, CurrentAircraft) == true)
	{
		std::string TechKind = CurrentAircraft.premium == "0" ? "Линейная" : "Премиумная";

		std::string s = 
			"Самолёт: " + CurrentAircraft.name + "\r\n" +
			"Класс: " + CurrentAircraft.air_class + "\r\n" +
			"Нация: " + CurrentAircraft.nation + "\r\n" +
			"Уровень: " + CurrentAircraft.level + "\r\n" +
			"Эра: " + CurrentAircraft.era + "\r\n" +
			"Вид техники: " + TechKind + "\r\n";

		m_AircraftInfo.SetWindowText(CString(s.c_str()));
	}
	



}
