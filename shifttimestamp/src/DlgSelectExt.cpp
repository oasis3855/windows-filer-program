// DlgSelectExt.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "ShiftTime.h"
#include "DlgSelectExt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSelectExt ダイアログ


CDlgSelectExt::CDlgSelectExt(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelectExt::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSelectExt)
	m_radio_sel = -1;
	//}}AFX_DATA_INIT
}


void CDlgSelectExt::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSelectExt)
	DDX_Radio(pDX, IDC_RADIO_SEL, m_radio_sel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSelectExt, CDialog)
	//{{AFX_MSG_MAP(CDlgSelectExt)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSelectExt メッセージ ハンドラ
