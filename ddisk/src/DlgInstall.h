#if !defined(AFX_DLGINSTALL_H__A79857A0_E201_11D3_AD9A_0090CCA1066A__INCLUDED_)
#define AFX_DLGINSTALL_H__A79857A0_E201_11D3_AD9A_0090CCA1066A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInstall.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInstall ダイアログ

class CDlgInstall : public CDialog
{
// コンストラクション
public:
	CDlgInstall(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDlgInstall)
	enum { IDD = IDD_DIALOG_INST };
	int		m_func;
	CString	m_text_winver;
	CString	m_warning;
	BOOL	m_uninst;
	BOOL	m_start;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDlgInstall)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDlgInstall)
	afx_msg void OnButtonHelp();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DLGINSTALL_H__A79857A0_E201_11D3_AD9A_0090CCA1066A__INCLUDED_)
