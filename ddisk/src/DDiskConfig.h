#if !defined(AFX_DDISKCONFIG_H__29D10422_DBAF_11D3_AD9A_0090CCA1066A__INCLUDED_)
#define AFX_DDISKCONFIG_H__29D10422_DBAF_11D3_AD9A_0090CCA1066A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DDiskConfig.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CDDiskConfig ダイアログ

class CDDiskConfig : public CDialog
{
// コンストラクション
public:
	CDDiskConfig(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDDiskConfig)
	enum { IDD = IDD_DIALOG_CONFIG };
	int		m_func;
	int		m_view;
	CString	m_text_winver;
	CString	m_edit_editor;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDDiskConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDDiskConfig)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnBrowse();
	afx_msg void OnBtnAbout();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnBtnMkuninst();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DDISKCONFIG_H__29D10422_DBAF_11D3_AD9A_0090CCA1066A__INCLUDED_)
