// FileSequenceCutterDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "FileSequenceCutter.h"
#include "FileSequenceCutterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileSequenceCutterDlg ダイアログ

CFileSequenceCutterDlg::CFileSequenceCutterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileSequenceCutterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileSequenceCutterDlg)
		// メモ: この位置に ClassWizard によってメンバの初期化が追加されます。
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileSequenceCutterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileSequenceCutterDlg)
	DDX_Control(pDX, IDC_RADIO_MARKER, m_radio_marker_ctrl);
	DDX_Control(pDX, IDC_CMB_KEYWORD, m_cmb_keyword_ctrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFileSequenceCutterDlg, CDialog)
	//{{AFX_MSG_MAP(CFileSequenceCutterDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BROWSEFILE, OnBtnBrowsefile)
	ON_BN_CLICKED(IDC_BTN_BROWSEPATH, OnBtnBrowsepath)
	ON_BN_CLICKED(IDC_BTN_ABOUT, OnBtnAbout)
	ON_BN_CLICKED(IDC_BTN_EXEC, OnBtnExec)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileSequenceCutterDlg メッセージ ハンドラ

BOOL CFileSequenceCutterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	
	// TODO: 特別な初期化を行う時はこの場所に追加してください。

	SetDlgItemText(IDC_CMB_KEYWORD, "00 00 00 00 00");
	this->CheckRadioButton(IDC_RADIO_MARKER, IDC_RADIO_MARKER2, IDC_RADIO_MARKER);

	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CFileSequenceCutterDlg::OnPaint() 
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
HCURSOR CFileSequenceCutterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// **********************************
// ファイル参照のボタンを押したとき
// **********************************
void CFileSequenceCutterDlg::OnBtnBrowsefile() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString strTmp1;
	strTmp1.LoadString(STR_BTN_PICKFILE);
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST|OFN_EXPLORER|OFN_READONLY,strTmp1);
	if(dlg.DoModal()==TRUE)
		SetDlgItemText(IDC_EDIT_SRCFILE, dlg.GetPathName());	
}

int CALLBACK myBrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);

// **********************************
// フォルダ参照のボタンを押したとき
// **********************************
void CFileSequenceCutterDlg::OnBtnBrowsepath() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	char strPathname[MAX_PATH];
	LPITEMIDLIST pidl;
	BROWSEINFO bi;

	// テキストボックスに入力されている親パスを得る
	GetDlgItemText(IDC_EDIT_DSTPATH, strPathname, MAX_PATH-1);

	// Win95 対策 （最後に \ が付いたフォルダ名は受け付けない）
	if(strlen(strPathname)>3)		// ルートフォルダと空白は除く
	{
		if(strPathname[strlen(strPathname)-1] == '\\')
			strPathname[strlen(strPathname)-1] = (char)NULL;
	}

	// BROWSEINFO 構造体の初期化
	ZeroMemory(&bi,sizeof(bi));
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
	bi.lpszTitle = (LPCSTR)"親フォルダの選択";
	bi.hwndOwner = m_hWnd;
	bi.lpfn = &myBrowseCallbackProc;	// 初期フォルダ設定のためコールバック関数設定
	bi.lParam = (LPARAM)strPathname;	// 初期フォルダをパラメータとして設定

	pidl = ::SHBrowseForFolder(&bi);
	if(pidl == NULL) return;			// キャンセルボタンが押された
	SHGetPathFromIDList(pidl, strPathname);

	////////////////////////
	// pidl を明示的に解放する
	////////////////////////
	IMalloc *imalloc;
	// Shellのメモリ管理オブジェクトを取得
	if( ::SHGetMalloc( &imalloc) != NOERROR) imalloc = NULL;
	// オブジェクト取得に成功した場合に開放する
	if( imalloc != NULL) imalloc->Free((void *)pidl); // ITEMIDLISTを開放

	// ルートフォルダの扱い。最後に \ がついているかどうか
	if(strPathname[strlen(strPathname)-1] != '\\')
		strcat(strPathname, "\\");

	// ファイル入力ボックスをアップデートする
	SetDlgItemText(IDC_EDIT_DSTPATH, strPathname);
	
}

