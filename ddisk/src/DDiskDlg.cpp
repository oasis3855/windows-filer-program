// ************************************************************
// ���C���E�_�C�A���O CDDiskDlg
// ************************************************************

#include "stdafx.h"
#include "DDisk.h"
#include "DDiskDlg.h"
#include "DDiskConfig.h"
#include "DiskCore.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDDiskDlg �_�C�A���O

CDDiskDlg::CDDiskDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDDiskDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDDiskDlg)
	m_sect = 0;
	m_size = 0;
	//}}AFX_DATA_INIT
	// ����: LoadIcon �� Win32 �� DestroyIcon �̃T�u�V�[�P���X��v�����܂���B
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	theApp = (CDDiskApp *)AfxGetApp();

}

void CDDiskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDDiskDlg)
	DDX_Control(pDX, IDC_COMBO_DISK, m_cmb_disk);
	DDX_Text(pDX, IDC_EDIT_SECT, m_sect);
	DDX_Text(pDX, IDC_EDIT_SIZE, m_size);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDDiskDlg, CDialog)
	//{{AFX_MSG_MAP(CDDiskDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_READ, OnBtnRead)
	ON_BN_CLICKED(IDC_BTN_DPB, OnBtnDpb)
	ON_BN_CLICKED(IDC_BTN_CONFIG, OnBtnConfig)
	ON_WM_VSCROLL()
	ON_EN_KILLFOCUS(IDC_EDIT_SIZE, OnKillfocusEditSize)
	ON_BN_CLICKED(IDC_BTN_BROWSE, OnBtnBrowse)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTN_WRITE, OnBtnWrite)
	ON_BN_CLICKED(IDC_BTN_EDIT, OnBtnEdit)
	ON_BN_CLICKED(IDC_BTN_HELP, OnBtnHelp)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDDiskDlg ���b�Z�[�W �n���h��

// �����_�C�A���O�{�b�N�X�ɍŏ����{�^����ǉ�����Ȃ�΁A�A�C�R����`�悷��
// �R�[�h���ȉ��ɋL�q����K�v������܂��BMFC �A�v���P�[�V������ document/view
// ���f�����g���Ă���̂ŁA���̏����̓t���[�����[�N�ɂ�莩���I�ɏ�������܂��B

void CDDiskDlg::OnPaint() 
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
HCURSOR CDDiskDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// ************************************************************
// �_�C�A���O���������̏����l�ݒ�
// ************************************************************
BOOL CDDiskDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���̃_�C�A���O�p�̃A�C�R����ݒ肵�܂��B�t���[�����[�N�̓A�v���P�[�V�����̃��C��
	// �E�B���h�E���_�C�A���O�łȂ����͎����I�ɐݒ肵�܂���B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R����ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R����ݒ�
	
	// TODO: ���ʂȏ��������s�����͂��̏ꏊ�ɒǉ����Ă��������B
	// �h���C�u�̃R���{�{�b�N�X�̏����ݒ�
	int i;
	
	for(i=1;i<=26;i++)
	{	// Z �܂ł̃h���C�u��ݒ�
		sprintf(m_buf, "%2d (%c:)", i, 0x40+i);
		m_cmb_disk.AddString(m_buf);
	}
	m_cmb_disk.SetCurSel(0); // �����ݒ�� A:

	// �Z�N�^��0�Ƃ���
	SetDlgItemInt(IDC_EDIT_SECT, 0);

	// �Z�N�^�T�C�Y��1�Ƃ���
	SetDlgItemInt(IDC_EDIT_SIZE, 1);

	// ��������Ӱ�ނ��m�[�}���f�[�^�Ƃ���
	CheckRadioButton(IDC_RADIO_TYPE, IDC_RADIO_TYPE4, IDC_RADIO_TYPE);

	
	return TRUE;  // TRUE ��Ԃ��ƃR���g���[���ɐݒ肵���t�H�[�J�X�͎����܂���B
}

// ************************************************************
// �Z�N�^�[�܂��̓Z�N�^�[���̃X�N���[���o�[�������ꂽ�ꍇ�̏���
//
// CScrollBar �́A���ɂ����Ă���Ȃ��̂ŁACWnd���X�N���[���o�[�������ꂽ���Ƃ����m����
// ���������Ȃ��Ƃ����Ȃ��B
// ************************************************************
void CDDiskDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
	DWORD n_sect;
	WORD n_size;
	
	n_sect = GetDlgItemInt(IDC_EDIT_SECT);
	n_size = GetDlgItemInt(IDC_EDIT_SIZE);

	if(pScrollBar->GetDlgCtrlID() == IDC_SCR_SECT)
	{
		switch(nSBCode)
		{
			case SB_LINEUP :
				n_sect++; break;
			case SB_LINEDOWN :
				if(n_sect>0) n_sect--;
				break;
			default : break;
		}
		SetDlgItemInt(IDC_EDIT_SECT, n_sect);
	}
	else if(pScrollBar->GetDlgCtrlID() == IDC_SCR_SIZE)
	{
		switch(nSBCode)
		{
			case SB_LINEUP :
				n_size++; break;
			case SB_LINEDOWN :
				if(n_size>1) n_size--;
				break;
			default : break;
		}
		SetDlgItemInt(IDC_EDIT_SIZE, n_size);
	}

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

// ************************************************************
// �u�\��(Read)�v�{�^���������ꂽ�ꍇ
// �_���f�B�X�N��ǂݍ��݁A�v���r���[�G���A�ɕ\������
// ************************************************************
void CDDiskDlg::OnBtnRead() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString tmpStr, tmpStr2;	// �X�g�����O ���\�[�X �ǂݍ��ݗp
	CString str="";				// �_�C�A���O�� ���E�C���h�E�p

	HANDLE hdev;
	char buf2[65], buf3[18];
	unsigned int i,j,k;
	DOSDPB dpb;
	int b_DPB_suc=0, b_Read_suc=0; 

	BYTE n_drive=0;
	DWORD n_sect=0;
	WORD n_size=1;
	n_drive = m_cmb_disk.GetCurSel() + 1;	// A=1 B=2 �ƂȂ�悤�ɁA1����
	n_sect = GetDlgItemInt(IDC_EDIT_SECT);
	n_size = GetDlgItemInt(IDC_EDIT_SIZE);
	if(n_size < 1) n_size = 1;

	// DeviceIoControl �p�� virtual device driver ���J��
	hdev = CreateFile("\\\\.\\VWIN32", 0, 0, NULL, 0, 0, NULL);
	if(hdev == INVALID_HANDLE_VALUE)
	{	// �n���h�����J���Ȃ������ꍇ
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_VWIN32);
		MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
		return ;
	}

	// DPB ��ǂݍ��ށi�f�B�X�N�̊�{�������W����j
	if(!ReadDPB(hdev, n_drive, &dpb))
	{	// DPB ���J���Ȃ������Ƃ�
		CloseHandle(hdev);
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_DPBREAD);
		MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
		return;
	}
	else
	{	// DPB ���ǂݍ��߂��ꍇ
		sprintf(m_buf, "Drive = %u\r\nTotal sectors = %u\r\nBytes per sector = %u\r\n",
			n_drive, dpb.cTotalSectors, dpb.cbSec);
		str += m_buf;
	}

	// �w��̃Z�N�^�[������������i�ǂݍ��݁j
	for(i=0; i<n_size; i++)
	{
		sprintf(m_buf, "\r\n====== Sector %u ======\r\n", n_sect+i);
		str += m_buf;

		// ********* ���ړǂݍ��� **********
		if(theApp->m_inttype == 2)	// INT 21H FUNC 7305H Win98
			b_Read_suc = ReadLogicalSectors(hdev, n_drive, n_sect+i, 1, (unsigned char*)&m_mainbuf);
		else if(theApp->m_inttype == 1)	// INT 25H Win95
			b_Read_suc = ReadLogicalSectors25(hdev, n_drive, n_sect+i, 1, (unsigned char*)&m_mainbuf);
		if(!b_Read_suc)
		{
			str += "====== Read Fail ======\r\n";
			continue ;
		}

		if(theApp->m_viewtype == 0)
		{	// �e�L�X�g�^�C�v�ł̕\��
			for(int l=0;l<=64;l++) buf2[l] = (char)0; // �o�b�t�@�̃N���A
			for(j=0,k=0; j<dpb.cbSec; j++,k++)
			{
				// buf2 �Ɉ�s���i64����)���߂Ă���o�͂���
				if(k>63)
				{	// 64�����𒴂���ꍇ�́A���̍s��
					k=0;
					str += buf2;
					for(int l=0;l<=64;l++) buf2[l] = (char)0; // �o�b�t�@�̃N���A
					str += "\r\n";
				}
				if(m_mainbuf[j]>=0x20 && m_mainbuf[j]<=0x7e) buf2[k] = m_mainbuf[j];
				else buf2[k] = '.';
			}
			str += buf2;
			str += "\r\n";
		}
		else if(theApp->m_viewtype == 1)
		{	// �o�C�i���E�e�L�X�g�^�C�v�ł̕\��
			for(int l=0;l<=64;l++) buf2[l] = (char)0; // �o�b�t�@�̃N���A
			for(l=0;l<=16;l++) buf3[l] = (char)0;
			for(j=0,k=0; j<dpb.cbSec; j++,k++)
			{
				if(k>15)
				{
					k=0;
					str += buf2;
					str += buf3;
					for(int l=0;l<=64;l++) buf2[l] = (char)0; // �o�b�t�@�̃N���A
					for(l=0;l<=16;l++) buf3[l] = (char)0;
					str += "\r\n";
				}
				sprintf(buf2+3*k, "%02X ", (unsigned char)m_mainbuf[j]);
				if(m_mainbuf[j]>=0x20 && m_mainbuf[j]<=0x7e) buf3[k] = m_mainbuf[j];
				else buf3[k] = '.';
			}
			str += buf2;
			str += buf3;
			str += "\r\n";
		}

		if(str.GetLength() > 31000)
		{
			tmpStr2.LoadString(IDS_MES_NOTPOS_30LINE);
			str += tmpStr2;
			break;
		}
	}	
	CloseHandle(hdev);

	SetDlgItemText(IDC_EDIT_PREVIEW, str);

	return;
}


