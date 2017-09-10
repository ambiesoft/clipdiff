#include "stdafx.h"
#include "Ruby.h"

namespace Ambiesoft {

	using namespace System;

	using namespace std;
	using namespace stdwin32;
	void Ruby::init()
	{
		if (initialized_)
			return;
		initialized_ = true;
		
		wstring thisdir = stdGetParentDirectory(stdGetModuleFileName());
		wstring rubyexe = stdCombinePath(thisdir, L"docdiff\\ruby1.8\\bin\\ruby.exe");
		wstring rubylibdir = stdCombinePath(thisdir, L"docdiff\\docdiff-0.3.3");
		wstring docdiffrb = stdCombinePath(thisdir, L"docdiff\\docdiff-0.3.3\\docdiff.rb");
		wstring t = stdGetEnvironmentVariable(L"RUBYLIB");

		if (t.empty())
			t = rubylibdir.c_str();
		else
			t = rubylibdir + L";" + t;
		SetEnvironmentVariable(L"RUBYLIB", t.c_str());


		rubyexe_ = gcnew String(rubyexe.c_str());
		docdiffrb_ = gcnew String(docdiffrb.c_str());

	}


}