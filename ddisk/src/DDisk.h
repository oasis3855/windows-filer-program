// DDisk.h : DDISK アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_DDISK_H__41C96AE5_D6FF_11D3_AD9A_0090CCA1066A__INCLUDED_)
#define AFX_DDISK_H__41C96AE5_D6FF_11D3_AD9A_0090CCA1066A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CDDiskApp:
// このクラスの動作の定義に関しては DDisk.cpp ファイルを参照してください。
//

class CDDiskApp : public CWinApp
{
public:
	void UninstallSeq();
	BOOL InstallSeq();
	CString m_binedit;
	void RegWriteAll(void);
	void RegReadAll(void);
	int m_inttype;
	int m_viewtype;
	CDDiskApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDDiskApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CDDiskApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	char m_buf[256];
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DDISK_H__41C96AE5_D6FF_11D3_AD9A_0090CCA1066A__INCLUDED_)
