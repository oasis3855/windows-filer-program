// ************************************************************
// �_���f�B�X�N�ɒ��ڃA�N�Z�X����֐��Q
// ************************************************************

#include "stdafx.h"
#include <windows.h>
#include "DiskCore.h"

#ifndef VWIN32_DIOC_DOS_IOCTL
#define VWIN32_DIOC_DOS_IOCTL		1
#endif

#ifndef VWIN32_DIOC_DOS_INT25
#define VWIN32_DIOC_DOS_INT25		2
#endif

#ifndef VWIN32_DIOC_DOS_INT26
#define VWIN32_DIOC_DOS_INT26		3
#endif

#ifndef VWIN32_DIOC_DOS_DRIVEINFO
#define VWIN32_DIOC_DOS_DRIVEINFO	6
#endif


// Intel x86 processor status flag
#ifndef CARRY_FLAG
#define CARRY_FLAG  0x1
#endif

typedef struct _DIOC_REGISTERS {
	DWORD reg_EBX;
	DWORD reg_EDX;
	DWORD reg_ECX;
	DWORD reg_EAX;
	DWORD reg_EDI;
	DWORD reg_ESI;
	DWORD reg_Flags;
}DIOC_REGISTERS;


#pragma pack(1)
typedef struct _DISKIO {
	DWORD  dwStartSector;   // �_���Z�N�^�ԍ��̊J�n�ԍ�
	WORD   wSectors;        // �Z�N�^��
	DWORD  dwBuffer;        // �ǂݍ���/�������݃o�b�t�@�̃A�h���X
} DISKIO;
#pragma pack()

// ************************************************************
// �_���f�B�X�N�̒��ړǂݎ�� INT21H Func=7305H
// ************************************************************
//
//   �ړI:
//     �w�肵���Z�N�^����ǂݎ��A�Ăяo�������񋟂���o�b�t�@�Ɋi�[���܂��B
//	 Int 21h function 7305h ���g�p���܂��B
//
//   �p�����[�^:
//     hDev
//        VWIN32 �������n���h���ł��B
//
//     bDrive
//        MS-DOS�̘_���h���C�u�ԍ��ł��B 0 = default, 1 = A, 2 = B,
//        3 = C, etc.
//
//     dwStartSector
//        �ŏ��ɓǂݎ����s���Z�N�^�ł��B
//
//     wSectors
//        �ǂݎ��Z�N�^�̐��ł��B
//
//     lpSectBuff
//        �ǂݎ�����Z�N�^���i�[���邽�߂̌Ăяo�������񋟂���o�b�t�@�ł��B
//
//   �߂�l:
//     ��������� TRUE ��Ԃ��܂��B����ȊO�� FALSE ��Ԃ��܂��B
//
//   �R�����g:
//     ���̊֐��́A�p�����[�^�̃`�F�b�N�͍s���܂���BlpSectBuff �́A�Ăяo������
//     �m�ۂ��܂��B�ǂݎ��ꂽ�f�[�^�����ׂĕێ��ł���悤�ɁAlpSectBuff �o�b�t�@
//     �ɂ͏\���ȗe�ʂ��m�ۂ���悤�ɂ��Ă��������B
// ************************************************************
BOOL ReadLogicalSectors (HANDLE hDev, BYTE   bDrive, DWORD  dwStartSector,
							WORD   wSectors, LPBYTE lpSectBuff)
{
	BOOL			fResult;
	DWORD			cb;
	DIOC_REGISTERS	reg = {0};
	DISKIO			dio = {0};

	dio.dwStartSector	= dwStartSector;
	dio.wSectors		= wSectors;
	dio.dwBuffer		= (DWORD)lpSectBuff;

	reg.reg_EAX = 0x7305;   // Ext_ABSDiskReadWrite
	reg.reg_EBX = (DWORD)&dio;
	reg.reg_ECX = -1;
	reg.reg_EDX = bDrive;   // Int 21h, fn 7305h �h���C�u�ԍ���1�x�[�X�ł��B

	// SI �̃r�b�g�O���O�Ȃ̂ŁA�ǂݍ��݂ƂȂ�

	fResult = DeviceIoControl(hDev, VWIN32_DIOC_DOS_DRIVEINFO, &reg, sizeof(reg),
								&reg, sizeof(reg), &cb, 0);


	// DeviceIoControl ����ѓǂݎ�肪�������Ă��邩�ǂ������؂��܂��B
	// INT21������ɓǂݏo���ꂽ�ꍇ�� fResult �� 1 �ƂȂ�B
	// INT21H Func7305H �����������ꍇ�� CF=0�ƂȂ�B
	fResult = fResult && !(reg.reg_Flags & CARRY_FLAG);

	return fResult;
}

