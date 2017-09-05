

#include "stdafx.h"
#include "FormMain.h"
#include "helper.h"
#include "Ruby.h"

#include "../../lsMisc/clrString.h"

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

	void FormMain::OnOutputDataReceived(System::Object ^sender, System::Diagnostics::DataReceivedEventArgs ^e)
	{
		sbRubyOut_.Append(e->Data);
	}
	void FormMain::OnErrorDataReceived(System::Object ^sender, System::Diagnostics::DataReceivedEventArgs ^e)
	{
		sbRubyErr_.Append(e->Data);
	}

	void FormMain::Paste(String^ left, String^ right, String^ resolution)
	{
		browser->Navigate(L"about:blank");

		sbRubyOut_.Clear();
		sbRubyErr_.Clear();

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
			Ruby::DocDiffrb,
			GetDocdiffResolutionOptionString(resolution),
			doubleQuote(file2),
			doubleQuote(file1));

		try
		{
			Process process;

			ProcessStartInfo startInfo;
			startInfo.FileName = Ruby::RubyExe;
			startInfo.Arguments = clrCommandLine;

			startInfo.CreateNoWindow = true;
			startInfo.UseShellExecute = false;

			startInfo.StandardOutputEncoding = Encoding::UTF8;
			startInfo.RedirectStandardOutput = true;
			
			startInfo.StandardErrorEncoding = Encoding::UTF8;
			startInfo.RedirectStandardError = true;

			process.OutputDataReceived += gcnew System::Diagnostics::DataReceivedEventHandler(this, &FormMain::OnOutputDataReceived);
			process.ErrorDataReceived += gcnew System::Diagnostics::DataReceivedEventHandler(this, &FormMain::OnErrorDataReceived);

			process.StartInfo = %startInfo;
			process.Start();

			process.BeginOutputReadLine();
			process.BeginErrorReadLine();

			//String^ line;
			//String^ error;
			//if (false)
			//{
			//	bool outDone = false;
			//	bool errDone = false;
			//	do
			//	{
			//		if (!outDone)
			//		{
			//			if (process.StandardOutput->Peek() > -1)
			//			{
			//				line = process.StandardOutput->ReadLine();
			//				if (line)
			//					sb.Append(line);
			//				else
			//					outDone = true;
			//			}
			//			else
			//				outDone = true;
			//		}

			//		if (!errDone)
			//		{
			//			if (process.StandardError->Peek() > -1)
			//			{
			//				error = process.StandardError->ReadLine();
			//				if (error)
			//					sbError.Append(error);
			//				else
			//					errDone = true;
			//			}
			//			else
			//				errDone = true;
			//		}
			//	} while (!outDone || !errDone);
			//}
			//else if (false)
			//{
			//	while (process.StandardOutput->Peek() > -1)
			//	{
			//		line = process.StandardOutput->ReadLine();
			//		if (line)
			//			sb.Append(line);
			//		else
			//			break;
			//	}

			//	while (process.StandardError->Peek() > -1)
			//	{
			//		error = process.StandardError->ReadLine();
			//		if (error)
			//			sbError.Append(error);
			//		else
			//			break;
			//	}
			//}

			process.WaitForExit();


			FileInfo fileinfo1t(file1);
			long long filesize1t = fileinfo1t.Length;
			DateTime filelastwrite1t = fileinfo1t.LastWriteTimeUtc;

			FileInfo fileinfo2t(file2);
			long long filesize2t = fileinfo2t.Length;
			DateTime filelastwrite2t = fileinfo2t.LastWriteTimeUtc;

			if (filesize1==filesize1t && filelastwrite1==filelastwrite1t)
				File::Delete(file1);

			if (filesize2 == filesize2t && filelastwrite2 == filelastwrite2t)
				File::Delete(file2);

			if (sbRubyErr_.Length != 0)
			{
				ErrorMessageBox(I18N(L"DocDiff failed.") + L"\r\n" + sbRubyErr_.ToString());
				this->Close();
				return;
			}

			//String^ resultHtml = sb.ToString();
			//resultHtml = AmbLib::ReplaceFirst(resultHtml, L"<?xml version=\"1.0\" encoding=\"UTF-8\"?>", L"");
			//
			//String^ resultFile = Path::GetTempFileName();
			//{
			//	StreamWriter sw(resultFile, false, Encoding::UTF8);
			//	sw.Write(resultHtml);
			//}

			this->BeginInvoke(gcnew VSDelegate(this, &FormMain::afterPaste), sbRubyOut_.ToString());

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
			String^ title = left_->Length > 32 ? left_->Substring(0, 32) : left_;
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


