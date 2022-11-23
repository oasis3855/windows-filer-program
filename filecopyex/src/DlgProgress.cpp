// DlgProgress.cpp : �C���v�������e�[�V���� �t�@�C��
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
// DlgProgress �_�C�A���O


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
// DlgProgress ���b�Z�[�W �n���h��

BOOL DlgProgress::CreateMyDlg(CWnd *pParentWnd)
{
	Create(IDD, NULL);
	return TRUE;
}

BOOL DlgProgress::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	p->hWnd = this->m_hWnd;
	p->hWndTxtCurbyte = GetDlgItem(IDC_STXT_CURSIZ)->m_hWnd;
	p->hWndTxtTotalbyte = GetDlgItem(IDC_STXT_TOTALSIZ)->m_hWnd;
	p->hWndTxtMes = GetDlgItem(IDC_STXT_MES)->m_hWnd;
	
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

void DlgProgress::OnBtnStop() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	OnOK();		// �_�C�A���O���I������
}
