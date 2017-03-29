// clipdiff.cpp : main project file.

#include "stdafx.h"
#include "FormMain.h"
#include "difflist.h"
#include "ListViewForScroll.h"
#include "LVInfo.h"

namespace clipdiff {


	using namespace Ambiesoft;

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


	System::Void FormMain::renderDiff(ListView^ lvSource, ListView^ lvDest)
	{
		double time = 0;

		ArrayList^ rep;
		try
		{
			DiffList^ dfDest = getListInfo(lvDest)->Diff;
			DiffList^ dfSource = getListInfo(lvSource)->Diff;
			time = de_->ProcessDiff(
				dfDest,
				dfSource,
				EngineLevel); // DifferenceEngine::DiffEngineLevel::Medium);

			rep = de_->DiffReport();

			stlResult->Text = String::Format(L"{0} secs.",time.ToString("#0.00"));

			lvDest->Items->Clear();
			lvSource->Items->Clear();

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

						lviDest->BackColor = Color::Red;
						lviDest->SubItems->Add(((TextLine^)dfDest->GetByIndex(drs->SourceIndex + i))->Line_);
						lviSource->BackColor = Color::White;
						lviSource->SubItems->Add("");

						lvDest->Items->Add(lviDest);
						lvSource->Items->Add(lviSource);
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
						lviDest->BackColor = Color::White;
						lviDest->SubItems->Add(((TextLine^)dfDest->GetByIndex(drs->SourceIndex+i))->Line_);
						lviSource->BackColor = Color::White;
						lviSource->SubItems->Add(((TextLine^)dfSource->GetByIndex(drs->DestIndex+i))->Line_);

						lvDest->Items->Add(lviDest);
						lvSource->Items->Add(lviSource);
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

						lviDest->BackColor = Color::White;
						lviDest->SubItems->Add("");
						lviSource->BackColor = Color::Aqua;
						lviSource->SubItems->Add(((TextLine^)dfSource->GetByIndex(drs->DestIndex+i))->Line_);

						lvDest->Items->Add(lviDest);
						lvSource->Items->Add(lviSource);
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

						lviDest->BackColor = Color::Yellow;
						lviDest->SubItems->Add(((TextLine^)dfDest->GetByIndex(drs->SourceIndex+i))->Line_);
						lviSource->BackColor = Color::Yellow;
						lviSource->SubItems->Add(((TextLine^)dfSource->GetByIndex(drs->DestIndex+i))->Line_);

						lvDest->Items->Add(lviDest);
						lvSource->Items->Add(lviSource);
						cnt++;
						replaceCount++;
					}
					break;
				}
			}

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


}

