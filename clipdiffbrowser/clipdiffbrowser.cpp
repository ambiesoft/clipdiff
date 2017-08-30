

#include "stdafx.h"
#include "FormMain.h"

using namespace clipdiffbrowser;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	System::Diagnostics::Debug::Assert(false);

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// メイン ウィンドウを作成して、実行します
	Application::Run(gcnew Form1());
	return 0;
}
