/* ディスクに直接アクセスする関数群 */

// WriteLogicalSectors INT21H Func7305H で書き込みﾓｰﾄﾞを指定するのに使用する
#define	_WRITETYPE_NORMAL	0x6001
#define	_WRITETYPE_FAT		0x2001
#define	_WRITETYPE_ROOT		0x4001
#define	_WRITETYPE_OTHER	0x0001



#pragma pack(1)
typedef struct _DOSDPB{
	BYTE    specialFunc;    //
	BYTE    devType;        //
	WORD    devAttr;        //
	WORD    cCyl;           // number of cylinders
	BYTE    mediaType;      //
	WORD    cbSec;          // Bytes per sector
	BYTE    secPerClus;     // Sectors per cluster
	WORD    cSecRes;        // Reserved sectors
	BYTE    cFAT;           // FATs
	WORD    cDir;           // Root Directory Entries
	WORD    cSec;           // Total number of sectors in image
	BYTE    bMedia;         // Media descriptor
	WORD    secPerFAT;      // Sectors per FAT
	WORD    secPerTrack;    // Sectors per track
	WORD    cHead;          // Heads
	DWORD   cSecHidden;     // Hidden sectors
	DWORD   cTotalSectors;  // Total sectors, if cbSec is zero
	BYTE    reserved[6];    //
} DOSDPB;
#pragma pack()


BOOL ReadLogicalSectors (HANDLE hDev, BYTE   bDrive, DWORD  dwStartSector,
                            WORD   wSectors, LPBYTE lpSectBuff);
BOOL WriteLogicalSectors (HANDLE hDev, BYTE bDrive, DWORD dwStartSector,
						WORD wSectors, LPBYTE lpSectBuff, UINT _type);
BOOL ReadDPB(HANDLE hDev, BYTE bDrive, DOSDPB *dpb);

BOOL ReadLogicalSectors25(HANDLE hDev, BYTE   bDrive, DWORD  dwStartSector,
							WORD   wSectors, LPBYTE lpSectBuff);
BOOL WriteLogicalSectors26 (HANDLE hDev, BYTE bDrive, DWORD dwStartSector,
						WORD wSectors, LPBYTE lpSectBuff);

BOOL LockLogicalDrive(HANDLE hDev, BYTE bDrive, BYTE LockLevel, BYTE Permissions);
BOOL UnLockLogicalDrive(HANDLE hDev, BYTE bDrive);
