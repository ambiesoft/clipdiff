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
		FormMain(void);
		
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

	private: System::Windows::Forms::ListView^  lv1;
	private: System::Windows::Forms::ColumnHeader^  chLine1;
	private: System::Windows::Forms::ColumnHeader^  chText1;









	private: System::Windows::Forms::ListView^  lv2;
	private: System::Windows::Forms::ColumnHeader^  chLine2;
	private: System::Windows::Forms::ColumnHeader^  chText2;



	private: System::Windows::Forms::TableLayoutPanel^  tlpMain;
	private: System::Windows::Forms::ToolStripMenuItem^  editToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  addColumnToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  removeColumnToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  optionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ignoreWhenClipboardTextsAreSameToolStripMenuItem;
	private: System::Windows::Forms::StatusStrip^  stMain;
	private: System::Windows::Forms::ToolStripStatusLabel^  stlMain;
	private: System::Windows::Forms::ToolStripMenuItem^  windowToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  alwaysOnTopToolStripMenuItem;



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
		void InitializeComponent(void);
	
#pragma endregion
		HWND ClipboardViewerNext_;
		DifferenceEngine::DiffEngine^ de_;
		DiffList^ df1_;
		DiffList^ df2_;
		String^ lastText_;
	protected: 
		virtual void WndProc(Message% m) override = Control::WndProc;
		void renderDiff();
		void addColumn();
		void removeColumn();

	private: System::Void FormMain_Load(System::Object^  sender, System::EventArgs^  e);
	private: System::Void FormMain_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
				ChangeClipboardChain((HWND)this->Handle.ToPointer(), ClipboardViewerNext_);
				ClipboardViewerNext_ = NULL;
			 }
	private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->Close();
			 }
	private: System::Void addColumnToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 addColumn();
			 }
private: System::Void removeColumnToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 removeColumn();
		 }
	private: System::Void tlpMain_SizeChanged(System::Object^  sender, System::EventArgs^  e);
			 
	private: System::Void ignoreWhenClipboardTextsAreSameToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				ignoreWhenClipboardTextsAreSameToolStripMenuItem->Checked=!ignoreWhenClipboardTextsAreSameToolStripMenuItem->Checked;
			 }
	private: System::Void alwaysOnTopToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void windowToolStripMenuItem_DropDownOpening(System::Object^  sender, System::EventArgs^  e);

	};
}

