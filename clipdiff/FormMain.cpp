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
#include "../../lsMisc/GetChildWindowBy.h"

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
		lv->MultiSelect = false;
		lv->Location = System::Drawing::Point(0, 0);
		lv->Name = L"lv" + index;
		lv->Size = System::Drawing::Size(138, 255);
		lv->TabIndex = index;
		lv->UseCompatibleStateImageBehavior = false;
		lv->View = System::Windows::Forms::View::Details;
		lv->ContextMenuStrip = ctxMenuList;
		
		lv->VirtualMode = true;
		lv->RetrieveVirtualItem += gcnew RetrieveVirtualItemEventHandler(this, &FormMain::onRetrieveItem);

		lv->Tag = gcnew LVInfo();
	
		lv->DoubleClick += gcnew System::EventHandler(this, &FormMain::lv_doubleClick);
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
		{
			ToolStripStatusLabel^ sslabelDate = gcnew ToolStripStatusLabel();
			sslabelDate->Spring = true;
			sslabelDate->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;

			ss->Items->Add(sslabelDate);
		}
		{
			ToolStripStatusLabel^ sslabelNewOld = gcnew ToolStripStatusLabel();
			sslabelNewOld->TextAlign = System::Drawing::ContentAlignment::MiddleRight;

			ss->Items->Add(sslabelNewOld);
		}
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
		return childHwnd_ = GetChildWindowByText(parentHwnd, L"clipdiffbrowser");
	}
	System::Void FormMain::spRoot_Panel2_Resize(System::Object^  sender, System::EventArgs^  e)
	{
		HWND h = GetChildMainFormWindow();
		if (!h)
			return;
		
		SendNotifyMessage(h, WM_APP_RESIZE, 0, 0);
	}

	System::Void FormMain::tsmDonate_Click(System::Object^  sender, System::EventArgs^  e)
	{
		try
		{
			System::Diagnostics::Process::Start(L"http://ambiesoft.mooo.com/donate/");
		}
		catch (Exception^ex)
		{
			Alert(ex);
		}

	}

	System::Void FormMain::TsmFind_Click(System::Object^ sender, System::EventArgs^ e)
	{
		cmbFind->Focus();
	}
	System::Void FormMain::CmbFind_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
	{
		if (e->KeyCode == Keys::Enter)
			findNext(cmbFind->Text);
	}
	System::Void FormMain::TsbFindUp_Click(System::Object^ sender, System::EventArgs^ e)
	{
		findPrev(cmbFind->Text);
	}
	System::Void FormMain::TsbFindDown_Click(System::Object^ sender, System::EventArgs^ e)
	{
		findNext(cmbFind->Text);
	}
	bool hasItemText(ListViewItem^ item, String^ text)
	{
		if (item->Text->IndexOf(text) >= 0)
			return true;

		for (int i = 0; i < item->SubItems->Count; ++i)
		{
			if (item->SubItems[i]->Text->IndexOf(text) >= 0)
				return true;
		}
		return false;
	}

	List<ListViewForScroll^>^ FormMain::GetAllLV(bool bReverse)
	{
		List<ListViewForScroll^>^ allLVs = gcnew List<ListViewForScroll^>();
		for (int i = 0; i < tlpMain->Controls->Count; ++i)
		{
			allLVs->Add(GetList(i));
		}
		
		if (bReverse)
			allLVs->Reverse();
		
		return allLVs;
	}

	void FormMain::findPrev(String^ findWord)
	{
		findCommon(false, findWord);
	}
	void FormMain::findNext(String^ findWord)
	{
		findCommon(true, findWord);
	}
	int FormMain::GetLVIndex(ListViewForScroll^ lv)
	{
		for (int i = 0; i < tlpMain->Controls->Count; ++i)
		{
			if (lv == GetList(i))
				return i;
		}
		return -1;
	}
	void FormMain::findCommon(bool bNext, String^ findWord)
	{
		// Create table arrya in which the focused table gets first
		List<ListViewForScroll^>^ allLVs = GetAllLV(!bNext);

		int focusIndex = -1;
		for (int i = 0; i < allLVs->Count; ++i)
		{
			ListViewForScroll^ lv = allLVs[i];
			if (lv->Focused)
			{
				focusIndex = i;
				break;
			}
		}
		
		if (focusIndex >= 0)
		{
			// Table has focus
			List<ListViewForScroll^> toAppends;
			List<ListViewForScroll^>^ allLVtmp = GetAllLV(!bNext);
			for (int i = 0; i < allLVtmp->Count; ++i)
			{
				ListViewForScroll^ lv = allLVtmp[i];
				DTRACE("LVIndex=" + GetLVIndex(lv));
				if (i >= focusIndex)
					break;
				
				allLVs->Remove(lv);
				toAppends.Add(lv);
			}

			allLVs->AddRange(toAppends.ToArray());
		}

#ifdef _DEBUG
		String^ message = "";
		for each(ListViewForScroll^ lv in allLVs)
		{
			message += GetLVIndex(lv);
			message += ":";
		}
		DTRACE("Find Order=" + message);
#endif

		bool first = true;
		for each(ListViewForScroll^ lv in allLVs)
		{
			DTRACE("LVIndex=" + GetLVIndex(lv));
			int startIndex = !bNext ? lv->Items->Count - 1 : 0;
			if (lv->SelectedIndices->Count == 0)
			{
				if (first)
					continue;
			}
			else
			{
				if (first)
					startIndex = lv->SelectedIndices[0] + (!bNext ? -1 : 1);
			}

			List<int> indexOrder;
			if (!bNext)
			{ 
				for (int i = startIndex; i >= 0; --i)
				{
					indexOrder.Add(i);
				}
			}
			else
			{
				for (int i = startIndex; i < lv->Items->Count; ++i)
				{
					indexOrder.Add(i);
				}
			}

			for each(int i in indexOrder)
			{
				if (hasItemText(lv->Items[i],findWord))
				{
					// found
					//lv->Items[i]->Selected = true;
					//lv->Items[i]->Focused = true;
					//lv->Items[i]->EnsureVisible();
					SelectItemAndAync(lv, lv->Items[i]);
					lv->Focus();
					return;
				}
			}
			first = false;
		}

		// not found, start from beginning
		for each(ListViewForScroll^ lv in GetAllLV(!bNext))
		{
			List<int> indexOrder;
			if (!bNext)
			{
				for (int i = lv->Items->Count -1 ; i >= 0; --i)
				{
					indexOrder.Add(i);
				}
			}
			else
			{
				for (int i = 0; i < lv->Items->Count; ++i)
				{
					indexOrder.Add(i);
				}
			}

			for each(int i in indexOrder)
			{
				if (hasItemText(lv->Items[i], findWord))
				{
					// found
					//lv->Items[i]->Selected = true;
					//lv->Items[i]->Focused = true;
					//lv->Items[i]->EnsureVisible();
					SelectItemAndAync(lv, lv->Items[i]);
					lv->Focus();
					return;
				}
			}
		}

		// not found at all
		MessageBeep(MB_ICONINFORMATION);
	}

}

