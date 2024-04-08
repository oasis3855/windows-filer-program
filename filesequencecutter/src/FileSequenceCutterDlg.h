// FileSequenceCutterDlg.h : �w�b�_�[ �t�@�C��
//

#if !defined(AFX_FILESEQUENCECUTTERDLG_H__10C0DADF_F383_497F_ABE5_5B711C708D2E__INCLUDED_)
#define AFX_FILESEQUENCECUTTERDLG_H__10C0DADF_F383_497F_ABE5_5B711C708D2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define FI_BUFFER_SIZE	100000		// �t�@�C���ǂݍ��݃o�b�t�@ 100kBytes
#define FI_READ_BUFFER_SIZE	100000	// �f�[�^�ǂݍ��݃o�b�t�@ 100kBytes

/////////////////////////////////////////////////////////////////////////////
// CFileSequenceCutterDlg �_�C�A���O

class CFileSequenceCutterDlg : public CDialog
{
// �\�z
public:
	BOOL fiWriteFile(long nStart, long nEnd, CString strFpath, int nSeqNo);
	int fiReadChar(void);
	CFileSequenceCutterDlg(CWnd* pParent = NULL);	// �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CFileSequenceCutterDlg)
	enum { IDD = IDD_FILESEQUENCECUTTER_DIALOG };
	CButton	m_radio_marker_ctrl;
	CComboBox	m_cmb_keyword_ctrl;
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CFileSequenceCutterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

	// �t�@�C���A�N�Z�X�p
	FILE *fi;
	long fi_cur_buf_addr;	// ���ݓǂݍ��܂�Ă���f�[�^�u���b�N�̐擪�A�h���X
	int fi_cur_buf_size;	// �ǂݍ��܂�Ă���f�[�^�̃T�C�Y
	long fi_read_ptr;		// �ǂݍ��݂��s���f�[�^�̃A�h���X
	int fi_read_size;		// �ǂݍ��݂��s���T�C�Y
	unsigned char fi_buf[FI_BUFFER_SIZE+1];		// �ǂݍ��݃o�b�t�@�i���������p�j
	unsigned char fi_r_buf[FI_READ_BUFFER_SIZE+1];	// �ǂݍ��݃f�[�^

// �C���v�������e�[�V����
protected:
	HICON m_hIcon;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CFileSequenceCutterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnBrowsefile();
	afx_msg void OnBtnBrowsepath();
	afx_msg void OnBtnAbout();
	afx_msg void OnBtnExec();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

BOOL IsStrHexnum(char *buf);

#endif // !defined(AFX_FILESEQUENCECUTTERDLG_H__10C0DADF_F383_497F_ABE5_5B711C708D2E__INCLUDED_)
