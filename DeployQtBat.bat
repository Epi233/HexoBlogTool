set PATH=D:\Programmes\Qt\6.0.3\mingw81_64\bin;D:/Programmes/Qt/Tools/mingw810_64\bin;%PATH%
cd /d %~dp0
cd Release
for /r "%cd%" %%i in (*.exe) do (windeployqt.exe "%%~nxi")
pause