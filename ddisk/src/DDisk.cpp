// DDisk.cpp : �A�v���P�[�V�����p�N���X�̒�`���s���܂��B
//

#include "stdafx.h"
#include "DDisk.h"
#include "DDiskDlg.h"
#include "DlgInstall.h"
#include "InstFunc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDDiskApp

BEGIN_MESSAGE_MAP(CDDiskApp, CWinApp)
	//{{AFX_MSG_MAP(CDDiskApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDDiskApp �N���X�̍\�z

CDDiskApp::CDDiskApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CDDiskApp �I�u�W�F�N�g

CDDiskApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDDiskApp �N���X�̏�����

BOOL CDDiskApp::InitInstance()
{
	// �W���I�ȏ���������
	// ���������̋@�\���g�p�����A���s�t�@�C���̃T�C�Y��������������
	//  ��Έȉ��̓���̏��������[�`���̒�����s�K�v�Ȃ��̂��폜����
	//  ���������B

	// ���W�X�g���̎w��
	// ���\�[�X��AFX_IDS_APP_TITLE�ɃA�v���P�[�V��������ݒ肷�邱�� 
	// m_pszAppName = "compdel" �Ƃ��Ă͂����Ȃ��I ASSERTION �G���[�ƂȂ�
	SetRegistryKey((LPCTSTR)"hi soft");

	LoadStdProfileSettings(0);	// MRU���X�g�Ǘ�(0:���Ȃ�)


#ifdef _AFXDLL
	Enable3dControls();			// ���L DLL ���� MFC ���g���ꍇ�͂������R�[�����Ă��������B
#else
	Enable3dControlsStatic();	// MFC �ƐÓI�Ƀ����N����ꍇ�͂������R�[�����Ă��������B
#endif

	CString tmpStr, tmpStr2;	// �X�g�����O ���\�[�X �ǂݍ��ݗp

	// �R�}���h���C���̉��
	if(!strcmpi(m_lpCmdLine, "/delete"))
	{	// �A���C���X�g�[��
		UninstallSeq();
		return FALSE;
	}
	else if(m_lpCmdLine[0] != NULL)
	{	// �����ȃp�����[�^�[���w�肳�ꂽ�ꍇ�A�p�����[�^�[���X�g��\������
		tmpStr.LoadString(IDS_ERR_PARAM);
		tmpStr2.LoadString(IDS_APPNAME);
		::MessageBox(NULL, tmpStr, tmpStr2, MB_OK|MB_ICONINFORMATION|MB_APPLMODAL);
		return FALSE;
	}

	if(!::ChkHkcuInstReg())
		if(!InstallSeq())return FALSE;

	RegReadAll();


	CDDiskDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �_�C�A���O�� <OK> �ŏ����ꂽ���̃R�[�h��
		//       �L�q���Ă��������B
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �_�C�A���O�� <��ݾ�> �ŏ����ꂽ���̃R�[�h��
		//       �L�q���Ă��������B
	}

	RegWriteAll();

	// �_�C�A���O�������Ă���A�v���P�[�V�����̃��b�Z�[�W �|���v���J�n������́A
	// �A�v���P�[�V�������I�����邽�߂� FALSE ��Ԃ��Ă��������B
	return FALSE;
}

// ************************************************************
// ���W�X�g�����̓ǂݍ���
// ************************************************************
void CDDiskApp::RegReadAll()
{
	m_inttype = GetProfileInt("Settings","INT_type",2);
	m_viewtype = GetProfileInt("Settings","VIEW_type",0);
	m_binedit = GetProfileString("Settings","BIN_EDIT","");
}

// ************************************************************
// ���W�X�g���֕ۑ�
// ************************************************************
void CDDiskApp::RegWriteAll()
{
	if(m_inttype != (int)GetProfileInt("Settings","INT_type",2))
		WriteProfileInt("Settings","INT_type",m_inttype);
	if(m_viewtype != (int)GetProfileInt("Settings","VIEW_type",0))
		WriteProfileInt("Settings","VIEW_type",m_viewtype);
	if(m_binedit != GetProfileString("Settings","BIN_EDIT",""))
		WriteProfileString("Settings","BIN_EDIT",m_binedit);
}


// ************************************************************
// �C���X�g�[��
// ************************************************************
BOOL CDDiskApp::InstallSeq()
{
	CDlgInstall dlg;
	OSVERSIONINFO ver;

	// �����{�^���̐ݒ�
	dlg.m_func = 2;		// �W���� Win98 �p�̊��荞�݂�I��
	dlg.m_uninst = TRUE;
	dlg.m_start = TRUE;
	

	// OS�̃o�[�W��������\������

	ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	::GetVersionEx((LPOSVERSIONINFO)&ver);

	dlg.m_text_winver = "Windows ";

	switch(ver.dwPlatformId)
	{
		case VER_PLATFORM_WIN32s :
				dlg.m_text_winver += "3.1 Win32s";
				dlg.m_warning.LoadString(IDS_WARNING_BADWIN);
				break;
		case VER_PLATFORM_WIN32_WINDOWS :
			if(ver.dwMinorVersion == 0)
			{
				if((ver.dwBuildNumber&0xffff) < 1000)
				{
					dlg.m_text_winver += "95";
					dlg.m_func = 1;		// INT 25H Win95 �̃{�^����I��
				}
				else dlg.m_text_winver += "95 OSR2";
				break;
			}
			else
			{
				if(ver.dwBuildNumber&0xffff < 2000)
					dlg.m_text_winver += "98";
				else dlg.m_text_winver += "98SE";
				break;
			}
		case VER_PLATFORM_WIN32_NT :
			dlg.m_text_winver += "NT, 2000";
			dlg.m_warning.LoadString(IDS_WARNING_BADWIN);
			break;
		default : dlg.m_text_winver += "Unknown"; break;
	}

	sprintf(m_buf, "  Version %Lu.%Lu.", ver.dwMajorVersion, ver.dwMinorVersion);
	dlg.m_text_winver += m_buf;

	switch(ver.dwPlatformId)
	{
		case VER_PLATFORM_WIN32_WINDOWS :
			sprintf(m_buf, "%Lu", ver.dwBuildNumber&0xffff);
			break;
		default :
			sprintf(m_buf, "%Lu", ver.dwBuildNumber);
			break;
	}
	dlg.m_text_winver += m_buf;

	sprintf(m_buf, " %s", ver.szCSDVersion);
	dlg.m_text_winver += m_buf;

	if(dlg.DoModal() != IDOK) return FALSE;		// ��ݾك{�^���������ꂽ�� �������Ȃ�

	// �I�v�V�����̐ݒ�
	m_inttype = dlg.m_func;
	m_viewtype = 0;
	m_binedit = "";

	RegWriteAll();	// ���W�X�g���ɏ�������

	// �C���X�g�[���t���O�̏�������
	::MkHkcuInstReg();
	
	// �A���C���X�g�[�����ɂ���
	if(dlg.m_uninst) ::MkUninstMnu();

	// �X�^�[�g���j���[�ɓo�^���鏈��
	if(dlg.m_start) ::MkProgramsMnu();

	return TRUE;
}


// ************************************************************
// �A���C���X�g�[��
// ************************************************************
void CDDiskApp::UninstallSeq()
{
	CString tmpStr, tmpStr2;	// �X�g�����O ���\�[�X �ǂݍ��ݗp
	
	tmpStr.LoadString(IDS_APPNAME);
	tmpStr2.LoadString(IDS_Q_UNINST);
	if(::MessageBox(NULL, tmpStr2, tmpStr, MB_ICONQUESTION|MB_YESNO|MB_SYSTEMMODAL) != IDYES)
		return;

	// ���W�X�g���̐ݒ�������� ���݂̃��[�U�[��񂩂�폜����
	::RmUserReg();

	// �X�^�[�g���j���[�̐ݒ�A�C�R���𖕎E
	::RmProgramsMnu();

	// �A���C���X�g�[���A�C�R���̍폜
	::RmUninstMnu();

	// �C���X�g�[���t���O�̍폜
	::RmHkcuInstReg();

	// ���̕\��
	tmpStr.LoadString(IDS_APPNAME);
	tmpStr2.LoadString(IDS_END_UNINST);
	::MessageBox(NULL, tmpStr2, tmpStr, MB_ICONINFORMATION|MB_OK|MB_SYSTEMMODAL);

}