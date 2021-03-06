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

namespace Ambiesoft {

	using namespace System;


	ref class Ruby abstract sealed
	{
		literal String^ SECTION_RUBY = L"Ruby";
		literal String^ KEY_RUBY_PATH = L"Path";
	public:
		literal String^ DefaultRubyPath = L"docdiff\\ruby2.4\\bin\\ruby.exe";
		
	private:
		static bool initialized_;


		static System::String^ rubyexe_;
		static System::String^ docdiffrb_;
		static System::String^ docdifflibdir_;
		static void init();
		
		static String^ rubyExeConfig_;
	public:
		static property System::String^ RubyExe
		{
			System::String^ get()
			{
				init();
				return rubyexe_;
			}
		}
		

		static property String^ RubyExeConfig
		{
			String^ get();
			void set(String^ value);
		}
		static property System::String^ DocDiffrb
		{
			System::String^ get()
			{
				init();
				return docdiffrb_;
			}
		}
		static property System::String^ DocDiffLibDir
		{
			System::String^ get()
			{
				init();
				return docdifflibdir_;
			}
		}

		static void RunRuby(System::String^ commandline,
			System::String^%out, System::String^% err);
		static void RunDocDiff(System::String^ commandline,
			System::String^%out, System::String^% err);

		
	};
}