// DDiskDlg.h : �w�b�_�[ �t�@�C��
//

#if !defined(AFX_DDISKDLG_H__41C96AE7_D6FF_11D3_AD9A_0090CCA1066A__INCLUDED_)
#define AFX_DDISKDLG_H__41C96AE7_D6FF_11D3_AD9A_0090CCA1066A__INCLUDED_

#include "DDisk.h"	// ClassView �ɂ���Ēǉ�����܂����B
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDDiskDlg �_�C�A���O

class CDDiskDlg : public CDialog
{
// �\�z
public:
	CDDiskDlg(CWnd* pParent = NULL);	// �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDDiskDlg)
	enum { IDD = IDD_DDISK_DIALOG };
	CComboBox	m_cmb_disk;
	UINT	m_sect;
	UINT	m_size;
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDDiskDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	CDDiskApp *theApp;
	HICON m_hIcon;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDDiskDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnRead();
	afx_msg void OnBtnDpb();
	afx_msg void OnBtnConfig();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKillfocusEditSize();
	afx_msg void OnBtnBrowse();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnWrite();
	afx_msg void OnBtnEdit();
	afx_msg void OnBtnHelp();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	char m_mainbuf[4100];
	char m_buf[256];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B


#endif // !defined(AFX_DDISKDLG_H__41C96AE7_D6FF_11D3_AD9A_0090CCA1066A__INCLUDED_)