// **********************************
// フォルダ選択 SDK ダイアログ ::SHBrowseForFolder 用の コールバック関数
// **********************************
int CALLBACK myBrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	// ダイアログが初期化されるとき （BFFM_INITIALIZED）
    if(uMsg == BFFM_INITIALIZED){
		// フォルダを選択する （BFFM_SETSELECTION）メッセージ
		if(lpData != NULL)
	        SendMessage(hwnd, BFFM_SETSELECTION, (WPARAM)TRUE, lpData);
    }
    return 0;
}


void CFileSequenceCutterDlg::OnBtnAbout() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString strTmp1, strTmp2;

	strTmp1.LoadString(STR_DLG_DLGTITLE);
	strTmp2.LoadString(STR_DLG_ABOUTBOX);

	MessageBox(strTmp2, strTmp1, MB_OK|MB_ICONINFORMATION);	
}

void CFileSequenceCutterDlg::OnBtnExec() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString strTmp1, strTmp2;
	int nKeyword;		// キーワードの数（バイト数）
	unsigned char strKeyword[256];	// 切り出し用キーワード
	int i, j, nTmpDat, nKwdMatch;
	int nFound;			// 見つかったキーワードの数

	long fi_marker_1, fi_marker_2;
	long fi_ptr_save;


	CString strFileSrc;
	CString strPathDst;
	CFile fFileSrc, fFileDst;
	CFileException fileException;


	// strtok (トークン切り出し) 専用の文字列宣言
	char str_ext_raw[1024];		// 切り出し元の文字列。切り出しにしたがって破壊される
	char str_delimit[] = ": ";	// 区切り文字 （コロン および 空白）
	char *str_strtok;			// 切り出された結果文字列

	char str_tmp[1024];

	GetDlgItemText(IDC_CMB_KEYWORD, strTmp1);

	strncpy(str_ext_raw, strTmp1, 1023);	// 破壊に備えてコピー

	nKeyword = 0;

	str_strtok = strtok(str_ext_raw, str_delimit);
	if(str_strtok != NULL)
	{
		strncpy(str_tmp, str_strtok, 1023);
		if(IsStrHexnum(str_tmp))
		{
			sscanf(str_tmp, "%x", &i);
			strKeyword[nKeyword] = (char)i;
			nKeyword++;
		}

		for(;;)
		{
			str_strtok = strtok(NULL, str_delimit);
			if(str_strtok == NULL) break;		// これ以上文字列が無い場合
			strncpy(str_tmp, str_strtok, 1023);
			if(IsStrHexnum(str_tmp))
			{
				sscanf(str_tmp, "%x", &i);
				strKeyword[nKeyword] = (char)i;
				nKeyword++;
			}
		}
	}

	strKeyword[nKeyword] = (char)0;


	if(nKeyword == 0)
	{	// キーワードが正しく入力されていない
		strTmp1.LoadString(STR_DLG_DLGTITLE);
		strTmp2.LoadString(STR_ERR_NOKEYWORD);

		MessageBox(strTmp2, strTmp1, MB_OK|MB_ICONINFORMATION);	

		return;
	}

	if(!GetDlgItemText(IDC_EDIT_SRCFILE, strFileSrc))
	{
		strTmp1.LoadString(STR_DLG_DLGTITLE);
		strTmp2.LoadString(STR_ERR_FILESRC_NOINPUT);

		MessageBox(strTmp2, strTmp1, MB_OK|MB_ICONINFORMATION);	

		return;
	}
	if(!GetDlgItemText(IDC_EDIT_DSTPATH, strPathDst))
	{
		strTmp1.LoadString(STR_DLG_DLGTITLE);
		strTmp2.LoadString(STR_ERR_PATHDST_NOINPUT);

		MessageBox(strTmp2, strTmp1, MB_OK|MB_ICONINFORMATION);	

		return;
	}

	// データファイルを開く
	if( (fi = fopen(strFileSrc, "rb")) == NULL)
	{
		strTmp1.LoadString(STR_DLG_DLGTITLE);
		strTmp2.LoadString(STR_ERR_OPEN_FILESRC);

		MessageBox(strTmp2, strTmp1, MB_OK|MB_ICONINFORMATION);	

		return;
	}

	fi_read_ptr = 0;		// 現在のファイルポインタ位置
	fi_cur_buf_addr = -1;	// 読み込みバッファの先頭アドレスを初期化
	nKwdMatch = 0;
	fi_marker_1 = -1;
	fi_marker_2 = -1;
	nFound = 0;

	for(;;)
	{
		for(;;)
		{
			j=0;
			nTmpDat = (int)fiReadChar();
			if(nTmpDat < 0) break;	// EOF
			if(nTmpDat == strKeyword[nKwdMatch])
			{
				fi_ptr_save = fi_read_ptr;
				for(j=1; j<=nKeyword-1; j++)
				{
					fi_read_ptr++;
					nKwdMatch++;
					nTmpDat = (int)fiReadChar();
					if(nTmpDat < 0) break;	// EOF
					if(nTmpDat != strKeyword[nKwdMatch]) break;	// マッチしない
				}
				fi_read_ptr = fi_ptr_save;
				nKwdMatch = 0;
			}

			if(nTmpDat<0) break;		// EOF
			if(j >= nKeyword) break;	// 見つけた
			fi_read_ptr++;
		}

		if(nTmpDat<0)
		{	// EOF
			fi_read_ptr--;	// ファイル末端
		}


		fi_marker_1 = fi_marker_2;
		fi_marker_2 = fi_read_ptr;

		if(fi_marker_1 >= 0)
		{
			nFound++;
			// ここで、ファイルの切り出し書き込み処理をする
			// fi_marker_1 ～ fi_marker_2 - 1
			if(!fiWriteFile(fi_marker_1, fi_marker_2-1, strPathDst, nFound))
			{	// ファイルの書き込みが出来ない
				break;
			}
		}

		if(nTmpDat<0) break;	// EOF

		fi_read_ptr++;

	}

	fclose(fi);
	
	strTmp1.Format("%d 個のファイルを切り出しました", nFound);
	MessageBox(strTmp1);

}

