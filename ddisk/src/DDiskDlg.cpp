// ************************************************************
// メイン・ダイアログ CDDiskDlg
// ************************************************************

#include "stdafx.h"
#include "DDisk.h"
#include "DDiskDlg.h"
#include "DDiskConfig.h"
#include "DiskCore.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDDiskDlg ダイアログ

CDDiskDlg::CDDiskDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDDiskDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDDiskDlg)
	m_sect = 0;
	m_size = 0;
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	theApp = (CDDiskApp *)AfxGetApp();

}

void CDDiskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDDiskDlg)
	DDX_Control(pDX, IDC_COMBO_DISK, m_cmb_disk);
	DDX_Text(pDX, IDC_EDIT_SECT, m_sect);
	DDX_Text(pDX, IDC_EDIT_SIZE, m_size);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDDiskDlg, CDialog)
	//{{AFX_MSG_MAP(CDDiskDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_READ, OnBtnRead)
	ON_BN_CLICKED(IDC_BTN_DPB, OnBtnDpb)
	ON_BN_CLICKED(IDC_BTN_CONFIG, OnBtnConfig)
	ON_WM_VSCROLL()
	ON_EN_KILLFOCUS(IDC_EDIT_SIZE, OnKillfocusEditSize)
	ON_BN_CLICKED(IDC_BTN_BROWSE, OnBtnBrowse)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTN_WRITE, OnBtnWrite)
	ON_BN_CLICKED(IDC_BTN_EDIT, OnBtnEdit)
	ON_BN_CLICKED(IDC_BTN_HELP, OnBtnHelp)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDDiskDlg メッセージ ハンドラ

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CDDiskDlg::OnPaint() 
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
HCURSOR CDDiskDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// ************************************************************
// ダイアログ初期化時の初期値設定
// ************************************************************
BOOL CDDiskDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	
	// TODO: 特別な初期化を行う時はこの場所に追加してください。
	// ドライブのコンボボックスの初期設定
	int i;
	
	for(i=1;i<=26;i++)
	{	// Z までのドライブを設定
		sprintf(m_buf, "%2d (%c:)", i, 0x40+i);
		m_cmb_disk.AddString(m_buf);
	}
	m_cmb_disk.SetCurSel(0); // 初期設定は A:

	// セクタを0とする
	SetDlgItemInt(IDC_EDIT_SECT, 0);

	// セクタサイズを1とする
	SetDlgItemInt(IDC_EDIT_SIZE, 1);

	// 書き込みﾓｰﾄﾞをノーマルデータとする
	CheckRadioButton(IDC_RADIO_TYPE, IDC_RADIO_TYPE4, IDC_RADIO_TYPE);

	
	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

// ************************************************************
// セクターまたはセクター数のスクロールバーが押された場合の処理
//
// CScrollBar は、何にもしてくれないので、CWndがスクロールバーが押されたことを検知して
// 処理をしないといけない。
// ************************************************************
void CDDiskDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	DWORD n_sect;
	WORD n_size;
	
	n_sect = GetDlgItemInt(IDC_EDIT_SECT);
	n_size = GetDlgItemInt(IDC_EDIT_SIZE);

	if(pScrollBar->GetDlgCtrlID() == IDC_SCR_SECT)
	{
		switch(nSBCode)
		{
			case SB_LINEUP :
				n_sect++; break;
			case SB_LINEDOWN :
				if(n_sect>0) n_sect--;
				break;
			default : break;
		}
		SetDlgItemInt(IDC_EDIT_SECT, n_sect);
	}
	else if(pScrollBar->GetDlgCtrlID() == IDC_SCR_SIZE)
	{
		switch(nSBCode)
		{
			case SB_LINEUP :
				n_size++; break;
			case SB_LINEDOWN :
				if(n_size>1) n_size--;
				break;
			default : break;
		}
		SetDlgItemInt(IDC_EDIT_SIZE, n_size);
	}

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

