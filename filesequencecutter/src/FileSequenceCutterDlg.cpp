// FileSequenceCutterDlg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "FileSequenceCutter.h"
#include "FileSequenceCutterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileSequenceCutterDlg �_�C�A���O

CFileSequenceCutterDlg::CFileSequenceCutterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileSequenceCutterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileSequenceCutterDlg)
		// ����: ���̈ʒu�� ClassWizard �ɂ���ă����o�̏��������ǉ�����܂��B
	//}}AFX_DATA_INIT
	// ����: LoadIcon �� Win32 �� DestroyIcon �̃T�u�V�[�P���X��v�����܂���B
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileSequenceCutterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileSequenceCutterDlg)
	DDX_Control(pDX, IDC_RADIO_MARKER, m_radio_marker_ctrl);
	DDX_Control(pDX, IDC_CMB_KEYWORD, m_cmb_keyword_ctrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFileSequenceCutterDlg, CDialog)
	//{{AFX_MSG_MAP(CFileSequenceCutterDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BROWSEFILE, OnBtnBrowsefile)
	ON_BN_CLICKED(IDC_BTN_BROWSEPATH, OnBtnBrowsepath)
	ON_BN_CLICKED(IDC_BTN_ABOUT, OnBtnAbout)
	ON_BN_CLICKED(IDC_BTN_EXEC, OnBtnExec)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileSequenceCutterDlg ���b�Z�[�W �n���h��

BOOL CFileSequenceCutterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���̃_�C�A���O�p�̃A�C�R����ݒ肵�܂��B�t���[�����[�N�̓A�v���P�[�V�����̃��C��
	// �E�B���h�E���_�C�A���O�łȂ����͎����I�ɐݒ肵�܂���B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R����ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R����ݒ�
	
	// TODO: ���ʂȏ��������s�����͂��̏ꏊ�ɒǉ����Ă��������B

	SetDlgItemText(IDC_CMB_KEYWORD, "00 00 00 00 00");
	this->CheckRadioButton(IDC_RADIO_MARKER, IDC_RADIO_MARKER2, IDC_RADIO_MARKER);

	return TRUE;  // TRUE ��Ԃ��ƃR���g���[���ɐݒ肵���t�H�[�J�X�͎����܂���B
}

// �����_�C�A���O�{�b�N�X�ɍŏ����{�^����ǉ�����Ȃ�΁A�A�C�R����`�悷��
// �R�[�h���ȉ��ɋL�q����K�v������܂��BMFC �A�v���P�[�V������ document/view
// ���f�����g���Ă���̂ŁA���̏����̓t���[�����[�N�ɂ�莩���I�ɏ�������܂��B

void CFileSequenceCutterDlg::OnPaint() 
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
HCURSOR CFileSequenceCutterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// **********************************
// �t�@�C���Q�Ƃ̃{�^�����������Ƃ�
// **********************************
void CFileSequenceCutterDlg::OnBtnBrowsefile() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString strTmp1;
	strTmp1.LoadString(STR_BTN_PICKFILE);
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST|OFN_EXPLORER|OFN_READONLY,strTmp1);
	if(dlg.DoModal()==TRUE)
		SetDlgItemText(IDC_EDIT_SRCFILE, dlg.GetPathName());	
}

int CALLBACK myBrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);

// **********************************
// �t�H���_�Q�Ƃ̃{�^�����������Ƃ�
// **********************************
void CFileSequenceCutterDlg::OnBtnBrowsepath() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	char strPathname[MAX_PATH];
	LPITEMIDLIST pidl;
	BROWSEINFO bi;

	// �e�L�X�g�{�b�N�X�ɓ��͂���Ă���e�p�X�𓾂�
	GetDlgItemText(IDC_EDIT_DSTPATH, strPathname, MAX_PATH-1);

	// Win95 �΍� �i�Ō�� \ ���t�����t�H���_���͎󂯕t���Ȃ��j
	if(strlen(strPathname)>3)		// ���[�g�t�H���_�Ƌ󔒂͏���
	{
		if(strPathname[strlen(strPathname)-1] == '\\')
			strPathname[strlen(strPathname)-1] = (char)NULL;
	}

	// BROWSEINFO �\���̂̏�����
	ZeroMemory(&bi,sizeof(bi));
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
	bi.lpszTitle = (LPCSTR)"�e�t�H���_�̑I��";
	bi.hwndOwner = m_hWnd;
	bi.lpfn = &myBrowseCallbackProc;	// �����t�H���_�ݒ�̂��߃R�[���o�b�N�֐��ݒ�
	bi.lParam = (LPARAM)strPathname;	// �����t�H���_���p�����[�^�Ƃ��Đݒ�

	pidl = ::SHBrowseForFolder(&bi);
	if(pidl == NULL) return;			// �L�����Z���{�^���������ꂽ
	SHGetPathFromIDList(pidl, strPathname);

	////////////////////////
	// pidl �𖾎��I�ɉ������
	////////////////////////
	IMalloc *imalloc;
	// Shell�̃������Ǘ��I�u�W�F�N�g���擾
	if( ::SHGetMalloc( &imalloc) != NOERROR) imalloc = NULL;
	// �I�u�W�F�N�g�擾�ɐ��������ꍇ�ɊJ������
	if( imalloc != NULL) imalloc->Free((void *)pidl); // ITEMIDLIST���J��

	// ���[�g�t�H���_�̈����B�Ō�� \ �����Ă��邩�ǂ���
	if(strPathname[strlen(strPathname)-1] != '\\')
		strcat(strPathname, "\\");

	// �t�@�C�����̓{�b�N�X���A�b�v�f�[�g����
	SetDlgItemText(IDC_EDIT_DSTPATH, strPathname);
	
}

