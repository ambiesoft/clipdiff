
set TARGETDIR=C:\Linkout\clipdiff\
set TARGETARCHIVE=C:\Linkout\clipdiff.exe

cd %~dp0

sdel %TARGETDIR%
IF EXIST %TARGETDIR% (
exit /b
)

"c:\Program Files\MSBuild\12.0\Bin\MSBuild" clipdiff.sln /t:zzzDistResource /p:Configuration=Dist
if %errorlevel% neq 0 exit /b %errorlevel%


sdel %TARGETARCHIVE%
IF EXIST %TARGETARCHIVE% (
exit /b
)


"C:\LegacyPrograms\7-Zip\7z.exe" a -sfx7z.sfx %TARGETARCHIVE% %TARGETDIR% -mx9
if %errorlevel% neq 0 exit /b %errorlevel%

echo everything OK
pause

