// CopyTimeDlg.h : �w�b�_�[ �t�@�C��
//

#if !defined(AFX_COPYTIMEDLG_H__B56BE426_9FB9_11D4_AD9A_0090CCA1066A__INCLUDED_)
#define AFX_COPYTIMEDLG_H__B56BE426_9FB9_11D4_AD9A_0090CCA1066A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCopyTimeDlg �_�C�A���O

class CCopyTimeDlg : public CDialog
{
// �\�z
public:
	BOOL CheckFile(LPCSTR FpathTo, LPCSTR Fname, CTime *FCTime, CTime *FMTime);
	CCopyTimeDlg(CWnd* pParent = NULL);	// �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CCopyTimeDlg)
	enum { IDD = IDD_COPYTIME_DIALOG };
	CString	m_edit_from;
	CString	m_edit_to;
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CCopyTimeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	HICON m_hIcon;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CCopyTimeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnFrom();
	afx_msg void OnBtnTo();
	afx_msg void OnBtnPreview();
	afx_msg void OnBtnHelp();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnBtnExec();
	afx_msg void OnBtnAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_COPYTIMEDLG_H__B56BE426_9FB9_11D4_AD9A_0090CCA1066A__INCLUDED_)
