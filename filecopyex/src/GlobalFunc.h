#ifndef _GLOBALFUNC_H


// �X���b�h�I���̃t���O
// �X���b�h���N���� 0, �N���� 1, �N������0 �ɂ���ƁA�X���b�h�I������
// volatile �Ő錾���邱��
// �R���p�C���ɍœK�����Ȃ��悤�Ɏw������
volatile extern int ThreadCtrlFlag;

// �X���b�h���̏������I�������t���O
volatile extern int ThreadEndFlag;

// �X���b�h�N�����ɓn���p�����[�^
struct ThreadArg
{
	HWND hWnd;
	HWND hWndTxtTotalbyte;
	HWND hWndTxtCurbyte;
	HWND hWndTxtMes;
	long int_filelen;	// ���̓t�@�C���̃T�C�Y
	long int_copystart, int_copyend;	// �R�s�[�̃X�^�[�g�E�X�g�b�v�̃o�C�g
	long int_bufsiz;	// �o�b�t�@�T�C�Y
	int sw_errordlg;	// �G���[�_�C�A���O�̕\��
	long int_skipsiz;	// �G���[���ɃX�L�b�v����o�C�g��
	int int_retry;		// �ő�G���[��
	int sw_fileend;		// �t�@�C���G���h�܂ŃR�s�[
	char strFnameFrom[256], strFnameTo[256];
};

// ���[�U��`�̃X���b�h
DWORD WINAPI ThreadMain(LPVOID p);

#endif

#define _GLOBALFUNC_H
