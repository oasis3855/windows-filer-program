// FileSequenceCutter.h : FILESEQUENCECUTTER �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_FILESEQUENCECUTTER_H__F9476F4A_9A2D_4DAD_8FD0_B5F71F1C728F__INCLUDED_)
#define AFX_FILESEQUENCECUTTER_H__F9476F4A_9A2D_4DAD_8FD0_B5F71F1C728F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CFileSequenceCutterApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� FileSequenceCutter.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CFileSequenceCutterApp : public CWinApp
{
public:
	CFileSequenceCutterApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CFileSequenceCutterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(CFileSequenceCutterApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_FILESEQUENCECUTTER_H__F9476F4A_9A2D_4DAD_8FD0_B5F71F1C728F__INCLUDED_)
