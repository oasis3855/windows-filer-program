#if !defined(AFX_DLGPREVIEW_H__B56BE442_9FB9_11D4_AD9A_0090CCA1066A__INCLUDED_)
#define AFX_DLGPREVIEW_H__B56BE442_9FB9_11D4_AD9A_0090CCA1066A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPreview.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPreview �_�C�A���O

class CDlgPreview : public CDialog
{
// �R���X�g���N�V����
public:
	CDlgPreview(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgPreview)
	enum { IDD = IDD_DLG_PREVIEW };
	CEdit	m_edit_main_ctrl;
	CString	m_edit_main_text;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgPreview)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgPreview)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGPREVIEW_H__B56BE442_9FB9_11D4_AD9A_0090CCA1066A__INCLUDED_)
