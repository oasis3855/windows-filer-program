// ShiftTime.h : SHIFTTIME アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_SHIFTTIME_H__CB3CBACB_A218_4577_BE02_5A465A167028__INCLUDED_)
#define AFX_SHIFTTIME_H__CB3CBACB_A218_4577_BE02_5A465A167028__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CShiftTimeApp:
// このクラスの動作の定義に関しては ShiftTime.cpp ファイルを参照してください。
//

class CShiftTimeApp : public CWinApp
{
public:
	CShiftTimeApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CShiftTimeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CShiftTimeApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SHIFTTIME_H__CB3CBACB_A218_4577_BE02_5A465A167028__INCLUDED_)