// ************************************************************
// 「表示(Read)」ボタンが押された場合
// 論理ディスクを読み込み、プレビューエリアに表示する
// ************************************************************
void CDDiskDlg::OnBtnRead() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString tmpStr, tmpStr2;	// ストリング リソース 読み込み用
	CString str="";				// ダイアログ内 情報ウインドウ用

	HANDLE hdev;
	char buf2[65], buf3[18];
	unsigned int i,j,k;
	DOSDPB dpb;
	int b_DPB_suc=0, b_Read_suc=0; 

	BYTE n_drive=0;
	DWORD n_sect=0;
	WORD n_size=1;
	n_drive = m_cmb_disk.GetCurSel() + 1;	// A=1 B=2 となるように、1足す
	n_sect = GetDlgItemInt(IDC_EDIT_SECT);
	n_size = GetDlgItemInt(IDC_EDIT_SIZE);
	if(n_size < 1) n_size = 1;

	// DeviceIoControl 用の virtual device driver を開く
	hdev = CreateFile("\\\\.\\VWIN32", 0, 0, NULL, 0, 0, NULL);
	if(hdev == INVALID_HANDLE_VALUE)
	{	// ハンドルが開けなかった場合
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_VWIN32);
		MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
		return ;
	}

	// DPB を読み込む（ディスクの基本情報を収集する）
	if(!ReadDPB(hdev, n_drive, &dpb))
	{	// DPB が開けなかったとき
		CloseHandle(hdev);
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_DPBREAD);
		MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
		return;
	}
	else
	{	// DPB が読み込めた場合
		sprintf(m_buf, "Drive = %u\r\nTotal sectors = %u\r\nBytes per sector = %u\r\n",
			n_drive, dpb.cTotalSectors, dpb.cbSec);
		str += m_buf;
	}

	// 指定のセクター数を処理する（読み込み）
	for(i=0; i<n_size; i++)
	{
		sprintf(m_buf, "\r\n====== Sector %u ======\r\n", n_sect+i);
		str += m_buf;

		// ********* 直接読み込み **********
		if(theApp->m_inttype == 2)	// INT 21H FUNC 7305H Win98
			b_Read_suc = ReadLogicalSectors(hdev, n_drive, n_sect+i, 1, (unsigned char*)&m_mainbuf);
		else if(theApp->m_inttype == 1)	// INT 25H Win95
			b_Read_suc = ReadLogicalSectors25(hdev, n_drive, n_sect+i, 1, (unsigned char*)&m_mainbuf);
		if(!b_Read_suc)
		{
			str += "====== Read Fail ======\r\n";
			continue ;
		}

		if(theApp->m_viewtype == 0)
		{	// テキストタイプでの表示
			for(int l=0;l<=64;l++) buf2[l] = (char)0; // バッファのクリア
			for(j=0,k=0; j<dpb.cbSec; j++,k++)
			{
				// buf2 に一行分（64文字)ためてから出力する
				if(k>63)
				{	// 64文字を超える場合は、次の行へ
					k=0;
					str += buf2;
					for(int l=0;l<=64;l++) buf2[l] = (char)0; // バッファのクリア
					str += "\r\n";
				}
				if(m_mainbuf[j]>=0x20 && m_mainbuf[j]<=0x7e) buf2[k] = m_mainbuf[j];
				else buf2[k] = '.';
			}
			str += buf2;
			str += "\r\n";
		}
		else if(theApp->m_viewtype == 1)
		{	// バイナリ・テキストタイプでの表示
			for(int l=0;l<=64;l++) buf2[l] = (char)0; // バッファのクリア
			for(l=0;l<=16;l++) buf3[l] = (char)0;
			for(j=0,k=0; j<dpb.cbSec; j++,k++)
			{
				if(k>15)
				{
					k=0;
					str += buf2;
					str += buf3;
					for(int l=0;l<=64;l++) buf2[l] = (char)0; // バッファのクリア
					for(l=0;l<=16;l++) buf3[l] = (char)0;
					str += "\r\n";
				}
				sprintf(buf2+3*k, "%02X ", (unsigned char)m_mainbuf[j]);
				if(m_mainbuf[j]>=0x20 && m_mainbuf[j]<=0x7e) buf3[k] = m_mainbuf[j];
				else buf3[k] = '.';
			}
			str += buf2;
			str += buf3;
			str += "\r\n";
		}

		if(str.GetLength() > 31000)
		{
			tmpStr2.LoadString(IDS_MES_NOTPOS_30LINE);
			str += tmpStr2;
			break;
		}
	}	
	CloseHandle(hdev);

	SetDlgItemText(IDC_EDIT_PREVIEW, str);

	return;
}


