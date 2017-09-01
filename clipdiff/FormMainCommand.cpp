// clipdiff.cpp : main project file.

#include "stdafx.h"

#include "FormMain.h"
#include "difflist.h"
#include "ListViewForScroll.h"
//#include "LVInfo.h"
#include "../../lsMisc/HandleUtility.h"


namespace clipdiff {


	using namespace Ambiesoft;
	using namespace System::Text;
	using namespace System::IO;
	using namespace System::Collections::Generic;

	using namespace stdwin32;
	using namespace std;

	System::Void FormMain::tsmAbout_Click(System::Object^  sender, System::EventArgs^  e)
	{
		System::Text::StringBuilder msg;

		msg.Append(Application::ProductName + L" version:");
		msg.Append(System::Reflection::Assembly::GetExecutingAssembly()->GetName()->Version->ToString());

		CenteredMessageBox::Show(this,
			msg.ToString(),
			Application::ProductName,
			MessageBoxButtons::OK,
			MessageBoxIcon::Information);
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
		FontDialog dlg;
		dlg.Font=FontLV;
		if(System::Windows::Forms::DialogResult::OK != dlg.ShowDialog())
			return;


		for(int i=0 ; i < tlpMain->Controls->Count; ++i)
		{
			ListViewForScroll^ lv = (ListViewForScroll^)tlpMain->Controls[i]->Tag;
			lv->Font = dlg.Font;
		}
		FontLV = dlg.Font;
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
		bool visible = !(((ListViewForScroll^)(tlpMain->Controls[0]->Tag))->HeaderStyle==ColumnHeaderStyle::None);
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

	DifferenceEngine::DiffEngineLevel FormMain::EngineLevel::get()
	{
			return engineLevel_;
	}
	void FormMain::EngineLevel::set(DifferenceEngine::DiffEngineLevel value)
	{
		engineLevel_ = value;
	}

	EngineKind FormMain::Engine::get()
	{
		return engine_;
	}
	void FormMain::Engine::set(EngineKind value)
	{
		if(engine_==value)
			return;
		
		if (value==EngineKind::DiffEngine)
		{
			HWND hChild = GetChildMainFormWindow();
			if (hChild)
			{
				SendNotifyMessage(childHwnd_, WM_CLOSE, 0, 0);
			}
			else if (childProcess_)
			{
				TerminateProcess(childHwnd_, 1);
			}
			ClearHandle(childProcess_);
			
			spRoot->Panel1Collapsed = false;
			spRoot->Panel2Collapsed = true;

			engine_ = value;
		}
		else if(value==EngineKind::DocDiff)
		{
			if (RunDocDiff())
				engine_ = value;
		}  // if(docdiff)
		else
		{
			DASSERT(false);
		}
	}

	bool FormMain::RunDocDiff()
	{
		ListViewForScroll^ list1 = (ListViewForScroll^)tlpMain->Controls[0]->Tag;
		ListViewForScroll^ list2 = (ListViewForScroll^)tlpMain->Controls[1]->Tag;

		String^ text1 = list1->GetDiff()->GetText();
		String^ text2 = list2->GetDiff()->GetText();

		return RunDocDiff(text1, text2, false);
	}
	bool FormMain::RunDocDiff(String^ text1, String^ text2, bool standalone)
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
				CDynamicSessionGlobalMemory sg1("clipdiff-data-1", (wcslen(pText1) + 1)*sizeof(wchar_t));
				CDynamicSessionGlobalMemory sg2("clipdiff-data-2", (wcslen(pText2) + 1)*sizeof(wchar_t));

				sg1.set((const unsigned char*)pText1);
				sg2.set((const unsigned char*)pText2);


				hEvent = CreateEventA(NULL, TRUE, FALSE, "clipdiff-launch-event");

				String^ commandline = String::Format(
					L"-p {0} -w {1} -e {2} {3} {4} {5}",
					GetCurrentProcessId(),
					(System::UInt64)this->spRoot->Panel2->Handle.ToPointer(),
					"clipdiff-launch-event",
					gcnew String(sg1.getName().c_str()),
					gcnew String(sg2.getName().c_str()),
					standalone ? L"-s" : L""
					);

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
				ListViewForScroll^ list1 = (ListViewForScroll^)tlpMain->Controls[0]->Tag;
				ListViewForScroll^ list2 = (ListViewForScroll^)tlpMain->Controls[1]->Tag;
				String^ text1 = list1->GetDiff()->GetText();
				String^ text2 = list2->GetDiff()->GetText();

				pin_ptr<const wchar_t> pText1 = PtrToStringChars(text1);
				pin_ptr<const wchar_t> pText2 = PtrToStringChars(text2);
				CDynamicSessionGlobalMemory sg1("clipdiff-data-1", (wcslen(pText1) + 1)*sizeof(wchar_t));
				CDynamicSessionGlobalMemory sg2("clipdiff-data-2", (wcslen(pText2) + 1)*sizeof(wchar_t));

				sg1.set((const unsigned char*)pText1);
				sg2.set((const unsigned char*)pText2);

				SendMessage(hWndChild, WM_APP_PASTE, 0, 0);
			}
			succeeded = true;
			return true;

		}
		catch (Exception^ ex)
		{
			WarningMessageBox(ex->Message);
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

	System::Void FormMain::lv_doubleClick(System::Object^  sender, System::EventArgs^  e)
	{
		Control^ focusedControl;
		for each(Control^ control in tlpMain->Controls)
		{
			if (control->ContainsFocus)
			{
				focusedControl = control;
				break;
			}
		}

		if (focusedControl == nullptr)
			return;

		int index = tlpMain->Controls->IndexOf(focusedControl);
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

		ListViewForScroll^ lv1 = (ListViewForScroll^)tlpMain->Controls[index]->Tag;
		ListViewForScroll^ lv2 = (ListViewForScroll^)tlpMain->Controls[targetIndex]->Tag;

		int selectedIndex = lv1->SelectedIndices[0];
		DASSERT(selectedIndex >= 0);
		String^ text1 = lv1->Items[selectedIndex]->SubItems[1]->Text;
		String^ text2 = lv2->Items[selectedIndex]->SubItems[1]->Text;

		RunDocDiff(text1, text2, true);
	}

	System::Void FormMain::tsmEngineLevel_DropDownOpening(System::Object^  sender, System::EventArgs^  e) 
	{
		tsmELFast->Checked = false;
		tsmELMedium->Checked = false;
		tsmELSlow->Checked = false;

		tsmDocdiff->Checked = false;

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
			tsmDocdiff->Checked = true;
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

	System::Void FormMain::tsmDocdiff_Click(System::Object^  sender, System::EventArgs^  e)
	{
		Engine=EngineKind::DocDiff;
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

				ListViewForScroll^ list = (ListViewForScroll^)tlpMain->Controls[i]->Tag;
				String^ text=list->GetDiff()->GetText();
				sw->Write(text);
				sw->Close();

				sbFiles.AppendLine(filenames[i]);
			}

			StringBuilder sb;
			sb.AppendLine(String::Format(I18N(L"Follwing {0} files have been created."), tlpMain->Controls->Count));
			sb.AppendLine();
			sb.Append(%sbFiles);
			CenteredMessageBox::Show(this,
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
		ListViewForScroll^ list = (ListViewForScroll^)tlpMain->Controls[colIndex]->Tag;
		String^ text=list->GetDiff()->GetText();

		try
		{
			DataObject ob;
			ob.SetData("clipdiff", 1);
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
			item->Text = I18N(String::Format(L"Copy Column {0}", i+1));
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
}

