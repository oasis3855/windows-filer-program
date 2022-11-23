// FileCpExDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "FileCpEx.h"
#include "FileCpExDlg.h"
#include "DlgErrSel.h"
#include "DlgProgress.h"
#include "GlobalFunc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileCpExDlg ダイアログ

CFileCpExDlg::CFileCpExDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileCpExDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileCpExDlg)
	m_txt_from = _T("");
	m_int_end = 0;
	m_int_skip = 0;
	m_int_start = 0;
	m_txt_to = _T("");
	m_int_retry = 0;
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileCpExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileCpExDlg)
	DDX_Control(pDX, IDC_CMB_BUFSIZ, m_ctrl_bufsiz);
	DDX_Control(pDX, IDC_CK_NULL, m_ctrl_null);
	DDX_Control(pDX, IDC_CK_FILEEND, m_ctrl_fileend);
	DDX_Control(pDX, IDC_CK_DLG, m_ctrl_dlg);
	DDX_Control(pDX, IDC_TXT_END, m_ctrl_end);
	DDX_Control(pDX, IDC_TXT_SKIP, m_ctrl_skip);
	DDX_Control(pDX, IDC_TXT_RETRY, m_ctrl_retry);
	DDX_Text(pDX, IDC_TXT_FROM, m_txt_from);
	DDV_MaxChars(pDX, m_txt_from, 256);
	DDX_Text(pDX, IDC_TXT_END, m_int_end);
	DDX_Text(pDX, IDC_TXT_SKIP, m_int_skip);
	DDX_Text(pDX, IDC_TXT_START, m_int_start);
	DDX_Text(pDX, IDC_TXT_TO, m_txt_to);
	DDV_MaxChars(pDX, m_txt_to, 256);
	DDX_Text(pDX, IDC_TXT_RETRY, m_int_retry);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFileCpExDlg, CDialog)
	//{{AFX_MSG_MAP(CFileCpExDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CK_FILEEND, OnCkFileend)
	ON_BN_CLICKED(IDC_CK_DLG, OnCkDlg)
	ON_CBN_SELCHANGE(IDC_CMB_BUFSIZ, OnSelchangeCmbBufsiz)
	ON_BN_CLICKED(IDC_BTN_COPY, OnBtnCopy)
	ON_BN_CLICKED(IDC_BTN_FROMBRW, OnBtnFrombrw)
	ON_BN_CLICKED(IDC_BTN_TOBRW, OnBtnTobrw)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileCpExDlg メッセージ ハンドラ

BOOL CFileCpExDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	
	// TODO: 特別な初期化を行う時はこの場所に追加してください。
	CString strTmp;
	m_ctrl_bufsiz.SetCurSel(7);		// 0 ... 7 : 16K を選択

	SetDlgItemInt(IDC_TXT_START, 0);
	SetDlgItemInt(IDC_TXT_END, 0);
	SetDlgItemInt(IDC_TXT_RETRY, 10);
	m_ctrl_bufsiz.GetLBText(m_ctrl_bufsiz.GetCurSel(), strTmp);
	SetDlgItemInt(IDC_TXT_SKIP, atoi((LPCSTR)strTmp));

	m_ctrl_fileend.SetCheck(1);
	m_ctrl_dlg.SetCheck(1);
	m_ctrl_null.SetCheck(1);

	OnCkFileend();	// ファイルエンドまでコピーのチェック状態の反映
	OnCkDlg();	// エラー時にダイアログのチェック状態の反映
	
	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CFileCpExDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画用のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// クライアントの矩形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンを描画します。
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// システムは、ユーザーが最小化ウィンドウをドラッグしている間、
// カーソルを表示するためにここを呼び出します。
HCURSOR CFileCpExDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFileCpExDlg::OnCkFileend() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	if(!IsDlgButtonChecked(IDC_CK_FILEEND))
	{
		m_ctrl_end.EnableWindow(TRUE);
	}
	else
	{
		m_ctrl_end.EnableWindow(FALSE);
	}
	
}

void CFileCpExDlg::OnCkDlg() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	if(!IsDlgButtonChecked(IDC_CK_DLG))
	{
		m_ctrl_retry.EnableWindow(TRUE);
		m_ctrl_skip.EnableWindow(TRUE);
	}
	else
	{
		m_ctrl_retry.EnableWindow(FALSE);
		m_ctrl_skip.EnableWindow(FALSE);
	}
	
}

