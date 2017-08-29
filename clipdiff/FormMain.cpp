// clipdiff.cpp : main project file.

#include "stdafx.h"
#include <vcclr.h>
#include "FormMain.h"
#include "difflist.h"
#include "ListViewForScroll.h"
#include "LVInfo.h"

#include "../../MyUtility/browseFolder.h"

namespace clipdiff {


	using namespace Ambiesoft;
	using namespace System::Text;
	using namespace System::Collections::Generic;

	FormMain::FormMain(void)
	{
		InitializeComponent();

		int intval;
		bool boolval;

		InitialIni_ =  Profile::ReadAll(Ambiesoft::AmbLib::GetIniPath());
		try 
		{
			String^ fontstring;
			Profile::GetString(APP_OPTION, L"Font", L"", fontstring, InitialIni_);

			if(!String::IsNullOrEmpty(fontstring))
			{
				System::ComponentModel::TypeConverter^ converter =
					System::ComponentModel::TypeDescriptor::GetConverter( System::Drawing::Font::typeid );

				FontLV = dynamic_cast<System::Drawing::Font^>(converter->ConvertFromString(fontstring));
			}
		}
		catch(Exception^ ex) 
		{
			MessageBox::Show(ex->Message,
				Application::ProductName);
		}


		Profile::GetBool(APP_OPTION, L"ShowToolbar", true, boolval, InitialIni_);
		toolMain->Visible=boolval;

		Profile::GetBool(APP_OPTION, L"ShowStatusbar", true, boolval, InitialIni_);
		stMain->Visible=boolval;

		Profile::GetBool(APP_OPTION, L"ShowListheader", true, boolval, InitialIni_);
		IsHeaderVisible=boolval;



		Profile::GetInt(APP_OPTION, L"EngineLevel", 1, intval, InitialIni_);
		EngineLevel = (DifferenceEngine::DiffEngineLevel)intval;




		addColumn();
		addColumn();


		bool posReadFailed=false;
		int x,y,width,height;
		posReadFailed |= !Profile::GetInt(APP_OPTION, L"X", -10000, x, InitialIni_);
		posReadFailed |= !Profile::GetInt(APP_OPTION, L"Y", -10000, y, InitialIni_);

		posReadFailed |= !Profile::GetInt(APP_OPTION, L"Width", -10000, width, InitialIni_);
		posReadFailed |= !Profile::GetInt(APP_OPTION, L"Height", -10000, height, InitialIni_);
		if(!posReadFailed)
		{
			if(AmbLib::IsPointInMonitor(x,y))
			{
				this->StartPosition = FormStartPosition::Manual;
				this->Location = System::Drawing::Point(x,y);
				this->Size = System::Drawing::Size(width, Height);
			}
		}


	}

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

	void FormMain::addColumn()
	{
		int index = !tlpMain ? 1 : tlpMain->ColumnCount+1;

		ListViewForScroll^ lv = gcnew ListViewForScroll();

		ColumnHeader^ chLine = (gcnew System::Windows::Forms::ColumnHeader());
		chLine->Text = L"Line";
		chLine->Name = L"chLine";

		ColumnHeader^ chText = (gcnew System::Windows::Forms::ColumnHeader());
		chText->Text = L"Text";
		chText->Name = L"chText";
		chText->Width = 213;

		lv->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  > {chLine, chText});
		lv->Dock = System::Windows::Forms::DockStyle::Fill;
		lv->FullRowSelect = true;
		lv->HeaderStyle = IsHeaderVisible ? ColumnHeaderStyle::Nonclickable : ColumnHeaderStyle::None;
		lv->HideSelection = false;
		lv->Location = System::Drawing::Point(0, 0);
		lv->Name = L"lv" + index;
		lv->Size = System::Drawing::Size(138, 255);
		lv->TabIndex = index;
		lv->UseCompatibleStateImageBehavior = false;
		lv->View = System::Windows::Forms::View::Details;
		lv->Tag = gcnew LVInfo();
		if(FontLV)
		{
			lv->Font=FontLV;
		}
		// flowLayoutPanel1->Controls->Add(lv);
		if(!tlpMain)
		{
			tlpMain = gcnew System::Windows::Forms::TableLayoutPanel();
			this->tlpMain->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tlpMain->Location = System::Drawing::Point(0, 24);
			this->tlpMain->Name = L"tlpMain";
			this->tlpMain->RowCount = 1;
			this->tlpMain->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tlpMain->Size = System::Drawing::Size(622, 387);
			this->tlpMain->TabIndex = 3;
			this->tlpMain->SizeChanged += gcnew System::EventHandler(this, &FormMain::tlpMain_SizeChanged);

			this->panelClient->Controls->Add(this->tlpMain);
		}

