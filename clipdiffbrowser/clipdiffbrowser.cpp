

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

DWORD WINAPI watcher(LPVOID lpParameter)
{
	{
		WaitForSingleObject(lpParameter, INFINITE);
		CloseHandle(lpParameter);
	}

	Sleep(1000);

	TerminateProcess(GetCurrentProcess(), -1);
	return 0;
}



[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
#ifdef _DEBUG
	if (!IsDebuggerPresent())
		System::Diagnostics::Debug::Assert(false);
#endif

	HANDLE hEvent = NULL;
	HWND hWndHost;
	String^ clrLeft;
	String^ clrRight;
	bool standalone = false;
	try
	{
		CCommandLineParserA parser;
		COptionA opProcess("-p", 1);
		parser.AddOption(&opProcess);

		COptionA opHwnd("-w", 1);
		parser.AddOption(&opHwnd);

		COptionA opEvent("-e", 1);
		parser.AddOption(&opEvent);

		COptionA opMain;
		parser.AddOption(&opMain);

		COptionA opStandAlone("-s");
		parser.AddOption(&opStandAlone);

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
		string eventName = opEvent.getFirstValue();
		if (eventName.empty())
		{
			ErrorMessageBox(I18N(L"No event specified. exiting"));
			return 1;
		}
		hEvent = CreateEventA(NULL, TRUE, FALSE, eventName.c_str());
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
		HANDLE parent = OpenProcess(SYNCHRONIZE, TRUE, pid);
		if (NULL == parent)
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
			CreateThread(NULL,
				0,
				watcher,
				(LPVOID)parent,
				0,
				NULL);
		}

		string left;
		string right;
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

	
		{
			CDynamicSessionGlobalMemory sg1(left.c_str());
			CDynamicSessionGlobalMemory sg2(right.c_str());


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

	Application::Run(gcnew FormMain(hWndHost, clrLeft, clrRight, standalone));
	return 0;
}
