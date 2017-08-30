#pragma once


namespace clipdiffbrowser {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class FormMain : public System::Windows::Forms::Form
	{
	private:
		initonly HWND hWndHost_;
		initonly String^ file1_;
		initonly String^ file2_;
	public:
		FormMain(HWND h, String^ file1, String^ file2)
		{
			hWndHost_ = h;
			file1_ = file1;
			file2_ = file2;
			InitializeComponent();
		}

	protected:
		~FormMain()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::WebBrowser^  browser;
	protected: 
		virtual void WndProc(System::Windows::Forms::Message% m) override = Control::WndProc;
	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->browser = (gcnew System::Windows::Forms::WebBrowser());
			this->SuspendLayout();
			// 
			// browser
			// 
			this->browser->Dock = System::Windows::Forms::DockStyle::Fill;
			this->browser->Location = System::Drawing::Point(0, 0);
			this->browser->MinimumSize = System::Drawing::Size(20, 20);
			this->browser->Name = L"browser";
			this->browser->Size = System::Drawing::Size(284, 261);
			this->browser->TabIndex = 0;
			// 
			// FormMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->browser);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"FormMain";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->Text = L"clipdiffbrowser";
			this->Load += gcnew System::EventHandler(this, &FormMain::FormMain_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void FormMain_Load(System::Object^  sender, System::EventArgs^  e);
	
	};
}

