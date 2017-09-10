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
#include "../Common/Ruby.h"

#include "../../lsMisc/cppclr/clrString.h"
#include "../../lsMisc/cppclr/clrHelper.h"

namespace clipdiffbrowser {

	using namespace stdwin32;
	using namespace Ambiesoft;
	using std::wstring;
	using namespace System::Diagnostics;
	using namespace System::Text;
	using namespace System::IO;



	void FormMain::afterPaste(String^ html)
	{
		while (!browser->Document || browser->ReadyState != WebBrowserReadyState::Complete)
		{
			Application::DoEvents();
		}
		browser->Document->Write(html);
	}
	String^ GetDocdiffResolutionOptionString(String^ resolution)
	{
		if (resolution == L"char")
			return L"--char";

		return L"--word";
	}

	//void FormMain::OnOutputDataReceived(System::Object ^sender, System::Diagnostics::DataReceivedEventArgs ^e)
	//{
	//	sbRubyOut_.Append(e->Data);
	//}
	//void FormMain::OnErrorDataReceived(System::Object ^sender, System::Diagnostics::DataReceivedEventArgs ^e)
	//{
	//	sbRubyErr_.Append(e->Data);
	//}




	void FormMain::Paste(String^ left, String^ right, String^ resolution)
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

		FileInfo fileinfo1(file1);
		long long filesize1 = fileinfo1.Length;
		DateTime filelastwrite1 = fileinfo1.LastWriteTimeUtc;

		FileInfo fileinfo2(file2);
		long long filesize2 = fileinfo2.Length;
		DateTime filelastwrite2 = fileinfo2.LastWriteTimeUtc;

		String^ clrCommandLine = String::Format(L"{0} --utf8 --crlf {1} {2} {3}",
			doubleQuote( Ruby::DocDiffrb),
			GetDocdiffResolutionOptionString(resolution),
			doubleQuote(file2),
			doubleQuote(file1));

		try
		{
			String^ out;
			String^ err;

			OpenCommnadGetResult(Ruby::RubyExe, clrCommandLine, Encoding::UTF8,
				out, err);




			FileInfo fileinfo1t(file1);
			long long filesize1t = fileinfo1t.Length;
			DateTime filelastwrite1t = fileinfo1t.LastWriteTimeUtc;

			FileInfo fileinfo2t(file2);
			long long filesize2t = fileinfo2t.Length;
			DateTime filelastwrite2t = fileinfo2t.LastWriteTimeUtc;

			if (filesize1 == filesize1t && filelastwrite1 == filelastwrite1t)
				File::Delete(file1);

			if (filesize2 == filesize2t && filelastwrite2 == filelastwrite2t)
				File::Delete(file2);

			if (!String::IsNullOrEmpty(err))
			{
				ErrorMessageBox(I18N(L"DocDiff failed.") + L"\r\n" + err);
				this->Close();
				return;
			}


			this->BeginInvoke(gcnew VSDelegate(this, &FormMain::afterPaste), out);

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

	System::Void FormMain::FormMain_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
	{
		if (!standalone_)
		{
			CloseHandle(ghParent);

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
	System::Void FormMain::FormMain_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e)
	{

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
			String^ title = left_->Length > 32 ? left_->Substring(0, 32)+L"..." : left_;
			title += L" | clipdiff";
			this->Text = title;
		}

		Paste(left_, right_, resolution_);



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

			{
				size_t size1 = sg1.size();
				size_t size2 = sg2.size();

				if (size1 > 0)
				{
					unsigned char* p1 = (unsigned char*)malloc(size1);
					memset(p1, 0, size1);
					sg1.get(p1);
					left = gcnew String((wchar_t*)p1);
					free(p1);
				}
				if (size2 > 0)
				{
					unsigned char* p2 = (unsigned char*)malloc(size2);
					memset(p2, 0, size2);
					sg2.get(p2);
					right = gcnew String((wchar_t*)p2);
					free(p2);
				}
			}

			String^ resolution;
			CDynamicSessionGlobalMemory sgResolution("clipdiff-data-resolution");
			{
				size_t sizeResolution = sgResolution.size();
				if (sizeResolution > 0)
				{
					unsigned char* pR = (unsigned char*)malloc(sizeResolution);
					memset(pR, 0, sizeResolution);
					sgResolution.get(pR);
					resolution = gcnew String((wchar_t*)pR);
					free(pR);
				}
			}

			Paste(left, right, resolution);
		}
		break;

		case WM_APP_CLOSE:
		{
			this->Close();
		}
		break;

		} //switch


		Form::WndProc(m);
	}






















} // namespace clipdiffbrowser



