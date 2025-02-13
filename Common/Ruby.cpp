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

#include "../../lsMisc/cppclr/clrString.h"
#include "../../lsMisc/cppclr/clrHelper.h"

#include "Common.h"
#include "Ruby.h"


namespace Ambiesoft {

	using namespace System;
	using namespace System::Text;
	using namespace System::IO;
	using namespace System::Windows::Forms;

	using std::wstring;
	using namespace Ambiesoft::stdosd;

	void Ruby::init()
	{
		if (initialized_)
			return;
		initialized_ = true;

		if (false)
		{
			wstring thisdir = stdGetParentDirectory(stdGetModuleFileName());
			wstring rubyexe = stdCombinePath(thisdir, L"docdiff\\ruby1.8\\bin\\ruby.exe");
			wstring rubylibdir = stdCombinePath(thisdir, L"docdiff\\docdiff-0.3.3");
			wstring docdiffrb = stdCombinePath(thisdir, L"docdiff\\docdiff-0.3.3\\docdiff.rb");
			// wstring t = stdGetEnvironmentVariable(L"RUBYLIB");

			rubyexe_ = CppUtils::GetShortFileName(gcnew String(rubyexe.c_str()));
			docdiffrb_ = CppUtils::GetShortFileName(gcnew String(docdiffrb.c_str()));
			docdifflibdir_ = CppUtils::GetShortFileName(gcnew String(rubylibdir.c_str()));
		}
		else
		{
			wstring thisdir = stdGetParentDirectory(stdGetModuleFileName());
			
			String^ rubyexe = Path::Combine(gcnew String(thisdir.c_str()),
				DefaultRubyPath);
			String^ savedPath = RubyExeConfig;
			if (!String::IsNullOrEmpty(savedPath))
				rubyexe_ = savedPath;
			else
				rubyexe_ = CppUtils::GetShortFileName(rubyexe);

			wstring rubylibdir = stdCombinePath(thisdir, L"docdiff\\docdiff-0.5.0\\lib");
			wstring docdiffrb = stdCombinePath(thisdir, L"docdiff\\docdiff-0.5.0\\bin\\docdiff");
			
			docdiffrb_ = CppUtils::GetShortFileName(gcnew String(docdiffrb.c_str()));
			docdifflibdir_ = CppUtils::GetShortFileName(gcnew String(rubylibdir.c_str()));
		}
	}

	void Ruby::RunRuby(System::String^ commandline,
		System::String^% out, System::String^% err)
	{
		String^ dir = Path::GetDirectoryName(Application::ExecutablePath);
		CLRHelper::TemporalCurrentDir tmpdir(dir);

		int retval;
		AmbLib::OpenCommandGetResult(
			Ruby::RubyExe,
			L"-v",
			Encoding::UTF8,
			retval,
			out,
			err);
	}
	void Ruby::RunDocDiff(System::String^ commandline,
		System::String^% out, System::String^% err)
	{
		String^ dir = Path::GetDirectoryName(Application::ExecutablePath);
		CLRHelper::TemporalCurrentDir tmpdir(dir);

		String^ clrCommandLine = String::Format(L"{0} {1} {2}",
			L"-I" + CLRHelper::doubleQuote(Ruby::DocDiffLibDir),
			CLRHelper::doubleQuote(Ruby::DocDiffrb),
			commandline);

		int intval;
		AmbLib::OpenCommandGetResult(Ruby::RubyExe,
			clrCommandLine,
			Encoding::UTF8,
			intval,
			out,
			err);
	}

	

	String^ Ruby::RubyExeConfig::get()
	{
		if (!rubyExeConfig_)
		{
			Profile::GetString(
				SECTION_RUBY,
				KEY_RUBY_PATH,
				String::Empty,
				rubyExeConfig_,
				Common::IniPath);
		}
		return rubyExeConfig_;
	}
	void Ruby::RubyExeConfig::set(String^ value)
	{
		rubyExeConfig_ = value;
		initialized_ = false;
		if (!Profile::WriteString(
			SECTION_RUBY,
			KEY_RUBY_PATH,
			value,
			Common::IniPath))
		{
			System::Windows::Forms::MessageBox::Show(
				I18N("Failed to save settings."),
				System::Windows::Forms::Application::ProductName,
				System::Windows::Forms::MessageBoxButtons::OK,
				System::Windows::Forms::MessageBoxIcon::Warning);
		}
	}
}