// **********************************
// �t�H���_�I�� SDK �_�C�A���O ::SHBrowseForFolder �p�� �R�[���o�b�N�֐�
// **********************************
int CALLBACK myBrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	// �_�C�A���O�������������Ƃ� �iBFFM_INITIALIZED�j
    if(uMsg == BFFM_INITIALIZED){
		// �t�H���_��I������ �iBFFM_SETSELECTION�j���b�Z�[�W
		if(lpData != NULL)
	        SendMessage(hwnd, BFFM_SETSELECTION, (WPARAM)TRUE, lpData);
    }
    return 0;
}


void CFileSequenceCutterDlg::OnBtnAbout() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString strTmp1, strTmp2;

	strTmp1.LoadString(STR_DLG_DLGTITLE);
	strTmp2.LoadString(STR_DLG_ABOUTBOX);

	MessageBox(strTmp2, strTmp1, MB_OK|MB_ICONINFORMATION);	
}

void CFileSequenceCutterDlg::OnBtnExec() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString strTmp1, strTmp2;
	int nKeyword;		// �L�[���[�h�̐��i�o�C�g���j
	unsigned char strKeyword[256];	// �؂�o���p�L�[���[�h
	int i, j, nTmpDat, nKwdMatch;
	int nFound;			// ���������L�[���[�h�̐�

	long fi_marker_1, fi_marker_2;
	long fi_ptr_save;


	CString strFileSrc;
	CString strPathDst;
	CFile fFileSrc, fFileDst;
	CFileException fileException;


	// strtok (�g�[�N���؂�o��) ��p�̕�����錾
	char str_ext_raw[1024];		// �؂�o�����̕�����B�؂�o���ɂ��������Ĕj�󂳂��
	char str_delimit[] = ": ";	// ��؂蕶�� �i�R���� ����� �󔒁j
	char *str_strtok;			// �؂�o���ꂽ���ʕ�����

	char str_tmp[1024];

	GetDlgItemText(IDC_CMB_KEYWORD, strTmp1);

	strncpy(str_ext_raw, strTmp1, 1023);	// �j��ɔ����ăR�s�[

	nKeyword = 0;

	str_strtok = strtok(str_ext_raw, str_delimit);
	if(str_strtok != NULL)
	{
		strncpy(str_tmp, str_strtok, 1023);
		if(IsStrHexnum(str_tmp))
		{
			sscanf(str_tmp, "%x", &i);
			strKeyword[nKeyword] = (char)i;
			nKeyword++;
		}

		for(;;)
		{
			str_strtok = strtok(NULL, str_delimit);
			if(str_strtok == NULL) break;		// ����ȏ㕶���񂪖����ꍇ
			strncpy(str_tmp, str_strtok, 1023);
			if(IsStrHexnum(str_tmp))
			{
				sscanf(str_tmp, "%x", &i);
				strKeyword[nKeyword] = (char)i;
				nKeyword++;
			}
		}
	}

	strKeyword[nKeyword] = (char)0;


	if(nKeyword == 0)
	{	// �L�[���[�h�����������͂���Ă��Ȃ�
		strTmp1.LoadString(STR_DLG_DLGTITLE);
		strTmp2.LoadString(STR_ERR_NOKEYWORD);

		MessageBox(strTmp2, strTmp1, MB_OK|MB_ICONINFORMATION);	

		return;
	}

	if(!GetDlgItemText(IDC_EDIT_SRCFILE, strFileSrc))
	{
		strTmp1.LoadString(STR_DLG_DLGTITLE);
		strTmp2.LoadString(STR_ERR_FILESRC_NOINPUT);

		MessageBox(strTmp2, strTmp1, MB_OK|MB_ICONINFORMATION);	

		return;
	}
	if(!GetDlgItemText(IDC_EDIT_DSTPATH, strPathDst))
	{
		strTmp1.LoadString(STR_DLG_DLGTITLE);
		strTmp2.LoadString(STR_ERR_PATHDST_NOINPUT);

		MessageBox(strTmp2, strTmp1, MB_OK|MB_ICONINFORMATION);	

		return;
	}

	// �f�[�^�t�@�C�����J��
	if( (fi = fopen(strFileSrc, "rb")) == NULL)
	{
		strTmp1.LoadString(STR_DLG_DLGTITLE);
		strTmp2.LoadString(STR_ERR_OPEN_FILESRC);

		MessageBox(strTmp2, strTmp1, MB_OK|MB_ICONINFORMATION);	

		return;
	}

	fi_read_ptr = 0;		// ���݂̃t�@�C���|�C���^�ʒu
	fi_cur_buf_addr = -1;	// �ǂݍ��݃o�b�t�@�̐擪�A�h���X��������
	nKwdMatch = 0;
	fi_marker_1 = -1;
	fi_marker_2 = -1;
	nFound = 0;

	for(;;)
	{
		for(;;)
		{
			j=0;
			nTmpDat = (int)fiReadChar();
			if(nTmpDat < 0) break;	// EOF
			if(nTmpDat == strKeyword[nKwdMatch])
			{
				fi_ptr_save = fi_read_ptr;
				for(j=1; j<=nKeyword-1; j++)
				{
					fi_read_ptr++;
					nKwdMatch++;
					nTmpDat = (int)fiReadChar();
					if(nTmpDat < 0) break;	// EOF
					if(nTmpDat != strKeyword[nKwdMatch]) break;	// �}�b�`���Ȃ�
				}
				fi_read_ptr = fi_ptr_save;
				nKwdMatch = 0;
			}

			if(nTmpDat<0) break;		// EOF
			if(j >= nKeyword) break;	// ������
			fi_read_ptr++;
		}

		if(nTmpDat<0)
		{	// EOF
			fi_read_ptr--;	// �t�@�C�����[
		}


		fi_marker_1 = fi_marker_2;
		fi_marker_2 = fi_read_ptr;

		if(fi_marker_1 >= 0)
		{
			nFound++;
			// �����ŁA�t�@�C���̐؂�o���������ݏ���������
			// fi_marker_1 �` fi_marker_2 - 1
			if(!fiWriteFile(fi_marker_1, fi_marker_2-1, strPathDst, nFound))
			{	// �t�@�C���̏������݂��o���Ȃ�
				break;
			}
		}

		if(nTmpDat<0) break;	// EOF

		fi_read_ptr++;

	}

	fclose(fi);
	
	strTmp1.Format("%d �̃t�@�C����؂�o���܂���", nFound);
	MessageBox(strTmp1);

}

