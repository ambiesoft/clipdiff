#pragma once


namespace clipdiff {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	ref class DiffList;
	ref class ListViewForScroll;

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
		literal String^ APP_OPTION=					L"Option";


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




















	private: System::Windows::Forms::ToolStripMenuItem^  editToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  addColumnToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  removeColumnToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  optionToolStripMenuItem;

	private: System::Windows::Forms::StatusStrip^  stMain;
	private: System::Windows::Forms::ToolStripStatusLabel^  stlMain;
	private: System::Windows::Forms::ToolStripMenuItem^  windowToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmTopMost;



	private: System::Windows::Forms::TableLayoutPanel^ tlpMain;
	private: System::Windows::Forms::Panel^  panelClient;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem1;


	private: System::Windows::Forms::ToolStrip^  toolMain;
	private: System::Windows::Forms::ToolStripButton^  tsbKeep;

	private: System::Windows::Forms::ToolStripMenuItem^  tsmKeep;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmIgnoreSame;
	private: System::Windows::Forms::ToolStripButton^  tsbIgnoreSame;
	private: System::Windows::Forms::ToolStripButton^  tsbTopMost;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmAbout;

	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem2;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmFont;
	private: System::Windows::Forms::ToolStripMenuItem^  viewToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmShowToolbar;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmShowStatusbar;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmShowListheader;
	private: System::Windows::Forms::ToolStripMenuItem^  engineLevelToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmELFast;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmELMedium;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmELSlow;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem3;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmSaveAs;
	private: System::Windows::Forms::ToolStripStatusLabel^  slChange;
	private: System::Windows::Forms::ToolStripStatusLabel^  stlResult;








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
		//DiffList^ df1_;
		//DiffList^ df2_;
		String^ lastText_;
		void onKeep();
		property bool IsKeep;

		void onIgnoreSame();
		property bool IsIgnoreSame;

		property System::Drawing::Font^ FontLV;
		property bool IsHeaderVisible;
		property DifferenceEngine::DiffEngineLevel EngineLevel;

	protected: 
		virtual void WndProc(Message% m) override = Control::WndProc;
		void renderDiff(ListView^ lv1, ListView^ lv2);
		void addColumn();
		void removeColumn();
		void updateTitle(int addCount, int replaceCount, int deleteCount, int nochangeCount);
		void updateTitle();
		System::Collections::Generic::List<System::IO::StreamWriter^>^ GetsaveAsFiles(int filecount, String^ filenamepre);

	private: System::Void FormMain_Load(System::Object^  sender, System::EventArgs^  e);
	private: System::Void FormMain_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e);
	private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void addColumnToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void removeColumnToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void tlpMain_SizeChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void onTopMost(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void windowToolStripMenuItem_DropDownOpening(System::Object^  sender, System::EventArgs^  e);
	private: System::Void FormMain_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
	


	private: System::Void tsmIgnoreSame_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void tsbIgnoreSame_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void tsmAbout_Click(System::Object^  sender, System::EventArgs^  e);

	private: System::Void tsmKeep_Click(System::Object^  sender, System::EventArgs^  e);

	System::Void tsbKeep_Click(System::Object^  sender, System::EventArgs^  e);

	System::Void tsmFont_Click(System::Object^  sender, System::EventArgs^  e) ;

System::Void tsmShowToolbar_Click(System::Object^  sender, System::EventArgs^  e);

System::Void tsmShowStatusbar_Click(System::Object^  sender, System::EventArgs^  e);

System::Void tsmShowListheader_Click(System::Object^  sender, System::EventArgs^  e);

System::Void toolMain_VisibleChanged(System::Object^  sender, System::EventArgs^  e);
		 
System::Void stMain_VisibleChanged(System::Object^  sender, System::EventArgs^  e);
		 
System::Void viewToolStripMenuItem_DropDownOpening(System::Object^  sender, System::EventArgs^  e);
		 
System::Void tsmELFast_Click(System::Object^  sender, System::EventArgs^  e);

System::Void tsmELMedium_Click(System::Object^  sender, System::EventArgs^  e);

System::Void tsmELSlow_Click(System::Object^  sender, System::EventArgs^  e);
		 






System::Void engineLevelToolStripMenuItem_DropDownOpening(System::Object^  sender, System::EventArgs^  e);
		 
System::Void tsmSaveAs_Click(System::Object^  sender, System::EventArgs^  e);

};
}

