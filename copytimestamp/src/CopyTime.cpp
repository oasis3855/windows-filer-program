// CopyTime.cpp : �A�v���P�[�V�����p�N���X�̒�`���s���܂��B
//

#include "stdafx.h"
#include "CopyTime.h"
#include "CopyTimeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCopyTimeApp

BEGIN_MESSAGE_MAP(CCopyTimeApp, CWinApp)
	//{{AFX_MSG_MAP(CCopyTimeApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCopyTimeApp �N���X�̍\�z

CCopyTimeApp::CCopyTimeApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CCopyTimeApp �I�u�W�F�N�g

CCopyTimeApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCopyTimeApp �N���X�̏�����

BOOL CCopyTimeApp::InitInstance()
{
	// �W���I�ȏ���������
	// ���������̋@�\���g�p�����A���s�t�@�C���̃T�C�Y��������������
	//  ��Έȉ��̓���̏��������[�`���̒�����s�K�v�Ȃ��̂��폜����
	//  ���������B

#ifdef _AFXDLL
	Enable3dControls();			// ���L DLL ���� MFC ���g���ꍇ�͂������R�[�����Ă��������B
#else
	Enable3dControlsStatic();	// MFC �ƐÓI�Ƀ����N����ꍇ�͂������R�[�����Ă��������B
#endif

	// ************************************************************
	// �R�}���h���C�������ɂ�鏈��  (/reg , /delete)
	// ��ɁA���W�X�g���g�p�Ɋւ��鏈��
	// ************************************************************
	if(!strcmpi(m_lpCmdLine, "/reg"))
	{	// ���W�X�g���g�p
		// �V�X�e�����W�X�g���̎g�p�ʒu��ݒ肷��
		// \HKEY_USERS\.Default\Software\hi_soft\AFS_IDS_APP_TITLE\Settings
		SetRegistryKey((LPCTSTR)"hi soft");
		LoadStdProfileSettings(0);	// MRU���X�g�Ǘ�(0:���Ȃ�)
	}
	else if(!strcmpi(m_lpCmdLine, "/delete"))
	{	// ���W�X�g�������폜
		// ���W�X�g���̐ݒ�������� ���݂̃��[�U�[��񂩂�폜����
		HKEY hCU;
		if (RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\hi soft\\CopyTime",
				0, KEY_QUERY_VALUE, &hCU) == ERROR_SUCCESS)
		{
			RegDeleteKey( hCU, "Settings");
			RegCloseKey(hCU);
		}
		if (RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\hi soft",
				0, KEY_QUERY_VALUE, &hCU) == ERROR_SUCCESS)
		{
			RegDeleteKey( hCU, "CopyTime");
			RegCloseKey(hCU);
		}

		::MessageBox(NULL, "CopyTime Uninstalled (registry info is deleted)", "CopyTime Uninstaller", MB_OK|MB_ICONINFORMATION);
		return FALSE;
	}


	CCopyTimeDlg dlg;
	m_pMainWnd = &dlg;

	if(!strcmpi(m_lpCmdLine, "/reg"))
	{	// ���W�X�g���g�p  �O��̃t�H���_���𔽉f����
		dlg.m_edit_from = GetProfileString("Settings","from","");
		dlg.m_edit_to = GetProfileString("Settings","to","");
	}
	
	
	// ************************************************************
	// ���C���_�C�A���O�̕\��
	// ************************************************************
	dlg.DoModal();

	// ************************************************************
	// ���W�X�g���g�p�Ɋւ��鏈��
	// ************************************************************
	if(!strcmpi(m_lpCmdLine, "/reg"))
	{	// ���W�X�g���g�p  �t�H���_�������W�X�g���ɏ�������
		if(dlg.m_edit_from != GetProfileString("Settings","from",""))
			WriteProfileString("Settings","from",dlg.m_edit_from);
		if(dlg.m_edit_to != GetProfileString("Settings","to",""))
			WriteProfileString("Settings","to",dlg.m_edit_to);
		
	}

	// �_�C�A���O�������Ă���A�v���P�[�V�����̃��b�Z�[�W �|���v���J�n������́A
	// �A�v���P�[�V�������I�����邽�߂� FALSE ��Ԃ��Ă��������B
	return FALSE;
}

