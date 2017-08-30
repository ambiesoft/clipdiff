

#include "stdafx.h"
#include "../../MyUtility/CommandLineParser.h"

#include "FormMain.h"
#include "helper.h"

using namespace clipdiffbrowser;
using namespace Ambiesoft;

using namespace System::Windows::Forms;

#pragma comment(lib, "user32.lib")

DWORD WINAPI watcher(LPVOID lpParameter)
{
	{
		WaitForSingleObject(lpParameter, INFINITE);
		CloseHandle(lpParameter);
	}

	Sleep(30 * 1000);

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

	CCommandLineParser parser;
	COption opProcess(L"-p", 1);
	parser.AddOption(&opProcess);

	COption opHwnd(L"-w", 1);
	parser.AddOption(&opHwnd);

	COption opMain;
	parser.AddOption(&opMain);

	parser.Parse();

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
	HWND hWndHost = (HWND)opHwnd.getFirstValueAsPointer();
	if (!::IsWindow(hWndHost))
	{
		ErrorMessageBox(I18N(L"Host Window specified is not a window. exiting."));
		return 1;
	}
	CreateThread(NULL,
		0,
		watcher,
		(LPVOID)parent,
		0,
		NULL);

	String^ file1;
	String^ file2;
	if (opMain.getValueCount() != 2)
	{
		ErrorMessageBox(I18N(L"2 Files must be specified. exiting."));
		return 1;
	}
	file1 = gcnew String(opMain.getValue(0).c_str());
	file2 = gcnew String(opMain.getValue(1).c_str());

	if (!System::IO::File::Exists(file1))
	{
		ErrorMessageBox(String::Format(I18N(L"{} does not exists."), file1));
		return 1;
	}
	if (!System::IO::File::Exists(file2))
	{
		ErrorMessageBox(String::Format(I18N(L"{} does not exists."), file2));
		return 1;
	}

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	Application::Run(gcnew FormMain(hWndHost, file1,file2));
	return 0;
}