// ************************************************************
// 「DPB」ボタンが押されたとき
// DPB を読み込んでプレビューエリアに表示する
// ************************************************************
void CDDiskDlg::OnBtnDpb() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString tmpStr, tmpStr2;	// ストリング リソース 読み込み用
	CString str="";				// ダイアログ内 情報ウインドウ用

	HANDLE hdev;
	DOSDPB dpb;
	BYTE n_drive=0;

	n_drive = m_cmb_disk.GetCurSel() + 1;	// A=1 B=2 となるように、1足す
	hdev = CreateFile("\\\\.\\VWIN32", 0, 0, NULL, 0, 0, NULL);
	if(hdev == INVALID_HANDLE_VALUE)
	{	// ハンドルが開けなかった場合
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_VWIN32);
		MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
		return ;
	}
	if(!ReadDPB(hdev, n_drive, &dpb))
	{	// DPB が開けなかったとき
		CloseHandle(hdev);
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_DPBREAD);
		MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
		return;
	}
	CloseHandle(hdev);


	// ドライブ番号
	sprintf(m_buf, "Drive No = %u (%c:)\r\n", n_drive, 0x40+n_drive);
	str = m_buf;

	// メディアの種類
	str += "Media Type = ";
	switch(dpb.devType)
	{
		case 0 : str += "0 (5.25 inch 360 KBytes Floppy Disk)\r\n"; break;
		case 1 : str += "1 (5.25 inch 1.2 MBytes Floppy Disk)\r\n"; break;
		case 2 : str += "2 (3.5 inch 720 KBytes Floppy Disk)\r\n"; break;
		case 3 : str += "3 (8 inch Low-density Floppy Disk)\r\n"; break;
		case 4 : str += "4 (8 inch High-density Floppy Disk)\r\n"; break;
		case 5 : str += "5 (Hard Disk)\r\n"; break;
		case 6 : str += "6 (Tape Drive)\r\n"; break;
		case 7 : str += "7 (3.5 inch 1.44 MBytes Floppy Disk)\r\n"; break;
		case 8 : str += "8 (Optical Disk)\r\n"; break;
		case 9 : str += "7 (3.5 inch 2.88 MBytes Floppy Disk)\r\n"; break;
		default :
			sprintf(m_buf, "%lu (Unknown Type Disk)\r\n", dpb.devType);
			str += m_buf;
			break;
	}

	// Removable か Fixed か
	if(dpb.devAttr & 0x01)
		sprintf(m_buf, "Device Attribute = %lu (Fixed Disk)\r\n", dpb.devAttr);
	else if(dpb.devAttr & 0x02)
		sprintf(m_buf, "Device Attribute = %lu (Removable Disk)\r\n", dpb.devAttr);
	else sprintf(m_buf, "Device Attribute = %lu (Unknown Type)\r\n");
	str += m_buf;

	sprintf(m_buf, "Media Type = %lu\r\n", dpb.bMedia);
	str += m_buf;
	sprintf(m_buf, "Cylinder = %lu\r\nBytes per sector = %lu\r\n", dpb.cCyl, dpb.cbSec);
	str += m_buf;
	sprintf(m_buf, "Sectors per cluster = %lu\r\nSectors per track = %lu\r\n", dpb.secPerClus, dpb.secPerTrack);
	str += m_buf;
	sprintf(m_buf, "Heads = %lu\r\nTotal sectors = %lu\r\n", dpb.cHead, dpb.cTotalSectors);
	str += m_buf;
	sprintf(m_buf, "FATs = %lu\r\nSectors per FAT = %lu\r\n", dpb.cFAT, dpb.secPerFAT);
	str += m_buf;

	sprintf(m_buf, "\r\n* Total size = %lu Bytes (%.2lf MBytes)\r\n", dpb.cTotalSectors*dpb.cbSec,
					(double)dpb.cTotalSectors*dpb.cbSec/1024/1000);
	str += m_buf;

	SetDlgItemText(IDC_EDIT_PREVIEW, str);

}

