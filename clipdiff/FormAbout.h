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
#pragma once

namespace clipdiff {

	using namespace System;


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

		enum class RunWhich {
			RunRuby,
			RunDocDiff,
		};
		static String^ Run(RunWhich r, String^ commandline);
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
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::LinkLabel^  llDiffEngine;

	private: System::Windows::Forms::TextBox^  txtClipdiffVersion;
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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->llDiffEngine = (gcnew System::Windows::Forms::LinkLabel());
			this->txtClipdiffVersion = (gcnew System::Windows::Forms::TextBox());
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
			this->rtMain->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->rtMain->Location = System::Drawing::Point(72, 124);
			this->rtMain->Name = L"rtMain";
			this->rtMain->ReadOnly = true;
			this->rtMain->Size = System::Drawing::Size(563, 158);
			this->rtMain->TabIndex = 1;
			this->rtMain->Text = L"";
			// 
			// btnOK
			// 
			this->btnOK->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btnOK->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->btnOK->Location = System::Drawing::Point(510, 291);
			this->btnOK->Name = L"btnOK";
			this->btnOK->Size = System::Drawing::Size(125, 23);
			this->btnOK->TabIndex = 0;
			this->btnOK->Text = L"&OK";
			this->btnOK->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(70, 87);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(60, 12);
			this->label1->TabIndex = 2;
			this->label1->Text = L"DiffEngine:";
			// 
			// llDiffEngine
			// 
			this->llDiffEngine->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->llDiffEngine->AutoSize = true;
			this->llDiffEngine->Location = System::Drawing::Point(70, 100);
			this->llDiffEngine->Name = L"llDiffEngine";
			this->llDiffEngine->Size = System::Drawing::Size(462, 12);
			this->llDiffEngine->TabIndex = 3;
			this->llDiffEngine->TabStop = true;
			this->llDiffEngine->Text = L"https://www.codeproject.com/Articles/6943/A-Generic-Reusable-Diff-Algorithm-in-C-"
				L"II";
			this->llDiffEngine->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &FormAbout::llDiffEngine_LinkClicked);
			// 
			// txtClipdiffVersion
			// 
			this->txtClipdiffVersion->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtClipdiffVersion->Location = System::Drawing::Point(70, 11);
			this->txtClipdiffVersion->Multiline = true;
			this->txtClipdiffVersion->Name = L"txtClipdiffVersion";
			this->txtClipdiffVersion->ReadOnly = true;
			this->txtClipdiffVersion->Size = System::Drawing::Size(565, 71);
			this->txtClipdiffVersion->TabIndex = 4;
			// 
			// FormAbout
			// 
			this->AcceptButton = this->btnOK;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(647, 322);
			this->Controls->Add(this->txtClipdiffVersion);
			this->Controls->Add(this->llDiffEngine);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->btnOK);
			this->Controls->Add(this->rtMain);
			this->Controls->Add(this->picBigIcon);
			this->HelpButton = true;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"FormAbout";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Show;
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
		System::Void llDiffEngine_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e);
	
};
}
