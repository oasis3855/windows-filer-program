// ************************************************************
// 設定・ダイアログ CDDiskConfig
// ************************************************************

#include "stdafx.h"
#include "DDisk.h"
#include "DDiskConfig.h"
#include "AboutDlg.h"
#include "InstFunc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDDiskConfig ダイアログ


CDDiskConfig::CDDiskConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDDiskConfig::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDDiskConfig)
	m_func = -1;
	m_view = -1;
	m_text_winver = _T("");\
	m_edit_editor = _T("");
	//}}AFX_DATA_INIT
}


void CDDiskConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDDiskConfig)
	DDX_Radio(pDX, IDC_RADIO_FUNC, m_func);
	DDX_Radio(pDX, IDC_RADIO_VIEW, m_view);
	DDX_Text(pDX, IDC_TEXT_WINVER, m_text_winver);
	DDX_Text(pDX, IDC_EDIT_EDITOR, m_edit_editor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDDiskConfig, CDialog)
	//{{AFX_MSG_MAP(CDDiskConfig)
	ON_BN_CLICKED(IDC_BTN_BROWSE, OnBtnBrowse)
	ON_BN_CLICKED(IDC_BTN_ABOUT, OnBtnAbout)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_BTN_MKUNINST, OnBtnMkuninst)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDDiskConfig メッセージ ハンドラ

BOOL CDDiskConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

// ************************************************************
// バイナリエディタの指定（パス検索）
// ************************************************************
void CDDiskConfig::OnBtnBrowse() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	char buf[256];

	GetDlgItemText(IDC_EDIT_EDITOR, buf, 125);
	CFileDialog dlg(TRUE, NULL, buf, OFN_CREATEPROMPT|OFN_EXPLORER|OFN_HIDEREADONLY,
				"Programs (*.EXE)|*.exe|All FIles|*.*||");
	if(dlg.DoModal()==TRUE)
		SetDlgItemText(IDC_EDIT_EDITOR, dlg.GetPathName());
	return;
}

// ************************************************************
// バージョン情報
// ************************************************************
void CDDiskConfig::OnBtnAbout() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CAboutDlg dlg;
	dlg.DoModal();
}

// ************************************************************
// ヘルプの表示 (F1 対応)
// ************************************************************
BOOL CDDiskConfig::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	CDDiskApp *theApp;
	theApp = (CDDiskApp *)AfxGetApp();
	
	theApp->WinHelp(0);		// DDisk.hm の値
	return 0;
}

// ************************************************************
// アンインストール・アイコンの作成
// ************************************************************
void CDDiskConfig::OnBtnMkuninst() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	::MkUninstMnu();	
}

// ************************************************************
// EOF
