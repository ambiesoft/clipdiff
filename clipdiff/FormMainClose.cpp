// clipdiff.cpp : main project file.

#include "stdafx.h"

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

		String^ inipath = AmbLib::GetIniPath();
		HashIni^ ini =  Profile::ReadAll(inipath);
		Profile::WriteInt(APP_OPTION, L"X", this->Location.X, ini);
		Profile::WriteInt(APP_OPTION, L"Y", this->Location.Y, ini);

		Profile::WriteInt(APP_OPTION, L"Width", this->Size.Width , ini);
		Profile::WriteInt(APP_OPTION, L"Height", this->Size.Height, ini);

		String^ fontstring=L"";
		if(FontLV) {
			System::ComponentModel::TypeConverter^ converter =
				System::ComponentModel::TypeDescriptor::GetConverter( System::Drawing::Font::typeid );

			fontstring = converter->ConvertToInvariantString(FontLV);


			// System::Drawing::Font^ font1 = dynamic_cast<System::Drawing::Font^>(converter->ConvertFromString( "Arial, 12pt" ));
		}
		Profile::WriteString(APP_OPTION, L"Font", fontstring, ini);


		Profile::WriteBool(APP_OPTION, L"ShowToolbar", toolMain->Visible, ini);
		Profile::WriteBool(APP_OPTION, L"ShowStatusbar", stMain->Visible, ini);
		Profile::WriteBool(APP_OPTION, L"ShowListheader", IsHeaderVisible, ini);

		Profile::WriteInt(APP_OPTION, L"EngineLevel", (int)EngineLevel, ini);

		Profile::WriteBool(APP_OPTION, "MonitorClipboard", IsMonitor, ini);
		Profile::WriteBool(APP_OPTION, "KeepLeft", IsKeepLeft, ini);
		Profile::WriteBool(APP_OPTION, "IgnoreSame", IsIgnoreSame, ini);
		Profile::WriteBool(APP_OPTION, "TopMost", this->TopMost, ini);

		for(;;)
		{
			try
			{
				Profile::WriteAll(ini, inipath,true);
				break;

			}
			catch(Exception^ ex)
			{
				if(System::Windows::Forms::DialogResult::Retry != MessageBox::Show(I18N("Failed to save settings." + "\r\n" + ex->Message),
					Application::ProductName,
					MessageBoxButtons::RetryCancel,
					MessageBoxIcon::Exclamation))
				{
					break;
				}
			}
		}


	}








	System::Void FormMain::FormMain_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) 
	{
		IsMonitor = false;
	}













}

