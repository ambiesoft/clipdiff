#pragma once

namespace clipdiff {
	using namespace System::Windows::Forms;
	ref class ListViewForScroll : System::Windows::Forms::ListView
	{
	public:
		ListViewForScroll();
		ListViewForScroll^ other_;

	protected:
		virtual void WndProc(Message% m) override = Control::WndProc;
	};

}