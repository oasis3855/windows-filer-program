#if !defined(AFX_DLGPREVIEW_H__B56BE442_9FB9_11D4_AD9A_0090CCA1066A__INCLUDED_)
#define AFX_DLGPREVIEW_H__B56BE442_9FB9_11D4_AD9A_0090CCA1066A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPreview.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPreview ダイアログ

class CDlgPreview : public CDialog
{
// コンストラクション
public:
	CDlgPreview(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDlgPreview)
	enum { IDD = IDD_DLG_PREVIEW };
	CEdit	m_edit_main_ctrl;
	CString	m_edit_main_text;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDlgPreview)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDlgPreview)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DLGPREVIEW_H__B56BE442_9FB9_11D4_AD9A_0090CCA1066A__INCLUDED_)
