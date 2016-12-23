#pragma once
#include "afxcmn.h"


// CScaleDialog dialog

class CScaleDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CScaleDialog)

public:
	CScaleDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CScaleDialog();

// Dialog Data
	enum { IDD = IDD_SCALE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
  int m_Scale;                                         // Stores the current view scale
protected:
  CSpinButtonCtrl m_Spin;                              // Spin control for view scale               
public:
  virtual BOOL OnInitDialog();
};
