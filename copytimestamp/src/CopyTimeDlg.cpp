// CopyTimeDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "CopyTime.h"
#include "CopyTimeDlg.h"
#include "DlgPreview.h"
#include "DlgAbout.h"
#include <io.h>			// findfirst

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCopyTimeDlg ダイアログ

CCopyTimeDlg::CCopyTimeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCopyTimeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCopyTimeDlg)
	m_edit_from = _T("");
	m_edit_to = _T("");
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCopyTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCopyTimeDlg)
	DDX_Text(pDX, IDC_EDIT_FROM, m_edit_from);
	DDX_Text(pDX, IDC_EDIT_TO, m_edit_to);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCopyTimeDlg, CDialog)
	//{{AFX_MSG_MAP(CCopyTimeDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_FROM, OnBtnFrom)
	ON_BN_CLICKED(IDC_BTN_TO, OnBtnTo)
	ON_BN_CLICKED(IDC_BTN_PREVIEW, OnBtnPreview)
	ON_BN_CLICKED(IDC_BTN_HELP, OnBtnHelp)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_BTN_EXEC, OnBtnExec)
	ON_BN_CLICKED(IDC_BTN_ABOUT, OnBtnAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCopyTimeDlg メッセージ ハンドラ

BOOL CCopyTimeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	
	// TODO: 特別な初期化を行う時はこの場所に追加してください。

	CheckDlgButton(IDC_CHECK_DISP, 1);	// 結果リストの表示のチェックをつける
	
	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CCopyTimeDlg::OnPaint() 
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
HCURSOR CCopyTimeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// ************************************************************
// コピー元フォルダのブラウズ
// ************************************************************
void CCopyTimeDlg::OnBtnFrom() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString StrTmp;		// 作業用
	char s_full[MAX_PATH];
	LPITEMIDLIST pidl;
	BROWSEINFO bi;
	ZeroMemory(&bi,sizeof(bi));
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
	StrTmp.LoadString(IDS_Q_SELFROM);	// "参照元フォルダの選択"
	bi.lpszTitle = (LPCSTR)StrTmp;
	bi.hwndOwner = m_hWnd;

	pidl = ::SHBrowseForFolder(&bi);	// フォルダ選択・コモンダイアログ
	if(pidl == NULL) return;
	SHGetPathFromIDList(pidl, s_full);

	// ルートフォルダの扱い。最後に \ がついているかどうか
	if(s_full[strlen(s_full)-1] != '\\')
		strcat(s_full, "\\");
	strcat(s_full, "*.*");
	// ファイル入力ボックスをアップデートする
	SetDlgItemText(IDC_EDIT_FROM, s_full);
	
}

// ************************************************************
// コピー先フォルダのブラウズ
// ************************************************************
void CCopyTimeDlg::OnBtnTo() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString StrTmp;		// 作業用
	char s_full[MAX_PATH];
	LPITEMIDLIST pidl;
	BROWSEINFO bi;
	ZeroMemory(&bi,sizeof(bi));
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
	StrTmp.LoadString(IDS_Q_SELTO);	// "コピー先のフォルダの選択"
	bi.lpszTitle = (LPCSTR)StrTmp;
	bi.hwndOwner = m_hWnd;

	pidl = ::SHBrowseForFolder(&bi);	// フォルダ選択・コモンダイアログ
	if(pidl == NULL) return;
	SHGetPathFromIDList(pidl, s_full);

	// ルートフォルダの扱い。最後に \ がついているかどうか
	if(s_full[strlen(s_full)-1] != '\\')
		strcat(s_full, "\\");
	// ファイル入力ボックスをアップデートする
	SetDlgItemText(IDC_EDIT_TO, s_full);
	
}

