// DlgPreview.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "CopyTime.h"
#include "DlgPreview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPreview �_�C�A���O


CDlgPreview::CDlgPreview(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreview::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPreview)
	m_edit_main_text = _T("");
	//}}AFX_DATA_INIT
}


void CDlgPreview::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPreview)
	DDX_Control(pDX, IDC_EDIT_MAIN, m_edit_main_ctrl);
	DDX_Text(pDX, IDC_EDIT_MAIN, m_edit_main_text);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPreview, CDialog)
	//{{AFX_MSG_MAP(CDlgPreview)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPreview ���b�Z�[�W �n���h��

void CDlgPreview::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����Ă�������

	// �e�L�X�g���I������Ă���̂���������
	m_edit_main_ctrl.SetSel(-1,0,FALSE);
	// �J�[�\����擪�s�Ɏ����Ă���
	m_edit_main_ctrl.LineScroll(0);
	
}
