
//BSD 2-Clause License
//
//Copyright (c) 2017, Ambiesoft
//All rights reserved.
//
//Redistribution and use in source and binary forms, with or without
//modification, are permitted provided that the following conditions are met:
//
//* Redistributions of source code must retain the above copyright notice, this
//  list of conditions and the following disclaimer.
//
//* Redistributions in binary form must reproduce the above copyright notice,
//  this list of conditions and the following disclaimer in the documentation
//  and/or other materials provided with the distribution.
//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
//FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
//CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
//OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "stdafx.h"
#include "FormMain.h"
#include "../Common/Ruby.h"

#include "Options.h"


namespace clipdiff {
	using namespace Ambiesoft;
	void Options::ChangeColorCommon(System::Object^ sender, System::EventArgs^ e)
	{
		Button^ button = (Button^)sender;
		ColorDialog dlg;
		dlg.Color = button->BackColor;
		CenteringDialog center(this);
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

	System::Void Options::btnBrowseRuby_Click(System::Object^  sender, System::EventArgs^  e)
	{
		OpenFileDialog ofd;
		ofd.FileName = txtRubyPath->Text;
		ofd.Filter = I18N(L"Executable") + L" (*.exe, *.com)|*.exe;*.com|" + I18N(L"All Files") + L" (*.*)|*.*";
		if (System::Windows::Forms::DialogResult::OK != ofd.ShowDialog())
			return;

		txtRubyPath->Text = ofd.FileName;
	}
	System::Void Options::btnRubyDefault_Click(System::Object^  sender, System::EventArgs^  e)
	{
		txtRubyPath->Text = Ruby::DefaultRubyPath;
	}

}