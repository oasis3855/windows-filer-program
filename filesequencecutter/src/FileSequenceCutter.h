// FileSequenceCutter.h : FILESEQUENCECUTTER アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_FILESEQUENCECUTTER_H__F9476F4A_9A2D_4DAD_8FD0_B5F71F1C728F__INCLUDED_)
#define AFX_FILESEQUENCECUTTER_H__F9476F4A_9A2D_4DAD_8FD0_B5F71F1C728F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CFileSequenceCutterApp:
// このクラスの動作の定義に関しては FileSequenceCutter.cpp ファイルを参照してください。
//

class CFileSequenceCutterApp : public CWinApp
{
public:
	CFileSequenceCutterApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CFileSequenceCutterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CFileSequenceCutterApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_FILESEQUENCECUTTER_H__F9476F4A_9A2D_4DAD_8FD0_B5F71F1C728F__INCLUDED_)
