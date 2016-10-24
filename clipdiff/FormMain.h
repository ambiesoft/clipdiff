#pragma once


namespace clipdiff {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	ref class DiffList;
	/// <summary>
	/// Summary for FormMain
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class FormMain : public System::Windows::Forms::Form
	{
	public:
		FormMain(void)
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
		~FormMain()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuMain;
	protected: 
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::SplitContainer^  splitRoot;
	private: System::Windows::Forms::ListView^  lv1;

	private: System::Windows::Forms::ColumnHeader^  chLine;
	private: System::Windows::Forms::ColumnHeader^  chText;
	private: System::Windows::Forms::ListView^  lv2;

	private: System::Windows::Forms::ColumnHeader^  columnHeader1;
	private: System::Windows::Forms::ColumnHeader^  columnHeader2;

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
			this->menuMain = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->splitRoot = (gcnew System::Windows::Forms::SplitContainer());
			this->lv1 = (gcnew System::Windows::Forms::ListView());
			this->chLine = (gcnew System::Windows::Forms::ColumnHeader());
			this->chText = (gcnew System::Windows::Forms::ColumnHeader());
			this->lv2 = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
			this->menuMain->SuspendLayout();
			this->splitRoot->Panel1->SuspendLayout();
			this->splitRoot->Panel2->SuspendLayout();
			this->splitRoot->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuMain
			// 
			this->menuMain->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->fileToolStripMenuItem});
			this->menuMain->Location = System::Drawing::Point(0, 0);
			this->menuMain->Name = L"menuMain";
			this->menuMain->Size = System::Drawing::Size(622, 24);
			this->menuMain->TabIndex = 0;
			this->menuMain->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->exitToolStripMenuItem});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(39, 20);
			this->fileToolStripMenuItem->Text = L"&File";
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->exitToolStripMenuItem->Text = L"&Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::exitToolStripMenuItem_Click);
			// 
			// splitRoot
			// 
			this->splitRoot->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitRoot->Location = System::Drawing::Point(0, 24);
			this->splitRoot->Name = L"splitRoot";
			// 
			// splitRoot.Panel1
			// 
			this->splitRoot->Panel1->Controls->Add(this->lv1);
			// 
			// splitRoot.Panel2
			// 
			this->splitRoot->Panel2->Controls->Add(this->lv2);
			this->splitRoot->Size = System::Drawing::Size(622, 421);
			this->splitRoot->SplitterDistance = 295;
			this->splitRoot->TabIndex = 1;
			// 
			// lv1
			// 
			this->lv1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->chLine, this->chText});
			this->lv1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lv1->Location = System::Drawing::Point(0, 0);
			this->lv1->Name = L"lv1";
			this->lv1->Size = System::Drawing::Size(295, 421);
			this->lv1->TabIndex = 0;
			this->lv1->UseCompatibleStateImageBehavior = false;
			this->lv1->View = System::Windows::Forms::View::Details;
			// 
			// chLine
			// 
			this->chLine->Text = L"Line";
			// 
			// chText
			// 
			this->chText->Text = L"Text";
			this->chText->Width = 213;
			// 
			// lv2
			// 
			this->lv2->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->columnHeader1, this->columnHeader2});
			this->lv2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lv2->Location = System::Drawing::Point(0, 0);
			this->lv2->Name = L"lv2";
			this->lv2->Size = System::Drawing::Size(323, 421);
			this->lv2->TabIndex = 1;
			this->lv2->UseCompatibleStateImageBehavior = false;
			this->lv2->View = System::Windows::Forms::View::Details;
			// 
			// columnHeader1
			// 
			this->columnHeader1->Text = L"Line";
			// 
			// columnHeader2
			// 
			this->columnHeader2->Text = L"Text";
			this->columnHeader2->Width = 213;
			// 
			// FormMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(622, 445);
			this->Controls->Add(this->splitRoot);
			this->Controls->Add(this->menuMain);
			this->MainMenuStrip = this->menuMain;
			this->Name = L"FormMain";
			this->Text = L"FormMain";
			this->Load += gcnew System::EventHandler(this, &FormMain::FormMain_Load);
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &FormMain::FormMain_FormClosed);
			this->menuMain->ResumeLayout(false);
			this->menuMain->PerformLayout();
			this->splitRoot->Panel1->ResumeLayout(false);
			this->splitRoot->Panel2->ResumeLayout(false);
			this->splitRoot->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		HWND ClipboardViewerNext_;
		DifferenceEngine::DiffEngine^ de_;
		DiffList^ df1_;
		DiffList^ df2_;
		String^ lastText_;
	protected: 
		virtual void WndProc(Message% m) override = Control::WndProc;
		void renderDiff();

	private: System::Void FormMain_Load(System::Object^  sender, System::EventArgs^  e);
	private: System::Void FormMain_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
				ChangeClipboardChain((HWND)this->Handle.ToPointer(), ClipboardViewerNext_);
				ClipboardViewerNext_ = NULL;
			 }
	private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->Close();
			 }
	};
}