// ������2���܂���1����16�i���������� TRUE ��Ԃ�
// 16�i���Ȃ� 0x00 �̌`���ŕ������ϊ�����
BOOL IsStrHexnum(char *buf)
{
	if(strlen(buf) == 4)
	{
		if(buf[0] == '0' && buf[1] == 'x')
		{
			// 0x00 �̌`���̂Ƃ�
			if(((buf[2] >= '0' && buf[2] <= '9') || (buf[2] >= 'A' && buf[2] <= 'F') || (buf[2] >= 'a' && buf[2] <= 'f')) && ((buf[3] >= '0' && buf[3] <= '9') || (buf[3] >= 'A' && buf[3] <= 'F') || (buf[3] >= 'a' && buf[3] <= 'f')))
				return TRUE;
		}
	}
	if(strlen(buf) == 3)
	{
		if(buf[0] == '0' && buf[1] == 'x')
		{
			// 0x0 �̌`���̂Ƃ�
			if((buf[2] >= '0' && buf[2] <= '9') || (buf[2] >= 'A' && buf[2] <= 'F') || (buf[2] >= 'a' && buf[2] <= 'f'))
				return TRUE;
		}
		else if(buf[2] == 'H' || buf[2] == 'h')
		{
			// 00H �`���̂Ƃ�
			if(((buf[0] >= '0' && buf[0] <= '9') || (buf[0] >= 'A' && buf[0] <= 'F') || (buf[0] >= 'a' && buf[0] <= 'f')) && ((buf[1] >= '0' && buf[1] <= '9') || (buf[1] >= 'A' && buf[1] <= 'F') || (buf[1] >= 'a' && buf[1] <= 'f')))
			{
				// 0x00 �`���ɕϊ�
				buf[4] = (char)0;
				buf[3] = buf[1];
				buf[2] = buf[0];
				buf[1] = 'x';
				buf[0] = '0';
				return TRUE;
			}
		}
	}
	if(strlen(buf) == 2)
	{
		// 00 �̌`���̂Ƃ�
		if(((buf[0] >= '0' && buf[0] <= '9') || (buf[0] >= 'A' && buf[0] <= 'F') || (buf[0] >= 'a' && buf[0] <= 'f')) && ((buf[1] >= '0' && buf[1] <= '9') || (buf[1] >= 'A' && buf[1] <= 'F') || (buf[1] >= 'a' && buf[1] <= 'f')))
		{
			// 0x00 �`���ɕϊ�
			buf[4] = (char)0;
			buf[3] = buf[1];
			buf[2] = buf[0];
			buf[1] = 'x';
			buf[0] = '0';
			return TRUE;
		}
		else if(buf[1] == 'H' || buf[1] == 'h')
		{
			// 0H �`���̂Ƃ�
			if(((buf[0] >= '0' && buf[0] <= '9') || (buf[0] >= 'A' && buf[0] <= 'F') || (buf[0] >= 'a' && buf[0] <= 'f')))
			{
				// 0x00 �`���ɕϊ�
				buf[3] = (char)0;
				buf[2] = buf[0];
				buf[1] = 'x';
				buf[0] = '0';
				return TRUE;
			}
		}
	}
	if(strlen(buf) == 1)
	{
		// 0 �`���̂Ƃ�
		if(((buf[0] >= '0' && buf[0] <= '9') || (buf[0] >= 'A' && buf[0] <= 'F') || (buf[0] >= 'a' && buf[0] <= 'f')))
		{
			// 0x00 �`���ɕϊ�
			buf[3] = (char)0;
			buf[2] = buf[0];
			buf[1] = 'x';
			buf[0] = '0';
			return TRUE;
		}
	}

	return FALSE;
}

