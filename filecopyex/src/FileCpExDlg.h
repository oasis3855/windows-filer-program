// FileCpExDlg.h : ヘッダー ファイル
//

#if !defined(AFX_FILECPEXDLG_H__5A55B36D_1CA8_4F0C_A0E4_CE9C04C655B0__INCLUDED_)
#define AFX_FILECPEXDLG_H__5A55B36D_1CA8_4F0C_A0E4_CE9C04C655B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFileCpExDlg ダイアログ

class CFileCpExDlg : public CDialog
{
// 構築
public:
	HANDLE ThreadHandle;
	CFileCpExDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CFileCpExDlg)
	enum { IDD = IDD_FILECPEX_DIALOG };
	CComboBox	m_ctrl_bufsiz;
	CButton	m_ctrl_null;
	CButton	m_ctrl_fileend;
	CButton	m_ctrl_dlg;
	CEdit	m_ctrl_end;
	CEdit	m_ctrl_skip;
	CEdit	m_ctrl_retry;
	CString	m_txt_from;
	UINT	m_int_end;
	UINT	m_int_skip;
	UINT	m_int_start;
	CString	m_txt_to;
	UINT	m_int_retry;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CFileCpExDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CFileCpExDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCkFileend();
	afx_msg void OnCkDlg();
	afx_msg void OnSelchangeCmbBufsiz();
	afx_msg void OnBtnCopy();
	afx_msg void OnBtnFrombrw();
	afx_msg void OnBtnTobrw();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_FILECPEXDLG_H__5A55B36D_1CA8_4F0C_A0E4_CE9C04C655B0__INCLUDED_)
