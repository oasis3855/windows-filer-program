#if !defined(AFX_DLGPROGRESS_H__C5150A43_FF95_4D1B_B7CA_4B3AFE6F1CAE__INCLUDED_)
#define AFX_DLGPROGRESS_H__C5150A43_FF95_4D1B_B7CA_4B3AFE6F1CAE__INCLUDED_

#include "GlobalFunc.h"	// ClassView によって追加されました。
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgProgress.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// DlgProgress ダイアログ

class DlgProgress : public CDialog
{
// コンストラクション
public:
	ThreadArg *p;
	BOOL CreateMyDlg(CWnd *pParentWnd);
	DlgProgress(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(DlgProgress)
	enum { IDD = IDD_DLG_PROGRESS };
	CString	m_txt_cursiz;
	CString	m_txt_totalsiz;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(DlgProgress)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(DlgProgress)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DLGPROGRESS_H__C5150A43_FF95_4D1B_B7CA_4B3AFE6F1CAE__INCLUDED_)
