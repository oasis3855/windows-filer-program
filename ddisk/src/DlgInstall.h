#if !defined(AFX_DLGINSTALL_H__A79857A0_E201_11D3_AD9A_0090CCA1066A__INCLUDED_)
#define AFX_DLGINSTALL_H__A79857A0_E201_11D3_AD9A_0090CCA1066A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInstall.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInstall �_�C�A���O

class CDlgInstall : public CDialog
{
// �R���X�g���N�V����
public:
	CDlgInstall(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgInstall)
	enum { IDD = IDD_DIALOG_INST };
	int		m_func;
	CString	m_text_winver;
	CString	m_warning;
	BOOL	m_uninst;
	BOOL	m_start;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgInstall)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgInstall)
	afx_msg void OnButtonHelp();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGINSTALL_H__A79857A0_E201_11D3_AD9A_0090CCA1066A__INCLUDED_)
