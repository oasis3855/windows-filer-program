// DlgInstall.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "ddisk.h"
#include "DlgInstall.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInstall ダイアログ


CDlgInstall::CDlgInstall(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInstall::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInstall)
	m_func = -1;
	m_text_winver = _T("");
	m_warning = _T("");
	m_uninst = FALSE;
	m_start = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgInstall::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInstall)
	DDX_Radio(pDX, IDC_RADIO_FUNC, m_func);
	DDX_Text(pDX, IDC_STR_WINVER, m_text_winver);
	DDX_Text(pDX, IDC_STR_WARNING, m_warning);
	DDX_Check(pDX, IDC_CHECK_UNINST, m_uninst);
	DDX_Check(pDX, IDC_CHECK_START, m_start);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInstall, CDialog)
	//{{AFX_MSG_MAP(CDlgInstall)
	ON_BN_CLICKED(IDC_BUTTON_HELP, OnButtonHelp)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInstall メッセージ ハンドラ

void CDlgInstall::OnButtonHelp() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CDDiskApp *theApp;
	theApp = (CDDiskApp *)AfxGetApp();
	theApp->WinHelp(0);		// DDisk.hm の値	
}

BOOL CDlgInstall::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	
	CDDiskApp *theApp;
	theApp = (CDDiskApp *)AfxGetApp();
	theApp->WinHelp(0);		// DDisk.hm の値
	return 0;
}
