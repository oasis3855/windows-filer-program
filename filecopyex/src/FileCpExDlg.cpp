// FileCpExDlg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "FileCpEx.h"
#include "FileCpExDlg.h"
#include "DlgErrSel.h"
#include "DlgProgress.h"
#include "GlobalFunc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileCpExDlg �_�C�A���O

CFileCpExDlg::CFileCpExDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileCpExDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileCpExDlg)
	m_txt_from = _T("");
	m_int_end = 0;
	m_int_skip = 0;
	m_int_start = 0;
	m_txt_to = _T("");
	m_int_retry = 0;
	//}}AFX_DATA_INIT
	// ����: LoadIcon �� Win32 �� DestroyIcon �̃T�u�V�[�P���X��v�����܂���B
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileCpExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileCpExDlg)
	DDX_Control(pDX, IDC_CMB_BUFSIZ, m_ctrl_bufsiz);
	DDX_Control(pDX, IDC_CK_NULL, m_ctrl_null);
	DDX_Control(pDX, IDC_CK_FILEEND, m_ctrl_fileend);
	DDX_Control(pDX, IDC_CK_DLG, m_ctrl_dlg);
	DDX_Control(pDX, IDC_TXT_END, m_ctrl_end);
	DDX_Control(pDX, IDC_TXT_SKIP, m_ctrl_skip);
	DDX_Control(pDX, IDC_TXT_RETRY, m_ctrl_retry);
	DDX_Text(pDX, IDC_TXT_FROM, m_txt_from);
	DDV_MaxChars(pDX, m_txt_from, 256);
	DDX_Text(pDX, IDC_TXT_END, m_int_end);
	DDX_Text(pDX, IDC_TXT_SKIP, m_int_skip);
	DDX_Text(pDX, IDC_TXT_START, m_int_start);
	DDX_Text(pDX, IDC_TXT_TO, m_txt_to);
	DDV_MaxChars(pDX, m_txt_to, 256);
	DDX_Text(pDX, IDC_TXT_RETRY, m_int_retry);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFileCpExDlg, CDialog)
	//{{AFX_MSG_MAP(CFileCpExDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CK_FILEEND, OnCkFileend)
	ON_BN_CLICKED(IDC_CK_DLG, OnCkDlg)
	ON_CBN_SELCHANGE(IDC_CMB_BUFSIZ, OnSelchangeCmbBufsiz)
	ON_BN_CLICKED(IDC_BTN_COPY, OnBtnCopy)
	ON_BN_CLICKED(IDC_BTN_FROMBRW, OnBtnFrombrw)
	ON_BN_CLICKED(IDC_BTN_TOBRW, OnBtnTobrw)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileCpExDlg ���b�Z�[�W �n���h��

BOOL CFileCpExDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���̃_�C�A���O�p�̃A�C�R����ݒ肵�܂��B�t���[�����[�N�̓A�v���P�[�V�����̃��C��
	// �E�B���h�E���_�C�A���O�łȂ����͎����I�ɐݒ肵�܂���B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R����ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R����ݒ�
	
	// TODO: ���ʂȏ��������s�����͂��̏ꏊ�ɒǉ����Ă��������B
	CString strTmp;
	m_ctrl_bufsiz.SetCurSel(7);		// 0 ... 7 : 16K ��I��

	SetDlgItemInt(IDC_TXT_START, 0);
	SetDlgItemInt(IDC_TXT_END, 0);
	SetDlgItemInt(IDC_TXT_RETRY, 10);
	m_ctrl_bufsiz.GetLBText(m_ctrl_bufsiz.GetCurSel(), strTmp);
	SetDlgItemInt(IDC_TXT_SKIP, atoi((LPCSTR)strTmp));

	m_ctrl_fileend.SetCheck(1);
	m_ctrl_dlg.SetCheck(1);
	m_ctrl_null.SetCheck(1);

	OnCkFileend();	// �t�@�C���G���h�܂ŃR�s�[�̃`�F�b�N��Ԃ̔��f
	OnCkDlg();	// �G���[���Ƀ_�C�A���O�̃`�F�b�N��Ԃ̔��f
	
	return TRUE;  // TRUE ��Ԃ��ƃR���g���[���ɐݒ肵���t�H�[�J�X�͎����܂���B
}

// �����_�C�A���O�{�b�N�X�ɍŏ����{�^����ǉ�����Ȃ�΁A�A�C�R����`�悷��
// �R�[�h���ȉ��ɋL�q����K�v������܂��BMFC �A�v���P�[�V������ document/view
// ���f�����g���Ă���̂ŁA���̏����̓t���[�����[�N�ɂ�莩���I�ɏ�������܂��B

void CFileCpExDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��p�̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// �N���C�A���g�̋�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R����`�悵�܂��B
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// �V�X�e���́A���[�U�[���ŏ����E�B���h�E���h���b�O���Ă���ԁA
// �J�[�\����\�����邽�߂ɂ������Ăяo���܂��B
HCURSOR CFileCpExDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFileCpExDlg::OnCkFileend() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	if(!IsDlgButtonChecked(IDC_CK_FILEEND))
	{
		m_ctrl_end.EnableWindow(TRUE);
	}
	else
	{
		m_ctrl_end.EnableWindow(FALSE);
	}
	
}

void CFileCpExDlg::OnCkDlg() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	if(!IsDlgButtonChecked(IDC_CK_DLG))
	{
		m_ctrl_retry.EnableWindow(TRUE);
		m_ctrl_skip.EnableWindow(TRUE);
	}
	else
	{
		m_ctrl_retry.EnableWindow(FALSE);
		m_ctrl_skip.EnableWindow(FALSE);
	}
	
}

void CFileCpExDlg::OnSelchangeCmbBufsiz() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString strTmp;
	m_ctrl_bufsiz.GetLBText(m_ctrl_bufsiz.GetCurSel(), strTmp);
	SetDlgItemInt(IDC_TXT_SKIP, atoi((LPCSTR)strTmp));
	
}

