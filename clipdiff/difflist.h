
namespace clipdiff {

	using namespace System;
	using namespace System::Collections::Generic;

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

		property String^ Line
		{
			String^ get() { return Line_; }
		}
	};

	ref class DiffList : DifferenceEngine::IDiffList
	{
	public:
		List<TextLine^>^ lines_;

	public:
		DiffList(String^ text);
		DiffList(List<TextLine^>^ ar)
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

		String^ GetText()
		{
			System::Text::StringBuilder sb;
			for each(TextLine^ line in lines_)
			{
				sb.AppendLine(line->Line);
			}
			return sb.ToString()->TrimEnd(Environment::NewLine->ToCharArray());
		}
	};

}