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

#include "ListViewForScroll.h"
namespace clipdiff {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	//ref class DiffList;


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
		literal String^ APP_OPTION = L"Option";

		void SelectItemAndAync(ListViewForScroll^ lv, ListViewItem^ item);
		bool SelectIfFound(ListViewForScroll^ lv, int i);
		bool WaitChildClose(int maxwait);
	private:
		HANDLE childProcess_;
		System::Windows::Forms::ToolStripMenuItem^  tsmDocdiffChar;
		System::Windows::Forms::ToolStripMenuItem^  tsmGotoWebpage;
		System::Windows::Forms::ContextMenuStrip^  ctxMenuList;
		System::Windows::Forms::ToolStripMenuItem^  tsmCompareThisLineWithDocdiffChar;
		System::Windows::Forms::ToolStripMenuItem^  tsmCompareThisLineWithDocdiffword;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem5;
	private: System::Windows::Forms::ToolStripMenuItem^  goToNextDiffLineToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  goToPrevDiffLineToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem6;
	private: System::Windows::Forms::ToolStripMenuItem^  optionsToolStripMenuItem;




	private:
		System::Drawing::Color defaultLVNoChangeBackColor_;
		int defaultLVNoChangeBackColorRGB_;
		System::Drawing::Color defaultLVAddBackColor_;
		System::Drawing::Color defaultLVDeleteBackColor_;
		System::Drawing::Color defaultLVReplaceBackColor_;

		int currentDiffIndex_;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem7;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmCloseAllSubwindows;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmDonate;
	private: System::Windows::Forms::ToolStripMenuItem^ tsmFind;
	private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator1;
	private: System::Windows::Forms::ToolStripComboBox^ cmbFind;
	private: System::Windows::Forms::ToolStripButton^ tsbFindUp;
	private: System::Windows::Forms::ToolStripButton^ tsbFindDown;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem8;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmFindPrev;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmFindNext;
			 HWND childHwnd_;
		HWND GetChildMainFormWindow();
		bool RunDocDiff();
		bool RunDocDiff(String^ text1, String^ text2, DocDiffEngineKind dk, bool standalone);
		void compareSelectedLineWithDocdiff(DocDiffEngineKind dk);
		System::Void lv_doubleClick(System::Object^  sender, System::EventArgs^  e);
		Panel^ GetPanel(int i);
		ToolStripItem^ GetSS(int i);
		ListViewForScroll^ GetList(int i);
		void UpdateView();
		void UpdateView2();
		void renderAllDiff();
		String^ GetDocdiffEngineLevelAsString(DocDiffEngineKind dk);
		ListViewForScroll^ GetSelectedListView();
		void GotoDiffLVCommon(bool bNext);
		void GotoNextDiffLV();
		void GotoNextDiffDocDiff();
		void GotoPrevDiffLV();
		void GotoPrevDiffDocDiff();
		
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
	private: System::Windows::Forms::ToolStripMenuItem^  tsmEdit;






















	private: System::Windows::Forms::ToolStripMenuItem^  tsmAddColumn;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmRemoveColumn;
	private: System::Windows::Forms::ToolStripMenuItem^  toolsToolStripMenuItem;


	private: System::Windows::Forms::StatusStrip^  stMain;
	private: System::Windows::Forms::ToolStripStatusLabel^  stlMain;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmWindow;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmTopMost;



	private: System::Windows::Forms::TableLayoutPanel^ tlpMain;
	private: System::Windows::Forms::Panel^  panelClient;
	private: System::Windows::Forms::ToolStripSeparator^  tsmSepCopyTop;



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
	private: System::Windows::Forms::ToolStripMenuItem^  tsmView;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmShowToolbar;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmShowStatusbar;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmShowListheader;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmEngineLevel;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmELFast;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmELMedium;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmELSlow;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem3;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmSaveAs;
	private: System::Windows::Forms::ToolStripStatusLabel^  slChange;
	private: System::Windows::Forms::ToolStripStatusLabel^  stlResult;

	private: System::Windows::Forms::ToolStripMenuItem^  tsmMonitorClipboard;
	private: System::Windows::Forms::ToolStripButton^  tsbMonitorClipboard;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmPaste;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripButton^  tsbPaste;
	private: System::Windows::Forms::SplitContainer^  spRoot;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem4;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmDocdiffWord;










