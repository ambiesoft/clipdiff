#include "stdafx.h"
#include "Options.h"


namespace clipdiff {
	using namespace Ambiesoft;
	void Options::ChangeColorCommon(System::Object^ sender, System::EventArgs^ e)
	{
		Button^ button = (Button^)sender;
		ColorDialog dlg;
		dlg.Color = button->BackColor;
		CenterWinDialog center(this);
		if (System::Windows::Forms::DialogResult::OK != dlg.ShowDialog())
			return;

		button->BackColor = dlg.Color;
	}
	System::Void Options::btnColorNoChange_Click(System::Object^  sender, System::EventArgs^  e)
	{
		ChangeColorCommon(sender, e);
	}
	System::Void Options::btnColorAdd_Click(System::Object^  sender, System::EventArgs^  e)
	{
		ChangeColorCommon(sender, e);
	}
	System::Void Options::btnColorDelete_Click(System::Object^  sender, System::EventArgs^  e)
	{
		ChangeColorCommon(sender, e);
	}
	System::Void Options::btnColorReplace_Click(System::Object^  sender, System::EventArgs^  e)
	{
		ChangeColorCommon(sender, e);
	}

}