// ************************************************************
// プレビュー
// 実際にコピーは行わない
// ************************************************************
void CCopyTimeDlg::OnBtnPreview() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString StrTmp, StrTmp1;		// 作業用
	CDlgPreview dlg;				// 結果表示用ダイアログ
	CString FpassFrom, FpassTo, StrMes;
	struct _finddata_t finddata;	// 参照元ファイル検索用
	long hFind;						// 参照元ファイル検索用
	CTime tmc_src, tmm_src, tmc_dst, tmm_dst;	// 参照元・コピー先 ファイルの作成・最終変更日時
	CFileStatus Fstatus;			// ファイル情報

	// ダイアログより、パス名の取得
	GetDlgItemText(IDC_EDIT_FROM, FpassFrom);
	GetDlgItemText(IDC_EDIT_TO, FpassTo);

	// フォルダ名が設定されていないとき
	if(FpassFrom == "" || FpassTo == "")
	{
		StrTmp.LoadString(IDS_ERR_NOSRC);	// 参照元、コピー先の双方のフォルダを指定してください
		StrTmp1.LoadString(IDS_ERR_NOSRC_CAP);	// CopyTimeからの情報
		MessageBox((LPCSTR)StrTmp, (LPCSTR)StrTmp1, MB_ICONWARNING);
		return;
	}

	StrMes.LoadString(IDS_STR_PASSFROM);	// \r\n参照元フォルダ : 
	StrMes += FpassFrom;
	StrMes += "\r\n\r\n";

    if( (hFind = _findfirst((LPCSTR)FpassFrom, &finddata )) == -1L )
	{	// 参照下ファイルが見つからない場合
		StrMes.LoadString(IDS_STR_ERR_NOFROM);
	}
	else{
		if(!(finddata.attrib & _A_SUBDIR))
		{	// 一つ目のファイルの発見
			// 変更先ファイルがあるか確認する
			if(CheckFile(FpassTo, finddata.name, &tmc_dst, &tmm_dst))
			{
				// 参照元ファイルの日付の取得
				tmm_src = finddata.time_write;
				tmc_src = finddata.time_create;
				// 参照元ファイルのデータの表示
				StrTmp.Format(IDS_FDATA_FROM, finddata.name,
						tmm_src.GetYear(), tmm_src.GetMonth(), tmm_src.GetDay(),
						tmm_src.GetHour(), tmm_src.GetMinute());
				StrMes += StrTmp;
				// コピーするかどうかの判定式
				if(tmm_src == tmm_dst && tmc_src == tmc_dst) StrMes += "\t==  ";
				else StrMes += "\t==> ";
				// 変更先ファイルデータの表示
				StrTmp.Format(IDS_FDATA_TO,
						tmm_dst.GetYear(), tmm_dst.GetMonth(), tmm_dst.GetDay(),
						tmm_dst.GetHour(), tmm_dst.GetMinute());
				StrMes += StrTmp;
			}
		}
		while(_findnext( hFind, &finddata ) == 0)
		{	// 続くファイルを連続発見
			if(!(finddata.attrib & _A_SUBDIR))
			{
				if(CheckFile(FpassTo, finddata.name, &tmc_dst, &tmm_dst))
				{
					// 参照元ファイルの日付の取得
					tmm_src = finddata.time_write;
					tmc_src = finddata.time_create;
					// 参照元ファイルのデータの表示
					StrTmp.Format(IDS_FDATA_FROM, finddata.name,
							tmm_src.GetYear(), tmm_src.GetMonth(), tmm_src.GetDay(),
							tmm_src.GetHour(), tmm_src.GetMinute());
					StrMes += StrTmp;
					// コピーするかどうかの判定式
					if(tmm_src == tmm_dst && tmc_src == tmc_dst) StrMes += "\t==  ";
					else StrMes += "\t==> ";
					// 変更先ファイルデータの表示
					StrTmp.Format(IDS_FDATA_TO,
							tmm_dst.GetYear(), tmm_dst.GetMonth(), tmm_dst.GetDay(),
							tmm_dst.GetHour(), tmm_dst.GetMinute());
					StrMes += StrTmp;
				}
			}
		}
	}

	// 結果表示のダイアログ
	dlg.m_edit_main_text= StrMes;
	dlg.DoModal();
}