// ************************************************************
// 「設定」ダイアログを表示する
// ************************************************************
void CDDiskDlg::OnBtnConfig() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CDDiskConfig dlg;
	OSVERSIONINFO ver;

	// OSのバージョン情報を表示する

	ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	::GetVersionEx((LPOSVERSIONINFO)&ver);

	dlg.m_text_winver = "Windows ";

	switch(ver.dwPlatformId)
	{
		case VER_PLATFORM_WIN32s :
			dlg.m_text_winver += "3.1 Win32s"; break;
		case VER_PLATFORM_WIN32_WINDOWS :
			if(ver.dwMinorVersion == 0)
			{
				if(ver.dwBuildNumber&0xffff < 1000)
					dlg.m_text_winver += "95";
				else dlg.m_text_winver += "95 OSR2";
				break;
			}
			else
			{
				if(ver.dwBuildNumber&0xffff < 2000)
					dlg.m_text_winver += "98";
				else dlg.m_text_winver += "98SE";
				break;
			}
		case VER_PLATFORM_WIN32_NT :
			dlg.m_text_winver += "NT, 2000"; break;
		default : dlg.m_text_winver += "Unknown"; break;
	}

	sprintf(m_buf, "  Version %Lu.%Lu.", ver.dwMajorVersion, ver.dwMinorVersion);
	dlg.m_text_winver += m_buf;

	switch(ver.dwPlatformId)
	{
		case VER_PLATFORM_WIN32_WINDOWS :
			sprintf(m_buf, "%Lu", ver.dwBuildNumber&0xffff);
			break;
		default :
			sprintf(m_buf, "%Lu", ver.dwBuildNumber);
			break;
	}
	dlg.m_text_winver += m_buf;

	sprintf(m_buf, " %s", ver.szCSDVersion);
	dlg.m_text_winver += m_buf;


	// 初期ボタンの設定
	dlg.m_func = theApp->m_inttype;
	dlg.m_view = theApp->m_viewtype;
	dlg.m_edit_editor = theApp->m_binedit;
	
	if(dlg.DoModal() == IDOK)
	{
		theApp->m_inttype = dlg.m_func;
		theApp->m_viewtype = dlg.m_view;
		theApp->m_binedit = dlg.m_edit_editor;
	}
}

// ************************************************************
// 読み込みセクター数の変更を監視し
// 0 以下の設定を 1 に書き換える
// ************************************************************
void CDDiskDlg::OnKillfocusEditSize() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	if(GetDlgItemInt(IDC_EDIT_SIZE) < 1)
		SetDlgItemInt(IDC_EDIT_SIZE, 1);
}

// ************************************************************
// ファイル・パスの設定ダイアログを表示する
// (読み込み・書き出しファイル名の設定）
// ************************************************************
void CDDiskDlg::OnBtnBrowse() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	GetDlgItemText(IDC_EDIT_FNAME, m_buf, 125);
	CFileDialog dlg(TRUE, NULL, m_buf, OFN_CREATEPROMPT|OFN_EXPLORER|OFN_HIDEREADONLY,
				"Binary File (*.BIN)|*.bin|Data File (*.DAT)|*.dat|All FIles|*.*||");
	if(dlg.DoModal()==TRUE)
		SetDlgItemText(IDC_EDIT_FNAME, dlg.GetPathName());
}

