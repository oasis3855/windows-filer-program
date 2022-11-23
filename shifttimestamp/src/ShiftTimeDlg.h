// ShiftTimeDlg.h : �w�b�_�[ �t�@�C��
//

#if !defined(AFX_SHIFTTIMEDLG_H__A337A349_35CB_4E6A_92CE_F1305E622258__INCLUDED_)
#define AFX_SHIFTTIMEDLG_H__A337A349_35CB_4E6A_92CE_F1305E622258__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CShiftTimeDlg �_�C�A���O

class CShiftTimeDlg : public CDialog
{
// �\�z
public:
	CShiftTimeDlg(CWnd* pParent = NULL);	// �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CShiftTimeDlg)
	enum { IDD = IDD_SHIFTTIME_DIALOG };
	CButton	m_chk_ZeroSec;
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CShiftTimeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	HICON m_hIcon;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CShiftTimeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnBrowse();
	afx_msg void OnBtnWildcard();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBtnExec();
	afx_msg void OnBtnHelp();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	char szTmp256[256];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SHIFTTIMEDLG_H__A337A349_35CB_4E6A_92CE_F1305E622258__INCLUDED_)
