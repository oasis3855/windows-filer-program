
____________________________________________________________________________

                        論理ディスク アクセスツール
                                version 0.5

                                                           inoue-h@iname.com
                                                          GDH03306@nifty.com

                                                Copyright (C) 2000 井上 博計

____________________________________________________________________________












もくじ

      はじめに
      １．動作環境
      ２．インストール
      ３．簡単な使用法
      ４．アンインストール
      ５．保証、著作権等　法律面でのお知らせ

      ENGLISH document after Japanese document .





はじめに
      論理ディスク アクセスツールをを使用いただきありがとうございます。 


      Windows98標準機能で、唯一欠落していたディスクエディタ。
      本プログラムを使用することで、論理ディスクの指定セクタを直接編集するこ
      とができるようになります。（編集作業には、別途バイナリーエディタを入手
      してください。）
      ブート・プログラムの書き換え、バックアップ。ディレクトリ・エントリやFA
      Tを書き換えることによる削除ファイルの復活。ハードディスク内の解析などな
      ど。
      パワー・ユーザーの希望にこたえる製品です。


      このプログラムでは次のようなことができます。

          ●論理ディスクのDPBを表示
          ●特定のセクターにあるデータをファイルに複写（保存）
          ●ファイルの内容を特定セクターに複写（書き込み）


      なお、使用の手引きは DDisk.hlpに入っていますので、そちらをご覧ください。



１．動作環境
      Windows 98 （日本語版）
      Windows 95 でも一部機能利用可
      Windows NT/2000 では利用不可

      FAT12, FAT16, FAT32の論理ディスクを対象とします。

      MFC42.DLL および MSVCRT.DLL がC:\WINDOWS\SYSTEMに存在すること
      これらのライブラリは最新版を用意してください。



２．インストール
      配布されたプログラム・パッケージを、適当なフォルダにコピーする。
      （新たにフォルダを作ることを薦めます。アンインストールに便利です。）

      DDisk.exeを実行すると、インストーラが起動します。



３．簡単な使用法
      スタートメニューの「Logical Disk Access Tool」メニューを実行します。



４．アンインストール
      コントロールパネルの「アプリケーションの追加と削除」からアンインストー
      ルします。.nf



５．使用許諾条件
      このプログラムとドキュメントをフリーウエアーとし、すべての著作権は作者
      である井上博計に属します。

      著作者はこのプログラム及びドキュメントに関するいかなる保証も行いません。
      このプログラムの使用はすべて使用者の責任において行って下さい。

      著作者による許可無しにこのプログラムとドキュメントを販売することは出来
      ません。ただし、無料ソフトとして配布する場合はディスク料金や郵送料等、
      最低限の対価の授受を伴ってもかまいません。また、雑誌などの販促物に付属
      させるときもこれに準じます。

      その他条件は、添付のヘルプファイル（DDisk.hlp）に準じます。


      Windows 95/98/2000/NT は Microsoft社の登録商標です
      Visual C++, Microsoft WordはMicrosoft社の登録商標です
      その他、このプログラム中の各社の製品名等は各社の登録商標です



Logical Disk Access Tool users manual

Thank you for using Logical Disk Access Tool .


To install DDisk.exe, copy DDisk.exe to your favorite folder. Then execute D
Disk.exe, installer automatically appiars.


IMPORTANT NOTICE
In your Syatem folder, there is latest MFC42.DLL and MSVCRT.DLL . You can ob
tain that from ftp://ftp.microsoft.com .


LEGAL NOTICE
This program is free ware. And all copyrights is reserved by INOUE. Hirokazu
(author). There is no guarantee of this program functioning correctly, and a
uthor is not responsible to every result of this program. Other condition fo
llows "sTAsk help file".
Every contacts with author is based on Japanese language only .



                                                              2000 / 02 / 17
____________________________________________________________________________