	protected:
		virtual void WndProc(System::Windows::Forms::Message% m) override = Control::WndProc;
	private: System::ComponentModel::IContainer^  components;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


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
		void onKeepLeft();
		bool isKeep_;
		property bool IsKeepLeft
		{
			bool get();
			void set(bool value);
		}

		void onIgnoreSame();
		bool isIgnoreSame_;
		property bool IsIgnoreSame
		{
			bool get();
			void set(bool value);
		}


		property System::Drawing::Font^ FontLV;
		property bool IsHeaderVisible;



		EngineKind engine_;
		EngineKind updatedEngine_;
		property EngineKind Engine
		{
			EngineKind get();
			void set(EngineKind value);
		}

		DifferenceEngine::DiffEngineLevel engineLevel_;
		DifferenceEngine::DiffEngineLevel updatedEngineLevel_;
		property DifferenceEngine::DiffEngineLevel EngineLevel
		{
			DifferenceEngine::DiffEngineLevel get();
			void set(DifferenceEngine::DiffEngineLevel value);
		}

		DocDiffEngineKind docdiffEngineLevel_;
		DocDiffEngineKind updatedDocdiffEngineLevel_;
		property DocDiffEngineKind DocDiffEngineLevel
		{
			DocDiffEngineKind get();
			void set(DocDiffEngineKind value);
		}


		void onMonitor();
		bool isMonitor_;
		property bool IsMonitor
		{
			bool get();
			void set(bool value);
		}

		initonly Ambiesoft::HashIni^ InitialIni_;

		void onIdle(Object^ sender, EventArgs^ e);

		bool isIdling_;
		property bool IsIdling
		{
			bool get();
			void set(bool value);
		}
		List<ListViewForScroll^>^ GetAllLV(bool bReverse);
		int GetLVIndex(ListViewForScroll^ lv);
	protected:
		property bool NoCloseSubWinConfirm;
		property bool HasSubWindows
		{
			bool get();
		}
		void CloseAllSubwindows();

		void renderDiff(ListView^ lvOld, ListView^ lvNew);
		void addColumn();
		void removeColumn();
		void updateTitle(int addCount, int replaceCount, int deleteCount, int nochangeCount);
		void updateTitle();
		void pasteClipboard();
		void pasteClipboard(bool showError);

		void findPrev(String^ findWord);
		void findNext(String^ findWord);
		void findCommon(bool bNext, String^ findWord);

		System::Collections::Generic::List<System::IO::StreamWriter^>^ GetsaveAsFiles(int filecount, String^ filenamepre, System::Collections::Generic::List<String^>^ filenames);

		System::Void copy_Clicked(System::Object^  sender, System::EventArgs^  e);
		System::Void FormMain_Load(System::Object^  sender, System::EventArgs^  e);
		System::Void FormMain_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e);
		System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmAddColumn_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmRemoveColumn_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tlpMain_SizeChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void onTopMost(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmWindow_DropDownOpening(System::Object^  sender, System::EventArgs^  e);
		System::Void FormMain_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
		System::Void tsmIgnoreSame_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsbIgnoreSame_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmAbout_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmKeep_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsbKeep_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmFont_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmShowToolbar_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmShowStatusbar_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmShowListheader_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void toolMain_VisibleChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void stMain_VisibleChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmView_DropDownOpening(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmELFast_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmELMedium_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmELSlow_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmEngineLevel_DropDownOpening(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmSaveAs_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmEdit_DropDownOpening(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmMonitorClipboard_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsbMonitorClipboard_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmPaste_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsbPaste_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmDocdiffWord_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void spRoot_Panel2_Resize(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmDocdiffChar_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmGotoWebpage_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmCompareThisLineWithDocdiffword_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmCompareThisLineWithDocdiffChar_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void goToNextDiffLineToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void goToPrevDiffLineToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void onRetrieveItem(System::Object^ sender, System::Windows::Forms::RetrieveVirtualItemEventArgs^ e);
		System::Void optionsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmCloseAllSubwindows_Click(System::Object^  sender, System::EventArgs^  e);

		void OnClick(System::Object ^sender, System::EventArgs ^e);
		

		System::Void tsmDonate_Click(System::Object^  sender, System::EventArgs^  e);
		
		System::Void TsmFind_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void CmbFind_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);
		System::Void TsbFindUp_Click(System::Object ^ sender, System::EventArgs ^ e);
		System::Void TsbFindDown_Click(System::Object ^ sender, System::EventArgs ^ e);


}; // class FormMain

} // namespace clipdiff

