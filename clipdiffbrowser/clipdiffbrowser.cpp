

#include "stdafx.h"
#include "FormMain.h"

using namespace clipdiffbrowser;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	System::Diagnostics::Debug::Assert(false);

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// ���C�� �E�B���h�E���쐬���āA���s���܂�
	Application::Run(gcnew Form1());
	return 0;
}
