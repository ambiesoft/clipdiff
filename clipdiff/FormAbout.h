#pragma once

namespace clipdiff {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for FormAbout
	/// </summary>
	public ref class FormAbout : public System::Windows::Forms::Form
	{
	public:
		FormAbout(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FormAbout()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  picBigIcon;
	private: System::Windows::Forms::RichTextBox^  rtMain;
	private: System::Windows::Forms::Button^  btnOK;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FormAbout::typeid));
			this->picBigIcon = (gcnew System::Windows::Forms::PictureBox());
			this->rtMain = (gcnew System::Windows::Forms::RichTextBox());
			this->btnOK = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picBigIcon))->BeginInit();
			this->SuspendLayout();
			// 
			// picBigIcon
			// 
			this->picBigIcon->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"picBigIcon.Image")));
			this->picBigIcon->Location = System::Drawing::Point(0, 12);
			this->picBigIcon->Name = L"picBigIcon";
			this->picBigIcon->Size = System::Drawing::Size(64, 64);
			this->picBigIcon->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->picBigIcon->TabIndex = 0;
			this->picBigIcon->TabStop = false;
			this->picBigIcon->WaitOnLoad = true;
			// 
			// rtMain
			// 
			this->rtMain->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->rtMain->Location = System::Drawing::Point(70, 12);
			this->rtMain->Name = L"rtMain";
			this->rtMain->ReadOnly = true;
			this->rtMain->Size = System::Drawing::Size(493, 225);
			this->rtMain->TabIndex = 1;
			this->rtMain->Text = L"";
			// 
			// btnOK
			// 
			this->btnOK->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->btnOK->Location = System::Drawing::Point(438, 246);
			this->btnOK->Name = L"btnOK";
			this->btnOK->Size = System::Drawing::Size(125, 23);
			this->btnOK->TabIndex = 2;
			this->btnOK->Text = L"&OK";
			this->btnOK->UseVisualStyleBackColor = true;
			// 
			// FormAbout
			// 
			this->AcceptButton = this->btnOK;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(575, 278);
			this->Controls->Add(this->btnOK);
			this->Controls->Add(this->rtMain);
			this->Controls->Add(this->picBigIcon);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->HelpButton = true;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"FormAbout";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"About clipdiff";
			this->Load += gcnew System::EventHandler(this, &FormAbout::OnLoad);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picBigIcon))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
		System::Void OnLoad(System::Object^  sender, System::EventArgs^  e);
	
	};
}
