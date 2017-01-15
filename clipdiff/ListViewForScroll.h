#pragma once

namespace clipdiff {
	
	using namespace System::Windows::Forms;

	ref class DiffList;

	ref class ListViewForScroll : System::Windows::Forms::ListView
	{
	public:
		ListViewForScroll();
		System::Collections::Generic::List<ListViewForScroll^> others_;

		DiffList^ GetDiff();
		void SetDiff(DiffList^ dl);
	protected:
		virtual void WndProc(Message% m) override = Control::WndProc;
	};

}