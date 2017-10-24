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

#pragma once

namespace clipdiff {

	using namespace System;
	using namespace System::Collections::Generic;

	ref class ResourceLoader abstract sealed
	{
		static System::Resources::ResourceManager^ theResource_ =
			gcnew System::Resources::ResourceManager(
			ResourceLoader::typeid->Namespace + ".StringResource",
			System::Reflection::Assembly::GetExecutingAssembly());

		static System::Globalization::CultureInfo^ ci_;

	internal:
		static bool setLang(String^ culture)
		{
			try
			{
				System::Globalization::CultureInfo^ ci = gcnew System::Globalization::CultureInfo(culture);
				System::Threading::Thread::CurrentThread->CurrentCulture = ci;
				System::Threading::Thread::CurrentThread->CurrentUICulture = ci;

				ci_ = ci;
			}
			catch (Exception^ ex)
			{
				Ambiesoft::CppUtils::Alert(ex);
				return false;
			}
			return true;
		}
		static String^ getI18NString(String^ sIn)
		{
			String^ ret = theResource_->GetString(sIn, ci_);
			return String::IsNullOrEmpty(ret) ? sIn : ret;
		}
	};

}