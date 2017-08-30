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

	FormMain::FormMain(void)
	{
		InitializeComponent();

		int intval;
		bool boolval;

		InitialIni_ =  Profile::ReadAll(Ambiesoft::AmbLib::GetIniPath());
		try 
		{
			String^ fontstring;
			Profile::GetString(APP_OPTION, L"Font", L"", fontstring, InitialIni_);

			if(!String::IsNullOrEmpty(fontstring))
			{
				System::ComponentModel::TypeConverter^ converter =
					System::ComponentModel::TypeDescriptor::GetConverter( System::Drawing::Font::typeid );

				FontLV = dynamic_cast<System::Drawing::Font^>(converter->ConvertFromString(fontstring));
			}
		}
		catch(Exception^ ex) 
		{
			MessageBox::Show(ex->Message,
				Application::ProductName);
		}


		Profile::GetBool(APP_OPTION, L"ShowToolbar", true, boolval, InitialIni_);
		toolMain->Visible=boolval;

		Profile::GetBool(APP_OPTION, L"ShowStatusbar", true, boolval, InitialIni_);
		stMain->Visible=boolval;

		Profile::GetBool(APP_OPTION, L"ShowListheader", true, boolval, InitialIni_);
		IsHeaderVisible=boolval;



		Profile::GetInt(APP_OPTION, L"EngineLevel", 1, intval, InitialIni_);
		EngineLevel = (DifferenceEngine::DiffEngineLevel)intval;




		addColumn();
		addColumn();


		bool posReadFailed=false;
		int x,y,width,height;
		posReadFailed |= !Profile::GetInt(APP_OPTION, L"X", -10000, x, InitialIni_);
		posReadFailed |= !Profile::GetInt(APP_OPTION, L"Y", -10000, y, InitialIni_);

		posReadFailed |= !Profile::GetInt(APP_OPTION, L"Width", -10000, width, InitialIni_);
		posReadFailed |= !Profile::GetInt(APP_OPTION, L"Height", -10000, height, InitialIni_);
		if(!posReadFailed)
		{
			if(AmbLib::IsPointInMonitor(x,y))
			{
				this->StartPosition = FormStartPosition::Manual;
				this->Location = System::Drawing::Point(x,y);
				this->Size = System::Drawing::Size(width, Height);
			}
		}


	}

}

