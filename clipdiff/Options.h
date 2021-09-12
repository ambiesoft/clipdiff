//BSD 2-Clause License
//
//Copyright (c) 2017, Ambiesoft
//All rights reserved.
//
//Redistribution and use in source and binary forms, with or without
//modification, are permitted provided that the following conditions are met:
//
//* Redistributions of source code must retain the above copyright notice, this
//  list of conditions and the following disclaimer.
//
//* Redistributions in binary form must reproduce the above copyright notice,
//  this list of conditions and the following disclaimer in the documentation
//  and/or other materials provided with the distribution.
//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
//FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
//CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
//OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#pragma once

namespace clipdiff {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Options
	/// </summary>
	public ref class Options : public System::Windows::Forms::Form
	{
	public:
		Options(void)
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
		~Options()
		{
			if (components)
			{
				delete components;
			}
		}
	internal: System::Windows::Forms::Button^  btnColorNoChange;
	protected:
	private: System::Windows::Forms::GroupBox^  grColor;
	internal: System::Windows::Forms::Button^  btnColorReplace;
	internal: System::Windows::Forms::Button^  btnColorDelete;
	internal: System::Windows::Forms::Button^  btnColorAdd;
	private: System::Windows::Forms::Button^  btnOK;
	internal:
	private: System::Windows::Forms::Button^  btnCancel;
	private: System::Windows::Forms::ColorDialog^  colorDialog1;
	private: System::Windows::Forms::GroupBox^  grRuby;

	private: System::Windows::Forms::Button^  btnBrowseRuby;
	internal: System::Windows::Forms::TextBox^  txtRubyPath;
	private:

	private:
	private: System::Windows::Forms::Label^  label1;
	internal: System::Windows::Forms::CheckBox^  chkNoCloseSubWinConfirm;
	private: System::Windows::Forms::TableLayoutPanel^  tlpRuby;
	internal: System::Windows::Forms::CheckBox^ chkShowTooltip;
	private:
	internal:

	internal:
	private:

	internal:

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Options::typeid));
			this->btnColorNoChange = (gcnew System::Windows::Forms::Button());
			this->grColor = (gcnew System::Windows::Forms::GroupBox());
			this->btnColorReplace = (gcnew System::Windows::Forms::Button());
			this->btnColorDelete = (gcnew System::Windows::Forms::Button());
			this->btnColorAdd = (gcnew System::Windows::Forms::Button());
			this->btnOK = (gcnew System::Windows::Forms::Button());
			this->btnCancel = (gcnew System::Windows::Forms::Button());
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->grRuby = (gcnew System::Windows::Forms::GroupBox());
			this->tlpRuby = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->btnBrowseRuby = (gcnew System::Windows::Forms::Button());
			this->txtRubyPath = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->chkNoCloseSubWinConfirm = (gcnew System::Windows::Forms::CheckBox());
			this->chkShowTooltip = (gcnew System::Windows::Forms::CheckBox());
			this->grColor->SuspendLayout();
			this->grRuby->SuspendLayout();
			this->tlpRuby->SuspendLayout();
			this->SuspendLayout();
			// 
			// btnColorNoChange
			// 
			resources->ApplyResources(this->btnColorNoChange, L"btnColorNoChange");
			this->btnColorNoChange->Name = L"btnColorNoChange";
			this->btnColorNoChange->UseVisualStyleBackColor = true;
			this->btnColorNoChange->Click += gcnew System::EventHandler(this, &Options::btnColorNoChange_Click);
			// 
			// grColor
			// 
			resources->ApplyResources(this->grColor, L"grColor");
			this->grColor->Controls->Add(this->btnColorReplace);
			this->grColor->Controls->Add(this->btnColorDelete);
			this->grColor->Controls->Add(this->btnColorAdd);
			this->grColor->Controls->Add(this->btnColorNoChange);
			this->grColor->Name = L"grColor";
			this->grColor->TabStop = false;
			// 
			// btnColorReplace
			// 
			resources->ApplyResources(this->btnColorReplace, L"btnColorReplace");
			this->btnColorReplace->Name = L"btnColorReplace";
			this->btnColorReplace->UseVisualStyleBackColor = true;
			this->btnColorReplace->Click += gcnew System::EventHandler(this, &Options::btnColorReplace_Click);
			// 
			// btnColorDelete
			// 
			resources->ApplyResources(this->btnColorDelete, L"btnColorDelete");
			this->btnColorDelete->Name = L"btnColorDelete";
			this->btnColorDelete->UseVisualStyleBackColor = true;
			this->btnColorDelete->Click += gcnew System::EventHandler(this, &Options::btnColorDelete_Click);
			// 
			// btnColorAdd
			// 
			resources->ApplyResources(this->btnColorAdd, L"btnColorAdd");
			this->btnColorAdd->Name = L"btnColorAdd";
			this->btnColorAdd->UseVisualStyleBackColor = true;
			this->btnColorAdd->Click += gcnew System::EventHandler(this, &Options::btnColorAdd_Click);
			// 
			// btnOK
			// 
			resources->ApplyResources(this->btnOK, L"btnOK");
			this->btnOK->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->btnOK->Name = L"btnOK";
			this->btnOK->UseVisualStyleBackColor = true;
			// 
			// btnCancel
			// 
			resources->ApplyResources(this->btnCancel, L"btnCancel");
			this->btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->btnCancel->Name = L"btnCancel";
			this->btnCancel->UseVisualStyleBackColor = true;
			// 
			// grRuby
			// 
			resources->ApplyResources(this->grRuby, L"grRuby");
			this->grRuby->Controls->Add(this->tlpRuby);
			this->grRuby->Name = L"grRuby";
			this->grRuby->TabStop = false;
			// 
			// tlpRuby
			// 
			resources->ApplyResources(this->tlpRuby, L"tlpRuby");
			this->tlpRuby->Controls->Add(this->btnBrowseRuby, 1, 1);
			this->tlpRuby->Controls->Add(this->txtRubyPath, 0, 1);
			this->tlpRuby->Controls->Add(this->label1, 0, 0);
			this->tlpRuby->Name = L"tlpRuby";
			// 
			// btnBrowseRuby
			// 
			resources->ApplyResources(this->btnBrowseRuby, L"btnBrowseRuby");
			this->btnBrowseRuby->Name = L"btnBrowseRuby";
			this->btnBrowseRuby->UseVisualStyleBackColor = true;
			this->btnBrowseRuby->Click += gcnew System::EventHandler(this, &Options::btnBrowseRuby_Click);
			// 
			// txtRubyPath
			// 
			resources->ApplyResources(this->txtRubyPath, L"txtRubyPath");
			this->txtRubyPath->Name = L"txtRubyPath";
			// 
			// label1
			// 
			resources->ApplyResources(this->label1, L"label1");
			this->label1->Name = L"label1";
			// 
			// chkNoCloseSubWinConfirm
			// 
			resources->ApplyResources(this->chkNoCloseSubWinConfirm, L"chkNoCloseSubWinConfirm");
			this->chkNoCloseSubWinConfirm->Name = L"chkNoCloseSubWinConfirm";
			this->chkNoCloseSubWinConfirm->UseVisualStyleBackColor = true;
			// 
			// chkShowTooltip
			// 
			resources->ApplyResources(this->chkShowTooltip, L"chkShowTooltip");
			this->chkShowTooltip->Name = L"chkShowTooltip";
			this->chkShowTooltip->UseVisualStyleBackColor = true;
			// 
			// Options
			// 
			this->AcceptButton = this->btnOK;
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->btnCancel;
			this->Controls->Add(this->chkShowTooltip);
			this->Controls->Add(this->chkNoCloseSubWinConfirm);
			this->Controls->Add(this->grRuby);
			this->Controls->Add(this->btnCancel);
			this->Controls->Add(this->btnOK);
			this->Controls->Add(this->grColor);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Options";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->grColor->ResumeLayout(false);
			this->grRuby->ResumeLayout(false);
			this->tlpRuby->ResumeLayout(false);
			this->tlpRuby->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		void ChangeColorCommon(System::Object^ sender, System::EventArgs^ e);
#pragma endregion


		System::Void btnColorNoChange_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnColorAdd_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnColorDelete_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnColorReplace_Click(System::Object^  sender, System::EventArgs^  e);

		System::Void btnBrowseRuby_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnRubyDefault_Click(System::Object^  sender, System::EventArgs^  e);

};
}
