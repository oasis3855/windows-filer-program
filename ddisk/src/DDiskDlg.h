// DDiskDlg.h : ヘッダー ファイル
//

#if !defined(AFX_DDISKDLG_H__41C96AE7_D6FF_11D3_AD9A_0090CCA1066A__INCLUDED_)
#define AFX_DDISKDLG_H__41C96AE7_D6FF_11D3_AD9A_0090CCA1066A__INCLUDED_

#include "DDisk.h"	// ClassView によって追加されました。
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDDiskDlg ダイアログ

class CDDiskDlg : public CDialog
{
// 構築
public:
	CDDiskDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDDiskDlg)
	enum { IDD = IDD_DDISK_DIALOG };
	CComboBox	m_cmb_disk;
	UINT	m_sect;
	UINT	m_size;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDDiskDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	CDDiskApp *theApp;
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDDiskDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnRead();
	afx_msg void OnBtnDpb();
	afx_msg void OnBtnConfig();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKillfocusEditSize();
	afx_msg void OnBtnBrowse();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnWrite();
	afx_msg void OnBtnEdit();
	afx_msg void OnBtnHelp();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	char m_mainbuf[4100];
	char m_buf[256];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。


#endif // !defined(AFX_DDISKDLG_H__41C96AE7_D6FF_11D3_AD9A_0090CCA1066A__INCLUDED_)

