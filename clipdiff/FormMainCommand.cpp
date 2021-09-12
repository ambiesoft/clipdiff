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

// clipdiff.cpp : main project file.

#include "stdafx.h"

#include "../Common/Ruby.h"
#include "FormMain.h"
#include "difflist.h"
#include "ListViewForScroll.h"
//#include "LVInfo.h"

#include "FormAbout.h"
#include "Options.h"

namespace clipdiff {


	
	using namespace System::Text;
	using namespace System::IO;
	using namespace System::Collections::Generic;
	using namespace System::Diagnostics;

	using namespace std;
	using namespace Ambiesoft;
	using namespace Ambiesoft::stdosd;

	System::Void FormMain::tsmAbout_Click(System::Object^  sender, System::EventArgs^  e)
	{
		FormAbout about;
		about.ShowDialog();

		//CenteredMessageBox::Show(this,
		//	msg.ToString(),
		//	Application::ProductName,
		//	MessageBoxButtons::OK,
		//	MessageBoxIcon::Information);
	}

	void FormMain::onKeepLeft()
	{
		IsKeepLeft = !IsKeepLeft;

	}
	bool FormMain::IsKeepLeft::get()
	{
		return isKeep_;
	}
	void FormMain::IsKeepLeft::set(bool value)
	{
		isKeep_=value;
		tsmKeep->Checked = value;
		tsbKeep->Checked = value;
	}

	void FormMain::onIgnoreSame()
	{
		IsIgnoreSame = !IsIgnoreSame;

	}
	bool FormMain::IsIgnoreSame::get()
	{
		return isIgnoreSame_;
	}
	void FormMain::IsIgnoreSame::set(bool value)
	{
		isIgnoreSame_=value;

		tsmIgnoreSame->Checked=value;
		tsbIgnoreSame->Checked=value;
	}


	System::Void FormMain::onTopMost(System::Object^  sender, System::EventArgs^  e)
	{
		bool newvalue = !tsmTopMost->Checked;
		tsmTopMost->Checked = newvalue;
		tsbTopMost->Checked = newvalue;

		this->TopMost = newvalue;
	}

	System::Void FormMain::tsmWindow_DropDownOpening(System::Object^  sender, System::EventArgs^  e)
	{
		tsmTopMost->Checked = this->TopMost;
	}


