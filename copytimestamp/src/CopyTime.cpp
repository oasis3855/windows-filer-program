// CopyTime.cpp : アプリケーション用クラスの定義を行います。
//

#include "stdafx.h"
#include "CopyTime.h"
#include "CopyTimeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCopyTimeApp

BEGIN_MESSAGE_MAP(CCopyTimeApp, CWinApp)
	//{{AFX_MSG_MAP(CCopyTimeApp)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCopyTimeApp クラスの構築

CCopyTimeApp::CCopyTimeApp()
{
	// TODO: この位置に構築用のコードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CCopyTimeApp オブジェクト

CCopyTimeApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCopyTimeApp クラスの初期化

BOOL CCopyTimeApp::InitInstance()
{
	// 標準的な初期化処理
	// もしこれらの機能を使用せず、実行ファイルのサイズを小さくしたけ
	//  れば以下の特定の初期化ルーチンの中から不必要なものを削除して
	//  ください。

#ifdef _AFXDLL
	Enable3dControls();			// 共有 DLL 内で MFC を使う場合はここをコールしてください。
#else
	Enable3dControlsStatic();	// MFC と静的にリンクする場合はここをコールしてください。
#endif

	// ************************************************************
	// コマンドライン引数による処理  (/reg , /delete)
	// 主に、レジストリ使用に関する処理
	// ************************************************************
	if(!strcmpi(m_lpCmdLine, "/reg"))
	{	// レジストリ使用
		// システムレジストリの使用位置を設定する
		// \HKEY_USERS\.Default\Software\hi_soft\AFS_IDS_APP_TITLE\Settings
		SetRegistryKey((LPCTSTR)"hi soft");
		LoadStdProfileSettings(0);	// MRUリスト管理(0:しない)
	}
	else if(!strcmpi(m_lpCmdLine, "/delete"))
	{	// レジストリ情報を削除
		// レジストリの設定情報を消去 現在のユーザー情報から削除する
		HKEY hCU;
		if (RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\hi soft\\CopyTime",
				0, KEY_QUERY_VALUE, &hCU) == ERROR_SUCCESS)
		{
			RegDeleteKey( hCU, "Settings");
			RegCloseKey(hCU);
		}
		if (RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\hi soft",
				0, KEY_QUERY_VALUE, &hCU) == ERROR_SUCCESS)
		{
			RegDeleteKey( hCU, "CopyTime");
			RegCloseKey(hCU);
		}

		::MessageBox(NULL, "CopyTime Uninstalled (registry info is deleted)", "CopyTime Uninstaller", MB_OK|MB_ICONINFORMATION);
		return FALSE;
	}


	CCopyTimeDlg dlg;
	m_pMainWnd = &dlg;

	if(!strcmpi(m_lpCmdLine, "/reg"))
	{	// レジストリ使用  前回のフォルダ情報を反映する
		dlg.m_edit_from = GetProfileString("Settings","from","");
		dlg.m_edit_to = GetProfileString("Settings","to","");
	}
	
	
	// ************************************************************
	// メインダイアログの表示
	// ************************************************************
	dlg.DoModal();

	// ************************************************************
	// レジストリ使用に関する処理
	// ************************************************************
	if(!strcmpi(m_lpCmdLine, "/reg"))
	{	// レジストリ使用  フォルダ情報をレジストリに書き込む
		if(dlg.m_edit_from != GetProfileString("Settings","from",""))
			WriteProfileString("Settings","from",dlg.m_edit_from);
		if(dlg.m_edit_to != GetProfileString("Settings","to",""))
			WriteProfileString("Settings","to",dlg.m_edit_to);
		
	}

	// ダイアログが閉じられてからアプリケーションのメッセージ ポンプを開始するよりは、
	// アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}

