// ShiftTimeDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "ShiftTime.h"
#include "ShiftTimeDlg.h"
#include "DlgSelectExt.h"
#include "DlgHelpDoc.h"
#include <io.h>			// findfirst

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// アプリケーションのバージョン情報で使われている CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// メッセージ ハンドラがありません。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShiftTimeDlg ダイアログ

CShiftTimeDlg::CShiftTimeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShiftTimeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShiftTimeDlg)
		// メモ: この位置に ClassWizard によってメンバの初期化が追加されます。
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShiftTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShiftTimeDlg)
	DDX_Control(pDX, IDC_CHECK_ZEROSEC, m_chk_ZeroSec);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CShiftTimeDlg, CDialog)
	//{{AFX_MSG_MAP(CShiftTimeDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BROWSE, OnBtnBrowse)
	ON_BN_CLICKED(IDC_BTN_WILDCARD, OnBtnWildcard)
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_BTN_EXEC, OnBtnExec)
	ON_BN_CLICKED(IDC_BTN_HELP, OnBtnHelp)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShiftTimeDlg メッセージ ハンドラ

BOOL CShiftTimeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "バージョン情報..." メニュー項目をシステム メニューへ追加します。

	// IDM_ABOUTBOX はコマンド メニューの範囲でなければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	
	// TODO: 特別な初期化を行う時はこの場所に追加してください。

	// ***********************
	// ダイアログ表示の初期値を設定
	// ***********************
	::GetTempPath(sizeof(szTmp256), szTmp256);
	SetDlgItemText(IDC_EDIT_PATH, szTmp256);	// テンポラリフォルダをとりあえず表示
	SetDlgItemText(IDC_EDIT_FILE, "*.*");

	SetDlgItemInt(IDC_EDIT_YEAR, 0);
	SetDlgItemInt(IDC_EDIT_MONTH, 0);
	SetDlgItemInt(IDC_EDIT_DAY, 0);
	SetDlgItemInt(IDC_EDIT_HOUR, 0);
	SetDlgItemInt(IDC_EDIT_MIN, 0);
	SetDlgItemInt(IDC_EDIT_SEC, 0);
	
	CheckRadioButton(IDC_RADIO_SHIFT, IDC_RADIO_SHIFT_2, IDC_RADIO_SHIFT);
	m_chk_ZeroSec.SetCheck(0);	// 初期値は「ゼロ秒にしない｣

	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

void CShiftTimeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CShiftTimeDlg::OnPaint() 
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
HCURSOR CShiftTimeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// *****************************************
// パスの参照ボタンが押されたとき
// コモンダイアログを表示する
// *****************************************
void CShiftTimeDlg::OnBtnBrowse() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	char s_full[MAX_PATH], s_full2[MAX_PATH];
	LPITEMIDLIST pidl;
	BROWSEINFO bi;
	ZeroMemory(&bi,sizeof(bi));
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
	bi.lpszTitle = (LPCSTR)"対象フォルダの選択";
	bi.hwndOwner = m_hWnd;
	bi.pszDisplayName = (LPSTR)s_full2;		// 使わないが領域だけは渡す

	pidl = ::SHBrowseForFolder(&bi);
	if(pidl == NULL) return;
	SHGetPathFromIDList(pidl, s_full);

	// ルートフォルダの扱い。最後に \ がついているかどうか
	if(s_full[strlen(s_full)-1] != '\\')
		strcat(s_full, "\\");
	// ファイル入力ボックスをアップデートする
	SetDlgItemText(IDC_EDIT_PATH, s_full);
	
}

