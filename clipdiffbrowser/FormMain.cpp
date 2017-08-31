

#include "stdafx.h"
#include <vcclr.h>
#include "FormMain.h"
#include "helper.h"
#include "Ruby.h"


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

	void FormMain::afterPaste(String^ html)
	{
		while (!browser->Document || browser->ReadyState != WebBrowserReadyState::Complete)
		{
			Application::DoEvents();
		}
		browser->Document->Write(html);
	}
	void FormMain::Paste(String^ left, String^ right)
	{
		browser->Navigate(L"about:blank");

		String^ file1 = Path::GetTempFileName();
		String^ file2 = Path::GetTempFileName();
		{
			StreamWriter sw1(file1, false, Encoding::UTF8);
			StreamWriter sw2(file2, false, Encoding::UTF8);

			sw1.Write(left);
			sw2.Write(right);
		}
		String^ clrCommandLine = String::Format(L"{0} --utf8 --crlf {1} {2}",
			Ruby::DocDiffrb,
			q_(file2),
			q_(file1));

		try
		{
			Process process;

			ProcessStartInfo startInfo;
			startInfo.FileName = Ruby::RubyExe;
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
			while (process.StandardOutput->Peek() > -1)
			{
				line = process.StandardOutput->ReadLine();
				if (line)
					sb.Append(line);
				else
					break;
			}

			while (process.StandardError->Peek() > -1)
			{
				error = process.StandardError->ReadLine();
				if (error)
					sbError.Append(error);
				else
					break;
			}


			process.WaitForExit();

			File::Delete(file1);
			File::Delete(file2);

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

			this->BeginInvoke(gcnew VSDelegate(this, &FormMain::afterPaste), sb.ToString());

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
	System::Void FormMain::FormMain_Load(System::Object^  sender, System::EventArgs^  e)
	{
		if (!standalone_)
		{
			LONG_PTR style = ::GetWindowLong((HWND)this->Handle.ToPointer(), GWL_STYLE);
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
		}
		else
		{
			String^ title = left_->Length > 32 ? left_->Substring(0, 32) : left_;
			title += L" | clipdiff";
			this->Text = title;
		}

		Paste(left_,right_);


		
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

		case WM_APP_PASTE:
		{
			String^ left;
			String^ right;
			CDynamicSessionGlobalMemory sg1("clipdiff-data-1");
			CDynamicSessionGlobalMemory sg2("clipdiff-data-2");

			size_t size1 = sg1.size();
			size_t size2 = sg2.size();

			if (size1 > 0)
			{
				unsigned char* p1 = (unsigned char*)malloc(size1);
				memset(p1, 0, size1);
				sg1.get(p1);
				left = gcnew String((wchar_t*)p1);
			}
			if (size2 > 0)
			{
				unsigned char* p2 = (unsigned char*)malloc(size2);
				memset(p2, 0, size2);
				sg2.get(p2);
				right = gcnew String((wchar_t*)p2);
			}

			Paste(left,right);
		}
		break;

		} //switch


		Form::WndProc(m);
	}






















} // namespace clipdiffbrowser