void CFileCpExDlg::OnBtnFrombrw() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_EXPLORER,
		"���ׂẴt�@�C��|*.*|mpeg �f�[�^|*.mp*|WAV �f�[�^|*.wav|���̑��̃f�[�^|*.dat||");
	dlg.m_ofn.lpstrTitle = "�R�s�[���t�@�C���̑I��";

	if(dlg.DoModal() != IDOK) return;

	// ̧�ٖ��e�L�X�g�{�b�N�X�Ƀt�@�C�������Z�b�g
	SetDlgItemText(IDC_TXT_FROM,dlg.GetPathName());
	
}

void CFileCpExDlg::OnBtnTobrw() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CFileDialog dlg(FALSE, NULL, NULL, OFN_OVERWRITEPROMPT|OFN_EXPLORER,
		"�ۑ��t�@�C��|*.*||");
	dlg.m_ofn.lpstrTitle = "�ۑ��t�@�C���̑I��";

	if(dlg.DoModal() != IDOK) return;

	// ̧�ٖ��e�L�X�g�{�b�N�X�Ƀt�@�C�������Z�b�g
	SetDlgItemText(IDC_TXT_TO,dlg.GetPathName());
	
}

#include <io.h>			// findfirst

void CFileCpExDlg::OnBtnCopy() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	if(::ThreadCtrlFlag)
	{	// �t���O���P�̂Ƃ��́A���łɃX���b�h�N���ς�
		MessageBox("�R�s�[�X���b�h�N���ς�", "�x��", MB_ICONINFORMATION);
		return ;
	}
	
	CString strTmp;
	static ThreadArg p;
	DlgProgress dlg;

	dlg.p = &p;

	GetDlgItemText(IDC_TXT_FROM, p.strFnameFrom, 255);
	GetDlgItemText(IDC_TXT_TO, p.strFnameTo, 255);

	if( (!strlen(p.strFnameFrom)) || (!strlen(p.strFnameTo)) )
	{
		MessageBox("���o�� �o���̃t�@�C�����w�肵�Ă�������", "�x��", MB_ICONINFORMATION);
		return ;
	}

//	p.hWnd = this->m_hWnd;
//	p.hWndTxtCurbyte = GetDlgItem(IDC_STXT_CURSIZ)->m_hWnd;
//	p.hWndTxtTotalbyte = GetDlgItem(IDC_STXT_TOTALSIZ)->m_hWnd;
//	p.hWndTxtMes = GetDlgItem(IDC_STXT_MES)->m_hWnd;

	p.int_copystart = GetDlgItemInt(IDC_TXT_START,0);
	p.int_copyend = GetDlgItemInt(IDC_TXT_END, 0);
	m_ctrl_bufsiz.GetLBText(m_ctrl_bufsiz.GetCurSel(), strTmp);
	p.int_bufsiz = (long)atoi((LPCSTR)strTmp);
	p.int_skipsiz = GetDlgItemInt(IDC_TXT_SKIP, 0);
	p.int_retry = GetDlgItemInt(IDC_TXT_RETRY, 0);
	if(IsDlgButtonChecked(IDC_CK_DLG)) p.sw_errordlg = 1;
	else p.sw_errordlg = 0;
	if(IsDlgButtonChecked(IDC_CK_FILEEND)) p.sw_fileend = 1;
	else p.sw_fileend = 0;


	::ThreadCtrlFlag = 1;	// �t���O���X���b�h�N�����ɂ���
	// �X���b�h�̋N��
	ThreadHandle = ::CreateThread(NULL, 0, ::ThreadMain, (LPVOID)&p, 0, 0);
	if(ThreadHandle == NULL)
	{
		::ThreadCtrlFlag = 0;
		MessageBox("�X���b�h�N���o���܂���ł���", "�x��", MB_ICONINFORMATION);
		return ;
	}

	dlg.DoModal();

	::ThreadCtrlFlag = 0;	// �t���O���O�ɂ��āA�X���b�h���ł̒�~��Ƃ��s��
	if(!::ThreadEndFlag)
	{
		// �X���b�h���I���V�O�i�����o���̂�҂i�����Ɂj
		::WaitForSingleObject(ThreadHandle,INFINITE);
	}
	// �n���h�����N���[�Y���ď��߂āA�I�u�W�F�N�g�����������
	::CloseHandle(ThreadHandle);


}

