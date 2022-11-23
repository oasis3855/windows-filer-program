#if !defined(AFX_DLGERRSEL_H__874B1EBF_3423_4A29_A665_F89384FF853D__INCLUDED_)
#define AFX_DLGERRSEL_H__874B1EBF_3423_4A29_A665_F89384FF853D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgErrSel.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// DlgErrSel ダイアログ

class DlgErrSel : public CDialog
{
// コンストラクション
public:
	DlgErrSel(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(DlgErrSel)
	enum { IDD = IDD_DLG_ERR };
	CButton	m_ctrl_sel;
	CEdit	m_ctrl_errskip;
	CEdit	m_ctrl_moreerr;
	CButton	m_ctrl_samesel;
	int		m_int_sel;
	UINT	m_int_errskip;
	UINT	m_int_moreerr;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(DlgErrSel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(DlgErrSel)
	afx_msg void OnRadioSel2();
	afx_msg void OnRadioSel();
	virtual BOOL OnInitDialog();
	afx_msg void OnCkSamesel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DLGERRSEL_H__874B1EBF_3423_4A29_A665_F89384FF853D__INCLUDED_)
