// ************************************************************
// ���C���_�C�A���O�A�o�[�W�����_�C�A���O
// ************************************************************

#include "stdafx.h"
#include "ShiftTime.h"
#include "ShiftTimeDlg.h"
#include "DlgSelectExt.h"
#include "DlgHelpDoc.h"
#include <io.h>			// findfirst

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// ************************************************************
// CAboutDlg �o�[�W�����_�C�A���O
// ************************************************************

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂�
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// ���b�Z�[�W �n���h��������܂���B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ************************************************************
// CShiftTimeDlg ���C���_�C�A���O
// ************************************************************

CShiftTimeDlg::CShiftTimeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShiftTimeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShiftTimeDlg)
		// ����: ���̈ʒu�� ClassWizard �ɂ���ă����o�̏��������ǉ�����܂��B
	//}}AFX_DATA_INIT
	// ����: LoadIcon �� Win32 �� DestroyIcon �̃T�u�V�[�P���X��v�����܂���B
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShiftTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShiftTimeDlg)
	DDX_Control(pDX, IDC_CHECK_ZEROSEC, m_chk_ZeroSec);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CShiftTimeDlg, CDialog)
	//{{AFX_MSG_MAP(CShiftTimeDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BROWSE, OnBtnBrowse)
	ON_BN_CLICKED(IDC_BTN_WILDCARD, OnBtnWildcard)
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_BTN_EXEC, OnBtnExec)
	ON_BN_CLICKED(IDC_BTN_HELP, OnBtnHelp)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CShiftTimeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "�o�[�W�������..." ���j���[���ڂ��V�X�e�� ���j���[�֒ǉ����܂��B

	// IDM_ABOUTBOX �̓R�}���h ���j���[�͈̔͂łȂ���΂Ȃ�܂���B
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���̃_�C�A���O�p�̃A�C�R����ݒ肵�܂��B�t���[�����[�N�̓A�v���P�[�V�����̃��C��
	// �E�B���h�E���_�C�A���O�łȂ����͎����I�ɐݒ肵�܂���B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R����ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R����ݒ�
	
	// TODO: ���ʂȏ��������s�����͂��̏ꏊ�ɒǉ����Ă��������B

	// ***********************
	// �_�C�A���O�\���̏����l��ݒ�
	// ***********************
	::GetTempPath(sizeof(szTmp256), szTmp256);
	SetDlgItemText(IDC_EDIT_PATH, szTmp256);	// �e���|�����t�H���_���Ƃ肠�����\��
	SetDlgItemText(IDC_EDIT_FILE, "*.*");

	SetDlgItemInt(IDC_EDIT_YEAR, 0);
	SetDlgItemInt(IDC_EDIT_MONTH, 0);
	SetDlgItemInt(IDC_EDIT_DAY, 0);
	SetDlgItemInt(IDC_EDIT_HOUR, 0);
	SetDlgItemInt(IDC_EDIT_MIN, 0);
	SetDlgItemInt(IDC_EDIT_SEC, 0);
	
	CheckRadioButton(IDC_RADIO_SHIFT, IDC_RADIO_SHIFT_2, IDC_RADIO_SHIFT);
	m_chk_ZeroSec.SetCheck(0);	// �����l�́u�[���b�ɂ��Ȃ��

	return TRUE;  // TRUE ��Ԃ��ƃR���g���[���ɐݒ肵���t�H�[�J�X�͎����܂���B
}

void CShiftTimeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����_�C�A���O�{�b�N�X�ɍŏ����{�^����ǉ�����Ȃ�΁A�A�C�R����`�悷��
// �R�[�h���ȉ��ɋL�q����K�v������܂��BMFC �A�v���P�[�V������ document/view
// ���f�����g���Ă���̂ŁA���̏����̓t���[�����[�N�ɂ�莩���I�ɏ�������܂��B

void CShiftTimeDlg::OnPaint() 
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
HCURSOR CShiftTimeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// *****************************************
// �p�X�̎Q�ƃ{�^���������ꂽ�Ƃ�
// �R�����_�C�A���O��\������
// *****************************************
void CShiftTimeDlg::OnBtnBrowse() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	char s_full[MAX_PATH], s_full2[MAX_PATH];
	CString strTmp;
	LPITEMIDLIST pidl;
	BROWSEINFO bi;

	ZeroMemory(&bi,sizeof(bi));
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
	strTmp.LoadString(STR_MES_BROWSEFOLDER);
	bi.lpszTitle = (LPCSTR)strTmp;		// �Ώۃt�H���_�̑I��
	bi.hwndOwner = m_hWnd;
	bi.pszDisplayName = (LPSTR)s_full2;		// �g��Ȃ����̈悾���͓n��

	pidl = ::SHBrowseForFolder(&bi);
	if(pidl == NULL) return;
	SHGetPathFromIDList(pidl, s_full);

	// ���[�g�t�H���_�̈����B�Ō�� \ �����Ă��邩�ǂ���
	if(s_full[strlen(s_full)-1] != '\\')
		strcat(s_full, "\\");
	// �t�@�C�����̓{�b�N�X���A�b�v�f�[�g����
	SetDlgItemText(IDC_EDIT_PATH, s_full);
	
}

// *****************************************
// �t�@�C�����Ƀ��C���h�J�[�h�����
// *****************************************
void CShiftTimeDlg::OnBtnWildcard() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CDlgSelectExt dlg;

	dlg.m_radio_sel = 10;

	if(dlg.DoModal() == IDOK)
	{
		switch(dlg.m_radio_sel)
		{
			case 0 : 	SetDlgItemText(IDC_EDIT_FILE, "*.jpg"); break;
			case 1 : 	SetDlgItemText(IDC_EDIT_FILE, "*.jpeg"); break;
			case 2 : 	SetDlgItemText(IDC_EDIT_FILE, "*.jp*"); break;
			case 3 : 	SetDlgItemText(IDC_EDIT_FILE, "*.tif"); break;
			case 4 : 	SetDlgItemText(IDC_EDIT_FILE, "*.bmp"); break;
			case 5 : 	SetDlgItemText(IDC_EDIT_FILE, "*.gif"); break;
			case 6 : 	SetDlgItemText(IDC_EDIT_FILE, "*.mp3"); break;
			case 7 : 	SetDlgItemText(IDC_EDIT_FILE, "*.mpg"); break;
			case 8 : 	SetDlgItemText(IDC_EDIT_FILE, "*.avi"); break;
			case 9 : 	SetDlgItemText(IDC_EDIT_FILE, "*.dat"); break;
			case 10 : 	SetDlgItemText(IDC_EDIT_FILE, "*.*"); break;
			default : 	SetDlgItemText(IDC_EDIT_FILE, "Program Error"); break;
		}
	}
	
}

// *****************************************
// �N�����Ȃǂ̐����X�N���[���o�[�������ꂽ�ꍇ�̏���
// *****************************************
void CShiftTimeDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
	
//	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
	int nYear, nMonth, nDay, nHour, nMin, nSec, nOp;

	// ���Ԑݒ�̌��݂̃e�L�X�g�{�b�N�X��ǂݍ���
	nYear = GetDlgItemInt(IDC_EDIT_YEAR, 0);
	nMonth = GetDlgItemInt(IDC_EDIT_MONTH, 0);
	nDay = GetDlgItemInt(IDC_EDIT_DAY, 0);
	nHour = GetDlgItemInt(IDC_EDIT_HOUR, 0);
	nMin = GetDlgItemInt(IDC_EDIT_MIN, 0);
	nSec = GetDlgItemInt(IDC_EDIT_SEC, 0);

	// �㉺�̖�󂪃N���b�N���ꂽ�Ƃ��̕�������SGN�ϐ��ɃZ�b�g
	switch(nSBCode)
	{
		case SB_LINEUP :
			nOp=1; break;
		case SB_LINEDOWN :
			nOp=-1; break;
		default :
			nOp=0; break;
	}

	// �N���b�N���ꂽ�R���g���[��ID�ɂ��������āA�Y���̃e�L�X�g�{�b�N�X�̒l��ύX����
	if(pScrollBar->GetDlgCtrlID() == IDC_SCRL_YEAR) SetDlgItemInt(IDC_EDIT_YEAR, nYear + nOp);
	if(pScrollBar->GetDlgCtrlID() == IDC_SCRL_MONTH) SetDlgItemInt(IDC_EDIT_MONTH, nMonth + nOp);
	if(pScrollBar->GetDlgCtrlID() == IDC_SCRL_DAY) SetDlgItemInt(IDC_EDIT_DAY, nDay + nOp);
	if(pScrollBar->GetDlgCtrlID() == IDC_SCRL_HOUR) SetDlgItemInt(IDC_EDIT_HOUR, nHour + nOp);
	if(pScrollBar->GetDlgCtrlID() == IDC_SCRL_MIN) SetDlgItemInt(IDC_EDIT_MIN, nMin + nOp);
	if(pScrollBar->GetDlgCtrlID() == IDC_SCRL_SEC) SetDlgItemInt(IDC_EDIT_SEC, nSec + nOp);

}

// *****************************************
// ���C�� ���[�`��
// *****************************************
void CShiftTimeDlg::OnBtnExec() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	BOOL bShiftPrev = FALSE;	// �O�ɂ��炷
	BOOL bZeroSec = FALSE;		// �[���b�ɂ��킹��
	BOOL bLog = FALSE;			// ���O��\�����邩�ǂ���
	CString szTmp1, szTmp2, szLogMsg;
	CString szAppName;			// �A�v���P�[�V�������i�_�C�A���O�p�j
	CString szTmpMsg;			// String Table �ǂݎ��p
	CString szPath;				// �p�X���i�t�@�C�����܂܂��j
	int nCount = 0;				// ���������t�@�C����
	struct _finddata_t finddata;	// findfirst�p
	long hFind;						// findfirst�p
	CTime tm_src, tm_dst;			// �o���̃t�@�C���̓���
	CFileStatus Fstatus;			// ������ύX����Ƃ��Ɏg��

	int nYear, nMonth, nDay, nHour, nMin, nSec, nOp;

	szAppName.LoadString(IDS_APPNAME);

	// �`�F�b�N�{�b�N�X�̓��e��ǂݎ��
	if(IsDlgButtonChecked(IDC_RADIO_SHIFT)) bShiftPrev = TRUE;
	if(IsDlgButtonChecked(IDC_CHECK_ZEROSEC)) bZeroSec = TRUE;
	if(IsDlgButtonChecked(IDC_CHECK_LOG)) bLog = TRUE;
	// �u�O�ɂ��炷�v�A�u���ɂ��炷�v�̕����̐ݒ�iSGN�j
	if(bShiftPrev) nOp = -1;
	else  nOp = 1;

	// ���Ԑݒ�̃e�L�X�g�{�b�N�X��ǂݎ��
	nYear = nOp * GetDlgItemInt(IDC_EDIT_YEAR, 0);
	nMonth = nOp * GetDlgItemInt(IDC_EDIT_MONTH, 0);
	nDay = nOp * GetDlgItemInt(IDC_EDIT_DAY, 0);
	nHour = nOp * GetDlgItemInt(IDC_EDIT_HOUR, 0);
	nMin = nOp * GetDlgItemInt(IDC_EDIT_MIN, 0);
	nSec = nOp * GetDlgItemInt(IDC_EDIT_SEC, 0);

	// ������ CTime �`���Ŋi�[  �ő�}68�N
	CTimeSpan tmShift(nYear*365 + nMonth*30 + nDay, nHour, nMin, nSec); 

	// �t�H���_���̃e�L�X�g�{�b�N�X��ǂݎ��
	GetDlgItemText(IDC_EDIT_PATH, szPath);
	if(szPath.GetLength() <= 0)
	{
		szTmpMsg.LoadString(STR_ERR_NOFOLDER);	// �Ώۃt�H���_���w�肳��Ă��܂���
		MessageBox(szTmpMsg, szAppName, MB_ICONSTOP|MB_OK);
		return;
	}
	// �t�@�C�����i���C���h�J�[�h�j�̃e�L�X�g�{�b�N�X��ǂݎ��
	GetDlgItemText(IDC_EDIT_FILE, szTmp2);
	if(szTmp2.GetLength() <= 0)
	{
		szTmpMsg.LoadString(STR_ERR_NOFILEWILD);	// �Ώۃt�@�C�����w�肳��Ă��܂���
		MessageBox(szTmpMsg, szAppName, MB_ICONSTOP|MB_OK);
		return;
	}

	szTmp1 = szPath + szTmp2;	// ���C���h�J�[�h�`���̃p�X����

	// ���O�\�� �̂��߂̕�����̍쐬
	if(bLog)
	{
		szTmpMsg.LoadString(STR_MES_01);	// �����p�X %s\r\n�������� %d �� %d ���� %d ��%d �b\r\n------------------------------\r\n\r\n
		szLogMsg.Format(szTmpMsg, szTmp1, tmShift.GetDays(), tmShift.GetHours(), tmShift.GetMinutes(), tmShift.GetSeconds());
	}

	// *****************************************
	// FINDFIRST �֐��ɂ�� �t�@�C���̌���
	// *****************************************
    if( (hFind = _findfirst((LPCSTR)szTmp1, &finddata )) == -1L )
	{
		szTmpMsg.LoadString(STR_ERR_FINDNOTHING);	// ���������Ɉ�v����t�@�C����������܂���
		MessageBox(szTmpMsg, szAppName, MB_ICONINFORMATION|MB_OK);
		return ;
	}

	if(!(finddata.attrib & _A_SUBDIR))	// �f�B���N�g�������łȂ��ꍇ
	{	// ��ڂ̃t�@�C���̔���
		szTmp2 = szPath + finddata.name;	// �t���p�X�̃t�@�C��������
		if(CFile::GetStatus(szTmp2, Fstatus)) // �t�@�C���̏��𓾂�
		{
			Fstatus.m_mtime += tmShift;			// �����������Čv�Z�i�ŏI�ύX���j
			Fstatus.m_ctime += tmShift;			// �����������Čv�Z�i�쐬���j
			if(bZeroSec)
			{	// �b���[���ɂ��鏈��
				nSec = Fstatus.m_mtime.GetSecond();
				Fstatus.m_mtime -= nSec;
				nSec = Fstatus.m_ctime.GetSecond();
				Fstatus.m_ctime -= nSec;
			}

			// ���O�\�� �̂��߂̕�����̍쐬
			if(bLog)
			{
				szTmpMsg.LoadString(STR_MES_02);	//  ���� : %s  (%04d/%02d/%02d %02d:%02d:%02d)\r\n
				szTmp1.Format(szTmpMsg, szTmp2,
						Fstatus.m_mtime.GetYear(), Fstatus.m_mtime.GetMonth(), Fstatus.m_mtime.GetDay(),
						Fstatus.m_mtime.GetHour(), Fstatus.m_mtime.GetMinute(), Fstatus.m_mtime.GetSecond());
			}
			// *****************************************
			// �t�@�C���ւ̏�������
			// *****************************************
			try{ CFile::SetStatus(szTmp2, Fstatus); }
			catch(CFileException *e)
			{	// �R�s�[��t�@�C���ɏ������߂Ȃ��Ƃ�
				long dummy = e->m_lOsError;	// �ue �������g���Ă��Ȃ��v�x����������邽�߂̃_�~�[
				nCount--;	// ���ƂŁA�C���N�������g�����̂ŁA�����Ō��炵�Ă���
				if(bLog)
				{
					szTmpMsg.LoadString(STR_ERR_WRITE);	//  ���s : %s\r\n
					szTmp1.Format(szTmpMsg, szTmp2);
				}
			}
			// ���������t�@�C�������C���N�������g
			nCount++;

			// ���O�\�� �̂��߂̕�����̍쐬
			if(bLog) szLogMsg += szTmp1;
		}
	}
	while(_findnext( hFind, &finddata ) == 0)
	{	// �����t�@�C����A������
		if(!(finddata.attrib & _A_SUBDIR))	// �f�B���N�g�������łȂ��ꍇ
		{
			szTmp2 = szPath + finddata.name;	// �t���p�X�̃t�@�C��������
			if(CFile::GetStatus(szTmp2, Fstatus)) // �t�@�C���̏��𓾂�
			{
				Fstatus.m_mtime += tmShift;			// �����������Čv�Z�i�ŏI�ύX���j
				Fstatus.m_ctime += tmShift;			// �����������Čv�Z�i�쐬���j
				if(bZeroSec)
				{	// �b���[���ɂ��鏈��
					nSec = Fstatus.m_mtime.GetSecond();
					Fstatus.m_mtime -= nSec;
					nSec = Fstatus.m_ctime.GetSecond();
					Fstatus.m_ctime -= nSec;
				}

				// ���O�\�� �̂��߂̕�����̍쐬
				if(bLog)
				{
					szTmpMsg.LoadString(STR_MES_02);	//  ���� : %s  (%04d/%02d/%02d %02d:%02d:%02d)\r\n
					szTmp1.Format(szTmpMsg, szTmp2,
							Fstatus.m_mtime.GetYear(), Fstatus.m_mtime.GetMonth(), Fstatus.m_mtime.GetDay(),
							Fstatus.m_mtime.GetHour(), Fstatus.m_mtime.GetMinute(), Fstatus.m_mtime.GetSecond());
				}
				// *****************************************
				// �t�@�C���ւ̏�������
				// *****************************************
				try{ CFile::SetStatus(szTmp2, Fstatus); }
				catch(CFileException *e)
				{	// �R�s�[��t�@�C���ɏ������߂Ȃ��Ƃ�
					long dummy = e->m_lOsError;	// �ue �������g���Ă��Ȃ��v�x����������邽�߂̃_�~�[
					nCount--;	// ���ƂŁA�C���N�������g�����̂ŁA�����Ō��炵�Ă���
					if(bLog)
					{
						szTmpMsg.LoadString(STR_ERR_WRITE);	//  ���s : %s\r\n
						szTmp1.Format(szTmpMsg, szTmp2);
					}
				}
				// ���������t�@�C�������C���N�������g
				nCount++;

				// ���O�\�� �̂��߂̕�����̍쐬
				if(bLog) szLogMsg += szTmp1;
			}
		}
	}

	// ���O�̕\��
	if(bLog)
	{
		szTmpMsg.LoadString(STR_MES_03);	// "\r\n------------------------------\r\n%d �̃t�@�C���̓��t�����������܂���"
		szTmp1.Format(szTmpMsg, nCount);
		szLogMsg += szTmp1;
		
		CDlgHelpDoc dlg;

		dlg.m_edit_main = szLogMsg;

		dlg.DoModal();

	}
	else
	{
		// ���O��\�����Ȃ��ꍇ�́A�ύX�����t�@�C������\��
		szTmpMsg.LoadString(STR_MES_04);	// "%d �̃t�@�C���̓��t�����������܂���"
		szTmp1.Format(szTmpMsg, nCount);
		MessageBox(szTmp1, szAppName, MB_ICONINFORMATION|MB_OK);
	}
}

// *****************************************
// �w���v �̕\��
// *****************************************
void CShiftTimeDlg::OnBtnHelp() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CDlgHelpDoc dlg;
	CString strTmp;

	strTmp.LoadString(STR_SW_LANG);

	if(strTmp == "JPN")
	{	// ���{�ꃊ�\�[�X�̂Ƃ�

		dlg.m_edit_main = "\r\n"
		
		"ShiftTime - �^�C���X�^���v�����c�[��\r\n"
		" Version 1.1   (freeware)\r\n"
		"\r\n\r\n"
		" (C) 2002 INOUE. Hirokazu\r\n"
		"\r\n\r\n\r\n"
		"�y�͂��߂Ɂz\r\n"
		"���̃v���O�����́A�����̃t�@�C���̃^�C���X�^���v�i���ԁj���ꊇ���āw��莞�Ԃ��炷�x�ݒ���s���c�[���ł�\r\n"
		"�����̖ړI�́A�����̂���C�O�ŎB�e�����u�f�W�J���̉摜�t�@�C���v�̃^�C���X�^���v"
		"�����n�����ɐݒ肵�Ȃ������ߍ쐬���Ă��܂�\r\n"
		"\r\n"
		"�t�@�C���̍쐬��������эŏI�X�V�������Ώۂł�\r\n"
		"\r\n"
		"UNIX �̃X�N���v�g�g���ȊO�̕������ł� :-) \r\n"
		"\r\n\r\n"
		"�y������z\r\n"
		"Windows 95/98/Me/NT/200/XP (���{��ł���ъe�����)\r\n"
		"MFC42.DLL ����� MSVCRT.DLL ���V�X�e���t�H���_�ɑ��݂��邱�ƁiVisual C++ 6.0 �Ή��Łj �Â��o�[�W������DLL�̏ꍇ�A�N���ł��܂���B\r\n"
		"\r\n"
		"���̃v���O�����ɂ́A���{��Ɖp��̂Q��ނ̐ݒ肪�܂܂�Ă��܂��B���{��ȊO��Windows�ŋN�������ꍇ�A�����I�ɉp�ꃂ�[�h�œ��삵�܂��B\r\n"
		"\r\n\r\n"
		"�y�C���X�g�[���z\r\n"
		"���̉�ʂ����Ă���Ƃ������Ƃ́A���łɃC���X�g�[�������ł�\r\n"
		"\r\n\r\n"
		"�y�A���C���X�g�[���z\r\n"
		"���̃v���O�����́A���W�X�g������ѐݒ�t�@�C���Ȃǂ𗘗p���܂���\r\n"
		"�v���O�����{�̂���������΂���ŏI���ł�\r\n"
		"\r\n\r\n"
		"�y���p�@�z\r\n"
		"�u�Ώۃt�H���_�v\r\n"
		"   �����Ɂu���v�L�������`�Ŏw�肷�邱�ƁB\r\n"
		"\r\n"
		"�u�Ώۃt�@�C���v\r\n"
		"   ���C���h�J�[�h�i*.JPG ��)���w��\\r\n"
		"\r\n"
		"���t�H���_ + ������̃t�@�C���� �� 256 �������z���Ȃ��͈�\r\n"
		"\r\n"
		"�u���Ԓ����v\r\n"
		"   1����=30���A1�N=365���Ŋ��Z���Ă���\r\n"
		"\r\n"
		"�ݒ荀�ڂ�K�X�ݒ肵����A�����J�n�{�^��������\r\n"
		"\r\n\r\n"
		"�y��z\r\n"
		"D:\\My Documents\\Photo �t�H���_�� D0001.JPG, D0002.JPG, ... D0999.JPG\r\n"
		"�̃^�C���X�^���v�� 9���Ԗ߂�����\r\n"
		"  �i���Ƃ��΁A2002/01/01 12:00 -> 2002/01/01 03:00�j\r\n"
		"\r\n"
		"�� �Ώۃt�H���_�� �uD:\\My Documents\\Photo\\�v �� �Ō�� \\ �L���͏d�v\r\n"
		"�� �Ώۃt�@�C���� �u*.jpg�v\r\n"
		"�� ���Ԓ����� �u9���ԁv�Ɓu�O�ɂ��炷�v��I������\r\n"
		"(�u-9���ԁv�Ɓu���ɂ��炷�v�ł����������ɂȂ�B�j\r\n"
		"\r\n\r\n"
		"�y���������z\r\n"
		"�u�ǂݎ�葮���v�̃t�@�C���͏����ł��Ȃ�\r\n"
		"�t�@�C���ȊO�̂��̂͑ΏۊO�i�t�H���_���j\r\n"
		"\r\n"
		"������ UNIX ���Ԃ͈̔́i���悻1970�N�`2032�N�j�����ݒ�ł��Ȃ�\r\n"
		"Windows�̊g���^�C���X�^���v�̂����u�쐬���v�A�u�ŏI�X�V���v�̂ݐݒ�ł��܂�\r\n"
		"\r\n"
		"�p�X���E�t�@�C�����ɗ��p�ł��镶���́A�ʏ� ANSI �̃A���t�@�x�b�g��z��B�i�����t�@�C�����܂ށj\r\n"
		"���{��̕������g���Ă���ꍇ�A�G���[���o�邩������܂���B�i0x5c�ŃG���[���o�Ȃ����Ƃ͊m�F���Ă��܂����A�S�Ă̕����R�[�h�Ŋm�F�͂��Ă��܂���j\r\n"
		"���S�ɗ��p���Ă����������߂ɂ́ADOS��8+3�`���̃p�X�E�t�@�C�����ŁALFN���g��Ȃ��A���t�@�x�b�g�݂̂ƌ����̂��ł����S�ł�\r\n"
		"�����ɃG���[���|�[�g�𑗂��Ă��������O�ɁA8+3�`���A���t�@�x�b�g�������Ă݂Ă�������\r\n"
		"\r\n"
		"����̓t���[�E�G�A�ł��B������󋵂ɑ΂��Ẵe�X�g�͍s���Ă��܂���B���p�҂̗ǎ����闘�p�����肢���܂�\r\n"
		"\r\n\r\n"
		"�y�e�N�m���W�z\r\n"
		"�\�[�X�R�[�h�̎��������O�ɁA���L��ǂ�ł݂Ă�������\r\n"
		"\r\n"
		"���̃v���O�����́A�Ώۃt�@�C���ɑ΂����̑�������Ă��邾���ł�\r\n"
		"CFile::GetStatus(szTmp2, Fstatus);		// �������擾��\r\n"
		"Fstatus.m_mtime += tmShift;			// �����������Čv�Z\r\n"
		"Fstatus.m_ctime += tmShift;			// �����������Čv�Z\r\n"
		"CFile::SetStatus(szTmp2, Fstatus);		// ��������������\r\n"
		"\r\n"
		"�������݂ł́A��O���� try - catch ���������Ă��܂�\r\n"
		"�Ȃ��A�����̕\����\r\n"
		"CTimeSpan tmShift(nYear*365 + nMonth*30 + nDay, nHour, nMin, nSec); \r\n"
		"\r\n\r\n"
		"�y�g�p���������z\r\n"
		"���̃v���O�����ƃh�L�������g���t���[�E�G�A�[�Ƃ��A���ׂĂ̒��쌠�͍�҂ł����㔎�v�ɑ����܂��B\r\n"
		"����҂͂��̃v���O�����y�уh�L�������g�Ɋւ��邢���Ȃ�ۏ؂��s���܂���B���̃v���O�����̎g�p�͂��ׂĎg�p�҂̐ӔC�ɂ����čs���ĉ������B\r\n"
		"�{���i�̓���i���퓮��A�ُ퓮��j�ɂ���Ĕ�邷�ׂĂ̌��ʂɂ��Ă̑S�ӔC�́A�{�\�t�g�̎g�p�҂ɂ���܂��B\r\n"
		"���̃v���O�����̃T�|�[�g�͒���҈��d�q���[�����g�p���čs���܂����A����҂��T�|�[�g���s���̂̓{�����e�B�A�ł����ċ`���E�Ӗ��ł͂���܂���B\r\n"
		"\r\n"
		"�l�b�g���[�N�𒷊��ԗ���ɂ��邱�Ƃ�����܂��̂ŁA�����I�Ƀ��[������������Ă���\��������܂��̂ł����Ӊ������B\r\n"
		"\r\n"
		"�� �t���[���[�����甭�M���ꂽ���[���́A�������܂��B �g�s�l�k���[����Y�t�t�@�C�����������A�Y�����[�U����̃��[���͂Q�x�Ǝ�M�܂���B�����ӂ��������B\r\n"
		"\r\n"
		"���̃v���O���������Г��Ɍf�ڂ�����A�̔����悤�Ƃ���S�Ă̕���\r\n"
		"\r\n"
		"����҂ɂ�鋖�����ɂ��̃v���O�����ƃh�L�������g��̔����邱�Ƃ͏o���܂���B\r\n"
		"�������A�����\�t�g�Ƃ��Ĕz�z����ꍇ�̓f�B�X�N������X�������A�Œ���̑Ή��̎���𔺂��Ă����܂��܂���B�܂��A�G���Ȃǂ̔̑����ɕt��������Ƃ�������ɏ����܂��B\r\n"
		"\r\n"
		"���ЁE�G�����̋L���Ƃ��Ď��グ��ꍇ��A���l�̖ړI�ŏ��Г��̕t��CD-ROM�Ɏ��^����ꍇ�́A��҂̋�����K�v�Ƃ��܂��B\r\n"
		"�Ȃ��A�����ԗ���ɂ��Ă���ꍇ������܂��̂ŁA�f�ڂ̋����̕Ԏ��������ꍇ�́u�s���v�Ɖ��߂��Ă��������B\r\n"
		"\r\n"
		"�����Ȃ�ꍇ�ł��A���̃w���v�t�@�C���ɋL�q����Ă���ȏ�̍�҂̌l���i���[���A�h���X���j���G�����Ɍf�ڂ�����A���J�����肵�Ȃ��ł��������B\r\n"
		"\r\n"
		"�y���[�U�[�E�T�|�[�g�A����z\r\n"
		"�d�q���[��\r\n"
		"  ���L�̃z�[���y�[�W�Ń��[���A�h���X�����J���Ă��܂��B\r\n"
		"  �i�E�C���X���[���΍�̂��߂̎��q��i�ɂ����͊肢�܂��j\r\n"
		"�z�[���y�[�W\r\n"
		"  http://inoue-h.connect.to/\r\n"
		"  http://www.vector.co.jp/authors/VA001911/index.html\r\n"
		"  http://www.ne.jp/asahi/oasis/inoue-h/index.html\r\n"
		"\r\n"
		"��L�̃A�h���X�����ł��Ă���ꍇ�A�����G���W���Łu��㔎�v�v�Ō������Ă��������B\r\n"
		"My Journey - ���̃y�[�W �����̃y�[�W�ł�\r\n";

	}
	else
	{	// �p�ꃊ�\�[�X�̂Ƃ�
		dlg.m_edit_main = "\r\n"
		
		"ShiftTime - Time Stamp Shifting Tool\r\n"
		" Version 1.1   (freeware)\r\n"
		"\r\n\r\n"
		" (C) 2002 INOUE. Hirokazu\r\n"
		"\r\n\r\n\r\n"
		"[Introduction]\r\n"
		"This program is designed for 'to shift time stamp in same folder' .\r\n"
		"I made this program for handling digital camera data file taken abroad ."
		"\r\n"
		"This program change only 'create time' and 'last modified time' .\r\n"
		"\r\n\r\n"
		"[Target System]\r\n"
		"Windows 95/98/Me/NT/200/XP (Japanese and Other Language)\r\n"
		"This program requires MFC42.DLL and MSVCRT.DLL (designed for Visual C++ 6.0) .\r\n"
		"\r\n"
		"This program contains Japanese and English text resource, and Resource is automatically selected according to your OS .\r\n"
		"\r\n\r\n"
		"[Install]\r\n"
		"No need to install .\r\n"
		"\r\n\r\n"
		"[Uninstall]\r\n"
		"Only delete program file .\r\n"
		"\r\n\r\n"
		"[How to Use]\r\n"
		" Folder :\r\n"
		"   Designate folder with browse button , or input path string end with '\\' .\r\n"
		"\r\n"
		" File\r\n"
		"   Designate file match path string using wildcard char .\r\n"
		"\r\n"
		"   *Full Path name must be under 256 chars .\r\n"
		"\r\n"
		" Shift\r\n"
		"   For program convence , 1 month = 30 days , 1 year = 365 days .\r\n"
		"\r\n"
		"Set every input field, press 'Exec' button .\r\n"
		"\r\n\r\n"
		"\r\n\r\n"
		"[Limitation]\r\n"
		"Read Only file cannot be handled .\r\n"
		"Object except file cannot be handled .\r\n"
		"\r\n"
		"Year range is from 1970 to 2032 .\r\n"
		"\r\n\r\n"
		"[Licence agreement]\r\n"
		"This program is free ware. And all copyrights is reserved by INOUE. Hirokazu (author).\r\n"
		"\r\n"
		"There is no guarantee of this program functioning correctly, and author is not responsible to every result of this program. Other condition follows on this document in japanese resource (Japanese Language only, sorry).\r\n"
		"\r\n"
		"[User Support]\r\n"
		"E-Mail\r\n"
		"  Please find mail address from following HOMEPAGE !\r\n"
		"Homepage\r\n"
		"  http://inoue-h.connect.to/\r\n"
		"  http://www.vector.co.jp/authors/VA001911/index.html\r\n"
		"  http://www.ne.jp/asahi/oasis/inoue-h/index.html\r\n";
	}

	// �_�C�A���O�̕\��
	dlg.DoModal();
}

// *****************************************
// F1 �L�[���������Ƃ��̏���
// *****************************************
BOOL CShiftTimeDlg::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
	OnBtnHelp();
	return TRUE;
}
