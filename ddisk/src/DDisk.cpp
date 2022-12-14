// DDisk.cpp : アプリケーション用クラスの定義を行います。
//

#include "stdafx.h"
#include "DDisk.h"
#include "DDiskDlg.h"
#include "DlgInstall.h"
#include "InstFunc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDDiskApp

BEGIN_MESSAGE_MAP(CDDiskApp, CWinApp)
	//{{AFX_MSG_MAP(CDDiskApp)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDDiskApp クラスの構築

CDDiskApp::CDDiskApp()
{
	// TODO: この位置に構築用のコードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CDDiskApp オブジェクト

CDDiskApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDDiskApp クラスの初期化

BOOL CDDiskApp::InitInstance()
{
	// 標準的な初期化処理
	// もしこれらの機能を使用せず、実行ファイルのサイズを小さくしたけ
	//  れば以下の特定の初期化ルーチンの中から不必要なものを削除して
	//  ください。

	// レジストリの指定
	// リソースでAFX_IDS_APP_TITLEにアプリケーション名を設定すること 
	// m_pszAppName = "compdel" としてはいけない！ ASSERTION エラーとなる
	SetRegistryKey((LPCTSTR)"hi soft");

	LoadStdProfileSettings(0);	// MRUリスト管理(0:しない)


#ifdef _AFXDLL
	Enable3dControls();			// 共有 DLL 内で MFC を使う場合はここをコールしてください。
#else
	Enable3dControlsStatic();	// MFC と静的にリンクする場合はここをコールしてください。
#endif

	CString tmpStr, tmpStr2;	// ストリング リソース 読み込み用

	// コマンドラインの解析
	if(!strcmpi(m_lpCmdLine, "/delete"))
	{	// アンインストール
		UninstallSeq();
		return FALSE;
	}
	else if(m_lpCmdLine[0] != NULL)
	{	// 無効なパラメーターが指定された場合、パラメーターリストを表示する
		tmpStr.LoadString(IDS_ERR_PARAM);
		tmpStr2.LoadString(IDS_APPNAME);
		::MessageBox(NULL, tmpStr, tmpStr2, MB_OK|MB_ICONINFORMATION|MB_APPLMODAL);
		return FALSE;
	}

	if(!::ChkHkcuInstReg())
		if(!InstallSeq())return FALSE;

	RegReadAll();


	CDDiskDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ダイアログが <OK> で消された時のコードを
		//       記述してください。
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ダイアログが <ｷｬﾝｾﾙ> で消された時のコードを
		//       記述してください。
	}

	RegWriteAll();

	// ダイアログが閉じられてからアプリケーションのメッセージ ポンプを開始するよりは、
	// アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}

// ************************************************************
// レジストリ情報の読み込み
// ************************************************************
void CDDiskApp::RegReadAll()
{
	m_inttype = GetProfileInt("Settings","INT_type",2);
	m_viewtype = GetProfileInt("Settings","VIEW_type",0);
	m_binedit = GetProfileString("Settings","BIN_EDIT","");
}

// ************************************************************
// レジストリへ保存
// ************************************************************
void CDDiskApp::RegWriteAll()
{
	if(m_inttype != (int)GetProfileInt("Settings","INT_type",2))
		WriteProfileInt("Settings","INT_type",m_inttype);
	if(m_viewtype != (int)GetProfileInt("Settings","VIEW_type",0))
		WriteProfileInt("Settings","VIEW_type",m_viewtype);
	if(m_binedit != GetProfileString("Settings","BIN_EDIT",""))
		WriteProfileString("Settings","BIN_EDIT",m_binedit);
}


// ************************************************************
// インストーラ
// ************************************************************
BOOL CDDiskApp::InstallSeq()
{
	CDlgInstall dlg;
	OSVERSIONINFO ver;

	// 初期ボタンの設定
	dlg.m_func = 2;		// 標準は Win98 用の割り込みを選択
	dlg.m_uninst = TRUE;
	dlg.m_start = TRUE;
	

	// OSのバージョン情報を表示する

	ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	::GetVersionEx((LPOSVERSIONINFO)&ver);

	dlg.m_text_winver = "Windows ";

	switch(ver.dwPlatformId)
	{
		case VER_PLATFORM_WIN32s :
				dlg.m_text_winver += "3.1 Win32s";
				dlg.m_warning.LoadString(IDS_WARNING_BADWIN);
				break;
		case VER_PLATFORM_WIN32_WINDOWS :
			if(ver.dwMinorVersion == 0)
			{
				if((ver.dwBuildNumber&0xffff) < 1000)
				{
					dlg.m_text_winver += "95";
					dlg.m_func = 1;		// INT 25H Win95 のボタンを選択
				}
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
			dlg.m_text_winver += "NT, 2000";
			dlg.m_warning.LoadString(IDS_WARNING_BADWIN);
			break;
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

	if(dlg.DoModal() != IDOK) return FALSE;		// ｷｬﾝｾﾙボタンが押されたら 何もしない

	// オプションの設定
	m_inttype = dlg.m_func;
	m_viewtype = 0;
	m_binedit = "";

	RegWriteAll();	// レジストリに書き込む

	// インストールフラグの書き込み
	::MkHkcuInstReg();
	
	// アンインストール情報について
	if(dlg.m_uninst) ::MkUninstMnu();

	// スタートメニューに登録する処理
	if(dlg.m_start) ::MkProgramsMnu();

	return TRUE;
}


// ************************************************************
// アンインストーラ
// ************************************************************
void CDDiskApp::UninstallSeq()
{
	CString tmpStr, tmpStr2;	// ストリング リソース 読み込み用
	
	tmpStr.LoadString(IDS_APPNAME);
	tmpStr2.LoadString(IDS_Q_UNINST);
	if(::MessageBox(NULL, tmpStr2, tmpStr, MB_ICONQUESTION|MB_YESNO|MB_SYSTEMMODAL) != IDYES)
		return;

	// レジストリの設定情報を消去 現在のユーザー情報から削除する
	::RmUserReg();

	// スタートメニューの設定アイコンを抹殺
	::RmProgramsMnu();

	// アンインストールアイコンの削除
	::RmUninstMnu();

	// インストールフラグの削除
	::RmHkcuInstReg();

	// 情報の表示
	tmpStr.LoadString(IDS_APPNAME);
	tmpStr2.LoadString(IDS_END_UNINST);
	::MessageBox(NULL, tmpStr2, tmpStr, MB_ICONINFORMATION|MB_OK|MB_SYSTEMMODAL);

}
