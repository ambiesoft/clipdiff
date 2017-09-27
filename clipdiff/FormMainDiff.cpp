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
#include "FormMain.h"
#include "difflist.h"
#include "ListViewForScroll.h"
#include "LVInfo.h"

namespace clipdiff {


	using namespace Ambiesoft;



	struct WindowLocker
	{
		HWND h_;
		bool enable_;
		WindowLocker(HWND h, bool enable = true) {
			enable_ = enable;
			if (!enable)
				return;

			h_ = h;
			DASSERT(::IsWindow(h));
			//			DVERIFY(::LockWindowUpdate(h));
			SendMessageA(h, WM_SETREDRAW, FALSE, 0);
		}
		~WindowLocker() {
			if (!enable_)
				return;
			//			::LockWindowUpdate(NULL);
			SendMessageA(h_, WM_SETREDRAW, TRUE, 0);
		}
	};

	ref struct ListViewPaintLocker
	{
		ListView^ lv_;
		ListViewPaintLocker(ListView^ lv)
		{
			lv_ = lv;
			lv->BeginUpdate();
		}
		~ListViewPaintLocker()
		{
			lv_->EndUpdate();
			lv_ = nullptr;
		}
	};
	LVInfo^ getListInfo(ListView^ lv)
	{
		return (LVInfo^)lv->Tag;
	}

	String^ getDiffIndex(int i,int index)
	{
		if(i < 0)
			return L" ";  // workaround to avoid scroll error

		return (i+index+1).ToString("00000");
	}