	System::Void FormMain::exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		this->Close();
	}

	System::Void FormMain::tsmAddColumn_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		addColumn();
	}
	
	System::Void FormMain::tsmRemoveColumn_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		removeColumn();
	}


	System::Void FormMain::tsmIgnoreSame_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		onIgnoreSame();
	}
	System::Void FormMain::tsbIgnoreSame_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		onIgnoreSame();
	}

	System::Void FormMain::tsmKeep_Click(System::Object^  sender, System::EventArgs^  e)
	{
		onKeepLeft();
	}
	System::Void FormMain::tsbKeep_Click(System::Object^  sender, System::EventArgs^  e)
	{
		onKeepLeft();
	}

	System::Void FormMain::tsmFont_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		CenteringDialog cd(this);
		FontDialog dlg;
		dlg.Font=FontLV;
		if(System::Windows::Forms::DialogResult::OK != dlg.ShowDialog())
			return;


		for(int i=0 ; i < tlpMain->Controls->Count; ++i)
		{
			ListViewForScroll^ lv = GetList(i);
			lv->Font = dlg.Font;
		}
		FontLV = dlg.Font;
	}
	System::Void FormMain::OnLVFontChanged(System::Object^ sender, System::EventArgs^ e)
	{
		FontLV = GetList(0)->Font;
	}
	System::Void FormMain::toolMain_VisibleChanged(System::Object^  sender, System::EventArgs^  e)
	{
		tsmShowToolbar->Checked = toolMain->Visible;
	}
	System::Void FormMain::tsmShowToolbar_Click(System::Object^  sender, System::EventArgs^  e)
	{
		toolMain->Visible = !toolMain->Visible;
	}

	System::Void FormMain::stMain_VisibleChanged(System::Object^  sender, System::EventArgs^  e)
	{
		tsmShowStatusbar->Checked = stMain->Visible;
	}
	System::Void FormMain::tsmShowStatusbar_Click(System::Object^  sender, System::EventArgs^  e)
	{
		stMain->Visible = !stMain->Visible;
	}

	System::Void FormMain::tsmView_DropDownOpening(System::Object^  sender, System::EventArgs^  e)
	{
		bool visible = !(GetList(0)->HeaderStyle==ColumnHeaderStyle::None);
		tsmShowListheader->Checked = visible;
	}
	System::Void FormMain::tsmShowListheader_Click(System::Object^  sender, System::EventArgs^  e)
	{
		IsHeaderVisible = !IsHeaderVisible;
		for each(Control^ control in tlpMain->Controls)
		{
			ListViewForScroll^ list = (ListViewForScroll^)control->Tag;
			list->HeaderStyle = IsHeaderVisible ? ColumnHeaderStyle::Nonclickable : ColumnHeaderStyle::None;
		}
	}


	bool FormMain::RunDocDiff()
	{
		ListViewForScroll^ list1 = GetList(0);
		ListViewForScroll^ list2 = GetList(1);

		String^ text1 = list1->GetDiff()->GetText();
		String^ text2 = list2->GetDiff()->GetText();

		return RunDocDiff(text1, text2, DocDiffEngineLevel, false);
	}

	String^ FormMain::GetDocdiffEngineLevelAsString(DocDiffEngineKind dk)
	{
		switch (dk)
		{
		case DocDiffEngineKind::DocDiffChar:
			return L"char";
		case DocDiffEngineKind::DocDiffWord:
			return L"word";
		}
		return L"";
	}
	bool FormMain::RunDocDiff(String^ text1, String^ text2, DocDiffEngineKind dk, bool standalone)
	{
		bool succeeded = false;
		HANDLE hEvent = NULL;
		try
		{
			// first, change sproot to show docdiff
			if (!standalone)
			{
				spRoot->Panel2Collapsed = false;
				spRoot->Panel1Collapsed = true;
			}

			HWND hWndChild = !standalone ? GetChildMainFormWindow() : NULL;
			if ( standalone || ( !hWndChild || WAIT_TIMEOUT != WaitForSingleObject(childProcess_, 0)))
			{
				if (!standalone)
					ClearHandle(childProcess_);

				// no child process found, we are to create it.
				wstring thisdir = stdGetParentDirectory(stdGetModuleFileName());
				wstring app = stdCombinePath(thisdir, L"clipdiffbrowser.exe");

				//String^ file1 = Path::GetTempFileName();
				//String^ file2 = Path::GetTempFileName();

				//{
				//	System::IO::StreamWriter sw1(file1, false, System::Text::Encoding::UTF8);
				//	sw1.WriteLine(L"あああ");
				//	sw1.WriteLine(L"いいい");
				//	sw1.WriteLine(L"ううう");

				//	System::IO::StreamWriter sw2(file2, false, System::Text::Encoding::UTF8);
				//	sw2.WriteLine(L"あああ");
				//	sw2.WriteLine(L"ううう");
				//} // make files close


				pin_ptr<const wchar_t> pText1 = PtrToStringChars(text1);
				pin_ptr<const wchar_t> pText2 = PtrToStringChars(text2);
				CDynamicSessionGlobalMemory sg1("clipdiff-data-1", ((int)wcslen(pText1) + 1)*sizeof(wchar_t));
				CDynamicSessionGlobalMemory sg2("clipdiff-data-2", ((int)wcslen(pText2) + 1)*sizeof(wchar_t));

				sg1.set((const unsigned char*)pText1);
				sg2.set((const unsigned char*)pText2);


				hEvent = CreateEventA(NULL, TRUE, FALSE, "clipdiff-launch-event");


				String^ commandline = String::Format(
					L"-p {0} -w {1} -e {2} {3} {4} {5} -r {6}",
					GetCurrentProcessId(),
					(System::UInt64)this->spRoot->Panel2->Handle.ToPointer(),
					"clipdiff-launch-event",
					gcnew String(sg1.getName().c_str()),
					gcnew String(sg2.getName().c_str()),
					standalone ? L"-s" : L"",
					GetDocdiffEngineLevelAsString(dk)
					);
				if (standalone)
				{
					String^ classname = TEXT("clipdiff-receiver");
					classname += GetCurrentProcessId().ToString();
					commandline += " -c " + classname;
				}

				pin_ptr<const wchar_t> pCommandLine = PtrToStringChars(commandline);

				HANDLE child;
				if (!OpenCommon(
					(HWND)this->Handle.ToPointer(),
					app.c_str(),
					pCommandLine,
					NULL,
					&child))
				{
					return false;
				}

				if (!standalone)
					childProcess_ = child;

					// make sg1 and sg2 accept
				HANDLE waits[] = { child, hEvent };
				WaitForMultipleObjects(_countof(waits), waits, FALSE, INFINITE);
				
				if (standalone)
					CloseHandle(child);
			}
			else
			{
				// child process is active, pass data to it
				ListViewForScroll^ list1 = GetList(0);
				ListViewForScroll^ list2 = GetList(1);
				String^ text1 = list1->GetDiff()->GetText();
				String^ text2 = list2->GetDiff()->GetText();

				pin_ptr<const wchar_t> pText1 = PtrToStringChars(text1);
				pin_ptr<const wchar_t> pText2 = PtrToStringChars(text2);
				CDynamicSessionGlobalMemory sg1("clipdiff-data-1", ((int)wcslen(pText1) + 1)*sizeof(wchar_t));
				CDynamicSessionGlobalMemory sg2("clipdiff-data-2", ((int)wcslen(pText2) + 1)*sizeof(wchar_t));

				sg1.set((const unsigned char*)pText1);
				sg2.set((const unsigned char*)pText2);

				
				String^ resolution = GetDocdiffEngineLevelAsString(dk);
				pin_ptr<const wchar_t> pResolution = PtrToStringChars(resolution);
				CDynamicSessionGlobalMemory sgResolution("clipdiff-data-resolution",
					((int)wcslen(pResolution) + 1)*sizeof(wchar_t));
				sgResolution.set((const unsigned char*)pResolution);
				
				SendMessage(hWndChild, WM_APP_PASTE, 0, 0);
			}
			succeeded = true;
			return true;

		}
		catch (Exception^ ex)
		{
			Alert(ex->Message);
			return false;
		}
		finally
		{
			CloseHandle(hEvent);
			if (!succeeded)
			{
				spRoot->Panel1Collapsed = false;
				spRoot->Panel2Collapsed = true;
			}
		}
	}
	ListViewForScroll^ FormMain::GetFocusedListView(int% index)
	{
		Control^ focusedControl;
		for each (Control ^ control in tlpMain->Controls)
		{
			if (control->ContainsFocus)
			{
				focusedControl = control;
				break;
			}
		}

		if (!focusedControl)
			return nullptr;

		index = tlpMain->Controls->IndexOf(focusedControl);
		return GetList(index);
	}
	ListViewForScroll^ FormMain::GetFocusedListView()
	{
		int dummy;
		return GetFocusedListView(dummy);
	}
	void FormMain::compareSelectedLineWithDocdiff(DocDiffEngineKind dk)
	{
		int index;
		ListViewForScroll^ focusedControl = GetFocusedListView(index);
		if (!focusedControl || index == -1)
			return;

		int targetIndex = -1;
		if (index == 0)
			targetIndex = 1;
		else if (index = 1)
			targetIndex = 0;
		else
			targetIndex = index - 1;

		DASSERT(!(index < 0 || targetIndex < 0));
		if (index < 0 || targetIndex < 0)
			return;

		ListViewForScroll^ lv1 = GetList(index);
		ListViewForScroll^ lv2 = GetList(targetIndex);

		if (lv1->SelectedIndices->Count == 0)
			return;

		StringBuilder sb1;
		StringBuilder sb2;
		for each (int selectedIndex in lv1->SelectedIndices)
		{
			DASSERT(selectedIndex >= 0);
			sb1.AppendLine(lv1->Items[selectedIndex]->SubItems[1]->Text);
			sb2.AppendLine(lv2->Items[selectedIndex]->SubItems[1]->Text);
		}
		RunDocDiff(sb1.ToString(), sb2.ToString(), dk, true);
	}
	System::Void FormMain::tsmCompareThisLineWithDocdiffChar_Click(System::Object^  sender, System::EventArgs^  e)
	{
		compareSelectedLineWithDocdiff(DocDiffEngineKind::DocDiffChar);
	}
	System::Void FormMain::tsmCompareThisLineWithDocdiffword_Click(System::Object^ sender, System::EventArgs^ e)
	{
		compareSelectedLineWithDocdiff(DocDiffEngineKind::DocDiffWord);
	}
	System::Void FormMain::tsmiCopyItem_Click(System::Object^ sender, System::EventArgs^ e)
	{
		ListViewForScroll^ lv = GetFocusedListView();
		if (!lv)
			return;
		
		StringBuilder sb;
		for each (int selectedIndex in lv->SelectedIndices)
		{
			DASSERT(selectedIndex >= 0);
			sb.AppendLine(lv->Items[selectedIndex]->SubItems[1]->Text);
		}
		
		try
		{
			DataObject ob;
			ob.SetData(clipboardFormat_, 1);
			ob.SetData(DataFormats::UnicodeText, sb.ToString());
			Clipboard::SetDataObject(% ob, true);
		}
		catch (Exception^ ex)
		{
			CppUtils::Alert(ex);
		}
	}
	System::Void FormMain::tsmCopy_Click(System::Object^ sender, System::EventArgs^ e)
	{
		tsmiCopyItem->PerformClick();
	}
	System::Void FormMain::lv_doubleClick(System::Object^  sender, System::EventArgs^  e)
	{
		compareSelectedLineWithDocdiff(DocDiffEngineLevel);
	}

	System::Void FormMain::tsmEngineLevel_DropDownOpening(System::Object^  sender, System::EventArgs^  e) 
	{
		tsmELFast->Checked = false;
		tsmELMedium->Checked = false;
		tsmELSlow->Checked = false;

		tsmDocdiffChar->Checked = false;
		tsmDocdiffWord->Checked = false;

		if (Engine == EngineKind::DiffEngine)
		{
			switch (EngineLevel)
			{
			case DifferenceEngine::DiffEngineLevel::FastImperfect:
				tsmELFast->Checked = true;
				break;
			case DifferenceEngine::DiffEngineLevel::Medium:
				tsmELMedium->Checked = true;
				break;
			case DifferenceEngine::DiffEngineLevel::SlowPerfect:
				tsmELSlow->Checked = true;
				break;
			default:
				System::Diagnostics::Debug::Assert(false);
				break;
			}
		}
		else
		{
			DASSERT(Engine == EngineKind::DocDiff);

			tsmDocdiffChar->Checked = false;
			tsmDocdiffWord->Checked = false;

			switch (DocDiffEngineLevel)
			{
			case DocDiffEngineKind::DocDiffChar:
				tsmDocdiffChar->Checked = true;
				break;
			case DocDiffEngineKind::DocDiffWord:
				tsmDocdiffWord->Checked = true;
				break;

			}
		}
	}

	System::Void FormMain::tsmELFast_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		Engine = EngineKind::DiffEngine;
		EngineLevel = DifferenceEngine::DiffEngineLevel::FastImperfect;
	}
	System::Void FormMain::tsmELMedium_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		Engine = EngineKind::DiffEngine;
		EngineLevel = DifferenceEngine::DiffEngineLevel::Medium;
	}
	System::Void FormMain::tsmELSlow_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		Engine = EngineKind::DiffEngine;
		EngineLevel = DifferenceEngine::DiffEngineLevel::SlowPerfect;
	}

	System::Void FormMain::tsmDocdiffWord_Click(System::Object^  sender, System::EventArgs^  e)
	{
		Engine = EngineKind::DocDiff;
		DocDiffEngineLevel = DocDiffEngineKind::DocDiffWord;
	}
	System::Void FormMain::tsmDocdiffChar_Click(System::Object^  sender, System::EventArgs^  e)
	{
		Engine = EngineKind::DocDiff;
		DocDiffEngineLevel = DocDiffEngineKind::DocDiffChar;
	}
	
	System::Void FormMain::tsmSaveAs_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		// String^ path = Environment::GetFolderPath(Environment::SpecialFolder::Desktop);
		String^ rootpath;

		{
			//pin_ptr<const wchar_t> pTitle = PtrToStringChars(Text);
			//TCHAR szFolder[MAX_PATH] = {0};
			if(!browseFolder(this, Text, rootpath))
				return;

			// rootpath = gcnew String(szFolder);

			//FolderBrowserDialog fbd;f
			//CenterWinDialog center(this);
			//if(System::Windows::Forms::DialogResult::OK != fbd.ShowDialog(this))
			//	return;

			//if(!Directory::Exists(fbd.SelectedPath))
			//{
			//	MessageBox::Show(String::Format(I18N(L"{0} does not exists."), fbd.SelectedPath),
			//		Application::ProductName);
			//	return;
			//}

			//rootpath = fbd.SelectedPath;
		}




		String^ filenamepre = rootpath + L"\\" + Application::ProductName + Environment::TickCount.ToString() + L"-";

		List<String^> filenames;
		List<StreamWriter^>^ streams = GetsaveAsFiles(tlpMain->Controls->Count, filenamepre, %filenames);
		if(!streams) 
		{
			MessageBox::Show(L"Could not create file on" + L" " + rootpath,
				Application::ProductName);
			return;
		}

		try
		{
			StringBuilder sbFiles;
			for(int i=0 ; i < tlpMain->Controls->Count; ++i)
			{
				StreamWriter^ sw=streams[i];

				ListViewForScroll^ list = GetList(i);
				String^ text=list->GetDiff()->GetText();
				sw->Write(text);
				sw->Close();

				sbFiles.AppendLine(filenames[i]);
			}

			StringBuilder sb;
			sb.AppendLine(String::Format(I18N(L"Follwing {0} files have been created."), tlpMain->Controls->Count));
			sb.AppendLine();
			sb.Append(%sbFiles);
			CppUtils::CenteredMessageBox(this,
				sb.ToString(),
				Application::ProductName,
				MessageBoxButtons::OK,
				MessageBoxIcon::Information);
		}
		catch(System::Exception^ ex)
		{
			MessageBox::Show(ex->Message,
				Application::ProductName);
		}
	}


	System::Void FormMain::copy_Clicked(System::Object^  sender, System::EventArgs^  e)
	{
		DASSERT_IS_CLASS(sender, ToolStripMenuItem);
		int colIndex = (int)(((ToolStripMenuItem^)sender)->Tag);
		ListViewForScroll^ list = GetList(colIndex);
		String^ text=list->GetDiff()->GetText();

		try
		{
			DataObject ob;
			ob.SetData(clipboardFormat_, 1);
			ob.SetData(DataFormats::UnicodeText, text);
			Clipboard::SetDataObject(%ob, true);
		}
		catch(System::Exception^ ex)
		{
			MessageBox::Show(ex->Message,
				Application::ProductName);
		}
	}

	
	System::Void FormMain::tsmEdit_DropDownOpening(System::Object^  sender, System::EventArgs^  e)
	{
		List<ToolStripItem^> itemToRemove;
		int startIndex = tsmEdit->DropDownItems->IndexOfKey(L"tsmSepCopyTop")+1;
		DASSERT(startIndex >= 1);
		int endIndex = tsmEdit->DropDownItems->Count;

		for(int i=startIndex ; i < endIndex ; ++i)
		{
			itemToRemove.Add(tsmEdit->DropDownItems[i]);
		}

		for each(ToolStripItem^ item in itemToRemove)
			tsmEdit->DropDownItems->Remove(item);

		//while(tsmEdit->DropDownItems[startIndex] != tsmSepCopyTop)
		//	tsmEdit->DropDownItems->RemoveAt(startIndex);

		for(int i=0 ; i < tlpMain->Controls->Count; ++i)
		{
			ToolStripMenuItem^ item = gcnew ToolStripMenuItem();
			item->Text = I18N(String::Format(I18N(L"Copy Column {0}"), i+1));
			item->Click += gcnew EventHandler(this, &FormMain::copy_Clicked);
			item->Tag = i;
			tsmEdit->DropDownItems->Insert(startIndex++, item);

		}
	}

	bool FormMain::IsMonitor::get()
	{
		return isMonitor_;
	}
	void FormMain::IsMonitor::set(bool b)
	{
		if(b==isMonitor_)
			return;

		isMonitor_ = b;
		if(b)
		{
			ClipboardViewerNext_ = SetClipboardViewer((HWND)this->Handle.ToPointer());
		}
		else
		{
			ChangeClipboardChain((HWND)this->Handle.ToPointer(), ClipboardViewerNext_);
			ClipboardViewerNext_ = NULL;
		}
		
		tsmMonitorClipboard->Checked = b;
		tsbMonitorClipboard->Checked = b;
	}
	void FormMain::onMonitor()
	{
		IsMonitor = !IsMonitor;
	}
	System::Void FormMain::tsmMonitorClipboard_Click(System::Object^  sender, System::EventArgs^  e)
	{
		onMonitor();
	}

	System::Void FormMain::tsbMonitorClipboard_Click(System::Object^  sender, System::EventArgs^  e)
	{
		onMonitor();
	}

	System::Void FormMain::tsmPaste_Click(System::Object^  sender, System::EventArgs^  e)
	{
		pasteClipboard();
	}
	System::Void FormMain::tsbPaste_Click(System::Object^  sender, System::EventArgs^  e)
	{
		pasteClipboard();
	}

	System::Void FormMain::tsmGotoWebpage_Click(System::Object^  sender, System::EventArgs^  e)
	{
		try
		{
			Process::Start(L"https://ambiesoft.github.io/webjumper/?target=clipdiff");
		}
		catch (Exception^ex)
		{
			Alert(ex);
		}
	}

	ListViewForScroll^ FormMain::GetSelectedListView()
	{
		for (int i = 0; i < tlpMain->Controls->Count; ++i)
		{
			ListViewForScroll^ lv = (ListViewForScroll^)GetPanel(i)->Tag;
			if (lv->Focused)
				return lv;
		}
		return nullptr;
	}



	void FormMain::GotoDiffLVCommon(bool bNext)
	{
		stlMain->Text = String::Empty;
		ListViewForScroll^ lv = GetSelectedListView();
		if (!lv)
			lv = GetList(0);

		do
		{
			if (currentDiffIndex_ == -2)
			{
				// search end and roll agiain
				if (bNext)
					currentDiffIndex_ = 0;
				else
					currentDiffIndex_ = lv->Items->Count - 1;
			}
			else
			{
				if (lv->SelectedIndices->Count != 0)
				{
					currentDiffIndex_ = lv->SelectedIndices[0];
				}

				if (bNext)
					currentDiffIndex_++;
				else
					currentDiffIndex_--;
			}

			if (bNext)
			{
				if (lv->Items->Count < currentDiffIndex_)
				{
					currentDiffIndex_ = -2;
					break;
				}
			}
			else
			{
				if (currentDiffIndex_ < 0)
				{
					currentDiffIndex_ = -2;
					break;
				}
			}

			if (bNext)
			{
				for (int i = currentDiffIndex_;
					(i < lv->Items->Count);
					++i)
				{
					if (SelectIfFound(lv, i))
						return;
				}
			}
			else
			{
				for (int i = currentDiffIndex_;
					(i >= 0);
					--i)
				{
					if (SelectIfFound(lv, i))
						return;
				}
			}
		} while (false);

		MessageBeep(MB_OK);
		SetTransientStatusText( 
			String::Format(I18N(L"Searching has hit {0}"),
				bNext ? I18N(L"Bottom") : I18N(L"Top")));

		currentDiffIndex_ = -2;
	}
	void FormMain::SetTransientStatusText(String^ clearText)
	{
		Timer^ timerClearStatus = gcnew Timer();
		stlMain->Text = clearText;
		timerClearStatus->Tag = clearText;
		timerClearStatus->Interval = 3000;
		timerClearStatus->Tick += gcnew System::EventHandler(this, &FormMain::timerClearStatus_Tick);
		timerClearStatus->Enabled = true;
	}
	System::Void FormMain::timerClearStatus_Tick(System::Object^ sender, System::EventArgs^ e)
	{
		Timer^ timerClearStatus = (Timer^)sender;
		if (timerClearStatus->Tag && timerClearStatus->Tag->ToString() == stlMain->Text)
			stlMain->Text = String::Empty;
		timerClearStatus->Enabled = false;
		delete timerClearStatus;
	}
	void FormMain::ClearSelections(ListViewForScroll^ lv)
	{
		for each (int item in lv->SelectedIndices)
		{
			lv->Items[item]->Selected = false;
		}
	}
	void FormMain::SelectItemAndAync(ListViewForScroll^ lv, ListViewItem^ item)
	{
		ClearSelections(lv);

		item->Selected = true;
		item->Focused = true;
		item->EnsureVisible();

		for each(ListViewForScroll^ lvOther in lv->others_)
		{
			::PostMessage((HWND)lvOther->Handle.ToPointer(),
				WM_APP_LISTVIEWSCROLLPOSCHANGED,
				0,
				lv->getTopIndex());
		}
	}

	bool FormMain::SelectIfFound(ListViewForScroll^ lv, int i)
	{
		ListViewItem^ item = lv->Items[i];
		if (item->BackColor.ToArgb() != defaultLVNoChangeBackColorRGB_)
		{
			SelectItemAndAync(lv, item);
			return true;
		}

		return false;
	}
	void FormMain::GotoNextDiffLV()
	{
		GotoDiffLVCommon(true);
	}
	void FormMain::GotoNextDiffDocDiff()
	{
		HWND h = GetChildMainFormWindow();
		if (!h)
			return;

		PostMessage(h, WM_APP_GOTONEXTDIFF, 0, 0);
	}
	void FormMain::GotoPrevDiffLV()
	{
		GotoDiffLVCommon(false);
	}
	void FormMain::GotoPrevDiffDocDiff()
	{
		HWND h = GetChildMainFormWindow();
		if (!h)
			return;

		PostMessage(h, WM_APP_GOTOPREVDIFF, 0, 0);
	}

	System::Void FormMain::goToNextDiffLineToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (!GetChildMainFormWindow())
			GotoNextDiffLV();
		else
			GotoNextDiffDocDiff();
	}

	System::Void FormMain::goToPrevDiffLineToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (!GetChildMainFormWindow())
			GotoPrevDiffLV();
		else
			GotoPrevDiffDocDiff();
	}
	
	System::Void FormMain::optionsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		Options dlg;
		dlg.chkShowTooltip->Checked = IsShowToolTip;
		
		dlg.btnColorNoChange->BackColor = defaultLVNoChangeBackColor_;
		dlg.btnColorAdd->BackColor = defaultLVAddBackColor_;
		dlg.btnColorDelete->BackColor = defaultLVDeleteBackColor_;
		dlg.btnColorReplace->BackColor = defaultLVReplaceBackColor_;

		dlg.txtRubyPath->Text = Ruby::RubyExeConfig;
		dlg.chkNoCloseSubWinConfirm->Checked = NoCloseSubWinConfirm;
		
		if (System::Windows::Forms::DialogResult::OK != dlg.ShowDialog())
			return;
		
		NoCloseSubWinConfirm = dlg.chkNoCloseSubWinConfirm->Checked;
		Ruby::RubyExeConfig = dlg.txtRubyPath->Text;

		defaultLVNoChangeBackColor_ = dlg.btnColorNoChange->BackColor;
		defaultLVNoChangeBackColorRGB_ = defaultLVNoChangeBackColor_.ToArgb();
		defaultLVAddBackColor_ = dlg.btnColorAdd->BackColor;
		defaultLVDeleteBackColor_ = dlg.btnColorDelete->BackColor;
		defaultLVReplaceBackColor_ = dlg.btnColorReplace->BackColor;

		IsShowToolTip = dlg.chkShowTooltip->Checked;

		for each (ListViewForScroll^ lv in GetAllLV())
			lv->ShowItemToolTips = IsShowToolTip;

		renderAllDiff();
	}


	wstring getSubwinClassName()
	{
		wstring classname = TEXT("clipdiff-receiver");
		classname += stdToString(GetCurrentProcessId());
		return classname;
	}
	System::Void FormMain::tsmCloseAllSubwindows_Click(System::Object^  sender, System::EventArgs^  e)
	{
		CloseAllSubwindows();
	}
	bool FormMain::HasSubWindows::get()
	{
		wstring cn = getSubwinClassName();
		return FindWindowEx(HWND_MESSAGE, NULL, cn.c_str(), NULL) != NULL;
	}
	void FormMain::CloseAllSubwindows()
	{
		wstring cn = getSubwinClassName();
		for (int i = 0; i < 1024; ++i)
		{
			HWND h = FindWindowEx(HWND_MESSAGE, NULL, cn.c_str(), NULL);
			if (!h)
				return;
			SendMessage(h, WM_APP_CLOSE, 0, 0);
		}
	}

}

