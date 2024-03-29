//Copyright (C) 2017 Ambiesoft All rights reserved.
//
//Redistribution and use in source and binary forms, with or without
//modification, are permitted provided that the following conditions
//are met:
//1. Redistributions of source code must retain the above copyright
//notice, this list of conditions and the following disclaimer.
//2. Redistributions in binary form must reproduce the above copyright
//notice, this list of conditions and the following disclaimer in the
//documentation and/or other materials provided with the distribution.
//
//THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
//ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//SUCH DAMAGE.

// clipdiff.cpp : main project file.

#include "stdafx.h"

#include "../Common/Common.h"

#include "FormMain.h"
//#include "difflist.h"
//#include "ListViewForScroll.h"
//#include "LVInfo.h"



namespace clipdiff {


	using namespace Ambiesoft;
	using namespace System::Text;
	using namespace System::Collections::Generic;




	System::Void FormMain::FormMain_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
	{
		IsIdling = false;

		if (e->CloseReason != System::Windows::Forms::CloseReason::WindowsShutDown && HasSubWindows)
		{
			if (NoCloseSubWinConfirm)
			{
				CloseAllSubwindows();
			}
			else
			{
				System::Windows::Forms::DialogResult dresult = CppUtils::CenteredMessageBox(this,
					I18N(L"Do you want to close subwindows?"),
					ProductName,
					MessageBoxButtons::YesNoCancel,
					MessageBoxIcon::Question);
				switch (dresult)
				{
				case System::Windows::Forms::DialogResult::Yes:
					CloseAllSubwindows();
					break;
				case System::Windows::Forms::DialogResult::Cancel:
					e->Cancel = true;
					return;
				}
			}
		}

		HWND hChild = GetChildMainFormWindow();
		SendNotifyMessage(hChild, WM_APP_CLOSE, 0, 0);

		String^ inipath = Common::IniPath;
		HashIni^ ini = Profile::ReadAll(inipath);
		Profile::WriteInt(APP_OPTION, SECTION_X, this->Location.X, ini);
		Profile::WriteInt(APP_OPTION, SECTION_Y, this->Location.Y, ini);

		Profile::WriteInt(APP_OPTION, SECTION_WIDTH, this->Size.Width, ini);
		Profile::WriteInt(APP_OPTION, SECTION_HEIGHT, this->Size.Height, ini);

		String^ fontstring = L"";
		if (FontLV) {
			System::ComponentModel::TypeConverter^ converter =
				System::ComponentModel::TypeDescriptor::GetConverter(System::Drawing::Font::typeid);

			fontstring = converter->ConvertToInvariantString(FontLV);


			// System::Drawing::Font^ font1 = dynamic_cast<System::Drawing::Font^>(converter->ConvertFromString( "Arial, 12pt" ));
		}
		Profile::WriteString(APP_OPTION, L"Font", fontstring, ini);

		Profile::WriteBool(APP_OPTION, SECTION_SHOWTOOLTIP, IsShowToolTip, ini);
		Profile::WriteBool(APP_OPTION, SECTION_SHOWTOOLBAR, toolMain->Visible, ini);
		Profile::WriteBool(APP_OPTION, SECTION_SHOWSTATUSBAR, stMain->Visible, ini);
		Profile::WriteBool(APP_OPTION, SECTION_SHOWLISTHEADER, IsHeaderVisible, ini);

		Profile::WriteInt(APP_OPTION, SECTION_ENGINELEVEL, (int)EngineLevel, ini);

		Profile::WriteBool(APP_OPTION, "MonitorClipboard", IsMonitor, ini);
		Profile::WriteBool(APP_OPTION, "KeepLeft", IsKeepLeft, ini);
		Profile::WriteBool(APP_OPTION, "IgnoreSame", IsIgnoreSame, ini);
		Profile::WriteBool(APP_OPTION, "TopMost", this->TopMost, ini);


		Profile::WriteInt(APP_OPTION,
			SECTION_LISTVIEWNOCHANGEBACKCOLOR,
			defaultLVNoChangeBackColor_.ToArgb(),
			ini);
		Profile::WriteInt(APP_OPTION,
			SECTION_LISTVIEWADDBACKCOLOR,
			defaultLVAddBackColor_.ToArgb(),
			ini);
		Profile::WriteInt(APP_OPTION,
			SECTION_LISTVIEWDELETEBACKCOLOR,
			defaultLVDeleteBackColor_.ToArgb(),
			ini);
		Profile::WriteInt(APP_OPTION,
			SECTION_LISTVIEWREPACEBACKCOLOR,
			defaultLVReplaceBackColor_.ToArgb(),
			ini);


		Profile::WriteBool(APP_OPTION, SECTION_NOCLOSESUBWINCONFIRM, NoCloseSubWinConfirm, ini);

		for (;;)
		{
			try
			{
				Profile::WriteAll(ini, inipath, true);
				break;
			}
			catch (Exception^ ex)
			{
				if (System::Windows::Forms::DialogResult::Retry != MessageBox::Show(
					I18N("Failed to save settings." + "\r\n" + ex->Message),
					Application::ProductName,
					MessageBoxButtons::RetryCancel,
					MessageBoxIcon::Exclamation))
				{
					break;
				}
			}
		}


	}






	bool FormMain::WaitChildClose(int maxwait)
	{
		for (;;)
		{
			DWORD dwRet = WaitForSingleObject(childProcess_, 500);

			if (dwRet != WAIT_TIMEOUT)
				return true;

			if (maxwait != INFINITE)
			{
				maxwait -= 500;
				if (maxwait <= 0)
					return false;
			}
			Application::DoEvents();
		}
	}

	System::Void FormMain::FormMain_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e)
	{
		IsMonitor = false;

		Visible = false;
		if (childProcess_)
		{
			int maxwait = 5000;
#ifdef _DEBUG
			maxwait = INFINITE;
#endif
			if (!WaitChildClose(maxwait))
				TerminateProcess(childProcess_, 12345);
			CloseHandle(childProcess_);
			childProcess_ = NULL;
		}
	}













}

