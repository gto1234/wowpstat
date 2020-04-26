// addairplaneDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "wowpstcl.h"
#include "addairplaneDlg.h"
#include "afxdialogex.h"
#include "CAircraftTable.h"


// Диалоговое окно addairplaneDlg

IMPLEMENT_DYNAMIC(addairplaneDlg, CDialogEx)

addairplaneDlg::addairplaneDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_AIRPLANE, pParent)
{
	m_DictAirClass = new CDictionaryTable("air_class"); //TODO: Проверка на 0, но ведь конструктор???
	m_DictLevel = new CDictionaryTable("levels");
	m_DictNation = new CDictionaryTable("nations");

}

addairplaneDlg::~addairplaneDlg()
{
	delete m_DictAirClass;
	delete m_DictLevel;
	delete m_DictNation;
}



void addairplaneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CLASS, m_AirClass);
	DDX_Control(pDX, IDC_COMBO_LEVEL, m_Level);
	DDX_Control(pDX, IDC_CHECK_PREMIUM, m_Premium);
	DDX_Control(pDX, IDC_COMBO_NATION, m_Nation);
	DDX_Control(pDX, IDC_EDIT_AIRPLANE_NAME, m_AircraftName);
}


BEGIN_MESSAGE_MAP(addairplaneDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &addairplaneDlg::OnClickedButtonAdd)
END_MESSAGE_MAP()


// Обработчики сообщений addairplaneDlg


void addairplaneDlg::OnClickedButtonAdd()
{
	// TODO: добавьте свой код обработчика уведомлений
	//TODO: Add new record here
	CString AircraftName;
	m_AircraftName.GetWindowText(AircraftName);
	CT2CA pszConvertedAnsiString(AircraftName);	
	CAircraftTable::AddAirCraft(m_DictAirClass->GetIDbyVisualComponentIndex(m_AirClass.GetCurSel()),
		m_DictNation->GetIDbyVisualComponentIndex(m_Nation.GetCurSel()),
		m_DictLevel->GetIDbyVisualComponentIndex(m_Level.GetCurSel()),
		std::string(pszConvertedAnsiString),
		m_Premium.GetCheck() & BST_CHECKED);

}

void addairplaneDlg::FillDictionaries()
{
	m_DictAirClass->AssociateWithVisualComponent(m_AirClass);
	m_DictLevel->AssociateWithVisualComponent(m_Level);
	m_DictNation->AssociateWithVisualComponent(m_Nation);
}


BOOL addairplaneDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	this->FillDictionaries();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // Исключение: страница свойств OCX должна возвращать значение FALSE
}


void addairplaneDlg::LoadDictionaries()
{
	// TODO: Добавьте сюда код реализации.
	m_DictAirClass->SelectAll();
	m_DictLevel->SelectAll();
	m_DictNation->SelectAll();
}
