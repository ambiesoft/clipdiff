// clipdiff.cpp : main project file.

#include "stdafx.h"
#include "../../MyUtility/GetChildWindowBy.h"

#include "FormMain.h"
//#include "difflist.h"
#include "ListViewForScroll.h"
#include "LVInfo.h"
#include "../Common/defines.h"


namespace clipdiff {


	using namespace Ambiesoft;
	using namespace System::Text;
	using namespace System::IO;
	using namespace System::Collections::Generic;

	

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

	bool FormMain::IsIdling::get()
	{
		return isIdling_;
	}
	void FormMain::IsIdling::set(bool value)
	{
		isIdling_ = value;
		if(value)
			Application::Idle += gcnew EventHandler(this, &FormMain::onIdle);
		else
			Application::Idle -= gcnew EventHandler(this, &FormMain::onIdle);
	}
	void FormMain::onIdle(Object^ sender, EventArgs^ e)
	{
		tsbTopMost->Checked = this->TopMost;
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



	HWND FormMain::GetChildMainFormWindow()
	{
		if (WAIT_TIMEOUT != WaitForSingleObject(childProcess_,0))
			return NULL;

		if (::IsWindow(childHwnd_))
		{
			DWORD dwProcessIDChild;
			GetWindowThreadProcessId(childHwnd_, &dwProcessIDChild);

			if (dwProcessIDChild == GetProcessId(childProcess_))
			{
				return childHwnd_;
			}
		}

		HWND parentHwnd = (HWND)spRoot->Panel2->Handle.ToPointer();
		return childHwnd_ = GetChildWindowByName(parentHwnd, L"clipdiffbrowser");
	}
	System::Void FormMain::spRoot_Panel2_Resize(System::Object^  sender, System::EventArgs^  e)
	{
		HWND h = GetChildMainFormWindow();
		if (!h)
			return;
		
		SendNotifyMessage(h, WM_APP_RESIZE, 0, 0);
	}

}

