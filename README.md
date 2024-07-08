# Danganronpa-Online-Client
This is the official client used, it is a derivative of [Attorney-Online-Client-Remake](https://github.com/AttorneyOnline/AO2-Client).

## Qt
This project uses Qt 5.15.2 (5.12.8 for Linux, and 5.15.13 for MacOS via [Homebrew](https://brew.sh/)), which is licensed under the [GNU Lesser General Public License](https://www.gnu.org/licenses/lgpl-3.0.txt) with [certain licensing restrictions and exceptions](https://www.qt.io/qt-licensing-terms/). To comply with licensing requirements for static linking, object code is available if you would like to relink with an alternative version of Qt, and the source code for Qt may be found at https://github.com/qt/qtbase, http://code.qt.io/cgit/, or at https://qt.io.

Copyright (C) 2022 The Qt Company Ltd.

## BASS
This project uses [BASS shared library](http://www.un4seen.com/).

Copyright (c) 1999-2022 Un4seen Developments Ltd. All rights reserved.

## Discord-RPC
This project uses the deprecated [discord-rpc library](https://github.com/discord/discord-rpc).

## VLC-Qt
This project uses [VLC-Qt 1.1.0](https://vlc-qt.tano.si/) in order to play videos with bundled codecs. You may find the source code and the binaries here: https://github.com/vlc-qt/vlc-qt

Copyright (C) 2010-2016 Tadej Novak

## Recommended Compilers in QtCreator

For development work on Windows to make 64-bit binaries, please use the MSVC2019 compiler. You will need to install the MSVC2019 Build Tools from the following website:
https://learn.microsoft.com/en-au/visualstudio/releases/2019/history

For development work on Windows to make 32-bit binaries, please use the MingW32-bit compiler.

For development work on the Mac to make 64-bit Silicon binaries, please use Clang (C/C++ arm 64bit).

For development work on the Mac to make 64-bit Intel binaries, please use Apple Clang (x64_64).

NOTE: If you get a `windeployqt` or `macdeployqt` not found error, you need to manually go to "QtCreator > Projects > Edit Build Configuration (Release) > Build Environment > Edit Path" and add the folder containing the correct version of the deployqt script (be sure to use the one matching the compiler and Qt version). For example, on Windows if using the default installation path, the path for MSVC2019 64-bit is `C:\Qt\5.15.2\msvc2019_64\bin`