// *****************************************
// ファイル名にワイルドカードを入力
// *****************************************
void CShiftTimeDlg::OnBtnWildcard() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CDlgSelectExt dlg;

	dlg.m_radio_sel = 10;

	if(dlg.DoModal() == IDOK)
	{
		switch(dlg.m_radio_sel)
		{
			case 0 : 	SetDlgItemText(IDC_EDIT_FILE, "*.jpg"); break;
			case 1 : 	SetDlgItemText(IDC_EDIT_FILE, "*.jpeg"); break;
			case 2 : 	SetDlgItemText(IDC_EDIT_FILE, "*.jp*"); break;
			case 3 : 	SetDlgItemText(IDC_EDIT_FILE, "*.tif"); break;
			case 4 : 	SetDlgItemText(IDC_EDIT_FILE, "*.bmp"); break;
			case 5 : 	SetDlgItemText(IDC_EDIT_FILE, "*.gif"); break;
			case 6 : 	SetDlgItemText(IDC_EDIT_FILE, "*.mp3"); break;
			case 7 : 	SetDlgItemText(IDC_EDIT_FILE, "*.mpg"); break;
			case 8 : 	SetDlgItemText(IDC_EDIT_FILE, "*.avi"); break;
			case 9 : 	SetDlgItemText(IDC_EDIT_FILE, "*.dat"); break;
			case 10 : 	SetDlgItemText(IDC_EDIT_FILE, "*.*"); break;
			default : 	SetDlgItemText(IDC_EDIT_FILE, "プログラムのエラーです"); break;
		}
	}
	
}

// *****************************************
// 年月日などの垂直スクロールバーが押された場合の処理
// *****************************************
void CShiftTimeDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	
//	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
	int nYear, nMonth, nDay, nHour, nMin, nSec, nOp;

	// 時間設定の現在のテキストボックスを読み込む
	nYear = GetDlgItemInt(IDC_EDIT_YEAR, 0);
	nMonth = GetDlgItemInt(IDC_EDIT_MONTH, 0);
	nDay = GetDlgItemInt(IDC_EDIT_DAY, 0);
	nHour = GetDlgItemInt(IDC_EDIT_HOUR, 0);
	nMin = GetDlgItemInt(IDC_EDIT_MIN, 0);
	nSec = GetDlgItemInt(IDC_EDIT_SEC, 0);

	// 上下の矢印がクリックされたときの方向性をSGN変数にセット
	switch(nSBCode)
	{
		case SB_LINEUP :
			nOp=1; break;
		case SB_LINEDOWN :
			nOp=-1; break;
		default :
			nOp=0; break;
	}

	// クリックされたコントロールIDにしたがって、該当のテキストボックスの値を変更する
	if(pScrollBar->GetDlgCtrlID() == IDC_SCRL_YEAR) SetDlgItemInt(IDC_EDIT_YEAR, nYear + nOp);
	if(pScrollBar->GetDlgCtrlID() == IDC_SCRL_MONTH) SetDlgItemInt(IDC_EDIT_MONTH, nMonth + nOp);
	if(pScrollBar->GetDlgCtrlID() == IDC_SCRL_DAY) SetDlgItemInt(IDC_EDIT_DAY, nDay + nOp);
	if(pScrollBar->GetDlgCtrlID() == IDC_SCRL_HOUR) SetDlgItemInt(IDC_EDIT_HOUR, nHour + nOp);
	if(pScrollBar->GetDlgCtrlID() == IDC_SCRL_MIN) SetDlgItemInt(IDC_EDIT_MIN, nMin + nOp);
	if(pScrollBar->GetDlgCtrlID() == IDC_SCRL_SEC) SetDlgItemInt(IDC_EDIT_SEC, nSec + nOp);

}

