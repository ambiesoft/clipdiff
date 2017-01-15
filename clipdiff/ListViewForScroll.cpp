#include "StdAfx.h"
#include <Commctrl.h>
#include "ListViewForScroll.h"


namespace clipdiff {
	using namespace System::Windows::Forms;
	
	
	ListViewForScroll::ListViewForScroll(void)
	{

	}

	void ListViewForScroll::WndProc(Message% m) 
	{
		switch(m.Msg)
		{
			case WM_VSCROLL:
			{
				//WORD pos = HIWORD(m.WParam.ToInt32());
				//WORD scv = LOWORD(m.WParam.ToInt32());

				//DTRACE("pos =" + pos);
				//DTRACE("scv =" + scv);

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
				::SendMessage((HWND)other_->Handle.ToPointer(),
					WM_APP_LISTVIEWSCROLLPOSCHANGED,
					0,0);
				return;
			}
			break;

			case WM_MOUSEWHEEL:
			{
				ListView::WndProc(m);
				::SendMessage((HWND)other_->Handle.ToPointer(),
					WM_APP_LISTVIEWSCROLLPOSCHANGED,
					0,0);
				return;
			}
			break;

			case WM_APP_LISTVIEWSCROLLPOSCHANGED:
			{
				if(other_->IsDisposed)
					break;

				ListViewItem^ top = other_->TopItem;
				if(!top)
					break;

				int index = other_->Items->IndexOf(top);
				if(index < 0)
					break;

				this->TopItem = this->Items[index];
			}
			break;
		}


		ListView::WndProc(m);

	}
}