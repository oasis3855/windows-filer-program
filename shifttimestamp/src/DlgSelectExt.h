#if !defined(AFX_DLGSELECTEXT_H__17397D2E_92A1_4921_8B56_8D565B037BD1__INCLUDED_)
#define AFX_DLGSELECTEXT_H__17397D2E_92A1_4921_8B56_8D565B037BD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSelectExt.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSelectExt ダイアログ

class CDlgSelectExt : public CDialog
{
// コンストラクション
public:
	CDlgSelectExt(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDlgSelectExt)
	enum { IDD = IDD_DLG_SELEXXT };
	int		m_radio_sel;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDlgSelectExt)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDlgSelectExt)
		// メモ: ClassWizard はこの位置にメンバ関数を追加します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DLGSELECTEXT_H__17397D2E_92A1_4921_8B56_8D565B037BD1__INCLUDED_)
