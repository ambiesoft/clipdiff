// clipdiff.cpp : main project file.

#include "stdafx.h"
#include "FormMain.h"
#include "difflist.h"

namespace clipdiff {

	void FormMain::addColumn()
	{
		ListView^ lv = (gcnew System::Windows::Forms::ListView());
		
		ColumnHeader^ chLine = (gcnew System::Windows::Forms::ColumnHeader());
		chLine->Text = L"Line";
		
		ColumnHeader^ chText = (gcnew System::Windows::Forms::ColumnHeader());
		chText->Text = L"Text";
		chText->Width = 213;

		lv->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  > {chLine, chText});
		lv->Dock = System::Windows::Forms::DockStyle::Fill;
		lv->Location = System::Drawing::Point(0, 0);
		lv->Name = L"lv";
		lv->Size = System::Drawing::Size(138, 255);
		lv->TabIndex = 0;
		lv->UseCompatibleStateImageBehavior = false;
		lv->View = System::Windows::Forms::View::Details;

		// flowLayoutPanel1->Controls->Add(lv);
		tlpMain->ColumnCount++;
		tlpMain->Controls->Add(lv, tlpMain->ColumnCount-1, 0);
		tlpMain->ColumnStyles->Clear();
		for(int i=0 ; i < tlpMain->ColumnCount; ++i)
			tlpMain->ColumnStyles->Add((gcnew ColumnStyle(SizeType::Percent, 100.0F/tlpMain->ColumnCount)));

		// this->tableLayoutPanel1->RowStyles->Clear();

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
		df1_ = gcnew DiffList(String::Empty);
		df2_ = gcnew DiffList(String::Empty);
		ClipboardViewerNext_ = SetClipboardViewer((HWND)this->Handle.ToPointer());
	}

	System::Void FormMain::renderDiff()
	{
		double time = 0;
		
		ArrayList^ rep;
		try
		{
			time = de_->ProcessDiff(df1_, df2_, DifferenceEngine::DiffEngineLevel::Medium);
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
						lviS->SubItems->Add(((TextLine^)df1_->GetByIndex(drs->SourceIndex + i))->Line_);
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
						lviS->SubItems->Add(((TextLine^)df1_->GetByIndex(drs->SourceIndex+i))->Line_);
						lviD->BackColor = Color::White;
						lviD->SubItems->Add(((TextLine^)df2_->GetByIndex(drs->DestIndex+i))->Line_);

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
						lviD->SubItems->Add(((TextLine^)df2_->GetByIndex(drs->DestIndex+i))->Line_);

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
						lviS->SubItems->Add(((TextLine^)df1_->GetByIndex(drs->SourceIndex+i))->Line_);
						lviD->BackColor = Color::LightGreen;
						lviD->SubItems->Add(((TextLine^)df2_->GetByIndex(drs->DestIndex+i))->Line_);

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


	void FormMain::WndProc(Message% m) 
	{
		switch( m.Msg )
		{
			case WM_DRAWCLIPBOARD:
			{
				try
				{
					String^ text;
					if ( Clipboard::ContainsText())
					{
						text = Clipboard::GetText();
					}

					if(String::IsNullOrEmpty(text))
						break;
			
					//if(text==lastText_)
					//	break;
					
					df2_ = df1_;  // gcnew DiffList(lastText_);
					df1_ = gcnew DiffList(text);
					lastText_ = text;
					renderDiff();
				}
				catch(System::Exception^){ }
				finally
				{
					if ( ClipboardViewerNext_ )
					{
						::SendMessageA(ClipboardViewerNext_, m.Msg, 
							(WPARAM)m.WParam.ToPointer(), (LPARAM)m.LParam.ToPointer());
					}
				}
			}
			break;

			case WM_CHANGECBCHAIN:
			{
				if ( (HWND)m.WParam.ToPointer() == ClipboardViewerNext_ )
				{
					ClipboardViewerNext_ = (HWND)m.LParam.ToPointer();
				}
				else if (ClipboardViewerNext_)
				{
					::SendMessageA(ClipboardViewerNext_, m.Msg,
						(WPARAM)m.WParam.ToPointer(), (LPARAM)m.LParam.ToPointer());
				}
			}
			break;

		default:
			Form::WndProc(m);
		}
	}

}

