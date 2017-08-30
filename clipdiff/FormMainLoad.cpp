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
		this->TopMost=boolval;

		this->Text = Application::ProductName;
		IsIdling = true;
	}
}

