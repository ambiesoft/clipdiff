// clipdiff.cpp : main project file.

#include "stdafx.h"
#include "FormMain.h"
#include "difflist.h"
#include "ListViewForScroll.h"
#include "LVInfo.h"

namespace clipdiff {


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

					if(ignoreWhenClipboardTextsAreSameToolStripMenuItem->Checked &&
						text==lastText_)
					{
						break;
					}

					
					for(int i=tlpMain->Controls->Count-1; i>=0 ; --i)
					{
						ListViewForScroll^ lv = (ListViewForScroll^)tlpMain->Controls[i];
						ListViewForScroll^ prevlv;
						if(i != 0)
						{
							prevlv=(ListViewForScroll^)tlpMain->Controls[i-1];

							if(i==1 && keepToolStripMenuItem->Checked)
								lv->SetDiff(gcnew DiffList(text));
							else
								lv->SetDiff(prevlv->GetDiff());
						}
						else
						{
							if(!keepToolStripMenuItem->Checked)
								lv->SetDiff(gcnew DiffList(text));
						}
					}

						
					//df2_ = df1_;  // gcnew DiffList(lastText_);
					//df1_ = gcnew DiffList(text);
					lastText_ = text;

					for(int i=tlpMain->Controls->Count-1; i>=0 ; --i)
					{
						ListViewForScroll^ lv = (ListViewForScroll^)tlpMain->Controls[i];
						ListViewForScroll^ prevlv;
						if(i != 0)
						{
							prevlv=(ListViewForScroll^)tlpMain->Controls[i-1];

							renderDiff(
								prevlv,
								lv);
						}
					}

					int maxwidth;
					for(int i=0 ; i < tlpMain->Controls->Count; ++i)
					{
						ListViewForScroll^ lv = (ListViewForScroll^)tlpMain->Controls[i];
						lv->AutoResizeColumns(ColumnHeaderAutoResizeStyle::ColumnContent);

						maxwidth = Math::Max(maxwidth, lv->Columns["chText"]->Width);

						lv->AutoResizeColumns(ColumnHeaderAutoResizeStyle::None);


					}
					for(int i=0 ; i < tlpMain->Controls->Count; ++i)
					{
						ListViewForScroll^ lv = (ListViewForScroll^)tlpMain->Controls[i];
						lv->Columns["chText"]->Width = maxwidth;
					}

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