// *****************************************
// メイン ルーチン
// *****************************************
void CShiftTimeDlg::OnBtnExec() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	BOOL bShiftPrev = FALSE;	// 前にずらす
	BOOL bZeroSec = FALSE;		// ゼロ秒にあわせる
	BOOL bLog = FALSE;			// ログを表示するかどうか
	CString szTmp1, szTmp2, szLogMsg;
	CString szPath;				// パス名（ファイル名含まず）
	int nCount = 0;				// 処理完了ファイル数
	struct _finddata_t finddata;	// findfirst用
	long hFind;						// findfirst用
	CTime tm_src, tm_dst;			// 双方のファイルの日時
	CFileStatus Fstatus;			// 日時を変更するときに使う

	int nYear, nMonth, nDay, nHour, nMin, nSec, nOp;

	// チェックボックスの内容を読み取る
	if(IsDlgButtonChecked(IDC_RADIO_SHIFT)) bShiftPrev = TRUE;
	if(IsDlgButtonChecked(IDC_CHECK_ZEROSEC)) bZeroSec = TRUE;
	if(IsDlgButtonChecked(IDC_CHECK_LOG)) bLog = TRUE;
	// 「前にずらす」、「後ろにずらす」の方向の設定（SGN）
	if(bShiftPrev) nOp = -1;
	else  nOp = 1;

	// 時間設定のテキストボックスを読み取る
	nYear = nOp * GetDlgItemInt(IDC_EDIT_YEAR, 0);
	nMonth = nOp * GetDlgItemInt(IDC_EDIT_MONTH, 0);
	nDay = nOp * GetDlgItemInt(IDC_EDIT_DAY, 0);
	nHour = nOp * GetDlgItemInt(IDC_EDIT_HOUR, 0);
	nMin = nOp * GetDlgItemInt(IDC_EDIT_MIN, 0);
	nSec = nOp * GetDlgItemInt(IDC_EDIT_SEC, 0);

	// 時差を CTime 形式で格納  最大±68年
	CTimeSpan tmShift(nYear*365 + nMonth*30 + nDay, nHour, nMin, nSec); 

	// フォルダ名のテキストボックスを読み取る
	GetDlgItemText(IDC_EDIT_PATH, szPath);
	if(szPath.GetLength() <= 0)
	{
		MessageBox("対象フォルダが指定されていません", "エラー", MB_ICONSTOP|MB_OK);
		return;
	}
	// ファイル名（ワイルドカード可）のテキストボックスを読み取る
	GetDlgItemText(IDC_EDIT_FILE, szTmp2);
	if(szTmp2.GetLength() <= 0)
	{
		MessageBox("対象ファイルが指定されていません", "エラー", MB_ICONSTOP|MB_OK);
		return;
	}

	szTmp1 = szPath + szTmp2;	// ワイルドカード形式のパス完成

	// ログ表示 のための文字列の作成
	if(bLog)
		szLogMsg.Format("検索パス %s\r\n調整時間 %d 日 %d 時間 %d 分%d 秒\r\n------------------------------\r\n\r\n", 
				szTmp1, tmShift.GetDays(), tmShift.GetHours(), tmShift.GetMinutes(), tmShift.GetSeconds());

	// *****************************************
	// FINDFIRST 関数による ファイルの検索
	// *****************************************
    if( (hFind = _findfirst((LPCSTR)szTmp1, &finddata )) == -1L )
	{
		MessageBox("検索条件に一致するファイルが見つかりません", "情報", MB_ICONINFORMATION|MB_OK);
		return ;
	}

	if(!(finddata.attrib & _A_SUBDIR))	// ディレクトリ属性でない場合
	{	// 一つ目のファイルの発見
		szTmp2 = szPath + finddata.name;	// フルパスのファイル名完成
		if(CFile::GetStatus(szTmp2, Fstatus)) // ファイルの情報を得る
		{
			Fstatus.m_mtime += tmShift;			// 時差を代入して計算（最終変更日）
			Fstatus.m_ctime += tmShift;			// 時差を代入して計算（作成日）
			if(bZeroSec)
			{	// 秒をゼロにする処理
				nSec = Fstatus.m_mtime.GetSecond();
				Fstatus.m_mtime -= nSec;
				nSec = Fstatus.m_ctime.GetSecond();
				Fstatus.m_ctime -= nSec;
			}

			// ログ表示 のための文字列の作成
			if(bLog)
				szTmp1.Format(" 完了 : %s  (%04d/%02d/%02d %02d:%02d:%02d)\r\n", szTmp2,
						Fstatus.m_mtime.GetYear(), Fstatus.m_mtime.GetMonth(), Fstatus.m_mtime.GetDay(),
						Fstatus.m_mtime.GetHour(), Fstatus.m_mtime.GetMinute(), Fstatus.m_mtime.GetSecond());
			// *****************************************
			// ファイルへの書き込み
			// *****************************************
			try{ CFile::SetStatus(szTmp2, Fstatus); }
			catch(CFileException *e)
			{	// コピー先ファイルに書き込めないとき
				long dummy = e->m_lOsError;	// 「e が一回も使われていない」警告を回避するためのダミー
				nCount--;	// あとで、インクリメントされるので、ここで減らしておく
				if(bLog) szTmp1.Format(" 失敗 : %s\r\n", szTmp2);
			}
			// 処理完了ファイル数をインクリメント
			nCount++;

			// ログ表示 のための文字列の作成
			if(bLog) szLogMsg += szTmp1;
		}
	}
	while(_findnext( hFind, &finddata ) == 0)
	{	// 続くファイルを連続発見
		if(!(finddata.attrib & _A_SUBDIR))	// ディレクトリ属性でない場合
		{
			szTmp2 = szPath + finddata.name;	// フルパスのファイル名完成
			if(CFile::GetStatus(szTmp2, Fstatus)) // ファイルの情報を得る
			{
				Fstatus.m_mtime += tmShift;			// 時差を代入して計算（最終変更日）
				Fstatus.m_ctime += tmShift;			// 時差を代入して計算（作成日）
				if(bZeroSec)
				{	// 秒をゼロにする処理
					nSec = Fstatus.m_mtime.GetSecond();
					Fstatus.m_mtime -= nSec;
					nSec = Fstatus.m_ctime.GetSecond();
					Fstatus.m_ctime -= nSec;
				}

				// ログ表示 のための文字列の作成
				if(bLog)
					szTmp1.Format(" 完了 : %s  (%04d/%02d/%02d %02d:%02d:%02d)\r\n", szTmp2,
							Fstatus.m_mtime.GetYear(), Fstatus.m_mtime.GetMonth(), Fstatus.m_mtime.GetDay(),
							Fstatus.m_mtime.GetHour(), Fstatus.m_mtime.GetMinute(), Fstatus.m_mtime.GetSecond());
				// *****************************************
				// ファイルへの書き込み
				// *****************************************
				try{ CFile::SetStatus(szTmp2, Fstatus); }
				catch(CFileException *e)
				{	// コピー先ファイルに書き込めないとき
					long dummy = e->m_lOsError;	// 「e が一回も使われていない」警告を回避するためのダミー
					nCount--;	// あとで、インクリメントされるので、ここで減らしておく
					if(bLog) szTmp1.Format(" 失敗 : %s\r\n", szTmp2);
				}
				// 処理完了ファイル数をインクリメント
				nCount++;

				// ログ表示 のための文字列の作成
				if(bLog) szLogMsg += szTmp1;
			}
		}
	}

	// ログの表示
	if(bLog)
	{
		szTmp1.Format("\r\n------------------------------\r\n%d 個のファイルの日付を書き換えました", nCount);
		szLogMsg += szTmp1;
		
		CDlgHelpDoc dlg;

		dlg.m_edit_main = szLogMsg;

		dlg.DoModal();

	}
	else
	{
		// ログを表示しない場合は、変更したファイル数を表示

		szTmp1.Format("%d 個のファイルの日付を書き換えました", nCount);
		MessageBox(szTmp1, "メッセージ", MB_ICONINFORMATION|MB_OK);
	}
}

