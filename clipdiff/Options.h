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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Options::typeid));
			this->btnColorNoChange = (gcnew System::Windows::Forms::Button());
			this->grColor = (gcnew System::Windows::Forms::GroupBox());
			this->btnColorReplace = (gcnew System::Windows::Forms::Button());
			this->btnColorDelete = (gcnew System::Windows::Forms::Button());
			this->btnColorAdd = (gcnew System::Windows::Forms::Button());
			this->btnOK = (gcnew System::Windows::Forms::Button());
			this->btnCancel = (gcnew System::Windows::Forms::Button());
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->grColor->SuspendLayout();
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
			// Options
			// 
			this->AcceptButton = this->btnOK;
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->btnCancel;
			this->Controls->Add(this->btnCancel);
			this->Controls->Add(this->btnOK);
			this->Controls->Add(this->grColor);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Options";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->grColor->ResumeLayout(false);
			this->ResumeLayout(false);

		}

		void ChangeColorCommon(System::Object^ sender, System::EventArgs^ e);
#pragma endregion


		System::Void btnColorNoChange_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnColorAdd_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnColorDelete_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnColorReplace_Click(System::Object^  sender, System::EventArgs^  e);

	};
}
