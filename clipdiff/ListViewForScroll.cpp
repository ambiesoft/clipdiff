#include "StdAfx.h"
#include <Commctrl.h>
#include "ListViewForScroll.h"


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
				::PostMessage((HWND)other_->Handle.ToPointer(),
					WM_APP_LISTVIEWSCROLLPOSCHANGED,
					0,0);
				return;
			}
			break;

		case WM_MOUSEWHEEL:
			{
				ListView::WndProc(m);
				::PostMessage((HWND)other_->Handle.ToPointer(),
					WM_APP_LISTVIEWSCROLLPOSCHANGED,
					0,0);
				return;
			}
			break;

		case WM_APP_LISTVIEWSCROLLPOSCHANGED:
			{
				if(m.WParam.ToInt32() > 10)
					break;


				if(other_->IsDisposed)
					break;

				int index = getTopIndex(other_);
				if(index < 0)
					break;

				working_=true;
				this->TopItem = this->Items[index];
				working_=false;

				if(index != getTopIndex(this))
				{
					::PostMessage((HWND)this->Handle.ToPointer(),
					WM_APP_LISTVIEWSCROLLPOSCHANGED,
					m.WParam.ToInt32()+1,
					0);
				}

				// Application::DoEvents();
			}
			break;
		}


		ListView::WndProc(m);

	}
}