// *****************************************
// ヘルプ の表示
// *****************************************
void CShiftTimeDlg::OnBtnHelp() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CDlgHelpDoc dlg;

	dlg.m_edit_main = "\r\n"
		"ShiftTime - タイムスタンプ調整ツール\r\n"
		" Version 1.0   (freeware)\r\n"
		"\r\n\r\n"
		" (C) 2002 INOUE. Hirokazu\r\n"
		" inoue-h@iname.com\r\n"
		"\r\n\r\n\r\n"
		"【はじめに】\r\n"
		"このプログラムは、複数のファイルのタイムスタンプ（時間）を一括して『一定時間ずらす』設定を行うツールです\r\n"
		"当初の目的は、時差のある海外で撮影した「デジカメの画像ファイル」のタイムスタンプ"
		"を現地時刻に設定しなおすため作成しています\r\n"
		"\r\n"
		"UNIX のスクリプト使い以外の方向けです :-) \r\n"
		"\r\n\r\n"
		"【動作環境】\r\n"
		"Windows 95/98/Me, Windows NT/200/XP 日本語版\r\n"
		"  MFC ver 4.2 のライブラリがインストールされていること (mfc42.dll, msvcrt.dll)\r\n"
		"\r\n\r\n"
		"【インストール】\r\n"
		"この画面を見ているということは、すでにインストール完了です\r\n"
		"\r\n\r\n"
		"【アンインストール】\r\n"
		"このプログラムは、レジストリおよび設定ファイルなどを利用しません\r\n"
		"プログラム本体を消去すればそれで終わりです\r\n"
		"\r\n\r\n"
		"【利用法】\r\n"
		"「対象フォルダ」\r\n"
		"   末尾に「￥」記号がつく形で指定すること。\r\n"
		"\r\n"
		"「対象ファイル」\r\n"
		"   ワイルドカード（*.JPG 等)を指定可能\r\n"
		"\r\n"
		"※フォルダ + 検索後のファイル名 で 256 文字を越えない範囲\r\n"
		"\r\n"
		"「時間調整」\r\n"
		"   1か月=30日、1年=365日で換算している\r\n"
		"\r\n"
		"設定項目を適宜設定したら、処理開始ボタンを押す\r\n"
		"\r\n\r\n"
		"【例】\r\n"
		"D:\\My Documents\\Photo フォルダの D0001.JPG, D0002.JPG, ... D0999.JPG\r\n"
		"のタイムスタンプを 9時間戻したい\r\n"
		"  （たとえば、2002/01/01 12:00 -> 2002/01/01 03:00）\r\n"
		"\r\n"
		"● 対象フォルダは 「D:\\My Documents\\Photo\\」 ← 最後の \\ 記号は重要\r\n"
		"● 対象ファイルは 「*.jpg」\r\n"
		"● 時間調整は 「9時間」と「前にずらす」を選択する\r\n"
		"(「-9時間」と「後ろにずらす」でも同じ処理になる。）\r\n"
		"\r\n\r\n"
		"【制限事項】\r\n"
		"「読み取り属性」のファイルは処理できない\r\n"
		"ファイル以外のものは対象外（フォルダ等）\r\n"
		"\r\n"
		"日時は UNIX 時間の範囲（およそ1970年〜2032年）しか設定できない\r\n"
		"Windowsの拡張タイムスタンプのうち「作成日」、「最終更新日」のみ設定できます\r\n"
		"\r\n"
		"パス名・ファイル名に利用できる文字は、通常 ANSI のアルファベットを想定。（長いファイル名含む）\r\n"
		"日本語の文字を使っている場合、エラーが出るかもしれません。（0x5cでエラーが出ないことは確認していますが、全ての文字コードで確認はしていません）\r\n"
		"安全に利用していただくためには、DOSの8+3形式のパス・ファイル名で、LFNを使わないアルファベットのみと言うのが最も安全です\r\n"
		"当方にエラーレポートを送っていただく前に、8+3形式アルファベットを試してみてください\r\n"
		"\r\n"
		"これはフリーウエアです。あらゆる状況に対してのテストは行っていません。利用者の良識ある利用をお願いします\r\n"
		"\r\n\r\n"
		"【テクノロジ】\r\n"
		"ソースコードの質問をする前に、下記を読んでみてください\r\n"
		"\r\n"
		"このプログラムは、対象ファイルに対し次の操作をしているだけです\r\n"
		"CFile::GetStatus(szTmp2, Fstatus);		// 属性を取得し\r\n"
		"Fstatus.m_mtime += tmShift;			// 時差を代入して計算\r\n"
		"Fstatus.m_ctime += tmShift;			// 時差を代入して計算\r\n"
		"CFile::SetStatus(szTmp2, Fstatus);		// 属性を書き込む\r\n"
		"\r\n"
		"書き込みでは、例外処理 try - catch 処理をしています\r\n"
		"なお、時差の表現は\r\n"
		"CTimeSpan tmShift(nYear*365 + nMonth*30 + nDay, nHour, nMin, nSec); \r\n"
		"\r\n\r\n"
		"【使用許諾条件】\r\n"
		"このプログラムとドキュメントをフリーウエアーとし、すべての著作権は作者である井上博計に属します。\r\n"
		"著作者はこのプログラム及びドキュメントに関するいかなる保証も行いません。このプログラムの使用はすべて使用者の責任において行って下さい。\r\n"
		"本製品の動作（正常動作、異常動作）によって被るすべての結果についての全責任は、本ソフトの使用者にあります。\r\n"
		"著作者による許可無しにこのプログラムとドキュメントを販売することは出来ません。ただし、無料ソフトとして配布する場合はディスク料金や郵送料等、最低限の対価の授受を伴ってもかまいません。また、雑誌などの販促物に付属させるときもこれに準じます。\r\n"
		"このプログラムのサポートは著作者宛電子メールを使用して行いますが、著作者がサポートを行うのはボランティアであって義務・責務ではありません。\r\n"
		"ネットワークを長期間留守にすることもありますので、自動的にメールが消去されている可能性もありますのでご注意下さい。\r\n"
		"\r\n\r\n"
		"「フリーウエアー、シェアウエアー」の記事として取り上げる場合や、同様の目的で書籍等の付属CD-ROMに収録することを、（作者からお断りの連絡をしない限り）許可します。\r\n"
		"雑誌、書籍に掲載する場合は、作者までご一報ください（下記のすべてのアドレスに対して）。なお、長期間留守にしている場合もありますので、掲載の許諾の返事が（1週間以内に）無い場合は「許可した」ものとして扱えます。この場合見本誌は（作者の住所が判明しない場合）、「大阪中央郵便局止め 井上博計宛」でお願いします。\r\n"
		"\r\n\r\n"
		"雑誌、CD-ROM等メディアへの収録の許諾は、作者が最後の許諾通知を行ってから １年間 とします。この期間を超えた後に掲載を行う場合は、再度許諾を取らなければなりません。\r\n"
		"掲載メディア１種類（雑誌なら１号分、販促配布分なら１週間以内に連続してプレスした１回分）につき、１件の許諾が必要です。\r\n"
		"ただし、すでに製造が終わった「在庫品」の出荷および流通過程にある製品を除きます。\r\n"
		"\r\n\r\n"
		"【ユーザー・サポート連絡先】\r\n"
		"電子メール\r\n"
		"  inoue-h@iname.com\r\n"
		"ホームページ\r\n"
		"  http://inoue-h.connect.to/\r\n"
		"  http://www.vector.co.jp/authors/VA001911/freeware/index.html\r\n"
		"  http://www.ne.jp/asahi/oasis/inoue-h/index.html\r\n"
		"\r\n"
		"上記のアドレスが消滅している場合、検索エンジンで「井上博計」で検索してください。\r\n"
		"My Journey - 旅のページ が私のページです\r\n";

	// ダイアログの表示
	dlg.DoModal();
}

// *****************************************
// F1 キーを押したときの処理
// *****************************************
BOOL CShiftTimeDlg::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	OnBtnHelp();
	return TRUE;
}
