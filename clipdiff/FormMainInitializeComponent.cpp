// clipdiff.cpp : main project file.

#include "stdafx.h"
#include "FormMain.h"


namespace clipdiff {


	void FormMain::InitializeComponent(void)
	{
		System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FormMain::typeid));
		this->menuMain = (gcnew System::Windows::Forms::MenuStrip());
		this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->tsmSaveAs = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->tsmView = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->tsmShowToolbar = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->tsmShowStatusbar = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->tsmShowListheader = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->tsmEdit = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->tsmPaste = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripSeparator());
		this->tsmAddColumn = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->tsmRemoveColumn = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->tsmSepCopyTop = (gcnew System::Windows::Forms::ToolStripSeparator());
		this->optionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->tsmMonitorClipboard = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->tsmKeep = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->tsmIgnoreSame = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->toolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripSeparator());
		this->tsmEngineLevel = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->tsmELFast = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->tsmELMedium = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->tsmELSlow = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->toolStripMenuItem3 = (gcnew System::Windows::Forms::ToolStripSeparator());
		this->tsmFont = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->tsmWindow = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->tsmTopMost = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->tsmAbout = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->stMain = (gcnew System::Windows::Forms::StatusStrip());
		this->stlMain = (gcnew System::Windows::Forms::ToolStripStatusLabel());
		this->slChange = (gcnew System::Windows::Forms::ToolStripStatusLabel());
		this->stlResult = (gcnew System::Windows::Forms::ToolStripStatusLabel());
		this->panelClient = (gcnew System::Windows::Forms::Panel());
		this->toolMain = (gcnew System::Windows::Forms::ToolStrip());
		this->tsbMonitorClipboard = (gcnew System::Windows::Forms::ToolStripButton());
		this->tsbKeep = (gcnew System::Windows::Forms::ToolStripButton());
		this->tsbIgnoreSame = (gcnew System::Windows::Forms::ToolStripButton());
		this->tsbTopMost = (gcnew System::Windows::Forms::ToolStripButton());
		this->tsbPaste = (gcnew System::Windows::Forms::ToolStripButton());
		this->spRoot = (gcnew System::Windows::Forms::SplitContainer());
		this->toolStripMenuItem4 = (gcnew System::Windows::Forms::ToolStripSeparator());
		this->tsmDocdiff = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->menuMain->SuspendLayout();
		this->stMain->SuspendLayout();
		this->toolMain->SuspendLayout();
		this->spRoot->Panel1->SuspendLayout();
		this->spRoot->SuspendLayout();
		this->SuspendLayout();
		// 
		// menuMain
		// 
		this->menuMain->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->fileToolStripMenuItem, 
			this->tsmView, this->tsmEdit, this->optionToolStripMenuItem, this->tsmWindow, this->helpToolStripMenuItem});
		this->menuMain->Location = System::Drawing::Point(0, 0);
		this->menuMain->Name = L"menuMain";
		this->menuMain->Size = System::Drawing::Size(716, 24);
		this->menuMain->TabIndex = 0;
		this->menuMain->Text = L"menuStrip1";
		// 
		// fileToolStripMenuItem
		// 
		this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->tsmSaveAs, 
			this->exitToolStripMenuItem});
		this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
		this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
		this->fileToolStripMenuItem->Text = L"&File";
		// 
		// tsmSaveAs
		// 
		this->tsmSaveAs->Name = L"tsmSaveAs";
		this->tsmSaveAs->Size = System::Drawing::Size(123, 22);
		this->tsmSaveAs->Text = L"&Save As...";
		this->tsmSaveAs->Click += gcnew System::EventHandler(this, &FormMain::tsmSaveAs_Click);
		// 
		// exitToolStripMenuItem
		// 
		this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
		this->exitToolStripMenuItem->Size = System::Drawing::Size(123, 22);
		this->exitToolStripMenuItem->Text = L"&Exit";
		this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::exitToolStripMenuItem_Click);
		// 
		// tsmView
		// 
		this->tsmView->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->tsmShowToolbar, 
			this->tsmShowStatusbar, this->tsmShowListheader});
		this->tsmView->Name = L"tsmView";
		this->tsmView->Size = System::Drawing::Size(44, 20);
		this->tsmView->Text = L"&View";
		this->tsmView->DropDownOpening += gcnew System::EventHandler(this, &FormMain::tsmView_DropDownOpening);
		// 
		// tsmShowToolbar
		// 
		this->tsmShowToolbar->Name = L"tsmShowToolbar";
		this->tsmShowToolbar->Size = System::Drawing::Size(130, 22);
		this->tsmShowToolbar->Text = L"&Toolbar";
		this->tsmShowToolbar->Click += gcnew System::EventHandler(this, &FormMain::tsmShowToolbar_Click);
		// 
		// tsmShowStatusbar
		// 
		this->tsmShowStatusbar->Name = L"tsmShowStatusbar";
		this->tsmShowStatusbar->Size = System::Drawing::Size(130, 22);
		this->tsmShowStatusbar->Text = L"&Statusbar";
		this->tsmShowStatusbar->Click += gcnew System::EventHandler(this, &FormMain::tsmShowStatusbar_Click);
		// 
		// tsmShowListheader
		// 
		this->tsmShowListheader->Name = L"tsmShowListheader";
		this->tsmShowListheader->Size = System::Drawing::Size(130, 22);
		this->tsmShowListheader->Text = L"ListHeader";
		this->tsmShowListheader->Click += gcnew System::EventHandler(this, &FormMain::tsmShowListheader_Click);
		// 
		// tsmEdit
		// 
		this->tsmEdit->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->tsmPaste, this->toolStripMenuItem1, 
			this->tsmAddColumn, this->tsmRemoveColumn, this->tsmSepCopyTop});
		this->tsmEdit->Name = L"tsmEdit";
		this->tsmEdit->Size = System::Drawing::Size(39, 20);
		this->tsmEdit->Text = L"&Edit";
		this->tsmEdit->DropDownOpening += gcnew System::EventHandler(this, &FormMain::tsmEdit_DropDownOpening);
		// 
		// tsmPaste
		// 
		this->tsmPaste->Name = L"tsmPaste";
		this->tsmPaste->Size = System::Drawing::Size(160, 22);
		this->tsmPaste->Text = L"&Paste";
		this->tsmPaste->Click += gcnew System::EventHandler(this, &FormMain::tsmPaste_Click);
		// 
		// toolStripMenuItem1
		// 
		this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
		this->toolStripMenuItem1->Size = System::Drawing::Size(157, 6);
		// 
		// tsmAddColumn
		// 
		this->tsmAddColumn->Name = L"tsmAddColumn";
		this->tsmAddColumn->Size = System::Drawing::Size(160, 22);
		this->tsmAddColumn->Text = L"&Add Column";
		this->tsmAddColumn->Click += gcnew System::EventHandler(this, &FormMain::tsmAddColumn_Click);
		// 
		// tsmRemoveColumn
		// 
		this->tsmRemoveColumn->Name = L"tsmRemoveColumn";
		this->tsmRemoveColumn->Size = System::Drawing::Size(160, 22);
		this->tsmRemoveColumn->Text = L"&Remove Column";
		this->tsmRemoveColumn->Click += gcnew System::EventHandler(this, &FormMain::tsmRemoveColumn_Click);
		// 
		// tsmSepCopyTop
		// 
		this->tsmSepCopyTop->Name = L"tsmSepCopyTop";
		this->tsmSepCopyTop->Size = System::Drawing::Size(157, 6);
		// 
		// optionToolStripMenuItem
		// 
		this->optionToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {this->tsmMonitorClipboard, 
			this->tsmKeep, this->tsmIgnoreSame, this->toolStripMenuItem2, this->tsmEngineLevel, this->toolStripMenuItem3, this->tsmFont});
		this->optionToolStripMenuItem->Name = L"optionToolStripMenuItem";
		this->optionToolStripMenuItem->Size = System::Drawing::Size(56, 20);
		this->optionToolStripMenuItem->Text = L"&Option";
		// 
		// tsmMonitorClipboard
		// 
		this->tsmMonitorClipboard->Name = L"tsmMonitorClipboard";
		this->tsmMonitorClipboard->Size = System::Drawing::Size(186, 22);
		this->tsmMonitorClipboard->Text = L"📋 &Monitor Clipboard";
		this->tsmMonitorClipboard->Click += gcnew System::EventHandler(this, &FormMain::tsmMonitorClipboard_Click);
		// 
		// tsmKeep
		// 
		this->tsmKeep->Name = L"tsmKeep";
		this->tsmKeep->Size = System::Drawing::Size(186, 22);
		this->tsmKeep->Text = L"📌 &KeepLeft";
		this->tsmKeep->Click += gcnew System::EventHandler(this, &FormMain::tsmKeep_Click);
		// 
		// tsmIgnoreSame
		// 
		this->tsmIgnoreSame->Name = L"tsmIgnoreSame";
		this->tsmIgnoreSame->Size = System::Drawing::Size(186, 22);
		this->tsmIgnoreSame->Text = L"↔️ &Ignore Same";
		this->tsmIgnoreSame->Click += gcnew System::EventHandler(this, &FormMain::tsmIgnoreSame_Click);
		// 
		// toolStripMenuItem2
		// 
		this->toolStripMenuItem2->Name = L"toolStripMenuItem2";
		this->toolStripMenuItem2->Size = System::Drawing::Size(183, 6);
		// 
		// tsmEngineLevel
		// 
		this->tsmEngineLevel->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->tsmELFast, 
			this->tsmELMedium, this->tsmELSlow, this->toolStripMenuItem4, this->tsmDocdiff});
		this->tsmEngineLevel->Name = L"tsmEngineLevel";
		this->tsmEngineLevel->Size = System::Drawing::Size(186, 22);
		this->tsmEngineLevel->Text = L"&Engine Level";
		this->tsmEngineLevel->DropDownOpening += gcnew System::EventHandler(this, &FormMain::tsmEngineLevel_DropDownOpening);
		// 
		// tsmELFast
		// 
		this->tsmELFast->Name = L"tsmELFast";
		this->tsmELFast->Size = System::Drawing::Size(152, 22);
		this->tsmELFast->Text = L"&FastImperfect";
		this->tsmELFast->Click += gcnew System::EventHandler(this, &FormMain::tsmELFast_Click);
		// 
		// tsmELMedium
		// 
		this->tsmELMedium->Name = L"tsmELMedium";
		this->tsmELMedium->Size = System::Drawing::Size(152, 22);
		this->tsmELMedium->Text = L"&Medium";
		this->tsmELMedium->Click += gcnew System::EventHandler(this, &FormMain::tsmELMedium_Click);
		// 
		// tsmELSlow
		// 
		this->tsmELSlow->Name = L"tsmELSlow";
		this->tsmELSlow->Size = System::Drawing::Size(152, 22);
		this->tsmELSlow->Text = L"&SlowPerfect";
		this->tsmELSlow->Click += gcnew System::EventHandler(this, &FormMain::tsmELSlow_Click);
		// 
		// toolStripMenuItem3
		// 
		this->toolStripMenuItem3->Name = L"toolStripMenuItem3";
		this->toolStripMenuItem3->Size = System::Drawing::Size(183, 6);
		// 
		// tsmFont
		// 
		this->tsmFont->Name = L"tsmFont";
		this->tsmFont->Size = System::Drawing::Size(186, 22);
		this->tsmFont->Text = L"&Font...";
		this->tsmFont->Click += gcnew System::EventHandler(this, &FormMain::tsmFont_Click);
		// 
		// tsmWindow
		// 
		this->tsmWindow->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->tsmTopMost});
		this->tsmWindow->Name = L"tsmWindow";
		this->tsmWindow->Size = System::Drawing::Size(63, 20);
		this->tsmWindow->Text = L"&Window";
		this->tsmWindow->DropDownOpening += gcnew System::EventHandler(this, &FormMain::tsmWindow_DropDownOpening);
		// 
		// tsmTopMost
		// 
		this->tsmTopMost->Name = L"tsmTopMost";
		this->tsmTopMost->Size = System::Drawing::Size(138, 22);
		this->tsmTopMost->Text = L"💳 &Top Most";
		this->tsmTopMost->Click += gcnew System::EventHandler(this, &FormMain::onTopMost);
		// 
		// helpToolStripMenuItem
		// 
		this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->tsmAbout});
		this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
		this->helpToolStripMenuItem->Size = System::Drawing::Size(44, 20);
		this->helpToolStripMenuItem->Text = L"&Help";
		// 
		// tsmAbout
		// 
		this->tsmAbout->Name = L"tsmAbout";
		this->tsmAbout->Size = System::Drawing::Size(116, 22);
		this->tsmAbout->Text = L"&About...";
		this->tsmAbout->Click += gcnew System::EventHandler(this, &FormMain::tsmAbout_Click);
		// 
		// stMain
		// 
		this->stMain->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->stlMain, this->slChange, 
			this->stlResult});
		this->stMain->Location = System::Drawing::Point(0, 423);
		this->stMain->Name = L"stMain";
		this->stMain->Size = System::Drawing::Size(716, 22);
		this->stMain->TabIndex = 4;
		this->stMain->VisibleChanged += gcnew System::EventHandler(this, &FormMain::stMain_VisibleChanged);
		// 
		// stlMain
		// 
		this->stlMain->Name = L"stlMain";
		this->stlMain->Size = System::Drawing::Size(701, 17);
		this->stlMain->Spring = true;
		// 
		// slChange
		// 
		this->slChange->Name = L"slChange";
		this->slChange->Size = System::Drawing::Size(0, 17);
		// 
		// stlResult
		// 
		this->stlResult->Name = L"stlResult";
		this->stlResult->Size = System::Drawing::Size(0, 17);
		// 
		// panelClient
		// 
		this->panelClient->Dock = System::Windows::Forms::DockStyle::Fill;
		this->panelClient->ForeColor = System::Drawing::Color::Black;
		this->panelClient->Location = System::Drawing::Point(0, 0);
		this->panelClient->Margin = System::Windows::Forms::Padding(0);
		this->panelClient->Name = L"panelClient";
		this->panelClient->Size = System::Drawing::Size(716, 374);
		this->panelClient->TabIndex = 5;
		// 
		// toolMain
		// 
		this->toolMain->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
		this->toolMain->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->tsbMonitorClipboard, 
			this->tsbKeep, this->tsbIgnoreSame, this->tsbTopMost, this->tsbPaste});
		this->toolMain->Location = System::Drawing::Point(0, 24);
		this->toolMain->Name = L"toolMain";
		this->toolMain->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
		this->toolMain->Size = System::Drawing::Size(716, 25);
		this->toolMain->TabIndex = 0;
		this->toolMain->VisibleChanged += gcnew System::EventHandler(this, &FormMain::toolMain_VisibleChanged);
		// 
		// tsbMonitorClipboard
		// 
		this->tsbMonitorClipboard->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
		this->tsbMonitorClipboard->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsbMonitorClipboard.Image")));
		this->tsbMonitorClipboard->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->tsbMonitorClipboard->Name = L"tsbMonitorClipboard";
		this->tsbMonitorClipboard->Size = System::Drawing::Size(23, 22);
		this->tsbMonitorClipboard->Text = L"📋";
		this->tsbMonitorClipboard->ToolTipText = L"Monitor Clipboard";
		this->tsbMonitorClipboard->Click += gcnew System::EventHandler(this, &FormMain::tsbMonitorClipboard_Click);
		// 
		// tsbKeep
		// 
		this->tsbKeep->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
		this->tsbKeep->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsbKeep.Image")));
		this->tsbKeep->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->tsbKeep->Name = L"tsbKeep";
		this->tsbKeep->Size = System::Drawing::Size(23, 22);
		this->tsbKeep->Text = L"📌";
		this->tsbKeep->ToolTipText = L"Keep Left";
		this->tsbKeep->Click += gcnew System::EventHandler(this, &FormMain::tsbKeep_Click);
		// 
		// tsbIgnoreSame
		// 
		this->tsbIgnoreSame->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
		this->tsbIgnoreSame->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsbIgnoreSame.Image")));
		this->tsbIgnoreSame->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->tsbIgnoreSame->Name = L"tsbIgnoreSame";
		this->tsbIgnoreSame->Size = System::Drawing::Size(23, 22);
		this->tsbIgnoreSame->Text = L"↔️";
		this->tsbIgnoreSame->ToolTipText = L"Ignore Same";
		this->tsbIgnoreSame->Click += gcnew System::EventHandler(this, &FormMain::tsbIgnoreSame_Click);
		// 
		// tsbTopMost
		// 
		this->tsbTopMost->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
		this->tsbTopMost->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsbTopMost.Image")));
		this->tsbTopMost->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->tsbTopMost->Name = L"tsbTopMost";
		this->tsbTopMost->Size = System::Drawing::Size(23, 22);
		this->tsbTopMost->Text = L"💳";
		this->tsbTopMost->ToolTipText = L"Top Most";
		this->tsbTopMost->Click += gcnew System::EventHandler(this, &FormMain::onTopMost);
		// 
		// tsbPaste
		// 
		this->tsbPaste->AutoSize = false;
		this->tsbPaste->BackColor = System::Drawing::Color::LightYellow;
		this->tsbPaste->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
		this->tsbPaste->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
			static_cast<System::Byte>(128)));
		this->tsbPaste->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsbPaste.Image")));
		this->tsbPaste->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
		this->tsbPaste->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->tsbPaste->Name = L"tsbPaste";
		this->tsbPaste->Size = System::Drawing::Size(60, 22);
		this->tsbPaste->Text = L"Paste";
		this->tsbPaste->Click += gcnew System::EventHandler(this, &FormMain::tsbPaste_Click);
		// 
		// spRoot
		// 
		this->spRoot->Dock = System::Windows::Forms::DockStyle::Fill;
		this->spRoot->Location = System::Drawing::Point(0, 49);
		this->spRoot->Name = L"spRoot";
		// 
		// spRoot.Panel1
		// 
		this->spRoot->Panel1->Controls->Add(this->panelClient);
		this->spRoot->Panel2Collapsed = true;
		this->spRoot->Size = System::Drawing::Size(716, 374);
		this->spRoot->SplitterDistance = 238;
		this->spRoot->TabIndex = 6;
		// 
		// toolStripMenuItem4
		// 
		this->toolStripMenuItem4->Name = L"toolStripMenuItem4";
		this->toolStripMenuItem4->Size = System::Drawing::Size(149, 6);
		// 
		// tsmDocdiff
		// 
		this->tsmDocdiff->Name = L"tsmDocdiff";
		this->tsmDocdiff->Size = System::Drawing::Size(152, 22);
		this->tsmDocdiff->Text = L"&docdiff";
		this->tsmDocdiff->Click += gcnew System::EventHandler(this, &FormMain::tsmDocdiff_Click);
		// 
		// FormMain
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(716, 445);
		this->Controls->Add(this->spRoot);
		this->Controls->Add(this->toolMain);
		this->Controls->Add(this->stMain);
		this->Controls->Add(this->menuMain);
		this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
		this->MainMenuStrip = this->menuMain;
		this->Name = L"FormMain";
		this->Load += gcnew System::EventHandler(this, &FormMain::FormMain_Load);
		this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &FormMain::FormMain_FormClosed);
		this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &FormMain::FormMain_FormClosing);
		this->menuMain->ResumeLayout(false);
		this->menuMain->PerformLayout();
		this->stMain->ResumeLayout(false);
		this->stMain->PerformLayout();
		this->toolMain->ResumeLayout(false);
		this->toolMain->PerformLayout();
		this->spRoot->Panel1->ResumeLayout(false);
		this->spRoot->ResumeLayout(false);
		this->ResumeLayout(false);
		this->PerformLayout();

	}

}

