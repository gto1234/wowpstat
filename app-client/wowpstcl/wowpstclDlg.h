
// wowpstclDlg.h: файл заголовка
//

#pragma once
#include "addairplaneDlg.h"
#include "CAircraftTable.h"

// Диалоговое окно CwowpstclDlg
class CwowpstclDlg : public CDialogEx
{
// Создание
public:
	CwowpstclDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	CToolBar m_Toolbar;
	addairplaneDlg m_DlgAddAirplane;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
private:
	// List of airplanes
	CListBox m_AircraftList;
	CEdit m_AircraftInfo;
	CAircraftTable m_AircraftTable;
public:
//	virtual HRESULT accDoDefaultAction(VARIANT varChild);
private:
	void RefreshAircraftList();
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnButtonFilter();
	afx_msg void OnButtonAdd();
};
