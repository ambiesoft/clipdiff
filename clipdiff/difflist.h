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