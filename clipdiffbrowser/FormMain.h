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
		initonly String^ left_;
		initonly String^ right_;
		initonly String^ resolution_;
		initonly bool standalone_;
		void Paste(String^ left, String^ right, String^ resolution);
		void afterPaste(String^ html);

		System::Text::StringBuilder sbRubyOut_;
		System::Text::StringBuilder sbRubyErr_;

	public:
		FormMain(HWND h, String^ left, String^ right, String^ resolution, bool standalone)
		{
			hWndHost_ = h;
			left_ = left;
			right_ = right;
			resolution_ = resolution;
			standalone_ = standalone;
			InitializeComponent();

			if (standalone)
			{
				this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;
				this->ShowIcon = true;
				this->ShowInTaskbar = true;
			}
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FormMain::typeid));
			this->browser = (gcnew System::Windows::Forms::WebBrowser());
			this->SuspendLayout();
			// 
			// browser
			// 
			this->browser->Dock = System::Windows::Forms::DockStyle::Fill;
			this->browser->Location = System::Drawing::Point(0, 0);
			this->browser->MinimumSize = System::Drawing::Size(20, 18);
			this->browser->Name = L"browser";
			this->browser->Size = System::Drawing::Size(774, 328);
			this->browser->TabIndex = 0;
			// 
			// FormMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(774, 328);
			this->Controls->Add(this->browser);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"FormMain";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->Text = L"clipdiffbrowser";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &FormMain::FormMain_FormClosing);
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &FormMain::FormMain_FormClosed);
			this->Load += gcnew System::EventHandler(this, &FormMain::FormMain_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void FormMain_Load(System::Object^  sender, System::EventArgs^  e);
	
			 void OnOutputDataReceived(System::Object ^sender, System::Diagnostics::DataReceivedEventArgs ^e);
			 void OnErrorDataReceived(System::Object ^sender, System::Diagnostics::DataReceivedEventArgs ^e);
	
			 System::Void FormMain_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
	
			 System::Void FormMain_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e);
	
	};
}

