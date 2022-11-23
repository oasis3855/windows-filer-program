#ifndef _GLOBALFUNC_H


// スレッド終了のフラグ
// スレッド未起動時 0, 起動時 1, 起動中に0 にすると、スレッド終了する
// volatile で宣言すること
// コンパイラに最適化しないように指示する
volatile extern int ThreadCtrlFlag;

// スレッド内の処理が終了したフラグ
volatile extern int ThreadEndFlag;

// スレッド起動時に渡すパラメータ
struct ThreadArg
{
	HWND hWnd;
	HWND hWndTxtTotalbyte;
	HWND hWndTxtCurbyte;
	HWND hWndTxtMes;
	long int_filelen;	// 入力ファイルのサイズ
	long int_copystart, int_copyend;	// コピーのスタート・ストップのバイト
	long int_bufsiz;	// バッファサイズ
	int sw_errordlg;	// エラーダイアログの表示
	long int_skipsiz;	// エラー時にスキップするバイト数
	int int_retry;		// 最大エラー数
	int sw_fileend;		// ファイルエンドまでコピー
	char strFnameFrom[256], strFnameTo[256];
};

// ユーザ定義のスレッド
DWORD WINAPI ThreadMain(LPVOID p);

#endif

#define _GLOBALFUNC_H