// ************************************************************
// �_���f�B�X�N�̒��ڏ������� INT21H Func=7305H
// ************************************************************
//
//   �ړI:
//     �Ăяo�������񋟂����o�b�t�@����A�w��̃Z�N�^�����������݂܂��B
//	 Int 21h function 7305h ���g�p���܂��B
//
//   �p�����[�^:
//     hDev
//        VWIN32 �������n���h���ł��B
//
//     bDrive
//        MS-DOS�̘_���h���C�u�ԍ��ł��B 0 = default, 1 = A, 2 = B,
//        3 = C, etc.
//
//     dwStartSector
//        �ŏ��ɏ������ރZ�N�^�ł��B
//
//     wSectors
//        �������ރZ�N�^�̐��ł��B
//
//     lpSectBuff
//        �������ރZ�N�^�����o�����߂̌Ăяo�������񋟂���o�b�t�@�ł��B
//
//   �߂�l:
//     ��������� TRUE ��Ԃ��܂��B����ȊO�� FALSE ��Ԃ��܂��B
//
//   �R�����g:
//     ���̊֐��́A�p�����[�^�̃`�F�b�N�͍s���܂���BlpSectBuff �́A�Ăяo������
//     �m�ۂ��܂��B�������܂ꂽ�f�[�^�����ׂĕێ��ł���悤�ɁAlpSectBuff �o�b�t�@
//     �ɂ͏\���ȗe�ʂ��m�ۂ���悤�ɂ��Ă��������B
//
// ************************************************************
BOOL WriteLogicalSectors (HANDLE hDev, BYTE bDrive, DWORD dwStartSector,
						WORD wSectors, LPBYTE lpSectBuff, UINT _type)
{
	BOOL			fResult;
	DWORD			cb;
	DIOC_REGISTERS	reg = {0};
	DISKIO			dio;

	dio.dwStartSector = dwStartSector;
	dio.wSectors      = wSectors;
	dio.dwBuffer      = (DWORD)lpSectBuff;

	reg.reg_EAX = 0x7305;   // Ext_ABSDiskReadWrite
	reg.reg_EBX = (DWORD)&dio;
	reg.reg_ECX = -1;
	reg.reg_EDX = bDrive;   // Int 21h, fn 7305h �h���C�u�ԍ���1�x�[�X�ł��B

//	reg.reg_ESI = 0x6001;   // ����ȃt�@�C�� �f�[�^�ł��B�i���̒l�ɂ��ẮA
							// �֐��̃h�L�������g���Q�Ƃ��Ă��������B�j
	reg.reg_ESI = _type;   // ����ȃt�@�C�� �f�[�^�ł��B�i���̒l�ɂ��ẮA
							// �֐��̃h�L�������g���Q�Ƃ��Ă��������B�j

	// SI �̃r�b�g�O��1�Ȃ̂ŁA�������݂ƂȂ�
	// SI = 6001h : Normal Data
	// SI = 2001h : FAT Data
	// SI = 4001h : Directry Data
	// SI = 1h : Other Data

	fResult = DeviceIoControl(hDev, VWIN32_DIOC_DOS_DRIVEINFO,
								&reg, sizeof(reg), &reg, sizeof(reg), &cb, 0);

	// DeviceIoControl ����я������݂��������Ă��邩�ǂ������؂��܂��B
	fResult = fResult && !(reg.reg_Flags & CARRY_FLAG);

	return fResult;
}

//********
//HOWTO: Getting Floppy Drive Type Information
//Last reviewed: February 20, 1997
//Article ID: Q163920 
//********/

// ************************************************************
// �_���h���C�u�� DPB ��ǂݎ�� INT21H Func=440DH
// ************************************************************
BOOL ReadDPB(HANDLE hDev, BYTE bDrive, DOSDPB *dpb)
{
	BOOL			fResult;
	DWORD			cb;
	DIOC_REGISTERS	reg;

	dpb->specialFunc = 0;  // return default type; do not hit disk

	reg.reg_EBX   = bDrive;       // BL = drive number (1-based)
	reg.reg_EDX   = (DWORD)dpb;  // DS:EDX -> DPB
	reg.reg_ECX   = 0x0860;       // CX = Get DPB
	reg.reg_EAX   = 0x440D;       // AX = Ioctl
	reg.reg_Flags = CARRY_FLAG;   // assume failure

	// Make sure both DeviceIoControl and Int 21h succeeded.
	fResult = DeviceIoControl (hDev, VWIN32_DIOC_DOS_IOCTL, &reg,
							sizeof(reg), &reg, sizeof(reg), &cb, 0);

	// DeviceIoControl ����ѓǂݎ�肪�������Ă��邩�ǂ������؂��܂��B
	fResult = fResult && !(reg.reg_Flags & CARRY_FLAG);

	return fResult;
}

