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