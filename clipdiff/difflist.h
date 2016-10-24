
namespace clipdiff {

	using namespace System;
	using namespace System::Collections;

	ref class TextLine : IComparable
	{
	public:
		String^ Line_;
		int hash_;

		TextLine(String^ str)
		{
			Line_ = str->Replace(L"\t", L"    ");
			hash_ = str->GetHashCode();
		}


		virtual int CompareTo(Object^ obj)
		{
			return hash_.CompareTo(((TextLine^)obj)->hash_);
		}
	};

	ref class DiffList : DifferenceEngine::IDiffList
	{
	public:
		ArrayList^ lines_;
	public:
		DiffList(String^ text);
		DiffList(ArrayList^ ar)
		{
			lines_=ar;
		}
		virtual int Count()
		{
			return lines_->Count;
		}

		virtual IComparable^ GetByIndex(int index)
		{
			return (TextLine^)lines_[index];
		}
	};

}