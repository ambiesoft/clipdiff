#pragma once

namespace Ambiesoft {

	ref class Ruby abstract sealed
	{
		static bool initialized_;


		static System::String^ rubyexe_;
		static System::String^ docdiffrb_;

		static void init();

	public:
		static property System::String^ RubyExe
		{
			System::String^ get()
			{
				init();
				return rubyexe_;
			}
		}
		static property System::String^ DocDiffrb
		{
			System::String^ get()
			{
				init();
				return docdiffrb_;
			}
		}
	};
}