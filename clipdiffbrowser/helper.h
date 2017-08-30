#pragma once


namespace clipdiffbrowser {
	
	
	System::Windows::Forms::DialogResult ErrorMessageBox(System::String^ err, DWORD error);
	System::Windows::Forms::DialogResult ErrorMessageBox(System::String^ err);
	System::Windows::Forms::DialogResult ErrorMessageBox(System::String^ err, System::Exception^ ex);

}

