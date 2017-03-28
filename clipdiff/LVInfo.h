#pragma once

namespace clipdiff {
	using namespace System;

	ref class DiffList;

	ref class LVInfo
	{
		DiffList^ df_;
	public:
		//property String^ OriginalText;
		property DiffList^ Diff
		{
			DiffList^ get();
			void set(DiffList^ dl);
		}
	public:
		LVInfo();
	};

}