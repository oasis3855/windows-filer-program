// DDisk.h : DDISK �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_DDISK_H__41C96AE5_D6FF_11D3_AD9A_0090CCA1066A__INCLUDED_)
#define AFX_DDISK_H__41C96AE5_D6FF_11D3_AD9A_0090CCA1066A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CDDiskApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� DDisk.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CDDiskApp : public CWinApp
{
public:
	void UninstallSeq();
	BOOL InstallSeq();
	CString m_binedit;
	void RegWriteAll(void);
	void RegReadAll(void);
	int m_inttype;
	int m_viewtype;
	CDDiskApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDDiskApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(CDDiskApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	char m_buf[256];
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DDISK_H__41C96AE5_D6FF_11D3_AD9A_0090CCA1066A__INCLUDED_)