// ************************************************************
// コピー先のファイルの存在をチェックし、存在していればファイルの時間を格納する
// ************************************************************
// 引数
//   FpathTo : コピー先のフォルダ名（最後に \ 記号付き）
//   Fname : ファイル名
//   FCTime : 得られた時間を返す変数へのポインタ (作成日)
//   FMTime : 得られた時間を返す変数へのポインタ (最終変更日)
//
// 戻り値
//   TRUE : ファイルが存在、FTime にファイルの時間（最終書き込み時間）をセット
//   FALSE : ファイルが存在しない
// ************************************************************
BOOL CCopyTimeDlg::CheckFile(LPCSTR FpathTo, LPCSTR Fname, CTime *FCTime, CTime *FMTime)
{
	CString StrFpath;				// 検索対象ファイルのフルパス名
	CFileStatus Fstatus;			// ファイル情報

	// 検索対象ファイルのフルパスを組み立てる
	StrFpath = FpathTo;
	StrFpath += Fname;

	if(CFile::GetStatus(StrFpath, Fstatus))
	{	// ファイル発見
		*FCTime = Fstatus.m_ctime;	// 作成日時
		*FMTime = Fstatus.m_mtime;	// 最終変更日時
		return TRUE;
	}
	else
	{
		return FALSE;	// ファイルが見つからない
	}  
}