		for each(Control^ control in tlpMain->Controls)
		{
			Panel^ otherPanel = (Panel^)control;
			ListViewForScroll^ other = (ListViewForScroll^)otherPanel->Tag;
			lv->others_.Add(other);

			other->others_.Add(lv);
		}

		Panel^ listPanel = gcnew Panel();
		listPanel->Tag=lv;
		listPanel->Dock= DockStyle::Fill;
		listPanel->Controls->Add(lv);

		StatusStrip^ ss = gcnew StatusStrip();
		ss->Dock=DockStyle::Top;
		ss->SizingGrip = false;
		ss->Items->Add("AAA");
		ss->TabIndex = 1;
		ss->Name = L"ListStatus";

		listPanel->Controls->Add(ss);


		tlpMain->ColumnCount++;
		tlpMain->Controls->Add(listPanel, tlpMain->ColumnCount-1, 0);
		tlpMain->ColumnStyles->Clear();
		for(int i=0 ; i < tlpMain->ColumnCount; ++i)
		{
			tlpMain->ColumnStyles->Add((gcnew ColumnStyle(SizeType::Percent, 100.0F/tlpMain->ColumnCount)));
		}
	}

	void FormMain::removeColumn()
	{
		if(tlpMain->ColumnCount <= 2)
			return;
		
		tlpMain->Controls->RemoveAt(tlpMain->Controls->Count-1);
		tlpMain->ColumnCount--;
		tlpMain->RowCount=1;
		// tlpMain->Controls->R Add(lv, tlpMain->ColumnCount-1, 0);
		tlpMain->ColumnStyles->Clear();
		for(int i=0 ; i < tlpMain->ColumnCount; ++i)
			tlpMain->ColumnStyles->Add((gcnew ColumnStyle(SizeType::Percent, 100.0F/tlpMain->ColumnCount)));
	}

	void FormMain::updateTitle(int addCount, int replaceCount, int deleteCount, int nochangeCount)
	{
		System::Text::StringBuilder title;
		System::Text::StringBuilder msg;
		if(addCount==0 && replaceCount==0 && deleteCount==0)
		{
			title.Append(L"Identical");
			msg.Append(L"Identical");
		}
		else
		{
			title.Append(addCount);
			title.Append(L" : ");

			msg.Append(L"Add"+L": "+addCount.ToString());
			msg.Append(L" ");



			title.Append(replaceCount);
			title.Append(L" : ");

			msg.Append(L"Replace"+L": "+replaceCount.ToString());
			msg.Append(L" ");



			title.Append(deleteCount);
			title.Append(L" : ");

			msg.Append(L"Delete"+L": "+deleteCount.ToString());
			msg.Append(L" ");



			title.Append(nochangeCount);
			msg.Append(L"Nochange"+L": "+nochangeCount.ToString());
		}

		slChange->Text = msg.ToString();


		title.Append(L" | ");
		title.Append(Application::ProductName);
		Text = title.ToString();

	}

	void FormMain::updateTitle()
	{
		updateTitle(0,0,0,0);
	}

	System::Void FormMain::FormMain_Load(System::Object^  sender, System::EventArgs^  e)
	{
		de_ = gcnew DifferenceEngine::DiffEngine();

		bool boolval;
		Profile::GetBool(APP_OPTION, "MonitorClipboard", false, boolval, InitialIni_);
		IsMonitor = boolval;

		this->Text = Application::ProductName;
	}



	System::Void FormMain::tlpMain_SizeChanged(System::Object^  sender, System::EventArgs^  e)
	{
		//lv1->AutoResizeColumns(ColumnHeaderAutoResizeStyle::ColumnContent);
		//lv2->AutoResizeColumns(ColumnHeaderAutoResizeStyle::ColumnContent);

		//int width = Math::Max(chText1->Width, chText2->Width);

		//lv1->AutoResizeColumns(ColumnHeaderAutoResizeStyle::None);
		//lv2->AutoResizeColumns(ColumnHeaderAutoResizeStyle::None);

		//chText1->Width = width;
		//chText2->Width = width;


		//lv2->Columns["Text"]->Width = width;
		//int hPad = lv1->Padding.Left + lv1->Padding.Right;
		//int i = lv1->Columns->IndexOfKey("Text");
		// lv1->Columns[i];
	}





	System::Void FormMain::FormMain_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
	{
		String^ inipath = AmbLib::GetIniPath();
		HashIni^ ini =  Profile::ReadAll(inipath);
		Profile::WriteInt(APP_OPTION, L"X", this->Location.X, ini);
		Profile::WriteInt(APP_OPTION, L"Y", this->Location.Y, ini);

		Profile::WriteInt(APP_OPTION, L"Width", this->Size.Width , ini);
		Profile::WriteInt(APP_OPTION, L"Height", this->Size.Height, ini);

		String^ fontstring=L"";
		if(FontLV) {
			System::ComponentModel::TypeConverter^ converter =
				System::ComponentModel::TypeDescriptor::GetConverter( System::Drawing::Font::typeid );

			fontstring = converter->ConvertToInvariantString(FontLV);


			// System::Drawing::Font^ font1 = dynamic_cast<System::Drawing::Font^>(converter->ConvertFromString( "Arial, 12pt" ));
		}
		Profile::WriteString(APP_OPTION, L"Font", fontstring, ini);


		Profile::WriteBool(APP_OPTION, L"ShowToolbar", toolMain->Visible, ini);
		Profile::WriteBool(APP_OPTION, L"ShowStatusbar", stMain->Visible, ini);
		Profile::WriteBool(APP_OPTION, L"ShowListheader", IsHeaderVisible, ini);

		Profile::WriteInt(APP_OPTION, L"EngineLevel", (int)EngineLevel, ini);

		Profile::WriteBool(APP_OPTION, "MonitorClipboard", IsMonitor, ini);

		for(;;)
		{
			try
			{
				Profile::WriteAll(ini, inipath,true);
				break;

			}
			catch(Exception^ ex)
			{
				if(System::Windows::Forms::DialogResult::Retry != MessageBox::Show(I18N("Failed to save settings." + "\r\n" + ex->Message),
					Application::ProductName,
					MessageBoxButtons::RetryCancel,
					MessageBoxIcon::Exclamation))
				{
					break;
				}
			}
		}


	}

	void FormMain::onKeep()
	{
		IsKeep = !IsKeep;

		tsmKeep->Checked = IsKeep;
		tsbKeep->Checked = IsKeep;
	}
	void FormMain::onIgnoreSame()
	{
		IsIgnoreSame = !IsIgnoreSame;

		tsmIgnoreSame->Checked=IsIgnoreSame;
		tsbIgnoreSame->Checked=IsIgnoreSame;
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


	System::Void FormMain::FormMain_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
		IsMonitor = false;
	}
	System::Void FormMain::exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		this->Close();
	}
	System::Void FormMain::tsmAddColumn_Click(System::Object^  sender, System::EventArgs^  e) {
		addColumn();
	}
	System::Void FormMain::tsmRemoveColumn_Click(System::Object^  sender, System::EventArgs^  e) {
		removeColumn();
	}


	System::Void FormMain::tsmIgnoreSame_Click(System::Object^  sender, System::EventArgs^  e) {
		onIgnoreSame();
	}
	System::Void FormMain::tsbIgnoreSame_Click(System::Object^  sender, System::EventArgs^  e) {
		onIgnoreSame();
	}

	System::Void FormMain::tsmKeep_Click(System::Object^  sender, System::EventArgs^  e)
	{
		onKeep();
	}
	System::Void FormMain::tsbKeep_Click(System::Object^  sender, System::EventArgs^  e)
	{
		onKeep();
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



	System::Void FormMain::tsmEngineLevel_DropDownOpening(System::Object^  sender, System::EventArgs^  e) 
	{
		tsmELFast->Checked = false;
		tsmELMedium->Checked = false;
		tsmELSlow->Checked = false;

		switch(EngineLevel)
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

	System::Void FormMain::tsmELFast_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		EngineLevel = DifferenceEngine::DiffEngineLevel::FastImperfect;
	}
	System::Void FormMain::tsmELMedium_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		EngineLevel = DifferenceEngine::DiffEngineLevel::Medium;
	}
	System::Void FormMain::tsmELSlow_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		EngineLevel = DifferenceEngine::DiffEngineLevel::SlowPerfect;
	}


	using namespace System::Collections::Generic;
	using namespace System::IO;
	List<StreamWriter^>^ FormMain::GetsaveAsFiles(int filecount, String^ filenamepre, List<String^>^ filenames)
	{
		List<StreamWriter^>^ ret = gcnew List<StreamWriter^>();
		try
		{
			for(int i=0 ; i < filecount; ++i)
			{
				String^ filename = filenamepre + (i+1).ToString() + L".txt";
				if(System::IO::File::Exists(filename))
				{
					return nullptr;
				}

				filenames->Add(filename);
				StreamWriter^ sw = gcnew StreamWriter(filename, false, System::Text::Encoding::UTF8);
				ret->Add(sw);
			}
			return ret;
		}
		catch(System::Exception^)
		{}

		return nullptr;

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

				ListViewForScroll^ list = (ListViewForScroll^)tlpMain->Controls[i];
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
}