// ************************************************************
// �_���f�B�X�N�̒��ړǂݎ�� INT25H
// ************************************************************
//
//  ���ӁF���̊֐��� Windows95��p�ł��BWindows95 OSR2�ȏ�ł͎g���܂���
//   �ړI:
//     �w�肵���Z�N�^����ǂݎ��A�Ăяo�������񋟂���o�b�t�@�Ɋi�[���܂��B
//	 Int 25h ���g�p���܂��B
//
//   �p�����[�^:
//     hDev
//        VWIN32 �������n���h���ł��B
//
//     bDrive
//        MS-DOS�̘_���h���C�u�ԍ��ł��B 0 = default, 1 = A, 2 = B,
//        3 = C, etc.
//
//     dwStartSector
//        �ŏ��ɓǂݎ����s���Z�N�^�ł��B
//
//     wSectors
//        �ǂݎ��Z�N�^�̐��ł��B
//
//     lpSectBuff
//        �ǂݎ�����Z�N�^���i�[���邽�߂̌Ăяo�������񋟂���o�b�t�@�ł��B
//
//   �߂�l:
//     ��������� TRUE ��Ԃ��܂��B����ȊO�� FALSE ��Ԃ��܂��B
//
//   �R�����g:
//     ���̊֐��́A�p�����[�^�̃`�F�b�N�͍s���܂���BlpSectBuff �́A�Ăяo������
//     �m�ۂ��܂��B�ǂݎ��ꂽ�f�[�^�����ׂĕێ��ł���悤�ɁAlpSectBuff �o�b�t�@
//     �ɂ͏\���ȗe�ʂ��m�ۂ���悤�ɂ��Ă��������B
// ************************************************************
BOOL ReadLogicalSectors25(HANDLE hDev, BYTE bDrive, DWORD dwStartSector,
							WORD wSectors, LPBYTE lpSectBuff)
{
	BOOL			fResult;
	DWORD			cb;
	DIOC_REGISTERS	reg = {0};
	DISKIO			dio = {0};

	dio.dwStartSector	= dwStartSector;
	dio.wSectors		= wSectors;
	dio.dwBuffer		= (DWORD)lpSectBuff;

	reg.reg_EAX = bDrive - 1;    // Int 25h �h���C�u�ԍ���0�x�[�X�ł��B
	reg.reg_EBX = (DWORD)&dio;
	reg.reg_ECX = 0xFFFF;        // DISKIO �\���̂��g�p���܂��B

	fResult = DeviceIoControl(hDev, VWIN32_DIOC_DOS_INT25,
									&reg, sizeof(reg), &reg, sizeof(reg), &cb, 0);



	// DeviceIoControl ����ѓǂݎ�肪�������Ă��邩�ǂ������؂��܂��B
	// INT21������ɓǂݏo���ꂽ�ꍇ�� fResult �� 1 �ƂȂ�B
	// INT21H Func7305H �����������ꍇ�� CF=0�ƂȂ�B
	fResult = fResult && !(reg.reg_Flags & CARRY_FLAG);

	return fResult;
}

