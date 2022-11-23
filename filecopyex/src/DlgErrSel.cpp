// DlgErrSel.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "FileCpEx.h"
#include "DlgErrSel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgErrSel ダイアログ


DlgErrSel::DlgErrSel(CWnd* pParent /*=NULL*/)
	: CDialog(DlgErrSel::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgErrSel)
	m_int_sel = -1;
	m_int_errskip = 0;
	m_int_moreerr = 0;
	//}}AFX_DATA_INIT
}


void DlgErrSel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgErrSel)
	DDX_Control(pDX, IDC_RADIO_SEL, m_ctrl_sel);
	DDX_Control(pDX, IDC_TXT_ERRSKIP, m_ctrl_errskip);
	DDX_Control(pDX, IDC_TXT_MOREERR, m_ctrl_moreerr);
	DDX_Control(pDX, IDC_CK_SAMESEL, m_ctrl_samesel);
	DDX_Radio(pDX, IDC_RADIO_SEL, m_int_sel);
	DDX_Text(pDX, IDC_TXT_ERRSKIP, m_int_errskip);
	DDX_Text(pDX, IDC_TXT_MOREERR, m_int_moreerr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgErrSel, CDialog)
	//{{AFX_MSG_MAP(DlgErrSel)
	ON_BN_CLICKED(IDC_RADIO_SEL2, OnRadioSel2)
	ON_BN_CLICKED(IDC_RADIO_SEL, OnRadioSel)
	ON_BN_CLICKED(IDC_CK_SAMESEL, OnCkSamesel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgErrSel メッセージ ハンドラ
BOOL DlgErrSel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	OnRadioSel();
	OnCkSamesel();
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}


void DlgErrSel::OnRadioSel2() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	if(!IsDlgButtonChecked(IDC_RADIO_SEL2))
	{
		m_ctrl_errskip.EnableWindow(FALSE);
	}
	else
	{
		m_ctrl_errskip.EnableWindow(TRUE);
	}
	
}

void DlgErrSel::OnRadioSel() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	if(!IsDlgButtonChecked(IDC_RADIO_SEL2))
	{
		m_ctrl_errskip.EnableWindow(FALSE);
	}
	else
	{
		m_ctrl_errskip.EnableWindow(TRUE);
	}
	
}

void DlgErrSel::OnCkSamesel() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	if(!IsDlgButtonChecked(IDC_CK_SAMESEL))
	{
		m_ctrl_moreerr.EnableWindow(FALSE);
	}
	else
	{
		m_ctrl_moreerr.EnableWindow(TRUE);
	}
	
}


