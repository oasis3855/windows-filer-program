## ![icon](readme_pics/softdown-ico-ie.gif) Internet Explorer Cookie コントローラ for Windows<!-- omit in toc -->

---
[Home](https://oasis3855.github.io/webpage/) > [Software](https://oasis3855.github.io/webpage/software/index.html) > [Software Download](https://oasis3855.github.io/webpage/software/software-download.html) > [ie_cookiecontrol](../ie_cookiecontrol/README.md) > ***ie_cookiecontrol*** (this page)

<br />
<br />

Last Updated : May. 2002

- [ソフトウエアのダウンロード](#ソフトウエアのダウンロード)
- [機能の概要](#機能の概要)
  - [技術的解説](#技術的解説)
- [動作環境](#動作環境)
- [バージョンアップ履歴](#バージョンアップ履歴)
- [ライセンス](#ライセンス)

<br />
<br />

## ソフトウエアのダウンロード

- ![download icon](../readme_pics/soft-ico-download-darkmode.gif)   [このGitHubリポジトリを参照する](../ie_cookiecontrol/download) 

- ![download icon](../readme_pics/soft-ico-download-darkmode.gif)   [GoogleDriveを参照する](https://drive.google.com/drive/folders/0B7BSijZJ2TAHMDI3YWE0YmUtNzZjZS00ZjUzLThkYjMtMmFkYmJjMjVhNzI3?resourcekey=0-0wvm6IbV4p93ILebG8X0PA)

<br />
<br />

## 機能の概要

Microsoft Internet Explorer（インターネット エクスプローラ）のCookieを、一定の条件をつけて一括削除するソフトウエア

***最近のInternet Explorerには、Cookieを自動削除するセキュリティ機能がビルトインされているため、このソフトウエアは必要ありません***

![設定ダイアログ](readme_pics/soft-win-cookiecontrol.gif)

Internet Explorerでは、Cookieをデータファイルとして保存しています。このソフトウエアでは、このデータファイルを一定の条件（例えば、ファイルの日時やファイル名など）を決めて一括削除することができます。

ウエブサイトを訪問したときに作られるCookieデータには、訪問履歴やパスワード、入力履歴など何らかのデータが保存されている場合があります。これらのデータはユーザの訪問サイトや入力履歴に合わせた公告表示など「商業上の目的」で利用される場合や、こっそりと個人情報を収集するための「悪意の目的」をもって使われる場合もあります。

必要のないCookieは削除してしまうのが、個人情報を守るためには必要だという考えで作られたのがこのソフトウエアです。

### 技術的解説

レジストリより、Cookie の保存フォルダを検索して、そこにある指定拡張子（通常は *.txt）のファイルをCookieのデータファイルとみなして処理しています。 

<br />
<br />

## 動作環境

- Windows 95/98/Me/NT/2000/XP
- Internet Explorer Version 4, 5, 5.5, 6.0 （Firefox, Chromeなどの他のブラウザでは機能しません） 

<br />
<br />

## バージョンアップ履歴

- Version 1.0 (2001/03/04)

  - 公開用初版 

- Version 1.1 (2002/04/07)

  - インストーラの改良 
  - 英語版のリソース添付（Multi Language 対応） 
  - Cookie フォルダの自動取得オプション追加 

- Version 1.2 (2002/05/07)

  - セキュリティ耐性向上 

<br />
<br />

## ライセンス

このソフトウエアは [GNU General Public License v3ライセンスで公開する](https://gpl.mhatta.org/gpl.ja.html) フリーソフトウエア