// ************************************************************
// �_���f�B�X�N�̒��ڏ������� INT26H
// ************************************************************
//
//   �ړI:
//     �Ăяo�������񋟂����o�b�t�@����A�w��̃Z�N�^�����������݂܂��B
//	 Int 26h ���g�p���܂��B
//
//   �p�����[�^:
//     hDev
//        VWIN32 �������n���h���ł��B
//
//     bDrive
//        MS-DOS�̘_���h���C�u�ԍ��ł��B 1 = A, 2 = B,
//        3 = C, etc.
//
//     dwStartSector
//        �ŏ��ɏ������ރZ�N�^�ł��B
//
//     wSectors
//        �������ރZ�N�^�̐��ł��B
//
//     lpSectBuff
//        �������ރZ�N�^�����o�����߂̌Ăяo�������񋟂���o�b�t�@�ł��B
//
//   �߂�l:
//     ��������� TRUE ��Ԃ��܂��B����ȊO�� FALSE ��Ԃ��܂��B
//
//   �R�����g:
//     ���̊֐��́A�p�����[�^�̃`�F�b�N�͍s���܂���BlpSectBuff �́A�Ăяo������
//     �m�ۂ��܂��B�������܂ꂽ�f�[�^�����ׂĕێ��ł���悤�ɁAlpSectBuff �o�b�t�@
//     �ɂ͏\���ȗe�ʂ��m�ۂ���悤�ɂ��Ă��������B
//
// ************************************************************
BOOL WriteLogicalSectors26 (HANDLE hDev, BYTE bDrive, DWORD dwStartSector,
						WORD wSectors, LPBYTE lpSectBuff)
{
	BOOL			fResult;
	DWORD			cb;
	DIOC_REGISTERS	reg = {0};
	DISKIO			dio;

	dio.dwStartSector = dwStartSector;
	dio.wSectors      = wSectors;
	dio.dwBuffer      = (DWORD)lpSectBuff;

	reg.reg_EAX = bDrive - 1;   // Int 26h �h���C�u�ԍ���0�x�[�X�ł��B
	reg.reg_EBX = (DWORD)&dio;
	reg.reg_ECX = -1;


	fResult = DeviceIoControl(hDev, VWIN32_DIOC_DOS_INT26,
								&reg, sizeof(reg), &reg, sizeof(reg), &cb, 0);

	// DeviceIoControl ����я������݂��������Ă��邩�ǂ������؂��܂��B
	fResult = fResult && !(reg.reg_Flags & CARRY_FLAG);

	return fResult;
}


// ************************************************************
// �_���h���C�u�����b�N���A���̃A�v���P�[�V��������̖W�Q��j�~���܂��B
// ************************************************************
//
//
//  hdev : VWIN32 �n���h��
//  bDrive : �h���C�u�ԍ� 1=A 2=B
//  LockLevel :
//		0 : �X�[�o�[���b�N�i�ʏ�͎g��Ȃ��j
//		1 : �ŉ��ʂ̃��x��
//		2
//		3 : �ŏ�ʂ̃��x��
//
//		���x���R�̃��b�N�𓾂�ɂ́A1,2,3�ƂR�񃍃b�N�̕K�v������
//  Permissions : (���x���ɂ���ĈقȂ邪�c)
//		�r�b�g0 : ���̃A�v���P�[�V�����ɏ������݂�������
//		�r�b�g1 : ���̃A�v���P�[�V�����Ƀt�@�C���쐬�������Ȃ�
//
//  �߂�l
//	��������� TRUE ��Ԃ�
//
//�ڍׂ́AMSDN [SDK] - [Windows Base Service] - [Windows 95 Feature] - [Using Win95 Features]
//   - [About Exclusive Lock]���Q��
//
// ************************************************************
BOOL LockLogicalDrive(HANDLE hDev, BYTE bDrive, BYTE LockLevel, BYTE Permissions)
{
	BOOL	fResult;
	DWORD	cb;
	DIOC_REGISTERS	reg={0};
	
	reg.reg_EAX = 0x440d;
	reg.reg_EBX = (0xff00 & (LockLevel << 8)) | (0x00ff & bDrive);
	reg.reg_ECX = 0x484a;
	reg.reg_EDX = Permissions;

	fResult = DeviceIoControl(hDev, VWIN32_DIOC_DOS_IOCTL,
								&reg, sizeof(reg), &reg, sizeof(reg), &cb, 0);

	fResult = fResult && !(reg.reg_Flags & CARRY_FLAG);

	return fResult;
}

// ************************************************************
// �_���h���C�u���A�����b�N����
// ************************************************************
BOOL UnLockLogicalDrive(HANDLE hDev, BYTE bDrive)
{
	BOOL	fResult;
	DWORD	cb;
	DIOC_REGISTERS	reg={0};
	
	reg.reg_EAX = 0x440d;
	reg.reg_EBX = (0x00ff & bDrive);
	reg.reg_ECX = 0x486a;

	fResult = DeviceIoControl(hDev, VWIN32_DIOC_DOS_IOCTL,
								&reg, sizeof(reg), &reg, sizeof(reg), &cb, 0);

	fResult = fResult && !(reg.reg_Flags & CARRY_FLAG);

	return fResult;
}

// ************************************************************
// EOF
