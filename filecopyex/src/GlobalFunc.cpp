#include "stdafx.h"
#include "GlobalFunc.h"
#include <io.h>			// findfirst

volatile int ThreadCtrlFlag;

// �X���b�h���̏������I�������t���O
volatile int ThreadEndFlag;


//
// ���[�U��`�̃X���b�h
//
DWORD WINAPI ThreadMain(LPVOID p)
{
	CString strTmp;

	ThreadArg *pArg=(ThreadArg*)p;

	ThreadCtrlFlag = 1;	// �t���O���X���b�h�N�����ɂ��� (�O�̂���)
	ThreadEndFlag = 0;	// �X���b�h���s�� (�O�̂���)

	FILE *in,*ot;
	char buf[65540];
	struct _finddata_t finddata;
	long hFind;

	if( (hFind = _findfirst((LPCSTR)pArg->strFnameFrom, &finddata )) == -1L )
	{	// 1�ڂ̃t�@�C����������Ȃ�
		::MessageBox(pArg->hWnd, "���� �t�@�C����������܂���", "�G���[", MB_ICONSTOP);
		ThreadEndFlag = 1;
		::ExitThread(0);
		return 0L;
	}
	pArg->int_filelen = finddata.size;
	if(pArg->sw_fileend) pArg->int_copyend = pArg->int_filelen;


	if( (in = fopen((LPCSTR)pArg->strFnameFrom, "rb")) == NULL)
	{
		::MessageBox(pArg->hWnd, "���� �t�@�C�����J���܂���", "�G���[", MB_ICONSTOP);
		ThreadEndFlag = 1;
		::ExitThread(0);
		return 0L;
	}
	if( (ot = fopen((LPCSTR)pArg->strFnameTo, "wb")) == NULL)
	{
		fclose(in);
		::MessageBox(pArg->hWnd, "�o�� �t�@�C�����J���܂���", "�G���[", MB_ICONSTOP);
		ThreadEndFlag = 1;
		::ExitThread(0);
		return 0L;
	}

	if(fseek(in, pArg->int_copystart, SEEK_SET))
	{
		fclose(in);
		fclose(ot);
		::MessageBox(pArg->hWnd, "���� �t�@�C���̓ǂݍ��ݐ擪�ֈړ��ł��܂���", "�G���[", MB_ICONSTOP);
		ThreadEndFlag = 1;
		::ExitThread(0);
		return 0L;
	}

	strTmp.Format("�R�s�[�Ώۂ̃o�C�g�� �F %ld Bytes", pArg->int_copyend - pArg->int_copystart);
	::SetWindowText(pArg->hWndTxtTotalbyte, strTmp);
	strTmp.Format("������ �F %ld Bytes", 0);
	::SetWindowText(pArg->hWndTxtCurbyte, strTmp);

	long int_maxbyte = pArg->int_copyend - pArg->int_copystart;
	int int_readsize;
	for(long i = 0; i <= int_maxbyte; i = i + pArg->int_bufsiz)
	{
		int_readsize = fread(&buf, sizeof(char), pArg->int_bufsiz, in);
		if(ferror(in))
		{
			::MessageBox(pArg->hWnd, "���� �t�@�C���̓ǂݍ��݃G���[", "�G���[", MB_ICONSTOP);
			break;
		}
		if(i + int_readsize > int_maxbyte) int_readsize = int_maxbyte - i;
		fwrite(&buf, sizeof(char), int_readsize, ot);
		if(ferror(ot))
		{
			::MessageBox(pArg->hWnd, "�o�� �t�@�C���̏������݃G���[", "�G���[", MB_ICONSTOP);
			break;
		}
		if(!ThreadCtrlFlag)
		{	// �t���O���O�ɂȂ�΁A�X���b�h�I������
			break;
		}
		strTmp.Format("������ �F %ld Bytes", i);
		::SetWindowText(pArg->hWndTxtCurbyte, strTmp);
	}
	strTmp.Format("������ �F %ld Bytes", i);
	::SetWindowText(pArg->hWndTxtCurbyte, strTmp);
	fclose(in);
	fclose(ot);

	ThreadEndFlag = 1;
	// ��ԕ\���_�C�A���O����������
	::PostMessage(pArg->hWnd, WM_CLOSE, 0, 0);
	::ExitThread(0);
	return 0L;
}