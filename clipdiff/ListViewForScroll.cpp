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

#include "StdAfx.h"

#include "ListViewForScroll.h"
#include "DiffList.h"
#include "LVInfo.h"

namespace clipdiff {
	using namespace System::Windows::Forms;


	ListViewForScroll::ListViewForScroll(void)
	{

	}

	int getTopIndex(ListViewForScroll^ list)
	{
		ListViewItem^ top = list->TopItem;
		if(!top)
			return -1;

		return list->Items->IndexOf(top);
	}

	bool working_;
	void ListViewForScroll::WndProc(Message% m) 
	{
		switch(m.Msg)
		{
		case WM_VSCROLL:
			{
				if(working_)
				{
					DTRACE("WM_VSCROLL cancelled");
					break;
				}

				WORD pos = HIWORD(m.WParam.ToInt32());
				WORD scv = LOWORD(m.WParam.ToInt32());

				//DTRACE("pos =" + pos);
				DTRACE("scv =" + scv);

				//if(scv==SB_THUMBTRACK)
				//	break;

				//ListView_Scroll((HWND)other_->Handle.ToPointer(), 0, pos);

				//int currentOther = GetScrollPos(
				//	(HWND)other_->Handle.ToPointer(),
				//	SB_VERT);

				//ListView_Scroll((HWND)other_->Handle.ToPointer(), 0, pos-currentOther);
				////SetScrollPos((HWND)other_->Handle.ToPointer(),
				////	SB_VERT,
				////	pos,
				////	TRUE);


				ListView::WndProc(m);
				for each(ListViewForScroll^ lvOther in others_)
				{
					::PostMessage((HWND)lvOther->Handle.ToPointer(),
						WM_APP_LISTVIEWSCROLLPOSCHANGED,
						0,
						getTopIndex(this));
				}
				return;
			}
			break;

		case WM_MOUSEWHEEL:
			{
				ListView::WndProc(m);
				for each(ListViewForScroll^ lvOther in others_)
				{
					::PostMessage((HWND)lvOther->Handle.ToPointer(),
						WM_APP_LISTVIEWSCROLLPOSCHANGED,
						0,
						getTopIndex(this));
				}
				return;
			}
			break;

		case WM_APP_LISTVIEWSCROLLPOSCHANGED:
			{
				if(m.WParam.ToInt32() > 10)
					break;

				if(IsDisposed)
					break;

				int index = m.LParam.ToInt32();
				if(index < 0)
					break;

				if( index >= this->Items->Count)
					break;

				working_=true;
				this->TopItem = this->Items[index];
				working_=false;

				if(index != getTopIndex(this))
				{
					::PostMessage((HWND)this->Handle.ToPointer(),
						WM_APP_LISTVIEWSCROLLPOSCHANGED,
						m.WParam.ToInt32()+1,
						m.LParam.ToInt32());
				}

				// Application::DoEvents();
			}
			break;
		}


		ListView::WndProc(m);

	}

	DiffList^ ListViewForScroll::GetDiff()
	{
		return ((LVInfo^)this->Tag)->Diff;
	}
	void ListViewForScroll::SetDiff(DiffList^ dl)
	{
		((LVInfo^)this->Tag)->Diff=dl;
	}

}