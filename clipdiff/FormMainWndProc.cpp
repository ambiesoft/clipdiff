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
	ToolStripItem^ FormMain::GetDateStrip(int i)
	{
		return ((StatusStrip^)GetPanel(i)->Controls->Find(L"ListStatus", false)[0])->Items[0];
	}
	ToolStripItem^ FormMain::GetNewOldStrip(int i)
	{
		return ((StatusStrip^)GetPanel(i)->Controls->Find(L"ListStatus", false)[0])->Items[1];
	}
	ListViewForScroll^ FormMain::GetList(int i)
	{
		return (ListViewForScroll^)GetPanel(i)->Tag;
	}
	void FormMain::renderAllDiff(RENDERDIFF_COLUMN renderColumn)
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

		if (renderColumn == RENDERDIFF_COLUMN::COLUMN_ADJUST)
		{
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
	}
	void FormMain::renderAllDiff()
	{
		renderAllDiff(RENDERDIFF_COLUMN::COLUMN_ADJUST);
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
				CppUtils::Alert(I18N(L"No texts on the clipboard."));
			}
			return;
		}

		if(IsIgnoreSame && text==lastText_)
		{
			if(showError)
				CppUtils::Alert(I18N(L"It is same content, ignored."));
			return;
		}

		// right to left
		for (int i = tlpMain->Controls->Count - 1; i >= 0; --i)
		{
			// Update Statusbar (it's on top) of listview
			ToolStripItem^ dateStrip = GetDateStrip(i);
			ToolStripItem^ newoldStrip = GetNewOldStrip(i);
			ListViewForScroll^ lv = GetList(i);

			ListViewForScroll^ prevlv;
			if (i != 0)
			{
				// 0 => 1 (1 = 0)
				ToolStripItem^ prevDateStrip = GetDateStrip(i - 1);
				ToolStripItem^ prevNewoldStrip = GetNewOldStrip(i - 1);

				prevlv = GetList(i - 1);

				if (i == 1 && IsKeepLeft)
				{
					dateStrip->Text = DateTime::Now.ToLongTimeString() + " " + DateTime::Now.ToShortDateString();
					newoldStrip->Text = I18N(L"New");
					prevNewoldStrip->Text = I18N(L"Old");

					lv->SetDiff(gcnew DiffList(text));
				}
				else
				{
					if (!String::IsNullOrEmpty(prevDateStrip->Text))
					{
						dateStrip->Text = prevDateStrip->Text;
						newoldStrip->Text = I18N(L"Old");
					}
					lv->SetDiff(prevlv->GetDiff());
				}
			}
			else
			{
				if (!IsKeepLeft)
				{
					dateStrip->Text = DateTime::Now.ToLongTimeString() + " " + DateTime::Now.ToShortDateString();
					newoldStrip->Text = I18N(L"New");

					lv->SetDiff(gcnew DiffList(text));
				}
			}
		}

		lastText_ = text;
		renderAllDiff();

		if (Engine == EngineKind::DocDiff)
		{
			RunDocDiff();
		}

		SetTransientStatusText(I18N(L"Pasted from clipboard"));
	}
	void FormMain::pasteClipboard()
	{
		pasteClipboard(false);
	}
	System::Void FormMain::tsmClear_Click(System::Object^ sender, System::EventArgs^ e)
	{
		for (int i = 0; i < tlpMain->Controls->Count; ++i)
		{
			ToolStripItem^ dateStrip = GetDateStrip(i);
			dateStrip->Text = String::Empty;

			ToolStripItem^ newoldStrip = GetNewOldStrip(i);
			newoldStrip->Text = String::Empty;

			ListViewForScroll^ lv = GetList(i);
			lv->SetDiff(gcnew DiffList(String::Empty));
		}

		lastText_ = String::Empty;
		renderAllDiff(RENDERDIFF_COLUMN::COLUMN_NONE);

		if (Engine == EngineKind::DocDiff)
		{
			RunDocDiff();
		}

		SetTransientStatusText(I18N(L"Cleared"));
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
					if(Clipboard::ContainsData(clipboardFormat_))
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
		
		case WM_DPICHANGED:
		{
			DTRACE(L"WM_DPICHANGED in SubWindow");

			const UINT newDpi = LOWORD((void*)m.WParam);
			{
				CLRHelper::FormLocker fl(this);
				CLRHelper::LayoutSuspender ls(this);

				RECT* pRect = (RECT*)(void*)m.LParam;
				//this->Location = System::Drawing::Point(pRect->left, pRect->top);
				//this->Size = System::Drawing::Size(pRect->right - pRect->left, pRect->bottom - pRect->top);
				SetWindowPos((HWND)this->Handle.ToPointer(),
					nullptr,
					pRect->left, pRect->top,
					pRect->right - pRect->left, pRect->bottom - pRect->top,
					SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE);

				ChangeUIForDpi(newDpi);
				ResetToobarImageSizes();
			}
		}
		break;
		default:
			Form::WndProc(m);
		}
	}

}

