#if !defined(AFX_DLGPROGRESS_H__C5150A43_FF95_4D1B_B7CA_4B3AFE6F1CAE__INCLUDED_)
#define AFX_DLGPROGRESS_H__C5150A43_FF95_4D1B_B7CA_4B3AFE6F1CAE__INCLUDED_

#include "GlobalFunc.h"	// ClassView �ɂ���Ēǉ�����܂����B
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgProgress.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// DlgProgress �_�C�A���O

class DlgProgress : public CDialog
{
// �R���X�g���N�V����
public:
	ThreadArg *p;
	BOOL CreateMyDlg(CWnd *pParentWnd);
	DlgProgress(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(DlgProgress)
	enum { IDD = IDD_DLG_PROGRESS };
	CString	m_txt_cursiz;
	CString	m_txt_totalsiz;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(DlgProgress)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(DlgProgress)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGPROGRESS_H__C5150A43_FF95_4D1B_B7CA_4B3AFE6F1CAE__INCLUDED_)
