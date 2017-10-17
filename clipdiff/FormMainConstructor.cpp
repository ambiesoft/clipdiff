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

	FormMain::FormMain(void)
	{
		InitializeComponent();

		int intval;
		bool boolval;

		InitialIni_ =  Profile::ReadAll(Common::IniPath);
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


		Engine = EngineKind::DiffEngine;

		Profile::GetInt(APP_OPTION, L"EngineLevel", 1, intval, InitialIni_);
		EngineLevel = (DifferenceEngine::DiffEngineLevel)intval;

		DocDiffEngineLevel = DocDiffEngineKind::DocDiffWord;


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
			if(AmbLib::IsPointInScreen(x,y))
			{
				this->StartPosition = FormStartPosition::Manual;
				this->Location = System::Drawing::Point(x,y);
				this->Size = System::Drawing::Size(width, Height);
			}
		}

		
		Profile::GetInt(APP_OPTION, L"ListViewNoChangeBackColor", Color::White.ToArgb(), intval, InitialIni_);
		defaultLVNoChangeBackColor_ = Color::FromArgb(intval);
		defaultLVNoChangeBackColorRGB_ = defaultLVNoChangeBackColor_.ToArgb();

		Profile::GetInt(APP_OPTION, L"ListViewAddBackColor", Color::Aqua.ToArgb(), intval, InitialIni_);
		defaultLVAddBackColor_ = Color::FromArgb(intval);

		Profile::GetInt(APP_OPTION, L"ListViewDeleteBackColor", Color::Red.ToArgb(), intval, InitialIni_);
		defaultLVDeleteBackColor_ = Color::FromArgb(intval);

		Profile::GetInt(APP_OPTION, L"ListViewRepaceBackColor", Color::Yellow.ToArgb(), intval, InitialIni_);
		defaultLVReplaceBackColor_ = Color::FromArgb(intval);
	}

}

