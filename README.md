# clipdiff
With clipdiff, you can check the differences of 2 texts without saving them to files.

# Enviromment
Windows, .NET 4.0 or higher.

# License
This software is freeware. See LICENSE.

# Install
If you downloaded the binary file, open it to extract files. No setup programs are provied.

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
* Open commnad prompt from 64bit process and 32bit process, 2 processes has different enviroment values. check the differences with clipdiff.
* Open clipdiff, select **[tools]->[Monitor clipboard]**.
* In the first command prompt, enter **set | clip**, this will set the environment values on the clipboard.
* In the second commnad prompt, enter samely **set | clip**.
* You can see the differences in the clipdiff.

# Developper
Get the source code by executing following commands.
```
git clone https://github.com/erasoni/SessionGlobalMemory.git
git clone https://github.com/erasoni/lsMisc.git
git clone https://github.com/erasoni/clipdiff.git
```
And open clipdiff.sln and build.

# Download
Download binary from https://github.com/erasoni/clipdiff/releases.

# Contact
ambiesoft.trueff@gmail.com
