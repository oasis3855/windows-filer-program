// ShiftTime.h : SHIFTTIME �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_SHIFTTIME_H__CB3CBACB_A218_4577_BE02_5A465A167028__INCLUDED_)
#define AFX_SHIFTTIME_H__CB3CBACB_A218_4577_BE02_5A465A167028__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CShiftTimeApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� ShiftTime.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CShiftTimeApp : public CWinApp
{
public:
	CShiftTimeApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CShiftTimeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(CShiftTimeApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SHIFTTIME_H__CB3CBACB_A218_4577_BE02_5A465A167028__INCLUDED_)
