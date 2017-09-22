@ECHO OFF
IF NOT "%~f0" == "~f0" GOTO :WinNT
@"C:\Linkout\clipdiff\docdiff\ruby2.4\bin\ruby.exe" "C:/Linkout/clipdiff/docdiff/ruby2.4/bin/rake" %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO :EOF
:WinNT
@"C:\Linkout\clipdiff\docdiff\ruby2.4\bin\ruby.exe" "%~dpn0" %*
