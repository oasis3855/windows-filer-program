// ************************************************************
// 論理ディスクに直接アクセスする関数群
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
	DWORD  dwStartSector;   // 論理セクタ番号の開始番号
	WORD   wSectors;        // セクタ数
	DWORD  dwBuffer;        // 読み込み/書き込みバッファのアドレス
} DISKIO;
#pragma pack()

// ************************************************************
// 論理ディスクの直接読み取り INT21H Func=7305H
// ************************************************************
//
//   目的:
//     指定したセクタ数を読み取り、呼び出し側が提供するバッファに格納します。
//	 Int 21h function 7305h を使用します。
//
//   パラメータ:
//     hDev
//        VWIN32 を示すハンドルです。
//
//     bDrive
//        MS-DOSの論理ドライブ番号です。 0 = default, 1 = A, 2 = B,
//        3 = C, etc.
//
//     dwStartSector
//        最初に読み取りを行うセクタです。
//
//     wSectors
//        読み取るセクタの数です。
//
//     lpSectBuff
//        読み取ったセクタを格納するための呼び出し側が提供するバッファです。
//
//   戻り値:
//     成功すると TRUE を返します。それ以外は FALSE を返します。
//
//   コメント:
//     この関数は、パラメータのチェックは行いません。lpSectBuff は、呼び出し側が
//     確保します。読み取られたデータをすべて保持できるように、lpSectBuff バッファ
//     には十分な容量を確保するようにしてください。
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
	reg.reg_EDX = bDrive;   // Int 21h, fn 7305h ドライブ番号は1ベースです。

	// SI のビット０が０なので、読み込みとなる

	fResult = DeviceIoControl(hDev, VWIN32_DIOC_DOS_DRIVEINFO, &reg, sizeof(reg),
								&reg, sizeof(reg), &cb, 0);


	// DeviceIoControl および読み取りが成功しているかどうか検証します。
	// INT21が正常に読み出された場合は fResult が 1 となる。
	// INT21H Func7305H が成功した場合は CF=0となる。
	fResult = fResult && !(reg.reg_Flags & CARRY_FLAG);

	return fResult;
}

// ************************************************************
// 論理ディスクの直接書き込み INT21H Func=7305H
// ************************************************************
//
//   目的:
//     呼び出し側が提供したバッファから、指定のセクタ数を書き込みます。
//	 Int 21h function 7305h を使用します。
//
//   パラメータ:
//     hDev
//        VWIN32 を示すハンドルです。
//
//     bDrive
//        MS-DOSの論理ドライブ番号です。 0 = default, 1 = A, 2 = B,
//        3 = C, etc.
//
//     dwStartSector
//        最初に書き込むセクタです。
//
//     wSectors
//        書き込むセクタの数です。
//
//     lpSectBuff
//        書き込むセクタを取り出すための呼び出し側が提供するバッファです。
//
//   戻り値:
//     成功すると TRUE を返します。それ以外は FALSE を返します。
//
//   コメント:
//     この関数は、パラメータのチェックは行いません。lpSectBuff は、呼び出し側が
//     確保します。書き込まれたデータをすべて保持できるように、lpSectBuff バッファ
//     には十分な容量を確保するようにしてください。
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
	reg.reg_EDX = bDrive;   // Int 21h, fn 7305h ドライブ番号は1ベースです。

//	reg.reg_ESI = 0x6001;   // 正常なファイル データです。（他の値については、
							// 関数のドキュメントを参照してください。）
	reg.reg_ESI = _type;   // 正常なファイル データです。（他の値については、
							// 関数のドキュメントを参照してください。）

	// SI のビット０が1なので、書き込みとなる
	// SI = 6001h : Normal Data
	// SI = 2001h : FAT Data
	// SI = 4001h : Directry Data
	// SI = 1h : Other Data

	fResult = DeviceIoControl(hDev, VWIN32_DIOC_DOS_DRIVEINFO,
								&reg, sizeof(reg), &reg, sizeof(reg), &cb, 0);

	// DeviceIoControl および書き込みが成功しているかどうか検証します。
	fResult = fResult && !(reg.reg_Flags & CARRY_FLAG);

	return fResult;
}

//********
//HOWTO: Getting Floppy Drive Type Information
//Last reviewed: February 20, 1997
//Article ID: Q163920 
//********/

// ************************************************************
// 論理ドライブの DPB を読み取る INT21H Func=440DH
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

	// DeviceIoControl および読み取りが成功しているかどうか検証します。
	fResult = fResult && !(reg.reg_Flags & CARRY_FLAG);

	return fResult;
}