// 文字列が2桁または1桁の16進数だったら TRUE を返す
// 16進数なら 0x00 の形式で文字列を変換する
BOOL IsStrHexnum(char *buf)
{
	if(strlen(buf) == 4)
	{
		if(buf[0] == '0' && buf[1] == 'x')
		{
			// 0x00 の形式のとき
			if(((buf[2] >= '0' && buf[2] <= '9') || (buf[2] >= 'A' && buf[2] <= 'F') || (buf[2] >= 'a' && buf[2] <= 'f')) && ((buf[3] >= '0' && buf[3] <= '9') || (buf[3] >= 'A' && buf[3] <= 'F') || (buf[3] >= 'a' && buf[3] <= 'f')))
				return TRUE;
		}
	}
	if(strlen(buf) == 3)
	{
		if(buf[0] == '0' && buf[1] == 'x')
		{
			// 0x0 の形式のとき
			if((buf[2] >= '0' && buf[2] <= '9') || (buf[2] >= 'A' && buf[2] <= 'F') || (buf[2] >= 'a' && buf[2] <= 'f'))
				return TRUE;
		}
		else if(buf[2] == 'H' || buf[2] == 'h')
		{
			// 00H 形式のとき
			if(((buf[0] >= '0' && buf[0] <= '9') || (buf[0] >= 'A' && buf[0] <= 'F') || (buf[0] >= 'a' && buf[0] <= 'f')) && ((buf[1] >= '0' && buf[1] <= '9') || (buf[1] >= 'A' && buf[1] <= 'F') || (buf[1] >= 'a' && buf[1] <= 'f')))
			{
				// 0x00 形式に変換
				buf[4] = (char)0;
				buf[3] = buf[1];
				buf[2] = buf[0];
				buf[1] = 'x';
				buf[0] = '0';
				return TRUE;
			}
		}
	}
	if(strlen(buf) == 2)
	{
		// 00 の形式のとき
		if(((buf[0] >= '0' && buf[0] <= '9') || (buf[0] >= 'A' && buf[0] <= 'F') || (buf[0] >= 'a' && buf[0] <= 'f')) && ((buf[1] >= '0' && buf[1] <= '9') || (buf[1] >= 'A' && buf[1] <= 'F') || (buf[1] >= 'a' && buf[1] <= 'f')))
		{
			// 0x00 形式に変換
			buf[4] = (char)0;
			buf[3] = buf[1];
			buf[2] = buf[0];
			buf[1] = 'x';
			buf[0] = '0';
			return TRUE;
		}
		else if(buf[1] == 'H' || buf[1] == 'h')
		{
			// 0H 形式のとき
			if(((buf[0] >= '0' && buf[0] <= '9') || (buf[0] >= 'A' && buf[0] <= 'F') || (buf[0] >= 'a' && buf[0] <= 'f')))
			{
				// 0x00 形式に変換
				buf[3] = (char)0;
				buf[2] = buf[0];
				buf[1] = 'x';
				buf[0] = '0';
				return TRUE;
			}
		}
	}
	if(strlen(buf) == 1)
	{
		// 0 形式のとき
		if(((buf[0] >= '0' && buf[0] <= '9') || (buf[0] >= 'A' && buf[0] <= 'F') || (buf[0] >= 'a' && buf[0] <= 'f')))
		{
			// 0x00 形式に変換
			buf[3] = (char)0;
			buf[2] = buf[0];
			buf[1] = 'x';
			buf[0] = '0';
			return TRUE;
		}
	}

	return FALSE;
}

