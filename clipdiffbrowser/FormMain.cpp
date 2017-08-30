

#include "stdafx.h"
#include <vcclr.h>
#include "FormMain.h"
#include "helper.h"



namespace clipdiffbrowser {

	using namespace stdwin32;
	using namespace Ambiesoft;
	using std::wstring;
	using namespace System::Diagnostics;
	using namespace System::Text;
	using namespace System::IO;

	String^ q_(String^ s)
	{
		if (String::IsNullOrEmpty(s))
			return s;
		if (s[0] == L'"')
			return s;

		bool needquote = false;
		for each(Char c in s)
		{
			if (Char::IsWhiteSpace(c))
			{
				needquote = true;
				break;
			}
		}

		return needquote ? L"\"" + s + L"\"" : s;
	}
	System::Void FormMain::FormMain_Load(System::Object^  sender, System::EventArgs^  e)
	{
		LONG_PTR style =::GetWindowLong((HWND)this->Handle.ToPointer(), GWL_STYLE);
		LONG_PTR newstyleAdd = WS_CHILD;
		LONG_PTR newstyleDel = WS_POPUP;
		::SetWindowLong((HWND)this->Handle.ToPointer(), GWL_STYLE, (style | newstyleAdd)&~newstyleDel);
		if (!::SetParent((HWND)this->Handle.ToPointer(), hWndHost_))
		{
			DWORD error = GetLastError();
			ErrorMessageBox(I18N(L"SetParent Failed."), error);
			this->Close();
			return;
		}
		::PostMessage((HWND)this->Handle.ToPointer(), WM_CHANGEUISTATE, UIS_INITIALIZE, NULL);
		::PostMessage(hWndHost_, WM_CHANGEUISTATE, UIS_INITIALIZE, NULL);

		RECT rHost;
		if (!GetWindowRect(hWndHost_, &rHost))
		{
			DWORD error = GetLastError();
			ErrorMessageBox(I18N(L"GetClientRect Failed."), error);
			this->Close();
			return;
		}

		this->Size = System::Drawing::Size(rHost.right - rHost.left, rHost.bottom - rHost.top);
		this->Location = System::Drawing::Point(0, 0);
		this->Dock = DockStyle::Fill;

		UpdateWindow((HWND)this->Handle.ToPointer());
		// browser->Navigate(L"http://ambiesoft.fam.cx/");

		wstring thisdir = stdGetParentDirectory(stdGetModuleFileName());
		wstring rubyexe = stdCombinePath(thisdir, L"docdiff\\ruby1.8\\bin\\ruby.exe");
		wstring rubylibdir = stdCombinePath(thisdir, L"docdiff\\docdiff-0.3.3");
		wstring docdiffrb = stdCombinePath(thisdir, L"docdiff\\docdiff-0.3.3\\docdiff.rb");
		wstring t = stdGetEnvironmentVariable(L"RUBYLIB");
		if (t.empty())
			t = rubylibdir.c_str();
		else
			t = rubylibdir + L";" + t;

		SetEnvironmentVariable(L"RUBYLIB", t.c_str());

		String^ clrCommandLine = String::Format(L"{0} --utf8 --crlf {1} {2}",
			gcnew String(docdiffrb.c_str()),
			q_(file1_),
			q_(file2_));
		//pin_ptr<const wchar_t> pCommandLine = PtrToStringChars(clrCommandLine);
		// HANDLE hRuby;
		//if (!OpenCommon((HWND)this->Handle.ToPointer(),
		//	rubyexe.c_str(),
		//	pCommandLine,
		//	NULL,
		//	&hRuby
		//	))
		//{
		//	DWORD error = GetLastError();
		//	ErrorMessageBox(I18N(L"Failed to launch ruby."), error);
		//	this->Close();
		//	return;
		//}

		try
		{
			Process process;

			ProcessStartInfo startInfo;
			startInfo.FileName = gcnew String(rubyexe.c_str());
			startInfo.Arguments = clrCommandLine;
			startInfo.CreateNoWindow = true;

			startInfo.StandardOutputEncoding = Encoding::UTF8;
			startInfo.RedirectStandardOutput = true;

			startInfo.StandardErrorEncoding = Encoding::UTF8;
			startInfo.RedirectStandardError = true;

			startInfo.UseShellExecute = false;
			
			process.StartInfo = %startInfo;
			process.Start();

			String^ line;
			String^ error;
			StringBuilder sb;
			StringBuilder sbError;
			do
			{
				line = process.StandardOutput->ReadLine();
				if (line)
					sb.Append(line);

				error = process.StandardError->ReadLine();
				if (error)
					sbError.Append(error);
			} while (line || error);

			process.WaitForExit();

			if (sbError.Length != 0)
			{
				ErrorMessageBox(I18N(L"DocDiff failed.") + L"\r\n" + sbError.ToString());
				this->Close();
				return;
			}

			String^ resultHtml = sb.ToString();
			resultHtml = AmbLib::ReplaceFirst(resultHtml, L"<?xml version=\"1.0\" encoding=\"UTF-8\"?>", L"");
			//resultText = AmbLib::ReplaceLast(resultText, L""
			String^ resultFile = Path::GetTempFileName();
			{
				StreamWriter sw(resultFile, false, Encoding::UTF8);
				sw.Write(resultHtml);
			}
			// browser->Document->Write(sb.ToString());
			browser->Navigate(resultFile);
		}
		catch (ObjectDisposedException^ ex)
		{
			ErrorMessageBox(I18N(L"Failed to lanuch ruby."), ex);
			this->Close();
			return;
		}
		catch (InvalidOperationException^ ex)
		{
			ErrorMessageBox(I18N(L"Failed to lanuch ruby."), ex);
			this->Close();
			return;
		}
		catch (Win32Exception^ ex)
		{
			ErrorMessageBox(I18N(L"Failed to lanuch ruby."), ex);
			this->Close();
			return;
		}
		
	}






























	void FormMain::WndProc(Message% m)
	{
		DTRACE(m);

		switch (m.Msg)
		{
		case WM_APP_RESIZE:
		{
			RECT rHost;
			if (!GetWindowRect(hWndHost_, &rHost))
			{
				DWORD error = GetLastError();
				ErrorMessageBox(I18N(L"GetClientRect Failed."), error);
				this->Close();
				return;
			}

			this->Size = System::Drawing::Size(rHost.right - rHost.left, rHost.bottom - rHost.top);
			this->Location = System::Drawing::Point(0, 0);
		}
		break;

		} //switch


		Form::WndProc(m);
	}






















} // namespace clipdiffbrowser