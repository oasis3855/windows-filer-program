#if !defined(AFX_DLGERRSEL_H__874B1EBF_3423_4A29_A665_F89384FF853D__INCLUDED_)
#define AFX_DLGERRSEL_H__874B1EBF_3423_4A29_A665_F89384FF853D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgErrSel.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// DlgErrSel �_�C�A���O

class DlgErrSel : public CDialog
{
// �R���X�g���N�V����
public:
	DlgErrSel(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(DlgErrSel)
	enum { IDD = IDD_DLG_ERR };
	CButton	m_ctrl_sel;
	CEdit	m_ctrl_errskip;
	CEdit	m_ctrl_moreerr;
	CButton	m_ctrl_samesel;
	int		m_int_sel;
	UINT	m_int_errskip;
	UINT	m_int_moreerr;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(DlgErrSel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(DlgErrSel)
	afx_msg void OnRadioSel2();
	afx_msg void OnRadioSel();
	virtual BOOL OnInitDialog();
	afx_msg void OnCkSamesel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGERRSEL_H__874B1EBF_3423_4A29_A665_F89384FF853D__INCLUDED_)
