// CopyTimeDlg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "CopyTime.h"
#include "CopyTimeDlg.h"
#include "DlgPreview.h"
#include "DlgAbout.h"
#include <io.h>			// findfirst

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCopyTimeDlg �_�C�A���O

CCopyTimeDlg::CCopyTimeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCopyTimeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCopyTimeDlg)
	m_edit_from = _T("");
	m_edit_to = _T("");
	//}}AFX_DATA_INIT
	// ����: LoadIcon �� Win32 �� DestroyIcon �̃T�u�V�[�P���X��v�����܂���B
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCopyTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCopyTimeDlg)
	DDX_Text(pDX, IDC_EDIT_FROM, m_edit_from);
	DDX_Text(pDX, IDC_EDIT_TO, m_edit_to);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCopyTimeDlg, CDialog)
	//{{AFX_MSG_MAP(CCopyTimeDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_FROM, OnBtnFrom)
	ON_BN_CLICKED(IDC_BTN_TO, OnBtnTo)
	ON_BN_CLICKED(IDC_BTN_PREVIEW, OnBtnPreview)
	ON_BN_CLICKED(IDC_BTN_HELP, OnBtnHelp)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_BTN_EXEC, OnBtnExec)
	ON_BN_CLICKED(IDC_BTN_ABOUT, OnBtnAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCopyTimeDlg ���b�Z�[�W �n���h��

BOOL CCopyTimeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���̃_�C�A���O�p�̃A�C�R����ݒ肵�܂��B�t���[�����[�N�̓A�v���P�[�V�����̃��C��
	// �E�B���h�E���_�C�A���O�łȂ����͎����I�ɐݒ肵�܂���B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R����ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R����ݒ�
	
	// TODO: ���ʂȏ��������s�����͂��̏ꏊ�ɒǉ����Ă��������B

	CheckDlgButton(IDC_CHECK_DISP, 1);	// ���ʃ��X�g�̕\���̃`�F�b�N������
	
	return TRUE;  // TRUE ��Ԃ��ƃR���g���[���ɐݒ肵���t�H�[�J�X�͎����܂���B
}

// �����_�C�A���O�{�b�N�X�ɍŏ����{�^����ǉ�����Ȃ�΁A�A�C�R����`�悷��
// �R�[�h���ȉ��ɋL�q����K�v������܂��BMFC �A�v���P�[�V������ document/view
// ���f�����g���Ă���̂ŁA���̏����̓t���[�����[�N�ɂ�莩���I�ɏ�������܂��B

void CCopyTimeDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��p�̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// �N���C�A���g�̋�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R����`�悵�܂��B
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// �V�X�e���́A���[�U�[���ŏ����E�B���h�E���h���b�O���Ă���ԁA
// �J�[�\����\�����邽�߂ɂ������Ăяo���܂��B
HCURSOR CCopyTimeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// ************************************************************
// �R�s�[���t�H���_�̃u���E�Y
// ************************************************************
void CCopyTimeDlg::OnBtnFrom() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString StrTmp;		// ��Ɨp
	char s_full[MAX_PATH];
	LPITEMIDLIST pidl;
	BROWSEINFO bi;
	ZeroMemory(&bi,sizeof(bi));
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
	StrTmp.LoadString(IDS_Q_SELFROM);	// "�Q�ƌ��t�H���_�̑I��"
	bi.lpszTitle = (LPCSTR)StrTmp;
	bi.hwndOwner = m_hWnd;

	pidl = ::SHBrowseForFolder(&bi);	// �t�H���_�I���E�R�����_�C�A���O
	if(pidl == NULL) return;
	SHGetPathFromIDList(pidl, s_full);

	// ���[�g�t�H���_�̈����B�Ō�� \ �����Ă��邩�ǂ���
	if(s_full[strlen(s_full)-1] != '\\')
		strcat(s_full, "\\");
	strcat(s_full, "*.*");
	// �t�@�C�����̓{�b�N�X���A�b�v�f�[�g����
	SetDlgItemText(IDC_EDIT_FROM, s_full);
	
}

// ************************************************************
// �R�s�[��t�H���_�̃u���E�Y
// ************************************************************
void CCopyTimeDlg::OnBtnTo() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString StrTmp;		// ��Ɨp
	char s_full[MAX_PATH];
	LPITEMIDLIST pidl;
	BROWSEINFO bi;
	ZeroMemory(&bi,sizeof(bi));
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
	StrTmp.LoadString(IDS_Q_SELTO);	// "�R�s�[��̃t�H���_�̑I��"
	bi.lpszTitle = (LPCSTR)StrTmp;
	bi.hwndOwner = m_hWnd;

	pidl = ::SHBrowseForFolder(&bi);	// �t�H���_�I���E�R�����_�C�A���O
	if(pidl == NULL) return;
	SHGetPathFromIDList(pidl, s_full);

	// ���[�g�t�H���_�̈����B�Ō�� \ �����Ă��邩�ǂ���
	if(s_full[strlen(s_full)-1] != '\\')
		strcat(s_full, "\\");
	// �t�@�C�����̓{�b�N�X���A�b�v�f�[�g����
	SetDlgItemText(IDC_EDIT_TO, s_full);
	
}

// ************************************************************
// �v���r���[
// ���ۂɃR�s�[�͍s��Ȃ�
// ************************************************************
void CCopyTimeDlg::OnBtnPreview() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString StrTmp, StrTmp1;		// ��Ɨp
	CDlgPreview dlg;				// ���ʕ\���p�_�C�A���O
	CString FpassFrom, FpassTo, StrMes;
	struct _finddata_t finddata;	// �Q�ƌ��t�@�C�������p
	long hFind;						// �Q�ƌ��t�@�C�������p
	CTime tmc_src, tmm_src, tmc_dst, tmm_dst;	// �Q�ƌ��E�R�s�[�� �t�@�C���̍쐬�E�ŏI�ύX����
	CFileStatus Fstatus;			// �t�@�C�����

	// �_�C�A���O���A�p�X���̎擾
	GetDlgItemText(IDC_EDIT_FROM, FpassFrom);
	GetDlgItemText(IDC_EDIT_TO, FpassTo);

	// �t�H���_�����ݒ肳��Ă��Ȃ��Ƃ�
	if(FpassFrom == "" || FpassTo == "")
	{
		StrTmp.LoadString(IDS_ERR_NOSRC);	// �Q�ƌ��A�R�s�[��̑o���̃t�H���_���w�肵�Ă�������
		StrTmp1.LoadString(IDS_ERR_NOSRC_CAP);	// CopyTime����̏��
		MessageBox((LPCSTR)StrTmp, (LPCSTR)StrTmp1, MB_ICONWARNING);
		return;
	}

	StrMes.LoadString(IDS_STR_PASSFROM);	// \r\n�Q�ƌ��t�H���_ : 
	StrMes += FpassFrom;
	StrMes += "\r\n\r\n";

    if( (hFind = _findfirst((LPCSTR)FpassFrom, &finddata )) == -1L )
	{	// �Q�Ɖ��t�@�C����������Ȃ��ꍇ
		StrMes.LoadString(IDS_STR_ERR_NOFROM);
	}
	else{
		if(!(finddata.attrib & _A_SUBDIR))
		{	// ��ڂ̃t�@�C���̔���
			// �ύX��t�@�C�������邩�m�F����
			if(CheckFile(FpassTo, finddata.name, &tmc_dst, &tmm_dst))
			{
				// �Q�ƌ��t�@�C���̓��t�̎擾
				tmm_src = finddata.time_write;
				tmc_src = finddata.time_create;
				// �Q�ƌ��t�@�C���̃f�[�^�̕\��
				StrTmp.Format(IDS_FDATA_FROM, finddata.name,
						tmm_src.GetYear(), tmm_src.GetMonth(), tmm_src.GetDay(),
						tmm_src.GetHour(), tmm_src.GetMinute());
				StrMes += StrTmp;
				// �R�s�[���邩�ǂ����̔��莮
				if(tmm_src == tmm_dst && tmc_src == tmc_dst) StrMes += "\t==  ";
				else StrMes += "\t==> ";
				// �ύX��t�@�C���f�[�^�̕\��
				StrTmp.Format(IDS_FDATA_TO,
						tmm_dst.GetYear(), tmm_dst.GetMonth(), tmm_dst.GetDay(),
						tmm_dst.GetHour(), tmm_dst.GetMinute());
				StrMes += StrTmp;
			}
		}
		while(_findnext( hFind, &finddata ) == 0)
		{	// �����t�@�C����A������
			if(!(finddata.attrib & _A_SUBDIR))
			{
				if(CheckFile(FpassTo, finddata.name, &tmc_dst, &tmm_dst))
				{
					// �Q�ƌ��t�@�C���̓��t�̎擾
					tmm_src = finddata.time_write;
					tmc_src = finddata.time_create;
					// �Q�ƌ��t�@�C���̃f�[�^�̕\��
					StrTmp.Format(IDS_FDATA_FROM, finddata.name,
							tmm_src.GetYear(), tmm_src.GetMonth(), tmm_src.GetDay(),
							tmm_src.GetHour(), tmm_src.GetMinute());
					StrMes += StrTmp;
					// �R�s�[���邩�ǂ����̔��莮
					if(tmm_src == tmm_dst && tmc_src == tmc_dst) StrMes += "\t==  ";
					else StrMes += "\t==> ";
					// �ύX��t�@�C���f�[�^�̕\��
					StrTmp.Format(IDS_FDATA_TO,
							tmm_dst.GetYear(), tmm_dst.GetMonth(), tmm_dst.GetDay(),
							tmm_dst.GetHour(), tmm_dst.GetMinute());
					StrMes += StrTmp;
				}
			}
		}
	}

	// ���ʕ\���̃_�C�A���O
	dlg.m_edit_main_text= StrMes;
	dlg.DoModal();
}

// ************************************************************
// �R�s�[��̃t�@�C���̑��݂��`�F�b�N���A���݂��Ă���΃t�@�C���̎��Ԃ��i�[����
// ************************************************************
// ����
//   FpathTo : �R�s�[��̃t�H���_���i�Ō�� \ �L���t���j
//   Fname : �t�@�C����
//   FCTime : ����ꂽ���Ԃ�Ԃ��ϐ��ւ̃|�C���^ (�쐬��)
//   FMTime : ����ꂽ���Ԃ�Ԃ��ϐ��ւ̃|�C���^ (�ŏI�ύX��)
//
// �߂�l
//   TRUE : �t�@�C�������݁AFTime �Ƀt�@�C���̎��ԁi�ŏI�������ݎ��ԁj���Z�b�g
//   FALSE : �t�@�C�������݂��Ȃ�
// ************************************************************
BOOL CCopyTimeDlg::CheckFile(LPCSTR FpathTo, LPCSTR Fname, CTime *FCTime, CTime *FMTime)
{
	CString StrFpath;				// �����Ώۃt�@�C���̃t���p�X��
	CFileStatus Fstatus;			// �t�@�C�����

	// �����Ώۃt�@�C���̃t���p�X��g�ݗ��Ă�
	StrFpath = FpathTo;
	StrFpath += Fname;

	if(CFile::GetStatus(StrFpath, Fstatus))
	{	// �t�@�C������
		*FCTime = Fstatus.m_ctime;	// �쐬����
		*FMTime = Fstatus.m_mtime;	// �ŏI�ύX����
		return TRUE;
	}
	else
	{
		return FALSE;	// �t�@�C����������Ȃ�
	}  
}

// ************************************************************
// �^�C���X�^���v�̃R�s�[�̃{�^�����������Ƃ��̏���
// ************************************************************
void CCopyTimeDlg::OnBtnExec() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CDlgPreview dlg;	// ���ʕ\���̃_�C�A���O
	CString FpassFrom, FpassTo, StrMes, StrTmp, StrTmp1;
	struct _finddata_t finddata;	// findfirst�p
	long hFind;						// findfirst�p
	CTime tmc_src, tmm_src, tmc_dst, tmm_dst;	// �Q�ƌ��E�R�s�[�� �t�@�C���̍쐬�E�ŏI�ύX����
	CFileStatus Fstatus;			// ������ύX����Ƃ��Ɏg��
	int counter = 0;				// ���������t�@�C���̌��𐔂���
	BOOL iModtimePriority = FALSE;	// �쐬�������ŏI�X�V�����ŏ㏑��

	if(IsDlgButtonChecked(IDC_CHECK_MODPRI))
		iModtimePriority = TRUE;

	// ���̓{�b�N�X����A�p�X�����擾����
	GetDlgItemText(IDC_EDIT_FROM, FpassFrom);
	GetDlgItemText(IDC_EDIT_TO, FpassTo);

	if(FpassFrom == "" || FpassTo == "")
	{
		StrTmp.LoadString(IDS_ERR_NOSRC);
		StrTmp1.LoadString(IDS_ERR_NOSRC_CAP);
		MessageBox((LPCSTR)StrTmp, (LPCSTR)StrTmp1, MB_ICONWARNING);
		return;	// �������͂���Ă��Ȃ��Ƃ��A�G���[
	}

	StrMes.LoadString(IDS_STR_PASSFROM);
	StrMes += FpassFrom;
	StrMes += "\r\n\r\n";

    if( (hFind = _findfirst((LPCSTR)FpassFrom, &finddata )) == -1L )
	{
		StrMes.LoadString(IDS_STR_ERR_NOFROM);
	}
	else{
		if(!(finddata.attrib & _A_SUBDIR))
		{	// ��ڂ̃t�@�C���̔���
			// �ύX��t�@�C�������邩�m�F����
			if(CheckFile(FpassTo, finddata.name, &tmc_dst, &tmm_dst))
			{
				// �Q�ƌ��t�@�C���̓��t�̎擾
				tmm_src = finddata.time_write;
				tmc_src = finddata.time_create;
				if(tmm_src != tmm_dst || tmc_src != tmc_dst)
				{	// �ŏI�ύX�����܂��͍쐬�������Ⴄ�ꍇ�� �R�s�[������
					// �Q�ƌ��t�@�C���̃f�[�^�̕\��
					StrTmp.Format(IDS_FDATA_FROM, finddata.name,
						tmm_src.GetYear(), tmm_src.GetMonth(), tmm_src.GetDay(),
						tmm_src.GetHour(), tmm_src.GetMinute());
					StrMes += StrTmp;
					StrMes += "\t==> ";
					// �ύX��t�@�C���f�[�^�̕\��
					StrTmp.Format(IDS_FDATA_TO,
						tmm_dst.GetYear(), tmm_dst.GetMonth(), tmm_dst.GetDay(),
						tmm_dst.GetHour(), tmm_dst.GetMinute());
					StrMes += StrTmp;
					// �t�@�C������ǂݍ���
					StrTmp = FpassTo; StrTmp += finddata.name;
					if(!CFile::GetStatus(StrTmp, Fstatus))
					{	// �R�s�[��t�@�C�����ُ�ȂƂ�
						StrTmp1.LoadString(IDS_ERR_FERR);
						StrMes += StrTmp1;
					}
					else
					{
						// ������ύX���� �t�@�C������������
						Fstatus.m_ctime = tmc_src;
						if(iModtimePriority) Fstatus.m_ctime = tmm_src;
						Fstatus.m_mtime = tmm_src;
						try{ CFile::SetStatus(StrTmp, Fstatus); }
						catch(CFileException *e)
						{	// �R�s�[��t�@�C���ɏ������߂Ȃ��Ƃ�
							long dummy = e->m_lOsError;	// �ue �������g���Ă��Ȃ��v�x����������邽�߂̃_�~�[
							if(Fstatus.m_attribute & 0x01) StrTmp1.LoadString(IDS_ERR_FWPROTECT);
							else StrTmp1.LoadString(IDS_ERR_FNWRT);
							StrMes += StrTmp1;
							counter--;
						}
						counter++;
					}
				}
			}
		}
		while(_findnext( hFind, &finddata ) == 0)
		{	// �����t�@�C����A������
			if(!(finddata.attrib & _A_SUBDIR))
			{
				if(CheckFile(FpassTo, finddata.name, &tmc_dst, &tmm_dst))
				{
					// �Q�ƌ��t�@�C���̓��t�̎擾
					tmm_src = finddata.time_write;
					tmc_src = finddata.time_create;
					if(tmm_src != tmm_dst || tmc_src != tmc_dst)
					{	// �ŏI�ύX�����܂��͍쐬�������Ⴄ�ꍇ�� �R�s�[������
						// �Q�ƌ��t�@�C���̃f�[�^�̕\��
						StrTmp.Format(IDS_FDATA_FROM, finddata.name,
							tmm_src.GetYear(), tmm_src.GetMonth(), tmm_src.GetDay(),
							tmm_src.GetHour(), tmm_src.GetMinute());
						StrMes += StrTmp;
						StrMes += "\t==> ";
						// �ύX��t�@�C���f�[�^�̕\��
						StrTmp.Format(IDS_FDATA_TO,
							tmm_dst.GetYear(), tmm_dst.GetMonth(), tmm_dst.GetDay(),
							tmm_dst.GetHour(), tmm_dst.GetMinute());
						StrMes += StrTmp;
						// �t�@�C������ǂݍ���
						StrTmp = FpassTo; StrTmp += finddata.name;
						if(!CFile::GetStatus(StrTmp, Fstatus))
						{
							StrTmp1.LoadString(IDS_ERR_FERR);
							StrMes += StrTmp1;
						}
						else
						{
							// ������ύX���� �t�@�C������������
							Fstatus.m_ctime = tmc_src;
							if(iModtimePriority) Fstatus.m_ctime = tmm_src;
							Fstatus.m_mtime = tmm_src;
							try{ CFile::SetStatus(StrTmp, Fstatus); }
							catch(CFileException *e)
							{
								long dummy = e->m_lOsError;	// �ue �������g���Ă��Ȃ��v�x����������邽�߂̃_�~�[
								if(Fstatus.m_attribute & 0x01) StrTmp1.LoadString(IDS_ERR_FWPROTECT);
								else StrTmp1.LoadString(IDS_ERR_FNWRT);
								StrMes += StrTmp1;
								counter--;
							}
							counter++;
						}
					}
				}
			}
		}
	}
	if(IsDlgButtonChecked(IDC_CHECK_DISP))
	{	// ���ʃ��X�g��\������
		StrMes += "\r\n\r\n";
		if(counter > 0)
		{
			StrTmp1.LoadString(IDS_MES_COPYFILECOUNT);
			StrTmp.Format(StrTmp1, counter);
		}
		else
		{
			StrTmp.LoadString(IDS_MES_NOFILCOPY);
		}
		StrMes += StrTmp;
		dlg.m_edit_main_text= StrMes;
		dlg.DoModal();
	}
	else if(!counter)
	{
		StrMes.LoadString(IDS_MES_NOFILCOPY);
		StrTmp1.LoadString(IDS_ERR_NOSRC_CAP);
		MessageBox((LPCSTR)StrMes, (LPCSTR)StrTmp1, MB_ICONWARNING);
	}
	
}

// ************************************************************
// ABOUT �_�C�A���O�̕\��
// ************************************************************
void CCopyTimeDlg::OnBtnAbout() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CDlgAbout dlg;
	dlg.DoModal();
	
}

// ************************************************************
// �w���v�{�^���������ƁA�w���v��\������
// ************************************************************
void CCopyTimeDlg::OnBtnHelp() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	WinHelp(1000,HELP_CONTENTS);
}

// ************************************************************
// F1 �L�[�̏���
// ************************************************************
BOOL CCopyTimeDlg::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
	WinHelp(1000,HELP_CONTENTS);
	return TRUE;
//	return CDialog::OnHelpInfo(pHelpInfo);
}

// ************************************************************
// EOF
