// CopyTimeDlg.h : ヘッダー ファイル
//

#if !defined(AFX_COPYTIMEDLG_H__B56BE426_9FB9_11D4_AD9A_0090CCA1066A__INCLUDED_)
#define AFX_COPYTIMEDLG_H__B56BE426_9FB9_11D4_AD9A_0090CCA1066A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCopyTimeDlg ダイアログ

class CCopyTimeDlg : public CDialog
{
// 構築
public:
	BOOL CheckFile(LPCSTR FpathTo, LPCSTR Fname, CTime *FCTime, CTime *FMTime);
	CCopyTimeDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CCopyTimeDlg)
	enum { IDD = IDD_COPYTIME_DIALOG };
	CString	m_edit_from;
	CString	m_edit_to;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CCopyTimeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CCopyTimeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnFrom();
	afx_msg void OnBtnTo();
	afx_msg void OnBtnPreview();
	afx_msg void OnBtnHelp();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnBtnExec();
	afx_msg void OnBtnAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_COPYTIMEDLG_H__B56BE426_9FB9_11D4_AD9A_0090CCA1066A__INCLUDED_)
