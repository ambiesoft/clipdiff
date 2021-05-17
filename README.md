# clipdiff
See the differences of 2 texts through the clipboard.

# Enviromment
Windows, .NET 4.0 or higher.

# License
This software is freeware. See LICENSE.

# Install
Dowload the latest archive from https://github.com/ambiesoft/clipdiff/releases.
The archive is self-extractable 7zip file, extract it and run 'clipdiff.exe'.

# Uninstall
Delete files.

# How to use
* Launch clipdiff.exe
* Copy first text you wanto check the difference.
* Click [Paste] button on the toolbar of clipdiff. The texts are pasted on the left pane of the main window.
* Copy second text you wanto check the difference.
* Click [Paste] again.
* Now you can compare the 2 texts.
* If you want to compare the differece of a word or a character, open context menu by right-cliking the line and select [docdiff(...)]

# Example
* Open two commnad prompt consoles from Explorer, one is 64bit process(C:\Windows\Sysnative\cmd.exe) and 32bit process(C:\Windows\SysWOW64\cmd.exe), 2 processes has different enviroment values. Here we are goint to check the differences with clipdiff.
* Open clipdiff, select **[tools]->[Monitor clipboard]**.
* In the first command prompt, enter **set | clip**, this will set the environment values on the clipboard and clipdiff captures it which will be shown on the left pane.
* In the second commnad prompt, enter samely **set | clip**. The left pane of clipdiff moves to right pane, and the captured clipboard text appears on the left pane.
* You can see the differences in the clipdiff.

# Developper
Get the source code by executing following commands.
```
git clone https://github.com/ambiesoft/SessionGlobalMemory.git
git clone https://github.com/ambiesoft/lsMisc.git
git clone https://github.com/ambiesoft/clipdiff.git
```
And open clipdiff.sln and build.

# Download
Download binary from <https://github.com/ambiesoft/clipdiff/releases>.

# Donation
<http://ambiesoft.mooo.com/donate/>

# Contact
ambiesoft.trueff@gmail.com
