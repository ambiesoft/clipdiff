#include "stdafx.h"
#include "helper.h"

#include "../../MyUtility/GetLastErrorString.h"

namespace clipdiffbrowser {
	using namespace System;
	using namespace System::Windows::Forms;

	using std::wstring;

	DialogResult ErrorMessageBox(String^ err)
	{
		return MessageBox::Show(err,
			Application::ProductName,
			MessageBoxButtons::OK,
			MessageBoxIcon::Error);
	}

	DialogResult ErrorMessageBox(String^ err, DWORD error)
	{
		if (error != NO_ERROR)
		{
			wstring s = GetLastErrorString(error);
			err += L": " + gcnew String(s.c_str());
		}
		return ErrorMessageBox(err);
	}

	DialogResult ErrorMessageBox(String^ err, System::Exception^ ex)
	{
		if (ex)
		{
			err += L": " + ex->Message;
		}
		return ErrorMessageBox(err);
	}

}

