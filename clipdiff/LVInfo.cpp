#include "StdAfx.h"
#include "LVInfo.h"
#include "DiffList.h"

namespace clipdiff {
	LVInfo::LVInfo()
	{
		df_ = gcnew DiffList(String::Empty);
	}



	DiffList^ LVInfo::Diff::get()
	{
		return df_;
	}

	void LVInfo::Diff::set(DiffList^ dl)
	{
		df_ = dl;
	}
}