// ************************************************************
// 論理ディスクの直接読み取り INT25H
// ************************************************************
//
//  注意：この関数は Windows95専用です。Windows95 OSR2以上では使えません
//   目的:
//     指定したセクタ数を読み取り、呼び出し側が提供するバッファに格納します。
//	 Int 25h を使用します。
//
//   パラメータ:
//     hDev
//        VWIN32 を示すハンドルです。
//
//     bDrive
//        MS-DOSの論理ドライブ番号です。 0 = default, 1 = A, 2 = B,
//        3 = C, etc.
//
//     dwStartSector
//        最初に読み取りを行うセクタです。
//
//     wSectors
//        読み取るセクタの数です。
//
//     lpSectBuff
//        読み取ったセクタを格納するための呼び出し側が提供するバッファです。
//
//   戻り値:
//     成功すると TRUE を返します。それ以外は FALSE を返します。
//
//   コメント:
//     この関数は、パラメータのチェックは行いません。lpSectBuff は、呼び出し側が
//     確保します。読み取られたデータをすべて保持できるように、lpSectBuff バッファ
//     には十分な容量を確保するようにしてください。
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

	reg.reg_EAX = bDrive - 1;    // Int 25h ドライブ番号は0ベースです。
	reg.reg_EBX = (DWORD)&dio;
	reg.reg_ECX = 0xFFFF;        // DISKIO 構造体を使用します。

	fResult = DeviceIoControl(hDev, VWIN32_DIOC_DOS_INT25,
									&reg, sizeof(reg), &reg, sizeof(reg), &cb, 0);



	// DeviceIoControl および読み取りが成功しているかどうか検証します。
	// INT21が正常に読み出された場合は fResult が 1 となる。
	// INT21H Func7305H が成功した場合は CF=0となる。
	fResult = fResult && !(reg.reg_Flags & CARRY_FLAG);

	return fResult;
}

// ************************************************************
// 論理ディスクの直接書き込み INT26H
// ************************************************************
//
//   目的:
//     呼び出し側が提供したバッファから、指定のセクタ数を書き込みます。
//	 Int 26h を使用します。
//
//   パラメータ:
//     hDev
//        VWIN32 を示すハンドルです。
//
//     bDrive
//        MS-DOSの論理ドライブ番号です。 1 = A, 2 = B,
//        3 = C, etc.
//
//     dwStartSector
//        最初に書き込むセクタです。
//
//     wSectors
//        書き込むセクタの数です。
//
//     lpSectBuff
//        書き込むセクタを取り出すための呼び出し側が提供するバッファです。
//
//   戻り値:
//     成功すると TRUE を返します。それ以外は FALSE を返します。
//
//   コメント:
//     この関数は、パラメータのチェックは行いません。lpSectBuff は、呼び出し側が
//     確保します。書き込まれたデータをすべて保持できるように、lpSectBuff バッファ
//     には十分な容量を確保するようにしてください。
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

	reg.reg_EAX = bDrive - 1;   // Int 26h ドライブ番号は0ベースです。
	reg.reg_EBX = (DWORD)&dio;
	reg.reg_ECX = -1;


	fResult = DeviceIoControl(hDev, VWIN32_DIOC_DOS_INT26,
								&reg, sizeof(reg), &reg, sizeof(reg), &cb, 0);

	// DeviceIoControl および書き込みが成功しているかどうか検証します。
	fResult = fResult && !(reg.reg_Flags & CARRY_FLAG);

	return fResult;
}


// ************************************************************
// 論理ドライブをロックし、他のアプリケーションからの妨害を阻止します。
// ************************************************************
//
//
//  hdev : VWIN32 ハンドル
//  bDrive : ドライブ番号 1=A 2=B
//  LockLevel :
//		0 : スーバーロック（通常は使わない）
//		1 : 最下位のレベル
//		2
//		3 : 最上位のレベル
//
//		レベル３のロックを得るには、1,2,3と３回ロックの必要がある
//  Permissions : (レベルによって異なるが…)
//		ビット0 : 他のアプリケーションに書き込みを許可する
//		ビット1 : 他のアプリケーションにファイル作成を許可しない
//
//  戻り値
//	成功すると TRUE を返す
//
//詳細は、MSDN [SDK] - [Windows Base Service] - [Windows 95 Feature] - [Using Win95 Features]
//   - [About Exclusive Lock]を参照
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
// 論理ドライブをアンロックする
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
