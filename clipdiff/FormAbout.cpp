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

#include "stdafx.h"
#include "FormAbout.h"

#include "../Common/Ruby.h"
#include "../../lsMisc/cppclr/clrHelper.h"
#include "../../lsMisc/cppclr/clrString.h"

#include "../Common/defines.h"

// run 'prepareBuild.bat'
#include "gitrev.h"

using namespace System::Text;
using namespace System::IO;
using namespace System::Windows::Forms;

using namespace Ambiesoft;

namespace clipdiff {

	String^ FormAbout::Run(RunWhich r, String^ commandline)
	{
		StringBuilder msg;
		msg.Append(L"> ");
		if (r==RunWhich::RunRuby)
			msg.Append(doubleQuote(Ruby::RubyExe));
		else
			msg.Append(doubleQuote(Ruby::DocDiffrb));
		msg.Append(L" ");
		msg.Append(commandline);
		msg.AppendLine();

		String^ out, ^err;
		if (r==RunWhich::RunRuby)
			Ruby::RunRuby(commandline, out, err);
		else
			Ruby::RunDocDiff(commandline, out, err);

		msg.AppendLine(out);
		msg.AppendLine(L"> ");

		return msg.ToString();
	}
	System::Void FormAbout::OnLoad(System::Object^  sender, System::EventArgs^  e)
	{
		System::Text::StringBuilder msg;

		msg.Append(Application::ProductName + L" version " + AmbLib::getAssemblyVersion(System::Reflection::Assembly::GetExecutingAssembly(),3));
		//
		//msg.Append(System::Reflection::Assembly::GetExecutingAssembly()->GetName()->Version->Major);
		//msg.Append(L".");
		//msg.Append(System::Reflection::Assembly::GetExecutingAssembly()->GetName()->Version->Minor);
		msg.AppendLine();

		msg.AppendLine(L"copyright Ambiesoft");
		msg.AppendLine();
		
		msg.AppendLine(L"gitrev:");
		msg.AppendLine(gcnew String(GITREV::GetHashMessage().c_str()));
		txtClipdiffVersion->Text = msg.ToString();

		try
		{
			msg.Clear();


			msg.Append(Run(RunWhich::RunRuby, L"-v"));
			msg.Append(Run(RunWhich::RunRuby, L"--copyright"));



			



			msg.Append(Run(RunWhich::RunDocDiff, L"--version"));
			msg.Append(Run(RunWhich::RunDocDiff, L"--license"));
			msg.Append(Run(RunWhich::RunDocDiff, L"--author"));






		}
		catch (Exception^ex)
		{
			msg.AppendLine(ex->Message);
		}

		rtMain->Text = msg.ToString();
	}

	System::Void FormAbout::llDiffEngine_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e)
	{
		try
		{
			System::Diagnostics::Process::Start(llDiffEngine->Text);
		}
		catch (Exception^ ex)
		{
			Alert(ex);
		}
	}

}