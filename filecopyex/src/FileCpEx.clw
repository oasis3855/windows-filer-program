; CLW ファイルは MFC ClassWizard の情報を含んでいます。

[General Info]
Version=1
LastClass=DlgProgress
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "FileCpEx.h"

ClassCount=4
Class1=CFileCpExApp
Class2=CFileCpExDlg

ResourceCount=4
Resource2=IDD_FILECPEX_DIALOG
Resource1=IDR_MAINFRAME
Class3=DlgErrSel
Resource3=IDD_DLG_ERR
Class4=DlgProgress
Resource4=IDD_DLG_PROGRESS

[CLS:CFileCpExApp]
Type=0
HeaderFile=FileCpEx.h
ImplementationFile=FileCpEx.cpp
Filter=N

[CLS:CFileCpExDlg]
Type=0
HeaderFile=FileCpExDlg.h
ImplementationFile=FileCpExDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CFileCpExDlg



[DLG:IDD_FILECPEX_DIALOG]
Type=1
Class=CFileCpExDlg
ControlCount=25
Control1=IDC_TXT_FROM,edit,1350631552
Control2=IDC_BTN_FROMBRW,button,1342242816
Control3=IDC_TXT_TO,edit,1350631552
Control4=IDC_BTN_TOBRW,button,1342242816
Control5=IDC_TXT_START,edit,1350631552
Control6=IDC_TXT_END,edit,1350631552
Control7=IDC_CK_FILEEND,button,1342242819
Control8=IDC_CMB_BUFSIZ,combobox,1344339971
Control9=IDC_CK_DLG,button,1342242819
Control10=IDC_TXT_RETRY,edit,1350631552
Control11=IDC_TXT_SKIP,edit,1350631552
Control12=IDC_CK_NULL,button,1342242819
Control13=IDC_BTN_COPY,button,1342242816
Control14=IDOK,button,1342242817
Control15=IDC_STATIC,static,1342308864
Control16=IDC_STATIC,static,1342308864
Control17=IDC_STATIC,static,1342308864
Control18=IDC_STATIC,static,1342308864
Control19=IDC_STATIC,static,1342308864
Control20=IDC_STATIC,static,1342308864
Control21=IDC_STATIC,static,1342308864
Control22=IDC_STATIC,static,1342308864
Control23=IDC_STATIC,static,1342308864
Control24=IDC_STATIC,static,1342308864
Control25=IDC_STATIC,static,1342308864

[DLG:IDD_DLG_ERR]
Type=1
Class=DlgErrSel
ControlCount=9
Control1=IDC_RADIO_SEL,button,1342373897
Control2=IDC_RADIO_SEL2,button,1342177289
Control3=IDC_TXT_ERRSKIP,edit,1350631552
Control4=IDC_CK_SAMESEL,button,1342242819
Control5=IDC_TXT_MOREERR,edit,1350631552
Control6=IDOK,button,1342242817
Control7=IDC_STXT_MES,static,1342308352
Control8=IDC_STATIC,static,1342308864
Control9=IDC_STATIC,static,1342308864

[CLS:DlgErrSel]
Type=0
HeaderFile=DlgErrSel.h
ImplementationFile=DlgErrSel.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_CK_SAMESEL

[DLG:IDD_DLG_PROGRESS]
Type=1
Class=DlgProgress
ControlCount=4
Control1=IDC_STXT_MES,static,1342308864
Control2=IDC_STXT_TOTALSIZ,static,1342308864
Control3=IDC_STXT_CURSIZ,static,1342308864
Control4=IDC_BTN_STOP,button,1342242816

[CLS:DlgProgress]
Type=0
HeaderFile=DlgProgress.h
ImplementationFile=DlgProgress.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_BTN_STOP

