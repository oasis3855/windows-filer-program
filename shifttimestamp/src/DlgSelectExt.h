#if !defined(AFX_DLGSELECTEXT_H__17397D2E_92A1_4921_8B56_8D565B037BD1__INCLUDED_)
#define AFX_DLGSELECTEXT_H__17397D2E_92A1_4921_8B56_8D565B037BD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSelectExt.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSelectExt �_�C�A���O

class CDlgSelectExt : public CDialog
{
// �R���X�g���N�V����
public:
	CDlgSelectExt(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgSelectExt)
	enum { IDD = IDD_DLG_SELEXXT };
	int		m_radio_sel;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgSelectExt)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgSelectExt)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGSELECTEXT_H__17397D2E_92A1_4921_8B56_8D565B037BD1__INCLUDED_)
