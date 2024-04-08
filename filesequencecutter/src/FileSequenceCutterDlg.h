// FileSequenceCutterDlg.h : ヘッダー ファイル
//

#if !defined(AFX_FILESEQUENCECUTTERDLG_H__10C0DADF_F383_497F_ABE5_5B711C708D2E__INCLUDED_)
#define AFX_FILESEQUENCECUTTERDLG_H__10C0DADF_F383_497F_ABE5_5B711C708D2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define FI_BUFFER_SIZE	100000		// ファイル読み込みバッファ 100kBytes
#define FI_READ_BUFFER_SIZE	100000	// データ読み込みバッファ 100kBytes

/////////////////////////////////////////////////////////////////////////////
// CFileSequenceCutterDlg ダイアログ

class CFileSequenceCutterDlg : public CDialog
{
// 構築
public:
	BOOL fiWriteFile(long nStart, long nEnd, CString strFpath, int nSeqNo);
	int fiReadChar(void);
	CFileSequenceCutterDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CFileSequenceCutterDlg)
	enum { IDD = IDD_FILESEQUENCECUTTER_DIALOG };
	CButton	m_radio_marker_ctrl;
	CComboBox	m_cmb_keyword_ctrl;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CFileSequenceCutterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

	// ファイルアクセス用
	FILE *fi;
	long fi_cur_buf_addr;	// 現在読み込まれているデータブロックの先頭アドレス
	int fi_cur_buf_size;	// 読み込まれているデータのサイズ
	long fi_read_ptr;		// 読み込みを行うデータのアドレス
	int fi_read_size;		// 読み込みを行うサイズ
	unsigned char fi_buf[FI_BUFFER_SIZE+1];		// 読み込みバッファ（内部処理用）
	unsigned char fi_r_buf[FI_READ_BUFFER_SIZE+1];	// 読み込みデータ

// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CFileSequenceCutterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnBrowsefile();
	afx_msg void OnBtnBrowsepath();
	afx_msg void OnBtnAbout();
	afx_msg void OnBtnExec();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

BOOL IsStrHexnum(char *buf);

#endif // !defined(AFX_FILESEQUENCECUTTERDLG_H__10C0DADF_F383_497F_ABE5_5B711C708D2E__INCLUDED_)
