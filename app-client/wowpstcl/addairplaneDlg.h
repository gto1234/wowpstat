#pragma once


// Диалоговое окно addairplaneDlg
#include "CDBEngenie.h"

class addairplaneDlg : public CDialogEx
{
	DECLARE_DYNAMIC(addairplaneDlg)

public:
	addairplaneDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~addairplaneDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_AIRPLANE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
private:
	CComboBox m_AirClass;
	CComboBox m_Level;
	CButton m_Premium;
	CComboBox m_Nation;
	CEdit m_AircraftName;

	CDictionaryTable* m_DictAirClass;
	CDictionaryTable* m_DictNation;
	CDictionaryTable* m_DictLevel;
public:
	afx_msg void OnClickedButtonAdd();
	void FillDictionaries();
	virtual BOOL OnInitDialog();
	void LoadDictionaries();
};
