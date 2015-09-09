@echo off

set bversion=x64
set vcvarsallPath=C:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\vcvarsall.bat

if not exist "%vcvarsallPath%" (echo Cannot find vcvarsall.bat at specified directory: "%vcvarsallPath%"&goto ending)
if not defined frameworkdir (echo Setting vcvarsall&call "%vcvarsallPath%" %bversion%)

setlocal
set builddir=debug_x64
if not exist %builddir% (echo Build directory: %builddir% does not exist, creating&mkdir %builddir%)

set CompilerFlags= -MTd -nologo -Gm- -GR- -EHa- -Od -Oi -WX -W4 -wd4201 -wd4100 -wd4189 -wd4505 -wd4702 -wd4127 -FC -Z7
set LinkerFlags= -SUBSYSTEM:CONSOLE -incremental:no -opt:ref User32.lib

cls
pushd %builddir%
echo.
echo BUILD STARTED AT %date% %time%
echo ----------------------------------


cl %CompilerFlags% ..\src\ontop.cpp -Fmontop.map /link %LinkerFlags%


echo ----------------------------------
echo BUILD FINISHED AT %date% %time%
popd

:ending
endlocal
