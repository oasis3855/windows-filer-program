// FileCpEx.h : FILECPEX �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_FILECPEX_H__9EB7C6D6_63FE_4861_8A89_741385F03DFE__INCLUDED_)
#define AFX_FILECPEX_H__9EB7C6D6_63FE_4861_8A89_741385F03DFE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CFileCpExApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� FileCpEx.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CFileCpExApp : public CWinApp
{
public:
	CFileCpExApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CFileCpExApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(CFileCpExApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_FILECPEX_H__9EB7C6D6_63FE_4861_8A89_741385F03DFE__INCLUDED_)