void CFileCpExDlg::OnSelchangeCmbBufsiz() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString strTmp;
	m_ctrl_bufsiz.GetLBText(m_ctrl_bufsiz.GetCurSel(), strTmp);
	SetDlgItemInt(IDC_TXT_SKIP, atoi((LPCSTR)strTmp));
	
}

void CFileCpExDlg::OnBtnFrombrw() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_EXPLORER,
		"すべてのファイル|*.*|mpeg データ|*.mp*|WAV データ|*.wav|その他のデータ|*.dat||");
	dlg.m_ofn.lpstrTitle = "コピー元ファイルの選択";

	if(dlg.DoModal() != IDOK) return;

	// ﾌｧｲﾙ名テキストボックスにファイル名をセット
	SetDlgItemText(IDC_TXT_FROM,dlg.GetPathName());
	
}

void CFileCpExDlg::OnBtnTobrw() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CFileDialog dlg(FALSE, NULL, NULL, OFN_OVERWRITEPROMPT|OFN_EXPLORER,
		"保存ファイル|*.*||");
	dlg.m_ofn.lpstrTitle = "保存ファイルの選択";

	if(dlg.DoModal() != IDOK) return;

	// ﾌｧｲﾙ名テキストボックスにファイル名をセット
	SetDlgItemText(IDC_TXT_TO,dlg.GetPathName());
	
}

#include <io.h>			// findfirst

void CFileCpExDlg::OnBtnCopy() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	if(::ThreadCtrlFlag)
	{	// フラグが１のときは、すでにスレッド起動済み
		MessageBox("コピースレッド起動済み", "警告", MB_ICONINFORMATION);
		return ;
	}
	
	CString strTmp;
	static ThreadArg p;
	DlgProgress dlg;

	dlg.p = &p;

	GetDlgItemText(IDC_TXT_FROM, p.strFnameFrom, 255);
	GetDlgItemText(IDC_TXT_TO, p.strFnameTo, 255);

	if( (!strlen(p.strFnameFrom)) || (!strlen(p.strFnameTo)) )
	{
		MessageBox("入出力 双方のファイルを指定してください", "警告", MB_ICONINFORMATION);
		return ;
	}

//	p.hWnd = this->m_hWnd;
//	p.hWndTxtCurbyte = GetDlgItem(IDC_STXT_CURSIZ)->m_hWnd;
//	p.hWndTxtTotalbyte = GetDlgItem(IDC_STXT_TOTALSIZ)->m_hWnd;
//	p.hWndTxtMes = GetDlgItem(IDC_STXT_MES)->m_hWnd;

	p.int_copystart = GetDlgItemInt(IDC_TXT_START,0);
	p.int_copyend = GetDlgItemInt(IDC_TXT_END, 0);
	m_ctrl_bufsiz.GetLBText(m_ctrl_bufsiz.GetCurSel(), strTmp);
	p.int_bufsiz = (long)atoi((LPCSTR)strTmp);
	p.int_skipsiz = GetDlgItemInt(IDC_TXT_SKIP, 0);
	p.int_retry = GetDlgItemInt(IDC_TXT_RETRY, 0);
	if(IsDlgButtonChecked(IDC_CK_DLG)) p.sw_errordlg = 1;
	else p.sw_errordlg = 0;
	if(IsDlgButtonChecked(IDC_CK_FILEEND)) p.sw_fileend = 1;
	else p.sw_fileend = 0;


	::ThreadCtrlFlag = 1;	// フラグをスレッド起動中にする
	// スレッドの起動
	ThreadHandle = ::CreateThread(NULL, 0, ::ThreadMain, (LPVOID)&p, 0, 0);
	if(ThreadHandle == NULL)
	{
		::ThreadCtrlFlag = 0;
		MessageBox("スレッド起動出来ませんでした", "警告", MB_ICONINFORMATION);
		return ;
	}

	dlg.DoModal();

	::ThreadCtrlFlag = 0;	// フラグを０にして、スレッド内での停止作業を行う
	if(!::ThreadEndFlag)
	{
		// スレッドが終了シグナルを出すのを待つ（無限に）
		::WaitForSingleObject(ThreadHandle,INFINITE);
	}
	// ハンドルをクローズして初めて、オブジェクトが消去される
	::CloseHandle(ThreadHandle);


}