// ************************************************************
// 「保存」ボタンを押したとき
// 論理ディスクの内容をデータファイルに書き込む
// ************************************************************
void CDDiskDlg::OnBtnSave() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString tmpStr, tmpStr2;	// ストリング リソース 読み込み用
	CString str="";				// ダイアログ内 情報ウインドウ用

	GetDlgItemText(IDC_EDIT_FNAME, m_buf, 125);
	if(!strlen(m_buf))
	{	// ファイル名が指定されていないとき
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_NOFILESEL);
		MessageBox(tmpStr2, tmpStr, MB_ICONWARNING|MB_OK);
		return;
	}
	HANDLE hdev;
	unsigned int i;
	DOSDPB dpb;
	int b_DPB_suc=0, b_Read_suc=0; 

	BYTE n_drive=0;
	DWORD n_sect=0;
	WORD n_size=1;
	n_drive = m_cmb_disk.GetCurSel() + 1;	// A=1 B=2 となるように、1足す
	n_sect = GetDlgItemInt(IDC_EDIT_SECT);
	n_size = GetDlgItemInt(IDC_EDIT_SIZE);
	if(n_size < 1) n_size = 1;

	// DeviceIoControl 用の virtual device driver を開く
	hdev = CreateFile("\\\\.\\VWIN32", 0, 0, NULL, 0, 0, NULL);
	if(hdev == INVALID_HANDLE_VALUE)
	{	// ハンドルが開けなかった場合
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_VWIN32);
		MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
		return ;
	}

	// DPB を読み込む（ディスクの基本情報を収集する）
	b_DPB_suc = ReadDPB(hdev, n_drive, &dpb);
	if(!b_DPB_suc)
	{	// DPB が開けなかったとき
		CloseHandle(hdev);
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_DPBREAD);
		MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
		return;
	}

	CFile fi;
	CFileException fi_except;

	if(!fi.Open(m_buf, CFile::modeCreate|CFile::modeWrite|CFile::shareDenyRead,
		&fi_except))
	{	// ファイルが開けなかったとき
		CloseHandle(hdev);
		if(fi_except.m_cause == CFileException::badPath)
			tmpStr2.LoadString(IDS_ERR_FILEOPENPATH);			// 不正なパス
		else if(fi_except.m_cause == CFileException::accessDenied)
			tmpStr2.LoadString(IDS_ERR_FILEACCESS);				// アクセス許可違反
		else tmpStr2.LoadString(IDS_ERR_FILEOPEN);				// その他のエラー
		MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
		return ;
	}

	str = "";
	for(i=0; i<n_size; i++)
	{
		// ********* 直接読み込み **********
		if(theApp->m_inttype == 2)	// INT 21H FUNC 7305H Win98
			b_Read_suc = ReadLogicalSectors(hdev, n_drive, n_sect+i, 1, (unsigned char*)&m_mainbuf);
		else if(theApp->m_inttype == 1)	// INT 25H Win95
			b_Read_suc = ReadLogicalSectors25(hdev, n_drive, n_sect+i, 1, (unsigned char*)&m_mainbuf);
		if(b_Read_suc)
		{	// 論理ディスク読み込みが成功したら、ファイルに書き込む
			try{
				fi.Write(m_mainbuf, dpb.cbSec);
			}
			catch(CFileException *e){
				// ファイルの書き込みが失敗した
				if(e->m_cause == CFileException::accessDenied)
					tmpStr2.LoadString(IDS_ERR_FILEACCESS);			// アクセス許可違反
				else if(e->m_cause == CFileException::diskFull)
					tmpStr2.LoadString(IDS_ERR_FILEFULL);			// Disk Full
				else tmpStr2.LoadString(IDS_ERR_FILEOTHER);			// その他のエラー
				MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
				continue;
			}
			sprintf(m_buf, "Save success Drive %d(%c:) Sector %d\r\n\r\n",
						n_drive, 0x40+n_drive, n_sect+i);
			str += m_buf;
		}
		else
		{	// 論理ディスク読み込みが失敗
			tmpStr.LoadString(IDS_APPNAME);
			tmpStr2.LoadString(IDS_ERR_DRIVEREAD);
			MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
			continue;
		}
	}

	CloseHandle(hdev);
	SetDlgItemText(IDC_EDIT_PREVIEW, str);

	try{
		fi.Close();
	}
	catch(CFileException *e){
		// ファイルを閉じるのに失敗した場合
		long dummy = e->m_lOsError;	// 「e が一回も使われていない」警告を回避するためのダミー
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_FILECLOSE);
		MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
	}
	return;
}

