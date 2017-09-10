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
#include "../../lsMisc/CommandLineParser.h"

#include "FormMain.h"
#include "helper.h"

using namespace clipdiffbrowser;
using namespace Ambiesoft;

using namespace System::Windows::Forms;

using std::string;
using std::wstring;
#pragma comment(lib, "user32.lib")

#include "../../lsMisc/stdwin32/stdwin32.h"
using namespace stdwin32;

#include "../../lsMisc/cppclr/clrHelper.h"

DWORD WINAPI watcher(LPVOID)
{
	{
		WaitForSingleObject(ghParent, INFINITE);
		CloseHandle(ghParent);
	}

	Sleep(gWatcherWait);

	TerminateProcess(GetCurrentProcess(), -1);
	return 0;
}



[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
#ifdef _DEBUG
	Ambiesoft::CSessionGlobalMemory<bool> sgDebugDownloadManager("sgDebugClipdiffBrowser");
	if (!IsDebuggerPresent() && sgDebugDownloadManager)
		System::Diagnostics::Debug::Assert(false);
#endif

	if (args->Length <= 0)
	{
		Alert(I18N(L"Please lauch clipdiff.exe"));
		return 1;
	}

	HANDLE hEvent = NULL;
	HWND hWndHost;
	String^ clrLeft;
	String^ clrRight;
	String^ resolution;
	bool standalone = false;
	try
	{
		CCommandLineParser parser;
		COption opProcess(L"-p", 1);
		parser.AddOption(&opProcess);

		COption opHwnd(L"-w", 1);
		parser.AddOption(&opHwnd);

		COption opEvent(L"-e", 1);
		parser.AddOption(&opEvent);

		COption opMain;
		parser.AddOption(&opMain);

		COption opStandAlone(L"-s");
		parser.AddOption(&opStandAlone);

		COption opResolution(L"-r", 1);
		parser.AddOption(&opResolution);

		parser.Parse();

		if (opStandAlone.hadOption())
		{
			//ErrorMessageBox(I18N(L"stadnalone"));
			standalone = true;
		}

		if (!opEvent.hadOption() || !opEvent.hadValue())
		{
			ErrorMessageBox(I18N(L"No event specified. exiting"));
			return 1;
		}
		wstring eventName = opEvent.getFirstValue();
		if (eventName.empty())
		{
			ErrorMessageBox(I18N(L"No event specified. exiting"));
			return 1;
		}
		hEvent = CreateEvent(NULL, TRUE, FALSE, eventName.c_str());
		DASSERT(GetLastError() == ERROR_ALREADY_EXISTS);
		DASSERT(hEvent);
		if (hEvent == NULL)
		{
			ErrorMessageBox(I18N(L"Failed to create event. exiting"));
			return 1;
		}

		if (!opProcess.hadOption() || !opProcess.hadValue())
		{
			ErrorMessageBox(I18N(L"No parent process specified. exiting"));
			return 1;
		}
		DWORD pid = opProcess.getFirstValueAsUInt();
		ghParent = OpenProcess(SYNCHRONIZE, TRUE, pid);
		if (NULL == ghParent)
		{
			ErrorMessageBox(I18N(L"Failed to open parent process. exiting"));
			return 1;
		}


		if (!opHwnd.hadOption() || !opHwnd.hadValue())
		{
			ErrorMessageBox(I18N(L"No parent window specified. exiting."));
			return 1;
		}
		hWndHost = (HWND)opHwnd.getFirstValueAsPointer();
		if (!::IsWindow(hWndHost))
		{
			ErrorMessageBox(I18N(L"Host Window specified is not a window. exiting."));
			return 1;
		}

		if (!standalone)
		{
			gWatcher = CreateThread(NULL,
				0,
				watcher,
				(LPVOID)NULL,
				0,
				NULL);
		}

		wstring left;
		wstring right;
		if (opMain.getValueCount() != 2)
		{
			ErrorMessageBox(I18N(L"2 Files must be specified. exiting."));
			return 1;
		}
		left = opMain.getValue(0);
		right = opMain.getValue(1);
		if (left.empty() || right.empty())
		{
			ErrorMessageBox(I18N(L"One of 2 main args is empty."));
			return 1;
		}

		//if (!System::IO::File::Exists(file1))
		//{
		//	ErrorMessageBox(String::Format(I18N(L"{} does not exists."), file1));
		//	return 1;
		//}
		//if (!System::IO::File::Exists(file2))
		//{
		//	ErrorMessageBox(String::Format(I18N(L"{} does not exists."), file2));
		//	return 1;
		//}

		if (opResolution.hadOption())
		{
			resolution = gcnew String(opResolution.getFirstValue().c_str());
		}

		{
			CDynamicSessionGlobalMemory sg1(stdToString(left).c_str());
			CDynamicSessionGlobalMemory sg2(stdToString(right).c_str());


			size_t size1 = sg1.size();
			size_t size2 = sg2.size();

			if (size1 > 0)
			{
				unsigned char* p1 = (unsigned char*)malloc(size1);
				memset(p1, 0, size1);
				sg1.get(p1);
				clrLeft = gcnew String((wchar_t*)p1);
			}
			if (size2 > 0)
			{
				unsigned char* p2 = (unsigned char*)malloc(size2);
				memset(p2, 0, size2);
				sg2.get(p2);
				clrRight = gcnew String((wchar_t*)p2);
			}

			DVERIFY(SetEvent(hEvent));
			CloseHandle(hEvent);
			hEvent = NULL;
		}
	}
	catch (Exception^ ex)
	{
		ErrorMessageBox(L"", ex);
		return 1;
	}
	finally
	{
		CloseHandle(hEvent);
		hEvent = NULL;
	}
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	Application::Run(gcnew FormMain(hWndHost, clrLeft, clrRight, resolution, standalone));
	return 0;
}
