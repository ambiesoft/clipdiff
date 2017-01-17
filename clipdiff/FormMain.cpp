// clipdiff.cpp : main project file.

#include "stdafx.h"
#include "FormMain.h"
#include "difflist.h"
#include "ListViewForScroll.h"
#include "LVInfo.h"

namespace clipdiff {

		
	using namespace Ambiesoft;

	FormMain::FormMain(void)
	{
		InitializeComponent();

		addColumn();
		addColumn();

		HashIni^ ini =  Profile::ReadAll(Ambiesoft::AmbLib::GetIniPath());
		bool posReadFailed=false;
		int x,y,width,height;
		posReadFailed |= !Profile::GetInt(APP_OPTION, L"X", -10000, x, ini);
		posReadFailed |= !Profile::GetInt(APP_OPTION, L"Y", -10000, y, ini);

		posReadFailed |= !Profile::GetInt(APP_OPTION, L"Width", -10000, width, ini);
		posReadFailed |= !Profile::GetInt(APP_OPTION, L"Height", -10000, height, ini);
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
		lv->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
		lv->HideSelection = false;
		lv->Location = System::Drawing::Point(0, 0);
		lv->Name = L"lv" + index;
		lv->Size = System::Drawing::Size(138, 255);
		lv->TabIndex = index;
		lv->UseCompatibleStateImageBehavior = false;
		lv->View = System::Windows::Forms::View::Details;
		lv->Tag = gcnew LVInfo();

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
			ListViewForScroll^ other = (ListViewForScroll^)control;
			lv->others_.Add(other);

			other->others_.Add(lv);
		}
		tlpMain->ColumnCount++;
		tlpMain->Controls->Add(lv, tlpMain->ColumnCount-1, 0);
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

		tlpMain->ColumnCount--;
		// tlpMain->Controls->R Add(lv, tlpMain->ColumnCount-1, 0);
		tlpMain->ColumnStyles->Clear();
		for(int i=0 ; i < tlpMain->ColumnCount; ++i)
			tlpMain->ColumnStyles->Add((gcnew ColumnStyle(SizeType::Percent, 100.0F/tlpMain->ColumnCount)));
	}

	System::Void FormMain::FormMain_Load(System::Object^  sender, System::EventArgs^  e)
	{
		de_ = gcnew DifferenceEngine::DiffEngine();
		ClipboardViewerNext_ = SetClipboardViewer((HWND)this->Handle.ToPointer());
	}

	LVInfo^ getListInfo(ListView^ lv)
	{
		return (LVInfo^)lv->Tag;
	}
	System::Void FormMain::renderDiff(ListView^ lv1, ListView^ lv2)
	{
		double time = 0;

		ArrayList^ rep;
		try
		{
			DiffList^ df1 = getListInfo(lv1)->Diff;
			DiffList^ df2 = getListInfo(lv2)->Diff;
			time = de_->ProcessDiff(
				df1,
				df2,
				DifferenceEngine::DiffEngineLevel::Medium);

			rep = de_->DiffReport();

			this->Text = String::Format(L"Results: {0} secs.",time.ToString("#0.00"));

			lv1->Items->Clear();
			lv2->Items->Clear();

			ListViewItem^ lviS;
			ListViewItem^ lviD;
			int cnt = 1;
			int i;

			for each( DifferenceEngine::DiffResultSpan^ drs in rep)
			{				

				switch (drs->Status)
				{
				case DifferenceEngine::DiffResultSpanStatus::DeleteSource:
					for (i = 0; i < drs->Length; i++)
					{
						lviS = gcnew ListViewItem(cnt.ToString(L"00000"));
						lviD = gcnew ListViewItem(cnt.ToString(L"00000"));
						lviS->BackColor = Color::Red;
						lviS->SubItems->Add(((TextLine^)df1->GetByIndex(drs->SourceIndex + i))->Line_);
						lviD->BackColor = Color::LightGray;
						lviD->SubItems->Add("");

						lv1->Items->Add(lviS);
						lv2->Items->Add(lviD);
						cnt++;
					}
					break;

				case DifferenceEngine::DiffResultSpanStatus::NoChange:
					for (i = 0; i < drs->Length; i++)
					{
						lviS = gcnew ListViewItem(cnt.ToString("00000"));
						lviD = gcnew ListViewItem(cnt.ToString("00000"));
						lviS->BackColor = Color::White;
						lviS->SubItems->Add(((TextLine^)df1->GetByIndex(drs->SourceIndex+i))->Line_);
						lviD->BackColor = Color::White;
						lviD->SubItems->Add(((TextLine^)df2->GetByIndex(drs->DestIndex+i))->Line_);

						lv1->Items->Add(lviS);
						lv2->Items->Add(lviD);
						cnt++;
					}
					break;

				case DifferenceEngine::DiffResultSpanStatus::AddDestination:
					for (i = 0; i < drs->Length; i++)
					{
						lviS = gcnew ListViewItem(cnt.ToString("00000"));
						lviD = gcnew ListViewItem(cnt.ToString("00000"));
						lviS->BackColor = Color::LightGray;
						lviS->SubItems->Add("");
						lviD->BackColor = Color::LightGreen;
						lviD->SubItems->Add(((TextLine^)df2->GetByIndex(drs->DestIndex+i))->Line_);

						lv1->Items->Add(lviS);
						lv2->Items->Add(lviD);
						cnt++;
					}
					break;

				case DifferenceEngine::DiffResultSpanStatus::Replace:
					for (i = 0; i < drs->Length; i++)
					{
						lviS = gcnew ListViewItem(cnt.ToString("00000"));
						lviD = gcnew ListViewItem(cnt.ToString("00000"));
						lviS->BackColor = Color::Red;
						lviS->SubItems->Add(((TextLine^)df1->GetByIndex(drs->SourceIndex+i))->Line_);
						lviD->BackColor = Color::LightGreen;
						lviD->SubItems->Add(((TextLine^)df2->GetByIndex(drs->DestIndex+i))->Line_);

						lv1->Items->Add(lviS);
						lv2->Items->Add(lviD);
						cnt++;
					}
					break;
				}

			}
		}
		catch(System::Exception^ ex)
		{
			MessageBox::Show(ex->Message,
				Application::ProductName,
				MessageBoxButtons::OK,
				MessageBoxIcon::Error);
			return;
		}

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


	System::Void FormMain::alwaysOnTopToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		bool newvalue = !alwaysOnTopToolStripMenuItem->Checked;
		alwaysOnTopToolStripMenuItem->Checked = newvalue;

		this->TopMost = newvalue;
	}

	System::Void FormMain::windowToolStripMenuItem_DropDownOpening(System::Object^  sender, System::EventArgs^  e)
	{
		alwaysOnTopToolStripMenuItem->Checked = this->TopMost;
	}



	System::Void FormMain::FormMain_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
	{
		String^ inipath = AmbLib::GetIniPath();
		HashIni^ ini =  Profile::ReadAll(inipath);
		Profile::WriteInt(APP_OPTION, L"X", this->Location.X, ini);
		Profile::WriteInt(APP_OPTION, L"Y", this->Location.Y, ini);

		Profile::WriteInt(APP_OPTION, L"Width", this->Size.Width , ini);
		Profile::WriteInt(APP_OPTION, L"Height", this->Size.Height, ini);

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
		bool newval = !keepToolStripMenuItem->Checked;

		keepToolStripMenuItem->Checked = newval;
		toolStripButton1->Checked = newval;
	}
}