int CFileSequenceCutterDlg::fiReadChar()
{
	int temp_addr;

	if((fi_cur_buf_addr < 0) || !((fi_cur_buf_addr <= fi_read_ptr) && (fi_read_ptr < fi_cur_buf_addr+FI_BUFFER_SIZE)))
	{	// �t�@�C���̓ǂݍ���
		fi_cur_buf_addr = (fi_read_ptr / FI_BUFFER_SIZE)*FI_BUFFER_SIZE;	// �擪�A�h���X
		if(fseek(fi, fi_cur_buf_addr, SEEK_SET))
			return FALSE;		// �V�[�N���s
		fi_cur_buf_size = fread(fi_buf, 1, FI_BUFFER_SIZE, fi);
	}

	temp_addr = fi_read_ptr - fi_cur_buf_addr;
	if(temp_addr > fi_cur_buf_size) return -1;

	return (int)fi_buf[temp_addr];

}

BOOL CFileSequenceCutterDlg::fiWriteFile(long nStart, long nEnd, CString strFpath, int nSeqNo)
{
	long nRead, nLength, li;
	int i;
	CString strFfullpath;
	CFileStatus Fstatus;

	FILE *fo;

	if(nStart >= nEnd) return FALSE;

	fo = NULL;

	for(i=0; i<1024; i++)
	{
		strFfullpath.Format("%sdat%05d.dat", strFpath, nSeqNo+i);

		if(CFile::GetStatus(strFfullpath, Fstatus))		// �t�@�C�������݂���
			continue;

		// �f�[�^�t�@�C�����J��
		if( (fo = fopen(strFfullpath, "wb")) != NULL)
			break;	// �t�@�C�����J�����ꍇ�̓��[�v���o��
	}

	if(fo == NULL) return FALSE;	// �t�@�C�����쐬�ł��Ȃ�����

	fi_cur_buf_addr = -1;		// �ǂݍ��݃o�b�t�@�j��

	fseek(fi, nStart, SEEK_SET);
	for(li=0; ; li++)
	{
		nLength = nEnd - nStart + 1;
		if(nLength > FI_BUFFER_SIZE) nLength = FI_BUFFER_SIZE;

		nRead = fread(fi_buf, 1, nLength, fi);
	
		if(nRead <= 0) break;
		if(fwrite(fi_buf, 1, nRead, fo) != (size_t)nRead) break;

		nStart = nStart + FI_BUFFER_SIZE;
		if(nStart > nEnd) break;		// �R�s�[����

	}

	fclose(fo);

	return TRUE;
}
