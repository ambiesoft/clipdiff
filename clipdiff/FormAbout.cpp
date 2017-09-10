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

using namespace System::Text;
using namespace Ambiesoft;

namespace clipdiff {

	System::Void FormAbout::OnLoad(System::Object^  sender, System::EventArgs^  e)
	{
		System::Text::StringBuilder msg;

		msg.Append(Application::ProductName + L" version ");
		msg.AppendLine(System::Reflection::Assembly::GetExecutingAssembly()->GetName()->Version->ToString());

		try
		{
			String^ out, ^err;
			OpenCommnadGetResult(Ruby::RubyExe,
				L"-v",
				Encoding::UTF8,
				out,
				err);

			msg.Append(L"> ");
			msg.Append(doubleQuote(Ruby::RubyExe));
			msg.Append(L" -v");
			msg.AppendLine();

			msg.AppendLine(out);
			msg.AppendLine(L"> ");

			msg.Append(L"> ");
			msg.Append(doubleQuote(Ruby::RubyExe));
			msg.Append(L" --copyright");
			msg.AppendLine();


			OpenCommnadGetResult(Ruby::RubyExe,
				L"--copyright",
				Encoding::UTF8,
				out,
				err);
			msg.AppendLine(out);
			msg.AppendLine(L"> ");

		}
		catch (Exception^ex)
		{
			msg.AppendLine(ex->Message);
		}

		rtMain->Text = msg.ToString();
	}

}