// ************************************************************
// 「書き込み」ボタンを押したとき
// データファイルの内容を論理ディスクに書き込む
// ************************************************************
void CDDiskDlg::OnBtnWrite() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString tmpStr, tmpStr2;	// ストリング リソース 読み込み用
	CString str="";				// ダイアログ内 情報ウインドウ用

	GetDlgItemText(IDC_EDIT_FNAME, m_buf, 125);
	if(!strlen(m_buf))
	{	// ファイル名が指定されていないとき
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_NOFILESEL);
		MessageBox(tmpStr2, tmpStr, MB_ICONWARNING|MB_OK);
		return;
	}

	HANDLE hdev;	// VWIN32 ハンドル
	unsigned int i, j;
	DOSDPB dpb;
	int b_Read_suc;
	UINT _write_type;

	BYTE n_drive=0;
	DWORD n_sect=0;
	WORD n_size=1;
	n_drive = m_cmb_disk.GetCurSel() + 1;	// A=1 B=2 となるように、1足す
	n_sect = GetDlgItemInt(IDC_EDIT_SECT);
	n_size = GetDlgItemInt(IDC_EDIT_SIZE);
	if(n_size < 1) n_size = 1;

	// DeviceIoControl 用の virtual device driver を開く
	hdev = CreateFile("\\\\.\\VWIN32", 0, 0, NULL, 0, 0, NULL);
	if(hdev == INVALID_HANDLE_VALUE)
	{	// ハンドルが開けなかった場合
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_VWIN32);
		MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
		return ;
	}

	// DPB を読み込む（ディスクの基本情報を収集する）
	if(!ReadDPB(hdev, n_drive, &dpb))
	{	// DPB が開けなかったとき
		CloseHandle(hdev);
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_DPBREAD);
		MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
		return;
	}

	// 指定のセクター数を処理する（読み込み）
	CFile fi;
	CFileException fi_except;

	if(!fi.Open(m_buf, CFile::modeRead|CFile::shareExclusive,
		&fi_except))
	{	// ファイルが開けなかったとき
		CloseHandle(hdev);
		tmpStr.LoadString(IDS_APPNAME);
		if(fi_except.m_cause == CFileException::badPath)
			tmpStr2.LoadString(IDS_ERR_FILEOPENPATH);			// 不正なパス
		else if(fi_except.m_cause == CFileException::accessDenied)
			tmpStr2.LoadString(IDS_ERR_FILEACCESS);				// アクセス許可違反
		else tmpStr2.LoadString(IDS_ERR_FILEOPEN);				// その他のエラー
		MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
		return ;
	}

	// この文章では m_buf があふれるので、 m_mainbuf を使用する
	tmpStr2.LoadString(IDS_ASK_WRITE_TO);
	sprintf(m_mainbuf, tmpStr2,
			n_drive, 0x40+n_drive, n_sect, n_drive, 0x40+n_drive, n_sect,
			n_size, n_size * dpb.cbSec);
	tmpStr.LoadString(IDS_APPNAME);
	if(MessageBox(m_mainbuf, tmpStr, MB_ICONQUESTION|MB_YESNO) != IDYES)
	{
		CloseHandle(hdev);
		return;
	}

	if(!LockLogicalDrive(hdev, n_drive, 1, 2))	// Level 1のロック
	{	// ロックに失敗したとき
		CloseHandle(hdev);
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_LOCK);
		MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
		return;
	}

	i=GetCheckedRadioButton(IDC_RADIO_TYPE, IDC_RADIO_TYPE4);
	switch(i)
	{	// INT 21H Func 7305のときの書き込みﾓｰﾄﾞを指定する
		case IDC_RADIO_TYPE : _write_type = _WRITETYPE_NORMAL; break;
		case IDC_RADIO_TYPE2 : _write_type = _WRITETYPE_FAT; break;
		case IDC_RADIO_TYPE3 : _write_type = _WRITETYPE_ROOT; break;
		default : _write_type = _WRITETYPE_OTHER; break;
	}

	str = "";
	for(i=0; i<n_size; i++)
	{
		// ファイルの読み込み
		try{
			j = fi.Read(&m_mainbuf, dpb.cbSec);
		}
		catch(CFileException *e){
			// ファイルの読み込みに失敗した
			tmpStr.LoadString(IDS_APPNAME);
			if(e->m_cause == CFileException::accessDenied)
				tmpStr2.LoadString(IDS_ERR_FILEACCESS);			// アクセス許可違反
			else if(e->m_cause == CFileException::endOfFile)
				tmpStr2.LoadString(IDS_ERR_FILEEOF);			// EOF
			else tmpStr2.LoadString(IDS_ERR_FILEOTHER);			// other
			MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
			i = n_size;		// ループを終わらせるための操作
			continue;		// 実際はループ終了
		}

		if(j < dpb.cbSec)
		{	// 読み込みバイト数が足りないとき
			tmpStr.LoadString(IDS_APPNAME);
			tmpStr2.LoadString(IDS_ERR_FILESHORT);
			if(MessageBox(tmpStr2, tmpStr, MB_ICONQUESTION|MB_YESNO) != IDYES)
			{
				i = n_size;		// ループを終わらせるための操作
				continue;		// 実際はループ終了
			}
		}

		// ********* 直接書き込み **********
		if(theApp->m_inttype == 2)	// INT 21H FUNC 7305H Win98
			b_Read_suc = WriteLogicalSectors(hdev, n_drive, n_sect+i, 1, (unsigned char *)&m_mainbuf, _write_type);
		else if(theApp->m_inttype == 1)	// INT 26H Win95
			b_Read_suc = WriteLogicalSectors26(hdev, n_drive, n_sect+i, 1, (unsigned char *)&m_mainbuf);
		if(b_Read_suc)
		{	// 論理ディスク書き込みが成功したら、メッセージ表示
			sprintf(m_buf, "Write success Drive %d(%c:) Sector %d\r\n\r\n",
						n_drive, 0x40+n_drive, n_sect+i);
			str += m_buf;
		}
		else
		{	// 論理ディスク書き込みが失敗
			tmpStr.LoadString(IDS_APPNAME);
			tmpStr2.LoadString(IDS_ERR_DRIVEWRITE);
			MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
			continue;
		}
	}

	if(!UnLockLogicalDrive(hdev, n_drive))	// Level 1のロック解除
	{	// ロック解除に失敗したとき
		CloseHandle(hdev);
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_LOCK);
		MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
		return;
	}

	CloseHandle(hdev);

	SetDlgItemText(IDC_EDIT_PREVIEW, str);

	try{
		fi.Close();
	}
	catch(CFileException *e){
		// ファイルを閉じるのに失敗した場合
		long dummy = e->m_lOsError;	// 「e が一回も使われていない」警告を回避するためのダミー
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_FILECLOSE);
		MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
	}
	return;
	
}