// ************************************************************
// �uDPB�v�{�^���������ꂽ�Ƃ�
// DPB ��ǂݍ���Ńv���r���[�G���A�ɕ\������
// ************************************************************
void CDDiskDlg::OnBtnDpb() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString tmpStr, tmpStr2;	// �X�g�����O ���\�[�X �ǂݍ��ݗp
	CString str="";				// �_�C�A���O�� ���E�C���h�E�p

	HANDLE hdev;
	DOSDPB dpb;
	BYTE n_drive=0;

	n_drive = m_cmb_disk.GetCurSel() + 1;	// A=1 B=2 �ƂȂ�悤�ɁA1����
	hdev = CreateFile("\\\\.\\VWIN32", 0, 0, NULL, 0, 0, NULL);
	if(hdev == INVALID_HANDLE_VALUE)
	{	// �n���h�����J���Ȃ������ꍇ
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_VWIN32);
		MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
		return ;
	}
	if(!ReadDPB(hdev, n_drive, &dpb))
	{	// DPB ���J���Ȃ������Ƃ�
		CloseHandle(hdev);
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_DPBREAD);
		MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
		return;
	}
	CloseHandle(hdev);


	// �h���C�u�ԍ�
	sprintf(m_buf, "Drive No = %u (%c:)\r\n", n_drive, 0x40+n_drive);
	str = m_buf;

	// ���f�B�A�̎��
	str += "Media Type = ";
	switch(dpb.devType)
	{
		case 0 : str += "0 (5.25 inch 360 KBytes Floppy Disk)\r\n"; break;
		case 1 : str += "1 (5.25 inch 1.2 MBytes Floppy Disk)\r\n"; break;
		case 2 : str += "2 (3.5 inch 720 KBytes Floppy Disk)\r\n"; break;
		case 3 : str += "3 (8 inch Low-density Floppy Disk)\r\n"; break;
		case 4 : str += "4 (8 inch High-density Floppy Disk)\r\n"; break;
		case 5 : str += "5 (Hard Disk)\r\n"; break;
		case 6 : str += "6 (Tape Drive)\r\n"; break;
		case 7 : str += "7 (3.5 inch 1.44 MBytes Floppy Disk)\r\n"; break;
		case 8 : str += "8 (Optical Disk)\r\n"; break;
		case 9 : str += "7 (3.5 inch 2.88 MBytes Floppy Disk)\r\n"; break;
		default :
			sprintf(m_buf, "%lu (Unknown Type Disk)\r\n", dpb.devType);
			str += m_buf;
			break;
	}

	// Removable �� Fixed ��
	if(dpb.devAttr & 0x01)
		sprintf(m_buf, "Device Attribute = %lu (Fixed Disk)\r\n", dpb.devAttr);
	else if(dpb.devAttr & 0x02)
		sprintf(m_buf, "Device Attribute = %lu (Removable Disk)\r\n", dpb.devAttr);
	else sprintf(m_buf, "Device Attribute = %lu (Unknown Type)\r\n");
	str += m_buf;

	sprintf(m_buf, "Media Type = %lu\r\n", dpb.bMedia);
	str += m_buf;
	sprintf(m_buf, "Cylinder = %lu\r\nBytes per sector = %lu\r\n", dpb.cCyl, dpb.cbSec);
	str += m_buf;
	sprintf(m_buf, "Sectors per cluster = %lu\r\nSectors per track = %lu\r\n", dpb.secPerClus, dpb.secPerTrack);
	str += m_buf;
	sprintf(m_buf, "Heads = %lu\r\nTotal sectors = %lu\r\n", dpb.cHead, dpb.cTotalSectors);
	str += m_buf;
	sprintf(m_buf, "FATs = %lu\r\nSectors per FAT = %lu\r\n", dpb.cFAT, dpb.secPerFAT);
	str += m_buf;

	sprintf(m_buf, "\r\n* Total size = %lu Bytes (%.2lf MBytes)\r\n", dpb.cTotalSectors*dpb.cbSec,
					(double)dpb.cTotalSectors*dpb.cbSec/1024/1000);
	str += m_buf;

	SetDlgItemText(IDC_EDIT_PREVIEW, str);

}

