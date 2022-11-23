// FileCpEx.h : FILECPEX アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_FILECPEX_H__9EB7C6D6_63FE_4861_8A89_741385F03DFE__INCLUDED_)
#define AFX_FILECPEX_H__9EB7C6D6_63FE_4861_8A89_741385F03DFE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CFileCpExApp:
// このクラスの動作の定義に関しては FileCpEx.cpp ファイルを参照してください。
//

class CFileCpExApp : public CWinApp
{
public:
	CFileCpExApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CFileCpExApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CFileCpExApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_FILECPEX_H__9EB7C6D6_63FE_4861_8A89_741385F03DFE__INCLUDED_)
