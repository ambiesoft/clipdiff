// clipdiff.cpp : main project file.

#include "stdafx.h"
#include "difflist.h"

namespace clipdiff {

	DiffList::DiffList(String^ text)
	{
		lines_ = gcnew List<TextLine^>();
		if(String::IsNullOrEmpty(text))
			return;

		text=text->Replace(L"\r\n", L"\n");
		text=text->Replace(L"\r", L"\n");
		array<String^>^ lines = text->Split(L'\n');
		
		for each(String^ s in lines)
		{
			lines_->Add(gcnew TextLine(s));
		}
		// lines_->AddRange(lines);
	}
}

