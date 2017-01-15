#include "StdAfx.h"
#include <Commctrl.h>
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