@echo off
set ProjectDir=%~dp0
set CompillersDir=C:\Users\M.D.Medvedev\Desktop\pr0jects\#Compilers

set INCLUDE_MSVC=%CompillersDir%\C++\MSVC\14.13.26128\include
set LIBDIR_MSVC=%CompillersDir%\C++\MSVC\14.13.26128\lib\x86
set INCLUDE_WK_um=%CompillersDir%\C++\Windows Kits\10\Include\10.0.16299.0\um
set INCLUDE_WK_ucrt=%CompillersDir%\C++\Windows Kits\10\Include\10.0.16299.0\ucrt
set INCLUDE_WK_shared=%CompillersDir%\C++\Windows Kits\10\Include\10.0.16299.0\shared
set LIBDIR_WK=%CompillersDir%\C++\Windows Kits\10\Lib\10.0.16299.0\um\x86


set LIBS="libcpmt.lib" "libcmt.lib" "oldnames.lib" "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib" "msvcrtd.lib" "libucrt.lib"

set SOURCES="%ProjectDir%main.cpp" "%ProjectDir%dataProcessing.cpp"
set SOURCES_Compiler="%ProjectDir%main.cpp" "%ProjectDir%dataProcessing.cpp"

set OBJECTS="%ProjectDir%main.obj" "%ProjectDir%dataProcessing.obj"
set OBJECTS_Compiler=/Fo"%ProjectDir%main.obj" "%ProjectDir%dataProcessing.obj"

set CompilerC++=%CompillersDir%\C++\MSVC\14.13.26128\bin\Hostx86\x86

set IncludeMSDir=/I "%ProjectDir%"

@echo on
SET INCLUDE=%INCLUDE_MSVC%;%INCLUDE_WK_um%;%INCLUDE_WK_ucrt%;%INCLUDE_WK_shared%;
SET LIB=%LIBDIR_MSVC%;%LIBDIR_WK%;%CompillersDir%\C++\Windows Kits\10\Lib\10.0.16299.0\ucrt\x86;

cd %ProjectDir%
%CompilerC++%\cl.exe /Fo"main.obj" /c "main.cpp" /FAs /EHsc /Od /Ob1 /Oi /Oy- /Z7 /I "%ProjectDir%"
%CompilerC++%\cl.exe /Fo"dataProcessing.obj" /c "dataProcessing.cpp" /FAs /EHsc /Od /Ob1 /Oi /Oy- /Z7 /I "%ProjectDir%"
%CompilerC++%\link.exe %OBJECTS% /OUT:"%ProjectDir%Saek0.exe" /DEBUG /MACHINE:"X86" /INCREMENTAL:NO /MAP /SUBSYSTEM:"CONSOLE" /NOLOGO
pause