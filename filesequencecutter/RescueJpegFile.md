## デジタルカメラ用メモリーからの画像の救出（復旧）<!-- omit in toc -->

---
[Home](https://oasis3855.github.io/webpage/) > [Software](https://oasis3855.github.io/webpage/software/index.html) > [Software Download](https://oasis3855.github.io/webpage/software/software-download.html) > [filesequencecutter](../filesequencecutter/README.md) > ***RescueJpegFile*** (this page)

<br />
<br />

Last Updated : Apr. 2024

<br />
<br />

## 概要

ディレクトリ・エントリやFATテーブルが破壊されたディスクから、ファイルの先頭に「EXIF/JPEGヘッダ情報」があるファイルを救出する方法です。

主に、デジカメのメモリーカードの管理領域が破壊された場合のデータ・レスキューを対象とします。

このページに書かれている方法は全て、OSの標準機能や、フリーソフトウエアのみで実行可能です。

## 注意

これらの操作の影響、結果についてはすべて自己責任で行ってください。
仮に、データがすべて消失したり、OSが破壊されたりしても作者は何ら責任を負いません。

このドキュメントで説明している内容が理解不能な方、自己責任について理解できない方は、「有料のデータ復旧サービス会社」を利用してください。

この件に関して当方への質問、提案、苦情、その他問い合わせ等は一切受け付けません。
当方が公開しているプログラムが正常に動作するかどうかは、一切保証できません。まず、自身で十分なテストを行ってください。

## 想定している利用環境

- USB ストレージデバイスとして接続されたメモリー・カード （リムーバブル・メディアとして認識）
- FAT ファイルシステム
- JPEG (EXIF) データ
- データは連続して格納されている（途中で削除、記録を繰り返していない）

<br />
<br />

## ディスク・イメージの抽出

追加ソフトウエアのインストールが不要で、標準機能のみで行える Linux で抽出することをお勧めします。

なお、追加ソフトウエアをインストールすることで、Windows でも実行可能です。

### Linux で抽出

対象ディスクを調査し、抽出すべきデータの「ブロック数」を得る。

```
$ sudo fdisk -l /dev/sdb

ディスク /dev/sdb: 3.84 GiB, 4126146560 バイト, 8058880 セクタ
Disk model:  USB CARD READER
単位: セクタ (1 * 512 = 512 バイト)
セクタサイズ (論理 / 物理): 512 バイト / 512 バイト
I/O サイズ (最小 / 推奨): 512 バイト / 512 バイト
ディスクラベルのタイプ: dos
ディスク識別子: 0x00000000

デバイス   起動 開始位置 最後から  セクタ サイズ Id タイプ
/dev/sdb1           8192  8058879 8050688   3.8G  b W95 FAT32
```

セクタ数 8050688 個 で、セクタサイズは 512 Bytes／セクタ という情報が得られた。

ここではサンプル例として、先頭より 2 GBytes（402400 セクタ分） を抽出し、出力ファイルのサイズを確認する。

```
$ sudo dd if=/dev/sdb of=./diskimage.bin bs=512 count=402400

402400+0 レコード入力
402400+0 レコード出力
206028800 bytes (206 MB, 196 MiB) copied, 9.79497 s, 21.0 MB/s

vm@Ubuntu2204M720q:~/Desktop$ ls -la

合計 201224
drwxr-xr-x  2 vm   vm       12288 2024-04-04 09:48:17 ./
drwxr-x--- 49 vm   vm        4096 2024-04-02 19:16:17 ../
-rw-r--r--  1 root root 206028800 2024-04-04 09:53:05 diskimage.bin
```

なお、ディスク全体をファイル抽出する場合は、fdiskで得られたセクタ数 8050688 個を用いれば良い。コマンド例としては次のようになる。

``` sudo dd if=/dev/sdb of=./diskimage.bin bs=512 count=8050688 ```

なお、実際より多いセクタ数を dd コマンドに指定しても、ディスク・エンドで自動的に終了します（するはず）。

<br />
<br />

## JPEGファイルの切り出し

jpeg/exif の 16進数Magic Number「 FFH D8H FFH E1H 」 をファイル開始のキーワードとして自動的にファイルを切り分けるソフトウエアを公開しています。

- [FileSequenceCutter ファイル連続カッター for Windows](./README.md)

取り扱い可能なファイル長はファイルポインタが long 変数で収まる範囲内です（約2 GBytes）。

書き出しフォルダには、何もファイルが入っていないフォルダを指定するのが望ましいです。「 data0000.dat 」のように数字をつけて書き出します。

キーワードは16進数8ビットのバイト列で記述します。16進数のみでも、0x を付けても、H を付けても認識するはずです。

なお、JPEGファイルのエンドは検出していませんので、次のファイルの先頭の1バイト手前、もしくはファイル・エンドまで書き出されます。気になる方はJPEGファイルの無駄領域を削除するソフトウエアで削除してください。

<br />
<br />

## EXIFデータによるファイル名の振りなおし、タイムスタンプの設定

jpegファイルのExifデータを用いて、ファイルの名前を変換したり、タイムスタンプをExifデータに合わせたりするツールを公開しています。

- [Exifデータによるjpegファイル名変更・タイムスタンプ変更](https://github.com/oasis3855/image-tools/tree/main/renfile-exif-win)

<br />
<br />

## 参考情報

- マルチプラットフォーム対応の [TestDisk](https://www.cgsecurity.org/wiki/TestDisk) , [PhotoRec](https://www.cgsecurity.org/wiki/PhotoRec)
- Windows [fsutil](https://learn.microsoft.com/en-us/windows-server/administration/windows-commands/fsutil) コマンド