// ************************************************************
// �u�ݒ�v�_�C�A���O��\������
// ************************************************************
void CDDiskDlg::OnBtnConfig() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CDDiskConfig dlg;
	OSVERSIONINFO ver;

	// OS�̃o�[�W��������\������

	ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	::GetVersionEx((LPOSVERSIONINFO)&ver);

	dlg.m_text_winver = "Windows ";

	switch(ver.dwPlatformId)
	{
		case VER_PLATFORM_WIN32s :
			dlg.m_text_winver += "3.1 Win32s"; break;
		case VER_PLATFORM_WIN32_WINDOWS :
			if(ver.dwMinorVersion == 0)
			{
				if(ver.dwBuildNumber&0xffff < 1000)
					dlg.m_text_winver += "95";
				else dlg.m_text_winver += "95 OSR2";
				break;
			}
			else
			{
				if(ver.dwBuildNumber&0xffff < 2000)
					dlg.m_text_winver += "98";
				else dlg.m_text_winver += "98SE";
				break;
			}
		case VER_PLATFORM_WIN32_NT :
			dlg.m_text_winver += "NT, 2000"; break;
		default : dlg.m_text_winver += "Unknown"; break;
	}

	sprintf(m_buf, "  Version %Lu.%Lu.", ver.dwMajorVersion, ver.dwMinorVersion);
	dlg.m_text_winver += m_buf;

	switch(ver.dwPlatformId)
	{
		case VER_PLATFORM_WIN32_WINDOWS :
			sprintf(m_buf, "%Lu", ver.dwBuildNumber&0xffff);
			break;
		default :
			sprintf(m_buf, "%Lu", ver.dwBuildNumber);
			break;
	}
	dlg.m_text_winver += m_buf;

	sprintf(m_buf, " %s", ver.szCSDVersion);
	dlg.m_text_winver += m_buf;


	// �����{�^���̐ݒ�
	dlg.m_func = theApp->m_inttype;
	dlg.m_view = theApp->m_viewtype;
	dlg.m_edit_editor = theApp->m_binedit;
	
	if(dlg.DoModal() == IDOK)
	{
		theApp->m_inttype = dlg.m_func;
		theApp->m_viewtype = dlg.m_view;
		theApp->m_binedit = dlg.m_edit_editor;
	}
}

