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

#include "FormMain.h"
//#include "difflist.h"
//#include "ListViewForScroll.h"
//#include "LVInfo.h"
//


namespace clipdiff {


	using namespace Ambiesoft;
	using namespace System::Text;
	using namespace System::IO;
	using namespace System::Collections::Generic;
	// using namespace DiffMatchPatch;
	System::Void FormMain::FormMain_Load(System::Object^  sender, System::EventArgs^  e)
	{
		de_ = gcnew DifferenceEngine::DiffEngine();

		bool boolval;
		Profile::GetBool(APP_OPTION, "MonitorClipboard", false, boolval, InitialIni_);
		IsMonitor = boolval;

		Profile::GetBool(APP_OPTION, "KeepLeft", false, boolval, InitialIni_);
		IsKeepLeft = boolval;

		Profile::GetBool(APP_OPTION, "IgnoreSame", false, boolval, InitialIni_);
		IsIgnoreSame = boolval;

		Profile::GetBool(APP_OPTION, "TopMost", false, boolval, InitialIni_);
		this->TopMost = boolval;

		this->Text = Application::ProductName;
		IsIdling = true;

#ifdef _DEBUG
		ToolStripMenuItem ^debug = gcnew ToolStripMenuItem();
		debug->Text = "Debug";
		debug->Click += gcnew System::EventHandler(this, &clipdiff::FormMain::OnClick);
		helpToolStripMenuItem->DropDownItems->Add(debug);
#endif
	}


	void FormMain::OnClick(System::Object ^sender, System::EventArgs ^e)
	{
		//diff_match_patch^ dmp = gcnew diff_match_patch();
		//List<Diff^>^ diff = dmp->diff_main("AAAA\nbbb", "AAb\nbbb");
	}
}