// ************************************************************
// タイムスタンプのコピーのボタンを押したときの処理
// ************************************************************
void CCopyTimeDlg::OnBtnExec() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CDlgPreview dlg;	// 結果表示のダイアログ
	CString FpassFrom, FpassTo, StrMes, StrTmp, StrTmp1;
	struct _finddata_t finddata;	// findfirst用
	long hFind;						// findfirst用
	CTime tmc_src, tmm_src, tmc_dst, tmm_dst;	// 参照元・コピー先 ファイルの作成・最終変更日時
	CFileStatus Fstatus;			// 日時を変更するときに使う
	int counter = 0;				// 成功したファイルの個数を数える
	BOOL iModtimePriority = FALSE;	// 作成日時を最終更新日時で上書き

	if(IsDlgButtonChecked(IDC_CHECK_MODPRI))
		iModtimePriority = TRUE;

	// 入力ボックスから、パス名を取得する
	GetDlgItemText(IDC_EDIT_FROM, FpassFrom);
	GetDlgItemText(IDC_EDIT_TO, FpassTo);

	if(FpassFrom == "" || FpassTo == "")
	{
		StrTmp.LoadString(IDS_ERR_NOSRC);
		StrTmp1.LoadString(IDS_ERR_NOSRC_CAP);
		MessageBox((LPCSTR)StrTmp, (LPCSTR)StrTmp1, MB_ICONWARNING);
		return;	// 両方入力されていないとき、エラー
	}

	StrMes.LoadString(IDS_STR_PASSFROM);
	StrMes += FpassFrom;
	StrMes += "\r\n\r\n";

    if( (hFind = _findfirst((LPCSTR)FpassFrom, &finddata )) == -1L )
	{
		StrMes.LoadString(IDS_STR_ERR_NOFROM);
	}
	else{
		if(!(finddata.attrib & _A_SUBDIR))
		{	// 一つ目のファイルの発見
			// 変更先ファイルがあるか確認する
			if(CheckFile(FpassTo, finddata.name, &tmc_dst, &tmm_dst))
			{
				// 参照元ファイルの日付の取得
				tmm_src = finddata.time_write;
				tmc_src = finddata.time_create;
				if(tmm_src != tmm_dst || tmc_src != tmc_dst)
				{	// 最終変更日時または作成日時が違う場合→ コピー処理へ
					// 参照元ファイルのデータの表示
					StrTmp.Format(IDS_FDATA_FROM, finddata.name,
						tmm_src.GetYear(), tmm_src.GetMonth(), tmm_src.GetDay(),
						tmm_src.GetHour(), tmm_src.GetMinute());
					StrMes += StrTmp;
					StrMes += "\t==> ";
					// 変更先ファイルデータの表示
					StrTmp.Format(IDS_FDATA_TO,
						tmm_dst.GetYear(), tmm_dst.GetMonth(), tmm_dst.GetDay(),
						tmm_dst.GetHour(), tmm_dst.GetMinute());
					StrMes += StrTmp;
					// ファイル情報を読み込む
					StrTmp = FpassTo; StrTmp += finddata.name;
					if(!CFile::GetStatus(StrTmp, Fstatus))
					{	// コピー先ファイルが異常なとき
						StrTmp1.LoadString(IDS_ERR_FERR);
						StrMes += StrTmp1;
					}
					else
					{
						// 時刻を変更して ファイルを書き込む
						Fstatus.m_ctime = tmc_src;
						if(iModtimePriority) Fstatus.m_ctime = tmm_src;
						Fstatus.m_mtime = tmm_src;
						try{ CFile::SetStatus(StrTmp, Fstatus); }
						catch(CFileException *e)
						{	// コピー先ファイルに書き込めないとき
							long dummy = e->m_lOsError;	// 「e が一回も使われていない」警告を回避するためのダミー
							if(Fstatus.m_attribute & 0x01) StrTmp1.LoadString(IDS_ERR_FWPROTECT);
							else StrTmp1.LoadString(IDS_ERR_FNWRT);
							StrMes += StrTmp1;
							counter--;
						}
						counter++;
					}
				}
			}
		}
		while(_findnext( hFind, &finddata ) == 0)
		{	// 続くファイルを連続発見
			if(!(finddata.attrib & _A_SUBDIR))
			{
				if(CheckFile(FpassTo, finddata.name, &tmc_dst, &tmm_dst))
				{
					// 参照元ファイルの日付の取得
					tmm_src = finddata.time_write;
					tmc_src = finddata.time_create;
					if(tmm_src != tmm_dst || tmc_src != tmc_dst)
					{	// 最終変更日時または作成日時が違う場合→ コピー処理へ
						// 参照元ファイルのデータの表示
						StrTmp.Format(IDS_FDATA_FROM, finddata.name,
							tmm_src.GetYear(), tmm_src.GetMonth(), tmm_src.GetDay(),
							tmm_src.GetHour(), tmm_src.GetMinute());
						StrMes += StrTmp;
						StrMes += "\t==> ";
						// 変更先ファイルデータの表示
						StrTmp.Format(IDS_FDATA_TO,
							tmm_dst.GetYear(), tmm_dst.GetMonth(), tmm_dst.GetDay(),
							tmm_dst.GetHour(), tmm_dst.GetMinute());
						StrMes += StrTmp;
						// ファイル情報を読み込む
						StrTmp = FpassTo; StrTmp += finddata.name;
						if(!CFile::GetStatus(StrTmp, Fstatus))
						{
							StrTmp1.LoadString(IDS_ERR_FERR);
							StrMes += StrTmp1;
						}
						else
						{
							// 時刻を変更して ファイルを書き込む
							Fstatus.m_ctime = tmc_src;
							if(iModtimePriority) Fstatus.m_ctime = tmm_src;
							Fstatus.m_mtime = tmm_src;
							try{ CFile::SetStatus(StrTmp, Fstatus); }
							catch(CFileException *e)
							{
								long dummy = e->m_lOsError;	// 「e が一回も使われていない」警告を回避するためのダミー
								if(Fstatus.m_attribute & 0x01) StrTmp1.LoadString(IDS_ERR_FWPROTECT);
								else StrTmp1.LoadString(IDS_ERR_FNWRT);
								StrMes += StrTmp1;
								counter--;
							}
							counter++;
						}
					}
				}
			}
		}
	}
	if(IsDlgButtonChecked(IDC_CHECK_DISP))
	{	// 結果リストを表示する
		StrMes += "\r\n\r\n";
		if(counter > 0)
		{
			StrTmp1.LoadString(IDS_MES_COPYFILECOUNT);
			StrTmp.Format(StrTmp1, counter);
		}
		else
		{
			StrTmp.LoadString(IDS_MES_NOFILCOPY);
		}
		StrMes += StrTmp;
		dlg.m_edit_main_text= StrMes;
		dlg.DoModal();
	}
	else if(!counter)
	{
		StrMes.LoadString(IDS_MES_NOFILCOPY);
		StrTmp1.LoadString(IDS_ERR_NOSRC_CAP);
		MessageBox((LPCSTR)StrMes, (LPCSTR)StrTmp1, MB_ICONWARNING);
	}
	
}

// ************************************************************
// ABOUT ダイアログの表示
// ************************************************************
void CCopyTimeDlg::OnBtnAbout() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CDlgAbout dlg;
	dlg.DoModal();
	
}

// ************************************************************
// ヘルプボタンを押すと、ヘルプを表示する
// ************************************************************
void CCopyTimeDlg::OnBtnHelp() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	WinHelp(1000,HELP_CONTENTS);
}

// ************************************************************
// F1 キーの処理
// ************************************************************
BOOL CCopyTimeDlg::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	WinHelp(1000,HELP_CONTENTS);
	return TRUE;
//	return CDialog::OnHelpInfo(pHelpInfo);
}

// ************************************************************
// EOF
