
@echo off


REM Compiler versions
REM clang version 17.0.3
REM Microsoft (R) C/C++ Optimizing Compiler Version 19.41.34123 for x64


call build_clean


REM -------------------------------- Common --------------------------------

set NAME=library

set SRC=.

set COMMON_COMPILE_FLAGS=/Od /c /W4 /WX /EHsc /std:c17 /GS- /Gs9999999
set INCLUDE_DIRS=/I"src" /I"src_external"
set DEBUG_COMPILE_FLAGS=/DDEBUG /Zi
set DEBUG_LINK_FLAGS=/SUBSYSTEM:CONSOLE /MACHINE:X64 /DEBUG:FULL
set LIBS=kernel32.lib user32.lib gdi32.lib opengl32.lib




REM -------------------------------- Clang --------------------------------

set CLANG_COMPILE_FLAGS=-march=skylake

set CLANG_INTERMEDIATE_DIR=.\clang_build_intermediate
set CLANG_DEPLOY_DEBUG_DIR=.\clang_deploy\debug

mkdir %CLANG_INTERMEDIATE_DIR%
mkdir %CLANG_DEPLOY_DEBUG_DIR%

clang-cl %COMMON_COMPILE_FLAGS% %CLANG_COMPILE_FLAGS% %DEBUG_COMPILE_FLAGS% %INCLUDE_DIRS% /Fo%CLANG_INTERMEDIATE_DIR%\test.obj %SRC%\test.c
if %errorlevel% neq 0 exit /b %errorlevel%

lld-link %DEBUG_LINK_FLAGS% %LIBS% %CLANG_INTERMEDIATE_DIR%\*.obj /OUT:"%CLANG_INTERMEDIATE_DIR%\%NAME%.exe"
if %errorlevel% neq 0 exit /b %errorlevel%

xcopy /Y %CLANG_INTERMEDIATE_DIR%\%NAME%.exe %CLANG_DEPLOY_DEBUG_DIR%
xcopy /Y %CLANG_INTERMEDIATE_DIR%\%NAME%.pdb %CLANG_DEPLOY_DEBUG_DIR%

echo.
echo %CLANG_DEPLOY_DEBUG_DIR%\%NAME%.exe
echo.


REM -------------------------------- MSVC ---------------------------------

set MSVC_INTERMEDIATE_DIR=.\msvc_build_intermediate
set MSVC_DEPLOY_DEBUG_DIR=.\msvc_deploy\debug

mkdir %MSVC_INTERMEDIATE_DIR%
mkdir %MSVC_DEPLOY_DEBUG_DIR%

cl %COMMON_COMPILE_FLAGS% %DEBUG_COMPILE_FLAGS% %INCLUDE_DIRS% /Fo%MSVC_INTERMEDIATE_DIR%\test.obj %SRC%\test.c
if %errorlevel% neq 0 exit /b %errorlevel%

link %DEBUG_LINK_FLAGS% %LIBS% %MSVC_INTERMEDIATE_DIR%\*.obj /OUT:"%MSVC_INTERMEDIATE_DIR%\%NAME%.exe"
if %errorlevel% neq 0 exit /b %errorlevel%

xcopy /Y %MSVC_INTERMEDIATE_DIR%\%NAME%.exe %MSVC_DEPLOY_DEBUG_DIR%
xcopy /Y %MSVC_INTERMEDIATE_DIR%\%NAME%.pdb %MSVC_DEPLOY_DEBUG_DIR%

echo.
echo %MSVC_DEPLOY_DEBUG_DIR%\%NAME%.exe
echo.

