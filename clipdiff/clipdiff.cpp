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

// clipdiff.cpp : main project file.

#include "stdafx.h"

#include "../../lsMisc/cppclr/clrHelper.h"
#include "../../lsMisc/CommandLineParser.h"
#include "../../lsMisc/HighDPI.h"

#include "FormMain.h"
#include "StringResource.h"


using namespace System::IO;
using namespace System::Windows::Forms;
using namespace System::Text;

using std::wstring;

using namespace clipdiff;
using namespace Ambiesoft;

ref class Program
{
	static bool checkPathState()
	{
		try
		{
			Object^ o = Microsoft::Win32::Registry::GetValue(
				L"HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\FileSystem",
				L"NtfsDisable8dot3NameCreation",
				nullptr);
			int oi = (int)o;
			if (1 != oi)
				return true; // ok, shortpath is enabled


			String^ dir = Path::GetDirectoryName(Application::ExecutablePath);
			array<unsigned char>^ bytes = Encoding::Default->GetBytes(dir);
			String^ dirback = Encoding::Default->GetString(bytes);

			if (dir == dirback)
				return true;  // ok, path is legit.

			String^ message = I18N(L"You system has 8dot3pathname feature disabled and this executable is placed on a path that name can not be converted to active code page characters. You need replace this executable to a directory where its pathname does not include non active codepage characters, or enable 8do3pathname feature.");
			Alert(message);
			return false;
		}
		catch (Exception^ ex)
		{
			StringBuilder sb;
			sb.AppendLine(I18N(L"Unexpected exception, could not continue."));
			sb.AppendLine();
			sb.AppendLine(ex->Message);

			Alert(sb.ToString());
			return false;
		}
	}
	
	static String^ getHelp()
	{
		StringBuilder sb;
		sb.AppendLine(L"clipdiff.exe [/culture CULTURE]");
		sb.AppendLine();
		sb.AppendLine("  CULTURE: Culture string like \"ja-JP\".");
		return sb.ToString();
	}
	static bool processCommandLine()
	{
		CCommandLineParser parser;
		wstring culture;
		bool help = false;
		parser.AddOption(L"/culture", 1, &culture);
		parser.AddOption(L"/h", L"/?", 0, &help);
		parser.AddOption(L"/help", 0, &help);

		parser.Parse();

		if (help)
		{
			CppUtils::Alert(getHelp());
			Environment::Exit(0);
		}
		if (!culture.empty())
		{
			if (!ResourceLoader::setLang(gcnew String(culture.c_str())))
			{
				CppUtils::Alert(String::Format(L"\"{0}\" is not recognized as lang", gcnew String(culture.c_str())));
				Environment::Exit(1);
			}
		}
		return true;
	}

	[STAThreadAttribute]
	static int main(array<System::String ^> ^args)
	{
		Ambiesoft::InitHighDPISupport();

		if (!checkPathState())
			return 1;

		if(!processCommandLine())
			return 1;

		// Enabling Windows XP visual effects before any controls are created
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);

		// Create the main window and run it
		Application::Run(gcnew FormMain());
		return 0;
	}
};