// ************************************************************
// 「編集」ボタンを押したとき
// バイナリー エディターを起動する
// ************************************************************
#include <process.h>
void CDDiskDlg::OnBtnEdit() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString tmpStr, tmpStr2;	// ストリング リソース 読み込み用

	GetDlgItemText(IDC_EDIT_FNAME, m_buf, 125);
	if(!strlen(m_buf))
	{	// ファイル名が指定されていないとき
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_NOFILESEL);
		MessageBox(tmpStr2, tmpStr, MB_ICONWARNING|MB_OK);
		return;
	}

	if(theApp->m_binedit == "")
	{	// バイナリー エディター が指定されていないとき
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_NOBINEDIT);
		MessageBox(tmpStr2, tmpStr, MB_ICONWARNING|MB_OK);
		return;
	}

	// ロングファイル名に対応するために " .... " で囲む処理
	CString buf;
	buf = "\"";
	buf += m_buf;
	buf += "\"";
	if(_spawnl(_P_NOWAIT, theApp->m_binedit, theApp->m_binedit, buf, NULL) == -1)
	{	// バイナリーエディターの起動に失敗したとき
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_BINEXEC);
		MessageBox(tmpStr2, tmpStr, MB_OK|MB_ICONSTOP);
	}

	return;
}

// ************************************************************
// ヘルプの表示
// ************************************************************
void CDDiskDlg::OnBtnHelp() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	theApp->WinHelp(0);		// DDisk.hm の値
}

// ************************************************************
// ヘルプの表示 (F1 キー対応)
// ************************************************************
BOOL CDDiskDlg::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください

	theApp->WinHelp(0);		// DDisk.hm の値
	return 0;
}

// ************************************************************
// EOF