// ************************************************************
// �ǂݍ��݃Z�N�^�[���̕ύX���Ď���
// 0 �ȉ��̐ݒ�� 1 �ɏ���������
// ************************************************************
void CDDiskDlg::OnKillfocusEditSize() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	if(GetDlgItemInt(IDC_EDIT_SIZE) < 1)
		SetDlgItemInt(IDC_EDIT_SIZE, 1);
}

// ************************************************************
// �t�@�C���E�p�X�̐ݒ�_�C�A���O��\������
// (�ǂݍ��݁E�����o���t�@�C�����̐ݒ�j
// ************************************************************
void CDDiskDlg::OnBtnBrowse() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	GetDlgItemText(IDC_EDIT_FNAME, m_buf, 125);
	CFileDialog dlg(TRUE, NULL, m_buf, OFN_CREATEPROMPT|OFN_EXPLORER|OFN_HIDEREADONLY,
				"Binary File (*.BIN)|*.bin|Data File (*.DAT)|*.dat|All FIles|*.*||");
	if(dlg.DoModal()==TRUE)
		SetDlgItemText(IDC_EDIT_FNAME, dlg.GetPathName());
}

// ************************************************************
// �u�ۑ��v�{�^�����������Ƃ�
// �_���f�B�X�N�̓��e���f�[�^�t�@�C���ɏ�������
// ************************************************************
void CDDiskDlg::OnBtnSave() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString tmpStr, tmpStr2;	// �X�g�����O ���\�[�X �ǂݍ��ݗp
	CString str="";				// �_�C�A���O�� ���E�C���h�E�p

	GetDlgItemText(IDC_EDIT_FNAME, m_buf, 125);
	if(!strlen(m_buf))
	{	// �t�@�C�������w�肳��Ă��Ȃ��Ƃ�
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_NOFILESEL);
		MessageBox(tmpStr2, tmpStr, MB_ICONWARNING|MB_OK);
		return;
	}
	HANDLE hdev;
	unsigned int i;
	DOSDPB dpb;
	int b_DPB_suc=0, b_Read_suc=0; 

	BYTE n_drive=0;
	DWORD n_sect=0;
	WORD n_size=1;
	n_drive = m_cmb_disk.GetCurSel() + 1;	// A=1 B=2 �ƂȂ�悤�ɁA1����
	n_sect = GetDlgItemInt(IDC_EDIT_SECT);
	n_size = GetDlgItemInt(IDC_EDIT_SIZE);
	if(n_size < 1) n_size = 1;

	// DeviceIoControl �p�� virtual device driver ���J��
	hdev = CreateFile("\\\\.\\VWIN32", 0, 0, NULL, 0, 0, NULL);
	if(hdev == INVALID_HANDLE_VALUE)
	{	// �n���h�����J���Ȃ������ꍇ
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_VWIN32);
		MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
		return ;
	}

	// DPB ��ǂݍ��ށi�f�B�X�N�̊�{�������W����j
	b_DPB_suc = ReadDPB(hdev, n_drive, &dpb);
	if(!b_DPB_suc)
	{	// DPB ���J���Ȃ������Ƃ�
		CloseHandle(hdev);
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_DPBREAD);
		MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
		return;
	}

	CFile fi;
	CFileException fi_except;

	if(!fi.Open(m_buf, CFile::modeCreate|CFile::modeWrite|CFile::shareDenyRead,
		&fi_except))
	{	// �t�@�C�����J���Ȃ������Ƃ�
		CloseHandle(hdev);
		if(fi_except.m_cause == CFileException::badPath)
			tmpStr2.LoadString(IDS_ERR_FILEOPENPATH);			// �s���ȃp�X
		else if(fi_except.m_cause == CFileException::accessDenied)
			tmpStr2.LoadString(IDS_ERR_FILEACCESS);				// �A�N�Z�X���ᔽ
		else tmpStr2.LoadString(IDS_ERR_FILEOPEN);				// ���̑��̃G���[
		MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
		return ;
	}

	str = "";
	for(i=0; i<n_size; i++)
	{
		// ********* ���ړǂݍ��� **********
		if(theApp->m_inttype == 2)	// INT 21H FUNC 7305H Win98
			b_Read_suc = ReadLogicalSectors(hdev, n_drive, n_sect+i, 1, (unsigned char*)&m_mainbuf);
		else if(theApp->m_inttype == 1)	// INT 25H Win95
			b_Read_suc = ReadLogicalSectors25(hdev, n_drive, n_sect+i, 1, (unsigned char*)&m_mainbuf);
		if(b_Read_suc)
		{	// �_���f�B�X�N�ǂݍ��݂�����������A�t�@�C���ɏ�������
			try{
				fi.Write(m_mainbuf, dpb.cbSec);
			}
			catch(CFileException *e){
				// �t�@�C���̏������݂����s����
				if(e->m_cause == CFileException::accessDenied)
					tmpStr2.LoadString(IDS_ERR_FILEACCESS);			// �A�N�Z�X���ᔽ
				else if(e->m_cause == CFileException::diskFull)
					tmpStr2.LoadString(IDS_ERR_FILEFULL);			// Disk Full
				else tmpStr2.LoadString(IDS_ERR_FILEOTHER);			// ���̑��̃G���[
				MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
				continue;
			}
			sprintf(m_buf, "Save success Drive %d(%c:) Sector %d\r\n\r\n",
						n_drive, 0x40+n_drive, n_sect+i);
			str += m_buf;
		}
		else
		{	// �_���f�B�X�N�ǂݍ��݂����s
			tmpStr.LoadString(IDS_APPNAME);
			tmpStr2.LoadString(IDS_ERR_DRIVEREAD);
			MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
			continue;
		}
	}

	CloseHandle(hdev);
	SetDlgItemText(IDC_EDIT_PREVIEW, str);

	try{
		fi.Close();
	}
	catch(CFileException *e){
		// �t�@�C�������̂Ɏ��s�����ꍇ
		long dummy = e->m_lOsError;	// �ue �������g���Ă��Ȃ��v�x����������邽�߂̃_�~�[
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_FILECLOSE);
		MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
	}
	return;
}

