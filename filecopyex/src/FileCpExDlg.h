// FileCpExDlg.h : �w�b�_�[ �t�@�C��
//

#if !defined(AFX_FILECPEXDLG_H__5A55B36D_1CA8_4F0C_A0E4_CE9C04C655B0__INCLUDED_)
#define AFX_FILECPEXDLG_H__5A55B36D_1CA8_4F0C_A0E4_CE9C04C655B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFileCpExDlg �_�C�A���O

class CFileCpExDlg : public CDialog
{
// �\�z
public:
	HANDLE ThreadHandle;
	CFileCpExDlg(CWnd* pParent = NULL);	// �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CFileCpExDlg)
	enum { IDD = IDD_FILECPEX_DIALOG };
	CComboBox	m_ctrl_bufsiz;
	CButton	m_ctrl_null;
	CButton	m_ctrl_fileend;
	CButton	m_ctrl_dlg;
	CEdit	m_ctrl_end;
	CEdit	m_ctrl_skip;
	CEdit	m_ctrl_retry;
	CString	m_txt_from;
	UINT	m_int_end;
	UINT	m_int_skip;
	UINT	m_int_start;
	CString	m_txt_to;
	UINT	m_int_retry;
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CFileCpExDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	HICON m_hIcon;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CFileCpExDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCkFileend();
	afx_msg void OnCkDlg();
	afx_msg void OnSelchangeCmbBufsiz();
	afx_msg void OnBtnCopy();
	afx_msg void OnBtnFrombrw();
	afx_msg void OnBtnTobrw();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_FILECPEXDLG_H__5A55B36D_1CA8_4F0C_A0E4_CE9C04C655B0__INCLUDED_)
