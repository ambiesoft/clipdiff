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

#include "../../lsMisc/cppclr/clrHelper.h"

#include "FormMain.h"
#include "difflist.h"
#include "ListViewForScroll.h"
//#include "LVInfo.h"

using namespace Ambiesoft;

namespace clipdiff {


	Panel^ FormMain::GetPanel(int i)
	{
		return (Panel^)tlpMain->Controls[i];
	}
	ToolStripItem^ FormMain::GetSS(int i)
	{
		return ((StatusStrip^)GetPanel(i)->Controls->Find(L"ListStatus", false)[0])->Items[0];
	}
	ListViewForScroll^ FormMain::GetList(int i)
	{
		return (ListViewForScroll^)GetPanel(i)->Tag;
	}
	void FormMain::renderAllDiff()
	{
		for (int i = tlpMain->Controls->Count - 1; i >= 0; --i)
		{
			ListViewForScroll^ lv = GetList(i);
			ListViewForScroll^ prevlv;
			if (i != 0)
			{
				prevlv = GetList(i - 1);

				renderDiff(
					prevlv,
					lv);
			}
		}

		int maxwidth = 0;
		for (int i = 0; i < tlpMain->Controls->Count; ++i)
		{
			ListViewForScroll^ lv = GetList(i);
			lv->AutoResizeColumns(ColumnHeaderAutoResizeStyle::ColumnContent);

			maxwidth = Math::Max(maxwidth, lv->Columns["chText"]->Width);

			lv->AutoResizeColumns(ColumnHeaderAutoResizeStyle::None);
		}
		for (int i = 0; i < tlpMain->Controls->Count; ++i)
		{
			ListViewForScroll^ lv = GetList(i);
			lv->Columns["chText"]->Width = maxwidth;
		}
	}
	void FormMain::pasteClipboard(bool showError)
	{
		String^ text;
		if ( Clipboard::ContainsText())
		{
			text = Clipboard::GetText();
		}

		if(String::IsNullOrEmpty(text))
		{
			if(showError)
			{
				Alert(I18N(L"No texts on the clipboard."));
			}
			return;
		}

		if(IsIgnoreSame && text==lastText_)
		{
			if(showError)
				Alert(I18N(L"It is same content, ignored."));
			return;
		}

		// right to left
		for(int i=tlpMain->Controls->Count-1; i>=0 ; --i)
		{
			// Update Statusbar (it's on top) of listview
			ToolStripItem^ ss = GetSS(i);
			ListViewForScroll^ lv = GetList(i);

			ListViewForScroll^ prevlv;
			if(i != 0)
			{
				// 0 => 1 (1 = 0)
				ToolStripItem^ prevss = GetSS(i - 1);
				prevlv = GetList(i - 1);

				if(i==1 && IsKeepLeft)
				{
					ss->Text="aaabbb";
					lv->SetDiff(gcnew DiffList(text));
				}
				else
				{
					ss->Text = prevss->Text;
					lv->SetDiff(prevlv->GetDiff());
				}
			}
			else
			{
				if(!IsKeepLeft)
				{
					ss->Text=DateTime::Now.ToLongTimeString() + " " + DateTime::Now.ToShortDateString();
					lv->SetDiff(gcnew DiffList(text));
				}
			}
		}


		//df2_ = df1_;  // gcnew DiffList(lastText_);
		//df1_ = gcnew DiffList(text);
		lastText_ = text;
		renderAllDiff();
		

		

		if (Engine == EngineKind::DocDiff)
		{
			RunDocDiff();
		}
	}
	void FormMain::pasteClipboard()
	{
		pasteClipboard(false);
	}

	void FormMain::WndProc(Message% m) 
	{
		switch( m.Msg )
		{
		case WM_DRAWCLIPBOARD:
			{
				DASSERT(IsMonitor);
				if(!IsMonitor)
					break;

				try
				{
					if(Clipboard::ContainsData("clipdiff"))
						break;

					pasteClipboard();
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

