set DISTORDIR=%~dp0distor\
set OutDir=%DISTORDIR%clipdiff\
set TARGETARCHIVE=%OutDir%..\clipdiff.exe


C:\Linkout\bin\sdel %DISTORDIR%
IF EXIST %DISTORDIR% (
exit /b %DISTORDIR%
)

cd %~dp0

set MSBUILDEXE="%ProgramFiles(x86)%\MSBuild\12.0\Bin\MSBuild.exe"
IF NOT EXIST %MSBUILDEXE% (
set MSBUILDEXE="%ProgramFiles%\MSBuild\12.0\Bin\MSBuild.exe"
)

%MSBUILDEXE% clipdiff.sln /t:zzzDistResource /p:Configuration=zzzDist /p:OutDir=%OutDir%
if %errorlevel% neq 0 exit /b %errorlevel%


sdel %TARGETARCHIVE%
IF EXIST %TARGETARCHIVE% (
exit /b
)


"C:\LegacyPrograms\7-Zip\7z.exe" a -sfx7z.sfx %TARGETARCHIVE% %OutDir% -mx9
if %errorlevel% neq 0 exit /b %errorlevel%


c:\Linkout\CommonExe\showballoon.exe /title:distor /balloonicon:1 "Everythin OK"


