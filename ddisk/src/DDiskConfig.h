#if !defined(AFX_DDISKCONFIG_H__29D10422_DBAF_11D3_AD9A_0090CCA1066A__INCLUDED_)
#define AFX_DDISKCONFIG_H__29D10422_DBAF_11D3_AD9A_0090CCA1066A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DDiskConfig.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDDiskConfig �_�C�A���O

class CDDiskConfig : public CDialog
{
// �R���X�g���N�V����
public:
	CDDiskConfig(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDDiskConfig)
	enum { IDD = IDD_DIALOG_CONFIG };
	int		m_func;
	int		m_view;
	CString	m_text_winver;
	CString	m_edit_editor;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDDiskConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDDiskConfig)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnBrowse();
	afx_msg void OnBtnAbout();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnBtnMkuninst();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DDISKCONFIG_H__29D10422_DBAF_11D3_AD9A_0090CCA1066A__INCLUDED_)
