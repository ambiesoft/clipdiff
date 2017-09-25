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

#include "stdafx.h"

#include "FormMain.h"
#include "helper.h"
//#include "../Common/Ruby.h"
//
//#include "../../lsMisc/cppclr/clrString.h"
//#include "../../lsMisc/cppclr/clrHelper.h"

namespace clipdiffbrowser {

	using namespace stdwin32;
	using namespace Ambiesoft;
	using std::wstring;
	using namespace System::Diagnostics;
	using namespace System::Text;
	using namespace System::IO;


	System::Void FormMain::FormMain_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
	{
	}
	System::Void FormMain::FormMain_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e)
	{
		if (!standalone_)
		{
			gbDisableTerminate = true;
			CloseHandle(ghParent);
			// TerminateThread(gWatcher, -1);
			CloseHandle(gWatcher);

			LONG_PTR style = ::GetWindowLong((HWND)this->Handle.ToPointer(), GWL_STYLE);
			LONG_PTR newstyleAdd = WS_POPUP;
			LONG_PTR newstyleDel = WS_CHILD;
			::SetWindowLong((HWND)this->Handle.ToPointer(), GWL_STYLE, (style | newstyleAdd)&~newstyleDel);
			if (!::SetParent((HWND)this->Handle.ToPointer(), NULL))
			{
				DWORD error = GetLastError();
				ErrorMessageBox(I18N(L"SetParent Failed."), error);
				this->Close();
				return;
			}
			::SendMessage((HWND)this->Handle.ToPointer(), WM_CHANGEUISTATE, UIS_INITIALIZE, NULL);
		}

	}









} // namespace clipdiffbrowser



