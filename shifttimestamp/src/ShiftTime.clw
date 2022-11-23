; CLW ファイルは MFC ClassWizard の情報を含んでいます。

[General Info]
Version=1
LastClass=CDlgSelectExt
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ShiftTime.h"

ClassCount=5
Class1=CShiftTimeApp
Class2=CShiftTimeDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_DLG_SELEXXT
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=CDlgHelpDoc
Resource4=IDD_DLG_HELPDOC
Class5=CDlgSelectExt
Resource5=IDD_SHIFTTIME_DIALOG

[CLS:CShiftTimeApp]
Type=0
HeaderFile=ShiftTime.h
ImplementationFile=ShiftTime.cpp
Filter=N

[CLS:CShiftTimeDlg]
Type=0
HeaderFile=ShiftTimeDlg.h
ImplementationFile=ShiftTimeDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CShiftTimeDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=ShiftTimeDlg.h
ImplementationFile=ShiftTimeDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SHIFTTIME_DIALOG]
Type=1
Class=CShiftTimeDlg
ControlCount=33
Control1=IDC_STATIC,static,1342308864
Control2=IDC_STATIC,static,1342308864
Control3=IDC_EDIT_PATH,edit,1350631552
Control4=IDC_BTN_BROWSE,button,1342242816
Control5=IDC_STATIC,static,1342308864
Control6=IDC_EDIT_FILE,edit,1350631552
Control7=IDC_BTN_WILDCARD,button,1342242816
Control8=IDC_STATIC,static,1342308864
Control9=IDC_EDIT_YEAR,edit,1350631552
Control10=IDC_SCRL_YEAR,scrollbar,1342177281
Control11=IDC_STATIC,static,1342308864
Control12=IDC_EDIT_MONTH,edit,1350631552
Control13=IDC_SCRL_MONTH,scrollbar,1342177281
Control14=IDC_STATIC,static,1342308864
Control15=IDC_EDIT_DAY,edit,1350631552
Control16=IDC_SCRL_DAY,scrollbar,1342177281
Control17=IDC_STATIC,static,1342308864
Control18=IDC_EDIT_HOUR,edit,1350631552
Control19=IDC_SCRL_HOUR,scrollbar,1342177281
Control20=IDC_STATIC,static,1342308864
Control21=IDC_EDIT_MIN,edit,1350631552
Control22=IDC_SCRL_MIN,scrollbar,1342177281
Control23=IDC_STATIC,static,1342308864
Control24=IDC_EDIT_SEC,edit,1350631552
Control25=IDC_SCRL_SEC,scrollbar,1342177281
Control26=IDC_STATIC,static,1342308864
Control27=IDC_RADIO_SHIFT,button,1342308361
Control28=IDC_RADIO_SHIFT_2,button,1342177289
Control29=IDC_CHECK_ZEROSEC,button,1342242819
Control30=IDC_CHECK_LOG,button,1342242819
Control31=IDC_BTN_EXEC,button,1342242816
Control32=IDCANCEL,button,1342242816
Control33=IDC_BTN_HELP,button,1342242816

[DLG:IDD_DLG_HELPDOC]
Type=1
Class=CDlgHelpDoc
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_EDIT_MAIN,edit,1352730628

[CLS:CDlgHelpDoc]
Type=0
HeaderFile=DlgHelpDoc.h
ImplementationFile=DlgHelpDoc.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgHelpDoc
VirtualFilter=dWC

[DLG:IDD_DLG_SELEXXT]
Type=1
Class=CDlgSelectExt
ControlCount=15
Control1=IDC_RADIO_SEL,button,1342373897
Control2=IDC_RADIO_SEL2,button,1342177289
Control3=IDC_RADIO_SEL3,button,1342177289
Control4=IDC_RADIO_SEL4,button,1342177289
Control5=IDC_RADIO_SEL5,button,1342177289
Control6=IDC_RADIO_SEL6,button,1342177289
Control7=IDC_RADIO_SEL7,button,1342177289
Control8=IDC_RADIO_SEL8,button,1342177289
Control9=IDC_RADIO_SEL9,button,1342177289
Control10=IDC_RADIO_SEL10,button,1342177289
Control11=IDC_RADIO_SEL11,button,1342177289
Control12=IDOK,button,1342242817
Control13=IDCANCEL,button,1342242816
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,static,1342308352

[CLS:CDlgSelectExt]
Type=0
HeaderFile=DlgSelectExt.h
ImplementationFile=DlgSelectExt.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_RADIO_SEL
VirtualFilter=dWC

