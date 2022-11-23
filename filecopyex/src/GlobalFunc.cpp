#include "stdafx.h"
#include "GlobalFunc.h"
#include <io.h>			// findfirst

volatile int ThreadCtrlFlag;

// スレッド内の処理が終了したフラグ
volatile int ThreadEndFlag;


//
// ユーザ定義のスレッド
//
DWORD WINAPI ThreadMain(LPVOID p)
{
	CString strTmp;

	ThreadArg *pArg=(ThreadArg*)p;

	ThreadCtrlFlag = 1;	// フラグをスレッド起動中にする (念のため)
	ThreadEndFlag = 0;	// スレッド実行中 (念のため)

	FILE *in,*ot;
	char buf[65540];
	struct _finddata_t finddata;
	long hFind;

	if( (hFind = _findfirst((LPCSTR)pArg->strFnameFrom, &finddata )) == -1L )
	{	// 1つ目のファイルが見つからない
		::MessageBox(pArg->hWnd, "入力 ファイルが見つかりません", "エラー", MB_ICONSTOP);
		ThreadEndFlag = 1;
		::ExitThread(0);
		return 0L;
	}
	pArg->int_filelen = finddata.size;
	if(pArg->sw_fileend) pArg->int_copyend = pArg->int_filelen;


	if( (in = fopen((LPCSTR)pArg->strFnameFrom, "rb")) == NULL)
	{
		::MessageBox(pArg->hWnd, "入力 ファイルが開けません", "エラー", MB_ICONSTOP);
		ThreadEndFlag = 1;
		::ExitThread(0);
		return 0L;
	}
	if( (ot = fopen((LPCSTR)pArg->strFnameTo, "wb")) == NULL)
	{
		fclose(in);
		::MessageBox(pArg->hWnd, "出力 ファイルが開けません", "エラー", MB_ICONSTOP);
		ThreadEndFlag = 1;
		::ExitThread(0);
		return 0L;
	}

	if(fseek(in, pArg->int_copystart, SEEK_SET))
	{
		fclose(in);
		fclose(ot);
		::MessageBox(pArg->hWnd, "入力 ファイルの読み込み先頭へ移動できません", "エラー", MB_ICONSTOP);
		ThreadEndFlag = 1;
		::ExitThread(0);
		return 0L;
	}

	strTmp.Format("コピー対象のバイト数 ： %ld Bytes", pArg->int_copyend - pArg->int_copystart);
	::SetWindowText(pArg->hWndTxtTotalbyte, strTmp);
	strTmp.Format("完了分 ： %ld Bytes", 0);
	::SetWindowText(pArg->hWndTxtCurbyte, strTmp);

	long int_maxbyte = pArg->int_copyend - pArg->int_copystart;
	int int_readsize;
	for(long i = 0; i <= int_maxbyte; i = i + pArg->int_bufsiz)
	{
		int_readsize = fread(&buf, sizeof(char), pArg->int_bufsiz, in);
		if(ferror(in))
		{
			::MessageBox(pArg->hWnd, "入力 ファイルの読み込みエラー", "エラー", MB_ICONSTOP);
			break;
		}
		if(i + int_readsize > int_maxbyte) int_readsize = int_maxbyte - i;
		fwrite(&buf, sizeof(char), int_readsize, ot);
		if(ferror(ot))
		{
			::MessageBox(pArg->hWnd, "出力 ファイルの書き込みエラー", "エラー", MB_ICONSTOP);
			break;
		}
		if(!ThreadCtrlFlag)
		{	// フラグが０になれば、スレッド終了する
			break;
		}
		strTmp.Format("完了分 ： %ld Bytes", i);
		::SetWindowText(pArg->hWndTxtCurbyte, strTmp);
	}
	strTmp.Format("完了分 ： %ld Bytes", i);
	::SetWindowText(pArg->hWndTxtCurbyte, strTmp);
	fclose(in);
	fclose(ot);

	ThreadEndFlag = 1;
	// 状態表示ダイアログを消去する
	::PostMessage(pArg->hWnd, WM_CLOSE, 0, 0);
	::ExitThread(0);
	return 0L;
}