	System::Void FormMain::renderDiff(ListView^ lvOld, ListView^ lvNew)
	{
		//WindowLocker((HWND)lvOld->Handle.ToPointer());
		//WindowLocker((HWND)lvNew->Handle.ToPointer());
		ListViewPaintLocker lvLock1(lvOld);
		ListViewPaintLocker lvLock2(lvOld);
		double time = 0;

		ArrayList^ rep;
		try
		{
			DiffList^ dfDest = getListInfo(lvNew)->Diff;
			DiffList^ dfSource = getListInfo(lvOld)->Diff;
			time = de_->ProcessDiff(
				dfDest,
				dfSource,
				EngineLevel); // DifferenceEngine::DiffEngineLevel::Medium);

			rep = de_->DiffReport();

			stlResult->Text = String::Format(L"{0} secs.",time.ToString("#0.00"));

			LVDiffData^ ddNew = getListInfo(lvNew)->Data;
			LVDiffData^ ddOld = getListInfo(lvOld)->Data;

			lvNew->VirtualListSize = 0;
			lvOld->VirtualListSize = 0;
			ddNew->Clear();
			ddOld->Clear();

			//lvNew->Items->Clear();
			//lvOld->Items->Clear();

			ListViewItem^ lviDest;
			ListViewItem^ lviSource;
			int cnt = 1;
			int i;

			int addCount=0;
			int deleteCount=0;
			int replaceCount=0;
			int nochangeCount=0;
			for each( DifferenceEngine::DiffResultSpan^ drs in rep)
			{				
				switch (drs->Status)
				{
				case DifferenceEngine::DiffResultSpanStatus::DeleteSource:
					for (i = 0; i < drs->Length; i++)
					{
						//lviDest = gcnew ListViewItem(cnt.ToString(L"00000"));
						//lviSource = gcnew ListViewItem(cnt.ToString(L"00000"));
						lviSource = gcnew ListViewItem(getDiffIndex(drs->DestIndex,i));
						lviDest = gcnew ListViewItem(getDiffIndex(drs->SourceIndex,i));

						lviDest->BackColor = defaultLVDeleteBackColor_;
						lviDest->SubItems->Add(((TextLine^)dfDest->GetByIndex(drs->SourceIndex + i))->Line_);
						lviSource->BackColor = defaultLVNoChangeBackColor_;
						lviSource->SubItems->Add("");

						//lvNew->Items->Add(lviDest);
						//lvOld->Items->Add(lviSource);
						ddNew->Add(lviDest);
						ddOld->Add(lviSource);

						cnt++;
						deleteCount++;
					}
					break;

				case DifferenceEngine::DiffResultSpanStatus::NoChange:
					for (i = 0; i < drs->Length; i++)
					{
						//lviDest = gcnew ListViewItem(cnt.ToString("00000"));
						//lviSource = gcnew ListViewItem(cnt.ToString("00000"));
						lviSource = gcnew ListViewItem(getDiffIndex(drs->DestIndex,i));
						lviDest = gcnew ListViewItem(getDiffIndex(drs->SourceIndex,i));
						lviDest->BackColor = defaultLVNoChangeBackColor_;
						lviDest->SubItems->Add(((TextLine^)dfDest->GetByIndex(drs->SourceIndex+i))->Line_);
						lviSource->BackColor = defaultLVNoChangeBackColor_;
						lviSource->SubItems->Add(((TextLine^)dfSource->GetByIndex(drs->DestIndex+i))->Line_);

						//lvNew->Items->Add(lviDest);
						//lvOld->Items->Add(lviSource);
						ddNew->Add(lviDest);
						ddOld->Add(lviSource);

						cnt++;
						nochangeCount++;
					}
					break;

				case DifferenceEngine::DiffResultSpanStatus::AddDestination:
					for (i = 0; i < drs->Length; i++)
					{
						//lviDest = gcnew ListViewItem(cnt.ToString("00000"));
						//lviSource = gcnew ListViewItem(cnt.ToString("00000"));
						lviSource = gcnew ListViewItem(getDiffIndex(drs->DestIndex,i));
						lviDest = gcnew ListViewItem(getDiffIndex(drs->SourceIndex,i));

						lviDest->BackColor = defaultLVNoChangeBackColor_;
						lviDest->SubItems->Add("");
						lviSource->BackColor = defaultLVAddBackColor_;
						lviSource->SubItems->Add(((TextLine^)dfSource->GetByIndex(drs->DestIndex+i))->Line_);

						//lvNew->Items->Add(lviDest);
						//lvOld->Items->Add(lviSource);
						ddNew->Add(lviDest);
						ddOld->Add(lviSource);

						cnt++;
						addCount++;
					}
					break;

				case DifferenceEngine::DiffResultSpanStatus::Replace:
					for (i = 0; i < drs->Length; i++)
					{
						//lviDest = gcnew ListViewItem(cnt.ToString("00000"));
						//lviSource = gcnew ListViewItem(cnt.ToString("00000"));
						lviSource = gcnew ListViewItem(getDiffIndex(drs->DestIndex,i));
						lviDest = gcnew ListViewItem(getDiffIndex(drs->SourceIndex,i));

						lviDest->BackColor = defaultLVReplaceBackColor_;
						lviDest->SubItems->Add(((TextLine^)dfDest->GetByIndex(drs->SourceIndex+i))->Line_);
						lviSource->BackColor = defaultLVReplaceBackColor_;
						lviSource->SubItems->Add(((TextLine^)dfSource->GetByIndex(drs->DestIndex+i))->Line_);

						//lvNew->Items->Add(lviDest);
						//lvOld->Items->Add(lviSource);
						ddNew->Add(lviDest);
						ddOld->Add(lviSource);
						cnt++;
						replaceCount++;
					}
					break;
				}
			}

			lvNew->VirtualListSize = ddNew->Count;
			if (ddNew->Count != 0)
				lvNew->EnsureVisible(0);

			lvOld->VirtualListSize = ddOld->Count;
			if (ddOld->Count != 0)
				lvOld->EnsureVisible(0);

			updateTitle(addCount, replaceCount, deleteCount, nochangeCount);
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

	System::Void FormMain::onRetrieveItem(System::Object^ sender, System::Windows::Forms::RetrieveVirtualItemEventArgs^ e)
	{
		LVDiffData^ data = getListInfo((ListView^)sender)->Data;
		e->Item = data->getAt(e->ItemIndex);
	}


}