// ************************************************************
// �u�������݁v�{�^�����������Ƃ�
// �f�[�^�t�@�C���̓��e��_���f�B�X�N�ɏ�������
// ************************************************************
void CDDiskDlg::OnBtnWrite() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString tmpStr, tmpStr2;	// �X�g�����O ���\�[�X �ǂݍ��ݗp
	CString str="";				// �_�C�A���O�� ���E�C���h�E�p

	GetDlgItemText(IDC_EDIT_FNAME, m_buf, 125);
	if(!strlen(m_buf))
	{	// �t�@�C�������w�肳��Ă��Ȃ��Ƃ�
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_NOFILESEL);
		MessageBox(tmpStr2, tmpStr, MB_ICONWARNING|MB_OK);
		return;
	}

	HANDLE hdev;	// VWIN32 �n���h��
	unsigned int i, j;
	DOSDPB dpb;
	int b_Read_suc;
	UINT _write_type;

	BYTE n_drive=0;
	DWORD n_sect=0;
	WORD n_size=1;
	n_drive = m_cmb_disk.GetCurSel() + 1;	// A=1 B=2 �ƂȂ�悤�ɁA1����
	n_sect = GetDlgItemInt(IDC_EDIT_SECT);
	n_size = GetDlgItemInt(IDC_EDIT_SIZE);
	if(n_size < 1) n_size = 1;

	// DeviceIoControl �p�� virtual device driver ���J��
	hdev = CreateFile("\\\\.\\VWIN32", 0, 0, NULL, 0, 0, NULL);
	if(hdev == INVALID_HANDLE_VALUE)
	{	// �n���h�����J���Ȃ������ꍇ
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_VWIN32);
		MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
		return ;
	}

	// DPB ��ǂݍ��ށi�f�B�X�N�̊�{�������W����j
	if(!ReadDPB(hdev, n_drive, &dpb))
	{	// DPB ���J���Ȃ������Ƃ�
		CloseHandle(hdev);
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_DPBREAD);
		MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
		return;
	}

	// �w��̃Z�N�^�[������������i�ǂݍ��݁j
	CFile fi;
	CFileException fi_except;

	if(!fi.Open(m_buf, CFile::modeRead|CFile::shareExclusive,
		&fi_except))
	{	// �t�@�C�����J���Ȃ������Ƃ�
		CloseHandle(hdev);
		tmpStr.LoadString(IDS_APPNAME);
		if(fi_except.m_cause == CFileException::badPath)
			tmpStr2.LoadString(IDS_ERR_FILEOPENPATH);			// �s���ȃp�X
		else if(fi_except.m_cause == CFileException::accessDenied)
			tmpStr2.LoadString(IDS_ERR_FILEACCESS);				// �A�N�Z�X���ᔽ
		else tmpStr2.LoadString(IDS_ERR_FILEOPEN);				// ���̑��̃G���[
		MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
		return ;
	}

	// ���̕��͂ł� m_buf �����ӂ��̂ŁA m_mainbuf ���g�p����
	tmpStr2.LoadString(IDS_ASK_WRITE_TO);
	sprintf(m_mainbuf, tmpStr2,
			n_drive, 0x40+n_drive, n_sect, n_drive, 0x40+n_drive, n_sect,
			n_size, n_size * dpb.cbSec);
	tmpStr.LoadString(IDS_APPNAME);
	if(MessageBox(m_mainbuf, tmpStr, MB_ICONQUESTION|MB_YESNO) != IDYES)
	{
		CloseHandle(hdev);
		return;
	}

	if(!LockLogicalDrive(hdev, n_drive, 1, 2))	// Level 1�̃��b�N
	{	// ���b�N�Ɏ��s�����Ƃ�
		CloseHandle(hdev);
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_LOCK);
		MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
		return;
	}

	i=GetCheckedRadioButton(IDC_RADIO_TYPE, IDC_RADIO_TYPE4);
	switch(i)
	{	// INT 21H Func 7305�̂Ƃ��̏�������Ӱ�ނ��w�肷��
		case IDC_RADIO_TYPE : _write_type = _WRITETYPE_NORMAL; break;
		case IDC_RADIO_TYPE2 : _write_type = _WRITETYPE_FAT; break;
		case IDC_RADIO_TYPE3 : _write_type = _WRITETYPE_ROOT; break;
		default : _write_type = _WRITETYPE_OTHER; break;
	}

	str = "";
	for(i=0; i<n_size; i++)
	{
		// �t�@�C���̓ǂݍ���
		try{
			j = fi.Read(&m_mainbuf, dpb.cbSec);
		}
		catch(CFileException *e){
			// �t�@�C���̓ǂݍ��݂Ɏ��s����
			tmpStr.LoadString(IDS_APPNAME);
			if(e->m_cause == CFileException::accessDenied)
				tmpStr2.LoadString(IDS_ERR_FILEACCESS);			// �A�N�Z�X���ᔽ
			else if(e->m_cause == CFileException::endOfFile)
				tmpStr2.LoadString(IDS_ERR_FILEEOF);			// EOF
			else tmpStr2.LoadString(IDS_ERR_FILEOTHER);			// other
			MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
			i = n_size;		// ���[�v���I��点�邽�߂̑���
			continue;		// ���ۂ̓��[�v�I��
		}

		if(j < dpb.cbSec)
		{	// �ǂݍ��݃o�C�g��������Ȃ��Ƃ�
			tmpStr.LoadString(IDS_APPNAME);
			tmpStr2.LoadString(IDS_ERR_FILESHORT);
			if(MessageBox(tmpStr2, tmpStr, MB_ICONQUESTION|MB_YESNO) != IDYES)
			{
				i = n_size;		// ���[�v���I��点�邽�߂̑���
				continue;		// ���ۂ̓��[�v�I��
			}
		}

		// ********* ���ڏ������� **********
		if(theApp->m_inttype == 2)	// INT 21H FUNC 7305H Win98
			b_Read_suc = WriteLogicalSectors(hdev, n_drive, n_sect+i, 1, (unsigned char *)&m_mainbuf, _write_type);
		else if(theApp->m_inttype == 1)	// INT 26H Win95
			b_Read_suc = WriteLogicalSectors26(hdev, n_drive, n_sect+i, 1, (unsigned char *)&m_mainbuf);
		if(b_Read_suc)
		{	// �_���f�B�X�N�������݂�����������A���b�Z�[�W�\��
			sprintf(m_buf, "Write success Drive %d(%c:) Sector %d\r\n\r\n",
						n_drive, 0x40+n_drive, n_sect+i);
			str += m_buf;
		}
		else
		{	// �_���f�B�X�N�������݂����s
			tmpStr.LoadString(IDS_APPNAME);
			tmpStr2.LoadString(IDS_ERR_DRIVEWRITE);
			MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
			continue;
		}
	}

	if(!UnLockLogicalDrive(hdev, n_drive))	// Level 1�̃��b�N����
	{	// ���b�N�����Ɏ��s�����Ƃ�
		CloseHandle(hdev);
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_LOCK);
		MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
		return;
	}

	CloseHandle(hdev);

	SetDlgItemText(IDC_EDIT_PREVIEW, str);

	try{
		fi.Close();
	}
	catch(CFileException *e){
		// �t�@�C�������̂Ɏ��s�����ꍇ
		long dummy = e->m_lOsError;	// �ue �������g���Ă��Ȃ��v�x����������邽�߂̃_�~�[
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_FILECLOSE);
		MessageBox(tmpStr2, tmpStr, MB_ICONSTOP|MB_OK);
	}
	return;
	
}

