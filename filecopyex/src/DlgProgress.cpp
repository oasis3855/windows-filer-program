// DlgProgress.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "FileCpEx.h"
#include "DlgProgress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgProgress ダイアログ


DlgProgress::DlgProgress(CWnd* pParent /*=NULL*/)
	: CDialog(DlgProgress::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgProgress)
	m_txt_cursiz = _T("");
	m_txt_totalsiz = _T("");
	//}}AFX_DATA_INIT
}


void DlgProgress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgProgress)
	DDX_Text(pDX, IDC_STXT_CURSIZ, m_txt_cursiz);
	DDX_Text(pDX, IDC_STXT_TOTALSIZ, m_txt_totalsiz);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgProgress, CDialog)
	//{{AFX_MSG_MAP(DlgProgress)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgProgress メッセージ ハンドラ

BOOL DlgProgress::CreateMyDlg(CWnd *pParentWnd)
{
	Create(IDD, NULL);
	return TRUE;
}

BOOL DlgProgress::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	p->hWnd = this->m_hWnd;
	p->hWndTxtCurbyte = GetDlgItem(IDC_STXT_CURSIZ)->m_hWnd;
	p->hWndTxtTotalbyte = GetDlgItem(IDC_STXT_TOTALSIZ)->m_hWnd;
	p->hWndTxtMes = GetDlgItem(IDC_STXT_MES)->m_hWnd;
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void DlgProgress::OnBtnStop() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnOK();		// ダイアログを終了する
}
