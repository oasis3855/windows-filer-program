// ************************************************************
// �ݒ�E�_�C�A���O CDDiskConfig
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
// CDDiskConfig �_�C�A���O


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
// CDDiskConfig ���b�Z�[�W �n���h��

BOOL CDDiskConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

// ************************************************************
// �o�C�i���G�f�B�^�̎w��i�p�X�����j
// ************************************************************
void CDDiskConfig::OnBtnBrowse() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	char buf[256];

	GetDlgItemText(IDC_EDIT_EDITOR, buf, 125);
	CFileDialog dlg(TRUE, NULL, buf, OFN_CREATEPROMPT|OFN_EXPLORER|OFN_HIDEREADONLY,
				"Programs (*.EXE)|*.exe|All FIles|*.*||");
	if(dlg.DoModal()==TRUE)
		SetDlgItemText(IDC_EDIT_EDITOR, dlg.GetPathName());
	return;
}

// ************************************************************
// �o�[�W�������
// ************************************************************
void CDDiskConfig::OnBtnAbout() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CAboutDlg dlg;
	dlg.DoModal();
}

// ************************************************************
// �w���v�̕\�� (F1 �Ή�)
// ************************************************************
BOOL CDDiskConfig::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
	CDDiskApp *theApp;
	theApp = (CDDiskApp *)AfxGetApp();
	
	theApp->WinHelp(0);		// DDisk.hm �̒l
	return 0;
}

// ************************************************************
// �A���C���X�g�[���E�A�C�R���̍쐬
// ************************************************************
void CDDiskConfig::OnBtnMkuninst() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	::MkUninstMnu();	
}

// ************************************************************
// EOF
