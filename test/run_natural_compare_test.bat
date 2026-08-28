@ECHO OFF
SETLOCAL
PUSHD %~dp0

SET "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
IF NOT EXIST "%VSWHERE%" (
  ECHO ERROR: vswhere.exe not found
  EXIT /B 1
)

FOR /f "delims=" %%A IN ('"%VSWHERE%" -latest -property installationPath') DO SET "VSINSTALL=%%A"
IF NOT DEFINED VSINSTALL (
  ECHO ERROR: Visual Studio not found
  EXIT /B 1
)

CALL "%VSINSTALL%\Common7\Tools\VsDevCmd.bat" -arch=amd64

SET "BUILDDIR=%~dp0build"
IF NOT EXIST "%BUILDDIR%" MD "%BUILDDIR%"

SET "TMPFILE=%BUILDDIR%\NaturalCompare.cpp"
powershell -Command "$s='%~dp0..\src\DSUtil\NaturalCompare.cpp'; $d='%BUILDDIR%\NaturalCompare.cpp'; Get-Content $s | Where-Object { $_ -notmatch 'stdafx\.h' -and $_ -notmatch 'NaturalCompare\.h' } | Set-Content $d"

PUSHD "%BUILDDIR%"

cl /std:c++17 /EHsc /I"%~dp0..\src" /I"%~dp0..\src\DSUtil" /I"%~dp0..\include" /Fe"NaturalCompareTest.exe" "%TMPFILE%" "%~dp0NaturalCompareTest.cpp"
IF %ERRORLEVEL% NEQ 0 (
  ECHO Build failed
  EXIT /B %ERRORLEVEL%
)

NaturalCompareTest.exe
POPD
POPD
ENDLOCAL
EXIT /B %ERRORLEVEL%
