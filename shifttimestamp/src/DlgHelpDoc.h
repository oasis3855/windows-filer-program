#if !defined(AFX_DLGHELPDOC_H__6AE983D7_3779_43AC_9E36_DB80CECDB434__INCLUDED_)
#define AFX_DLGHELPDOC_H__6AE983D7_3779_43AC_9E36_DB80CECDB434__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgHelpDoc.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDlgHelpDoc �_�C�A���O

class CDlgHelpDoc : public CDialog
{
// �R���X�g���N�V����
public:
	CDlgHelpDoc(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgHelpDoc)
	enum { IDD = IDD_DLG_HELPDOC };
	CString	m_edit_main;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgHelpDoc)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgHelpDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGHELPDOC_H__6AE983D7_3779_43AC_9E36_DB80CECDB434__INCLUDED_)