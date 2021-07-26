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
		currentSelectedSpan_ = -1;
		diffSpans_ = nullptr;

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


		String^ clrCommandLine = String::Format(L"--utf8 --crlf {0} {1} {2}",
			GetDocdiffResolutionOptionString(resolution),
			doubleQuote(getShortPah(file2)),
			doubleQuote(getShortPah(file1)) );

		try
		{
			String^ out;
			String^ err;

			//OpenCommnadGetResult(Ruby::RubyExe, clrCommandLine, Encoding::UTF8,
			//	out, err);

			Ruby::RunDocDiff(clrCommandLine, out, err);


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

	System::Void FormMain::FormMain_Load(System::Object^  sender, System::EventArgs^  e)
	{
		ghForm = (HWND)this->Handle.ToPointer();
		if (!standalone_)
		{
			LONG_PTR style = ::GetWindowLong((HWND)this->Handle.ToPointer(), GWL_STYLE);
			LONG_PTR newstyleAdd = WS_CHILD;
			LONG_PTR newstyleDel = WS_POPUP;
			::SetWindowLongPtr((HWND)this->Handle.ToPointer(), GWL_STYLE, (style | newstyleAdd)&~newstyleDel);
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
		}
		else
		{
			String^ title = left_->Length > 32 ? left_->Substring(0, 32)+L"..." : left_;
			title += L" | clipdiff";
			this->Text = title;
		}

		Paste(left_, right_, resolution_);
	}


	int FormMain::TotalSpan::get()
	{
		if (diffSpans_)
		{
			return diffSpans_->Count;
		}
		diffSpans_ = gcnew System::Collections::Generic::List<HtmlElement^>();

		HtmlDocument^ doc = browser->Document;
		if (!doc)
			return 0;

		for each(HtmlElement^ elem in doc->GetElementsByTagName("span"))
		{
			String^ styleclass = elem->GetAttribute("className");
			if(!String::IsNullOrEmpty(styleclass) && styleclass != "common")
			{
				diffSpans_->Add(elem);
			}
		}
		return diffSpans_->Count;
	}

	//bool FormMain::IsSpanElement(HtmlElement^ elem)
	//{
	//	if (!elem)
	//		return false;

	//	return String::Compare(elem->TagName, "span", StringComparison::InvariantCultureIgnoreCase)==0;
	//}
	//HtmlElement^ FormMain::GetNextElement0(HtmlElement^ elem)
	//{
	//	HtmlElement^ ret = GetNextElement1(elem);
	//	if (ret)
	//		return ret;

	//	if (!elem->Parent)
	//		return nullptr;

	//	if (!elem->Parent->NextSibling)
	//		return nullptr;

	//	return GetNextElement0(elem->Parent->NextSibling);
	//}
	//HtmlElement^ FormMain::GetNextElement1(HtmlElement^ elem)
	//	{
	//		HtmlElement^ ret = GetNextElement2(elem);
	//	if (ret)
	//		return ret;

	//	if (elem->NextSibling)
	//		return GetNextElement1(elem->NextSibling);

	//	return nullptr;
	//}
	//HtmlElement^ FormMain::GetNextElement2(HtmlElement^ elem)
	//{
	//	if (!elem)
	//		return nullptr;

	//	for each (HtmlElement^ child in elem->Children)
	//	{
	//		if (IsSpanElement(child))
	//			return child;

	//		HtmlElement^ ret = GetNextElement2(child);
	//		if (IsSpanElement(ret))
	//			return ret;
	//	}

	//	// no child
	//	HtmlElement^ sibling = GetNextElement2(elem->NextSibling);
	//	if (IsSpanElement(sibling))
	//		return sibling;

	//	return nullptr; // GetNextElement(elem->Parent->NextSibling);
	//}
	void FormMain::GotoPrevDiff()
	{
		--currentSelectedSpan_;
		if (currentSelectedSpan_ < 0)
		{
			MessageBeep(MB_OK);
			if (TotalSpan != 0)
				currentSelectedSpan_ = TotalSpan;
			return;
		}
		diffSpans_[currentSelectedSpan_]->ScrollIntoView(true);
	}
	void FormMain::GotoNextDiff()
	{
		++currentSelectedSpan_;
		if(currentSelectedSpan_ >= TotalSpan)
		{
			MessageBeep(MB_OK);
			currentSelectedSpan_ = -1;
			return;
		}
		diffSpans_[currentSelectedSpan_]->ScrollIntoView(true);
		//if (!currentDiffLine_)
		//{
		//	HtmlDocument^ doc = browser->Document;
		//	if (!doc)
		//		return;

		//	currentDiffLine_ = GetNextElement0(doc->Body);
		//}
		//else
		//{
		//	currentDiffLine_ = GetNextElement0(currentDiffLine_);
		//}
		//for each(HtmlElement^ elem in doc->GetElementsByTagName(L"SPAN"))
		//{
		//	String^ styleclass = elem->GetAttribute("className");
		//	if(!String::IsNullOrEmpty(styleclass) && styleclass != "common")
		//	{
		//		elem->ScrollIntoView(true);
		//		elem->SetAttribute("CurrentDiffLine", "1");
		//		return;
		//	}
		//}

		//for (; currentDiffLine_; currentDiffLine_ = GetNextElement0(currentDiffLine_))
		//{
		//	String^ styleclass = currentDiffLine_->GetAttribute("className");
		//	if (!String::IsNullOrEmpty(styleclass) && styleclass != "common")
		//	{
		//		currentDiffLine_->ScrollIntoView(true);
		//		return;
		//	}
		//}
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

		case WM_APP_GOTOPREVDIFF:
		{
			GotoPrevDiff();
		}
		break;
		case WM_APP_GOTONEXTDIFF:
		{
			GotoNextDiff();
		}
		break;

		} //switch


		Form::WndProc(m);
	}






















} // namespace clipdiffbrowser



