@echo off
 
:: Create build dir
set testDir=%~dp0..\build_test
if not exist %testDir% mkdir %testDir%
pushd %testDir%

:: Create obj dir
set objDir=.\obj
if not exist %objDir% mkdir %objDir%

:: Needed folders
set extDir=%~dp0..\external
set scriptDir=%~dp0..\scripts

:: Use make to build default target
cd %scriptDir%\
mingw32-make test

cd %testDir%

:: Copy dependencies
if not exist %testDir%\SDL2.dll xcopy /y %extDir%\SDL2-2.0.7\lib\x86\SDL2.dll .
if not exist %testDir%\SDL2_image.dll xcopy /y %extDir%\SDL2_image-2.0.2\lib\x86\SDL2_image.dll .
if not exist %testDir%\SDL2_mixer.dll xcopy /y %extDir%\SDL2_mixer-2.0.2\lib\x86\SDL2_mixer.dll .
if not exist %testDir%\SDL2_ttf.dll xcopy /y %extDir%\SDL2_ttf-2.0.14\lib\x86\SDL2_ttf.dll .
if not exist %testDir%\glew32.dll xcopy /y %extDir%\glew-2.1.0\bin\Release\Win32\glew32.dll .
if not exist %testDir%\libpng16-16.dll xcopy /y %extDir%\SDL2_image-2.0.2\lib\x86\libpng16-16.dll .
if not exist %testDir%\zlib1.dll xcopy /y %extDir%\SDL2_image-2.0.2\lib\x86\zlib1.dll .

:: Copy assets
set assetsDir=%~dp0..\assets

:: Copy assets
if not exist %testDir%\assets mkdir %testDir%\assets
xcopy /y /s %assetsDir% %testDir%\assets

:: Remove test obj files
rd /s /q %testDir%\%objDir%

popd