int CFileSequenceCutterDlg::fiReadChar()
{
	int temp_addr;

	if((fi_cur_buf_addr < 0) || !((fi_cur_buf_addr <= fi_read_ptr) && (fi_read_ptr < fi_cur_buf_addr+FI_BUFFER_SIZE)))
	{	// ファイルの読み込み
		fi_cur_buf_addr = (fi_read_ptr / FI_BUFFER_SIZE)*FI_BUFFER_SIZE;	// 先頭アドレス
		if(fseek(fi, fi_cur_buf_addr, SEEK_SET))
			return FALSE;		// シーク失敗
		fi_cur_buf_size = fread(fi_buf, 1, FI_BUFFER_SIZE, fi);
	}

	temp_addr = fi_read_ptr - fi_cur_buf_addr;
	if(temp_addr > fi_cur_buf_size) return -1;

	return (int)fi_buf[temp_addr];

}

BOOL CFileSequenceCutterDlg::fiWriteFile(long nStart, long nEnd, CString strFpath, int nSeqNo)
{
	long nRead, nLength, li;
	int i;
	CString strFfullpath;
	CFileStatus Fstatus;

	FILE *fo;

	if(nStart >= nEnd) return FALSE;

	fo = NULL;

	for(i=0; i<1024; i++)
	{
		strFfullpath.Format("%sdat%05d.dat", strFpath, nSeqNo+i);

		if(CFile::GetStatus(strFfullpath, Fstatus))		// ファイルが存在する
			continue;

		// データファイルを開く
		if( (fo = fopen(strFfullpath, "wb")) != NULL)
			break;	// ファイルが開けた場合はループを出る
	}

	if(fo == NULL) return FALSE;	// ファイルが作成できなかった

	fi_cur_buf_addr = -1;		// 読み込みバッファ破壊

	fseek(fi, nStart, SEEK_SET);
	for(li=0; ; li++)
	{
		nLength = nEnd - nStart + 1;
		if(nLength > FI_BUFFER_SIZE) nLength = FI_BUFFER_SIZE;

		nRead = fread(fi_buf, 1, nLength, fi);
	
		if(nRead <= 0) break;
		if(fwrite(fi_buf, 1, nRead, fo) != (size_t)nRead) break;

		nStart = nStart + FI_BUFFER_SIZE;
		if(nStart > nEnd) break;		// コピー完了

	}

	fclose(fo);

	return TRUE;
}
