// CopyTime.h : COPYTIME アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_COPYTIME_H__B56BE424_9FB9_11D4_AD9A_0090CCA1066A__INCLUDED_)
#define AFX_COPYTIME_H__B56BE424_9FB9_11D4_AD9A_0090CCA1066A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CCopyTimeApp:
// このクラスの動作の定義に関しては CopyTime.cpp ファイルを参照してください。
//

class CCopyTimeApp : public CWinApp
{
public:
	CCopyTimeApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CCopyTimeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CCopyTimeApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。


#endif // !defined(AFX_COPYTIME_H__B56BE424_9FB9_11D4_AD9A_0090CCA1066A__INCLUDED_)
