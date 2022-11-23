// ShiftTimeDlg.h : ヘッダー ファイル
//

#if !defined(AFX_SHIFTTIMEDLG_H__A337A349_35CB_4E6A_92CE_F1305E622258__INCLUDED_)
#define AFX_SHIFTTIMEDLG_H__A337A349_35CB_4E6A_92CE_F1305E622258__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CShiftTimeDlg ダイアログ

class CShiftTimeDlg : public CDialog
{
// 構築
public:
	CShiftTimeDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CShiftTimeDlg)
	enum { IDD = IDD_SHIFTTIME_DIALOG };
	CButton	m_chk_ZeroSec;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CShiftTimeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CShiftTimeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnBrowse();
	afx_msg void OnBtnWildcard();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBtnExec();
	afx_msg void OnBtnHelp();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	char szTmp256[256];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SHIFTTIMEDLG_H__A337A349_35CB_4E6A_92CE_F1305E622258__INCLUDED_)