// ************************************************************
// �u�ҏW�v�{�^�����������Ƃ�
// �o�C�i���[ �G�f�B�^�[���N������
// ************************************************************
#include <process.h>
void CDDiskDlg::OnBtnEdit() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString tmpStr, tmpStr2;	// �X�g�����O ���\�[�X �ǂݍ��ݗp

	GetDlgItemText(IDC_EDIT_FNAME, m_buf, 125);
	if(!strlen(m_buf))
	{	// �t�@�C�������w�肳��Ă��Ȃ��Ƃ�
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_NOFILESEL);
		MessageBox(tmpStr2, tmpStr, MB_ICONWARNING|MB_OK);
		return;
	}

	if(theApp->m_binedit == "")
	{	// �o�C�i���[ �G�f�B�^�[ ���w�肳��Ă��Ȃ��Ƃ�
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_NOBINEDIT);
		MessageBox(tmpStr2, tmpStr, MB_ICONWARNING|MB_OK);
		return;
	}

	// �����O�t�@�C�����ɑΉ����邽�߂� " .... " �ň͂ޏ���
	CString buf;
	buf = "\"";
	buf += m_buf;
	buf += "\"";
	if(_spawnl(_P_NOWAIT, theApp->m_binedit, theApp->m_binedit, buf, NULL) == -1)
	{	// �o�C�i���[�G�f�B�^�[�̋N���Ɏ��s�����Ƃ�
		tmpStr.LoadString(IDS_APPNAME);
		tmpStr2.LoadString(IDS_ERR_BINEXEC);
		MessageBox(tmpStr2, tmpStr, MB_OK|MB_ICONSTOP);
	}

	return;
}

// ************************************************************
// �w���v�̕\��
// ************************************************************
void CDDiskDlg::OnBtnHelp() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	theApp->WinHelp(0);		// DDisk.hm �̒l
}

// ************************************************************
// �w���v�̕\�� (F1 �L�[�Ή�)
// ************************************************************
BOOL CDDiskDlg::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������

	theApp->WinHelp(0);		// DDisk.hm �̒l
	return 0;
}

// ************************************************************
// EOF
