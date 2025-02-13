﻿// clipdiff.cpp : main project file.

#include "stdafx.h"
#include "FormMain.h"


namespace clipdiff {


	void FormMain::InitializeComponent(void)
	{
        this->components = (gcnew System::ComponentModel::Container());
        System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(FormMain::typeid));
        this->spRoot = (gcnew System::Windows::Forms::SplitContainer());
        this->panelClient = (gcnew System::Windows::Forms::Panel());
        this->menuMain = (gcnew System::Windows::Forms::MenuStrip());
        this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->tsmSaveAs = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->tsmView = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->tsmShowToolbar = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->tsmShowStatusbar = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->tsmShowListheader = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->toolStripMenuItem5 = (gcnew System::Windows::Forms::ToolStripSeparator());
        this->goToPrevDiffLineToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->goToNextDiffLineToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->toolStripMenuItem8 = (gcnew System::Windows::Forms::ToolStripSeparator());
        this->tsmFindPrev = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->tsmFindNext = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->tsmEdit = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->tsmCopy = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->tsmPaste = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->tsmClear = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripSeparator());
        this->tsmAddColumn = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->tsmRemoveColumn = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->tsmSepCopyTop = (gcnew System::Windows::Forms::ToolStripSeparator());
        this->tsmFind = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->toolsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->tsmMonitorClipboard = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->tsmKeep = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->tsmIgnoreSame = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->toolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripSeparator());
        this->tsmEngineLevel = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->tsmELFast = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->tsmELMedium = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->tsmELSlow = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->toolStripMenuItem4 = (gcnew System::Windows::Forms::ToolStripSeparator());
        this->tsmDocdiffChar = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->tsmDocdiffWord = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->toolStripMenuItem3 = (gcnew System::Windows::Forms::ToolStripSeparator());
        this->tsmFont = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->toolStripMenuItem6 = (gcnew System::Windows::Forms::ToolStripSeparator());
        this->optionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->tsmWindow = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->tsmTopMost = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->toolStripMenuItem7 = (gcnew System::Windows::Forms::ToolStripSeparator());
        this->tsmCloseAllSubwindows = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->tsmAbout = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->tsmGotoWebpage = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->tsmDonate = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->stMain = (gcnew System::Windows::Forms::StatusStrip());
        this->stlMain = (gcnew System::Windows::Forms::ToolStripStatusLabel());
        this->slChange = (gcnew System::Windows::Forms::ToolStripStatusLabel());
        this->stlResult = (gcnew System::Windows::Forms::ToolStripStatusLabel());
        this->toolMain = (gcnew Ambiesoft::ClickThroughToolStrip());
        this->tsbMonitorClipboard = (gcnew System::Windows::Forms::ToolStripButton());
        this->tsbKeep = (gcnew System::Windows::Forms::ToolStripButton());
        this->tsbIgnoreSame = (gcnew System::Windows::Forms::ToolStripButton());
        this->tsbTopMost = (gcnew System::Windows::Forms::ToolStripButton());
        this->tsbPaste = (gcnew System::Windows::Forms::ToolStripButton());
        this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
        this->cmbFind = (gcnew System::Windows::Forms::ToolStripComboBox());
        this->tsbFindUp = (gcnew System::Windows::Forms::ToolStripButton());
        this->tsbFindDown = (gcnew System::Windows::Forms::ToolStripButton());
        this->ctxMenuList = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
        this->tsmCompareThisLineWithDocdiffChar = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->tsmCompareThisLineWithDocdiffword = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->toolStripMenuItem9 = (gcnew System::Windows::Forms::ToolStripSeparator());
        this->tsmiCopyItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->spRoot))->BeginInit();
        this->spRoot->Panel1->SuspendLayout();
        this->spRoot->SuspendLayout();
        this->menuMain->SuspendLayout();
        this->stMain->SuspendLayout();
        this->toolMain->SuspendLayout();
        this->ctxMenuList->SuspendLayout();
        this->SuspendLayout();
        // 
        // spRoot
        // 
        resources->ApplyResources(this->spRoot, L"spRoot");
        this->spRoot->Name = L"spRoot";
        // 
        // spRoot.Panel1
        // 
        resources->ApplyResources(this->spRoot->Panel1, L"spRoot.Panel1");
        this->spRoot->Panel1->Controls->Add(this->panelClient);
        // 
        // spRoot.Panel2
        // 
        resources->ApplyResources(this->spRoot->Panel2, L"spRoot.Panel2");
        this->spRoot->Panel2->Resize += gcnew System::EventHandler(this, &FormMain::spRoot_Panel2_Resize);
        this->spRoot->Panel2Collapsed = true;
        // 
        // panelClient
        // 
        resources->ApplyResources(this->panelClient, L"panelClient");
        this->panelClient->ForeColor = System::Drawing::Color::Black;
        this->panelClient->Name = L"panelClient";
        // 
        // menuMain
        // 
        resources->ApplyResources(this->menuMain, L"menuMain");
        this->menuMain->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
            this->fileToolStripMenuItem,
                this->tsmView, this->tsmEdit, this->toolsToolStripMenuItem, this->tsmWindow, this->helpToolStripMenuItem
        });
        this->menuMain->Name = L"menuMain";
        // 
        // fileToolStripMenuItem
        // 
        resources->ApplyResources(this->fileToolStripMenuItem, L"fileToolStripMenuItem");
        this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
            this->tsmSaveAs,
                this->exitToolStripMenuItem
        });
        this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
        // 
        // tsmSaveAs
        // 
        resources->ApplyResources(this->tsmSaveAs, L"tsmSaveAs");
        this->tsmSaveAs->Name = L"tsmSaveAs";
        this->tsmSaveAs->Click += gcnew System::EventHandler(this, &FormMain::tsmSaveAs_Click);
        // 
        // exitToolStripMenuItem
        // 
        resources->ApplyResources(this->exitToolStripMenuItem, L"exitToolStripMenuItem");
        this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
        this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::exitToolStripMenuItem_Click);
        // 
        // tsmView
        // 
        resources->ApplyResources(this->tsmView, L"tsmView");
        this->tsmView->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(9) {
            this->tsmShowToolbar,
                this->tsmShowStatusbar, this->tsmShowListheader, this->toolStripMenuItem5, this->goToPrevDiffLineToolStripMenuItem, this->goToNextDiffLineToolStripMenuItem,
                this->toolStripMenuItem8, this->tsmFindPrev, this->tsmFindNext
        });
        this->tsmView->Name = L"tsmView";
        this->tsmView->DropDownOpening += gcnew System::EventHandler(this, &FormMain::tsmView_DropDownOpening);
        // 
        // tsmShowToolbar
        // 
        resources->ApplyResources(this->tsmShowToolbar, L"tsmShowToolbar");
        this->tsmShowToolbar->Name = L"tsmShowToolbar";
        this->tsmShowToolbar->Click += gcnew System::EventHandler(this, &FormMain::tsmShowToolbar_Click);
        // 
        // tsmShowStatusbar
        // 
        resources->ApplyResources(this->tsmShowStatusbar, L"tsmShowStatusbar");
        this->tsmShowStatusbar->Name = L"tsmShowStatusbar";
        this->tsmShowStatusbar->Click += gcnew System::EventHandler(this, &FormMain::tsmShowStatusbar_Click);
        // 
        // tsmShowListheader
        // 
        resources->ApplyResources(this->tsmShowListheader, L"tsmShowListheader");
        this->tsmShowListheader->Name = L"tsmShowListheader";
        this->tsmShowListheader->Click += gcnew System::EventHandler(this, &FormMain::tsmShowListheader_Click);
        // 
        // toolStripMenuItem5
        // 
        resources->ApplyResources(this->toolStripMenuItem5, L"toolStripMenuItem5");
        this->toolStripMenuItem5->Name = L"toolStripMenuItem5";
        // 
        // goToPrevDiffLineToolStripMenuItem
        // 
        resources->ApplyResources(this->goToPrevDiffLineToolStripMenuItem, L"goToPrevDiffLineToolStripMenuItem");
        this->goToPrevDiffLineToolStripMenuItem->Name = L"goToPrevDiffLineToolStripMenuItem";
        this->goToPrevDiffLineToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::goToPrevDiffLineToolStripMenuItem_Click);
        // 
        // goToNextDiffLineToolStripMenuItem
        // 
        resources->ApplyResources(this->goToNextDiffLineToolStripMenuItem, L"goToNextDiffLineToolStripMenuItem");
        this->goToNextDiffLineToolStripMenuItem->Name = L"goToNextDiffLineToolStripMenuItem";
        this->goToNextDiffLineToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::goToNextDiffLineToolStripMenuItem_Click);
        // 
        // toolStripMenuItem8
        // 
        resources->ApplyResources(this->toolStripMenuItem8, L"toolStripMenuItem8");
        this->toolStripMenuItem8->Name = L"toolStripMenuItem8";
        // 
        // tsmFindPrev
        // 
        resources->ApplyResources(this->tsmFindPrev, L"tsmFindPrev");
        this->tsmFindPrev->Name = L"tsmFindPrev";
        this->tsmFindPrev->Click += gcnew System::EventHandler(this, &FormMain::TsbFindUp_Click);
        // 
        // tsmFindNext
        // 
        resources->ApplyResources(this->tsmFindNext, L"tsmFindNext");
        this->tsmFindNext->Name = L"tsmFindNext";
        this->tsmFindNext->Click += gcnew System::EventHandler(this, &FormMain::TsbFindDown_Click);
        // 
        // tsmEdit
        // 
        resources->ApplyResources(this->tsmEdit, L"tsmEdit");
        this->tsmEdit->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(8) {
            this->tsmCopy, this->tsmPaste,
                this->tsmClear, this->toolStripMenuItem1, this->tsmAddColumn, this->tsmRemoveColumn, this->tsmSepCopyTop, this->tsmFind
        });
        this->tsmEdit->Name = L"tsmEdit";
        this->tsmEdit->DropDownOpening += gcnew System::EventHandler(this, &FormMain::tsmEdit_DropDownOpening);
        // 
        // tsmCopy
        // 
        resources->ApplyResources(this->tsmCopy, L"tsmCopy");
        this->tsmCopy->Name = L"tsmCopy";
        this->tsmCopy->Click += gcnew System::EventHandler(this, &FormMain::tsmCopy_Click);
        // 
        // tsmPaste
        // 
        resources->ApplyResources(this->tsmPaste, L"tsmPaste");
        this->tsmPaste->Name = L"tsmPaste";
        this->tsmPaste->Click += gcnew System::EventHandler(this, &FormMain::tsmPaste_Click);
        // 
        // tsmClear
        // 
        resources->ApplyResources(this->tsmClear, L"tsmClear");
        this->tsmClear->Name = L"tsmClear";
        this->tsmClear->Click += gcnew System::EventHandler(this, &FormMain::tsmClear_Click);
        // 
        // toolStripMenuItem1
        // 
        resources->ApplyResources(this->toolStripMenuItem1, L"toolStripMenuItem1");
        this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
        // 
        // tsmAddColumn
        // 
        resources->ApplyResources(this->tsmAddColumn, L"tsmAddColumn");
        this->tsmAddColumn->Name = L"tsmAddColumn";
        this->tsmAddColumn->Click += gcnew System::EventHandler(this, &FormMain::tsmAddColumn_Click);
        // 
        // tsmRemoveColumn
        // 
        resources->ApplyResources(this->tsmRemoveColumn, L"tsmRemoveColumn");
        this->tsmRemoveColumn->Name = L"tsmRemoveColumn";
        this->tsmRemoveColumn->Click += gcnew System::EventHandler(this, &FormMain::tsmRemoveColumn_Click);
        // 
        // tsmSepCopyTop
        // 
        resources->ApplyResources(this->tsmSepCopyTop, L"tsmSepCopyTop");
        this->tsmSepCopyTop->Name = L"tsmSepCopyTop";
        // 
        // tsmFind
        // 
        resources->ApplyResources(this->tsmFind, L"tsmFind");
        this->tsmFind->Name = L"tsmFind";
        this->tsmFind->Click += gcnew System::EventHandler(this, &FormMain::TsmFind_Click);
        // 
        // toolsToolStripMenuItem
        // 
        resources->ApplyResources(this->toolsToolStripMenuItem, L"toolsToolStripMenuItem");
        this->toolsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(9) {
            this->tsmMonitorClipboard,
                this->tsmKeep, this->tsmIgnoreSame, this->toolStripMenuItem2, this->tsmEngineLevel, this->toolStripMenuItem3, this->tsmFont,
                this->toolStripMenuItem6, this->optionsToolStripMenuItem
        });
        this->toolsToolStripMenuItem->Name = L"toolsToolStripMenuItem";
        // 
        // tsmMonitorClipboard
        // 
        resources->ApplyResources(this->tsmMonitorClipboard, L"tsmMonitorClipboard");
        this->tsmMonitorClipboard->Name = L"tsmMonitorClipboard";
        this->tsmMonitorClipboard->Click += gcnew System::EventHandler(this, &FormMain::tsmMonitorClipboard_Click);
        // 
        // tsmKeep
        // 
        resources->ApplyResources(this->tsmKeep, L"tsmKeep");
        this->tsmKeep->Name = L"tsmKeep";
        this->tsmKeep->Click += gcnew System::EventHandler(this, &FormMain::tsmKeep_Click);
        // 
        // tsmIgnoreSame
        // 
        resources->ApplyResources(this->tsmIgnoreSame, L"tsmIgnoreSame");
        this->tsmIgnoreSame->Name = L"tsmIgnoreSame";
        this->tsmIgnoreSame->Click += gcnew System::EventHandler(this, &FormMain::tsmIgnoreSame_Click);
        // 
        // toolStripMenuItem2
        // 
        resources->ApplyResources(this->toolStripMenuItem2, L"toolStripMenuItem2");
        this->toolStripMenuItem2->Name = L"toolStripMenuItem2";
        // 
        // tsmEngineLevel
        // 
        resources->ApplyResources(this->tsmEngineLevel, L"tsmEngineLevel");
        this->tsmEngineLevel->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
            this->tsmELFast,
                this->tsmELMedium, this->tsmELSlow, this->toolStripMenuItem4, this->tsmDocdiffChar, this->tsmDocdiffWord
        });
        this->tsmEngineLevel->Name = L"tsmEngineLevel";
        this->tsmEngineLevel->DropDownOpening += gcnew System::EventHandler(this, &FormMain::tsmEngineLevel_DropDownOpening);
        // 
        // tsmELFast
        // 
        resources->ApplyResources(this->tsmELFast, L"tsmELFast");
        this->tsmELFast->Name = L"tsmELFast";
        this->tsmELFast->Click += gcnew System::EventHandler(this, &FormMain::tsmELFast_Click);
        // 
        // tsmELMedium
        // 
        resources->ApplyResources(this->tsmELMedium, L"tsmELMedium");
        this->tsmELMedium->Name = L"tsmELMedium";
        this->tsmELMedium->Click += gcnew System::EventHandler(this, &FormMain::tsmELMedium_Click);
        // 
        // tsmELSlow
        // 
        resources->ApplyResources(this->tsmELSlow, L"tsmELSlow");
        this->tsmELSlow->Name = L"tsmELSlow";
        this->tsmELSlow->Click += gcnew System::EventHandler(this, &FormMain::tsmELSlow_Click);
        // 
        // toolStripMenuItem4
        // 
        resources->ApplyResources(this->toolStripMenuItem4, L"toolStripMenuItem4");
        this->toolStripMenuItem4->Name = L"toolStripMenuItem4";
        // 
        // tsmDocdiffChar
        // 
        resources->ApplyResources(this->tsmDocdiffChar, L"tsmDocdiffChar");
        this->tsmDocdiffChar->Name = L"tsmDocdiffChar";
        this->tsmDocdiffChar->Click += gcnew System::EventHandler(this, &FormMain::tsmDocdiffChar_Click);
        // 
        // tsmDocdiffWord
        // 
        resources->ApplyResources(this->tsmDocdiffWord, L"tsmDocdiffWord");
        this->tsmDocdiffWord->Name = L"tsmDocdiffWord";
        this->tsmDocdiffWord->Click += gcnew System::EventHandler(this, &FormMain::tsmDocdiffWord_Click);
        // 
        // toolStripMenuItem3
        // 
        resources->ApplyResources(this->toolStripMenuItem3, L"toolStripMenuItem3");
        this->toolStripMenuItem3->Name = L"toolStripMenuItem3";
        // 
        // tsmFont
        // 
        resources->ApplyResources(this->tsmFont, L"tsmFont");
        this->tsmFont->Name = L"tsmFont";
        this->tsmFont->Click += gcnew System::EventHandler(this, &FormMain::tsmFont_Click);
        // 
        // toolStripMenuItem6
        // 
        resources->ApplyResources(this->toolStripMenuItem6, L"toolStripMenuItem6");
        this->toolStripMenuItem6->Name = L"toolStripMenuItem6";
        // 
        // optionsToolStripMenuItem
        // 
        resources->ApplyResources(this->optionsToolStripMenuItem, L"optionsToolStripMenuItem");
        this->optionsToolStripMenuItem->Name = L"optionsToolStripMenuItem";
        this->optionsToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::optionsToolStripMenuItem_Click);
        // 
        // tsmWindow
        // 
        resources->ApplyResources(this->tsmWindow, L"tsmWindow");
        this->tsmWindow->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
            this->tsmTopMost,
                this->toolStripMenuItem7, this->tsmCloseAllSubwindows
        });
        this->tsmWindow->Name = L"tsmWindow";
        this->tsmWindow->DropDownOpening += gcnew System::EventHandler(this, &FormMain::tsmWindow_DropDownOpening);
        // 
        // tsmTopMost
        // 
        resources->ApplyResources(this->tsmTopMost, L"tsmTopMost");
        this->tsmTopMost->Name = L"tsmTopMost";
        this->tsmTopMost->Click += gcnew System::EventHandler(this, &FormMain::onTopMost);
        // 
        // toolStripMenuItem7
        // 
        resources->ApplyResources(this->toolStripMenuItem7, L"toolStripMenuItem7");
        this->toolStripMenuItem7->Name = L"toolStripMenuItem7";
        // 
        // tsmCloseAllSubwindows
        // 
        resources->ApplyResources(this->tsmCloseAllSubwindows, L"tsmCloseAllSubwindows");
        this->tsmCloseAllSubwindows->Name = L"tsmCloseAllSubwindows";
        this->tsmCloseAllSubwindows->Click += gcnew System::EventHandler(this, &FormMain::tsmCloseAllSubwindows_Click);
        // 
        // helpToolStripMenuItem
        // 
        resources->ApplyResources(this->helpToolStripMenuItem, L"helpToolStripMenuItem");
        this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
            this->tsmAbout,
                this->tsmGotoWebpage, this->tsmDonate
        });
        this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
        // 
        // tsmAbout
        // 
        resources->ApplyResources(this->tsmAbout, L"tsmAbout");
        this->tsmAbout->Name = L"tsmAbout";
        this->tsmAbout->Click += gcnew System::EventHandler(this, &FormMain::tsmAbout_Click);
        // 
        // tsmGotoWebpage
        // 
        resources->ApplyResources(this->tsmGotoWebpage, L"tsmGotoWebpage");
        this->tsmGotoWebpage->Name = L"tsmGotoWebpage";
        this->tsmGotoWebpage->Click += gcnew System::EventHandler(this, &FormMain::tsmGotoWebpage_Click);
        // 
        // tsmDonate
        // 
        resources->ApplyResources(this->tsmDonate, L"tsmDonate");
        this->tsmDonate->Name = L"tsmDonate";
        this->tsmDonate->Click += gcnew System::EventHandler(this, &FormMain::tsmDonate_Click);
        // 
        // stMain
        // 
        resources->ApplyResources(this->stMain, L"stMain");
        this->stMain->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
            this->stlMain, this->slChange,
                this->stlResult
        });
        this->stMain->Name = L"stMain";
        this->stMain->VisibleChanged += gcnew System::EventHandler(this, &FormMain::stMain_VisibleChanged);
        // 
        // stlMain
        // 
        resources->ApplyResources(this->stlMain, L"stlMain");
        this->stlMain->Name = L"stlMain";
        this->stlMain->Spring = true;
        // 
        // slChange
        // 
        resources->ApplyResources(this->slChange, L"slChange");
        this->slChange->Name = L"slChange";
        // 
        // stlResult
        // 
        resources->ApplyResources(this->stlResult, L"stlResult");
        this->stlResult->Name = L"stlResult";
        // 
        // toolMain
        // 
        resources->ApplyResources(this->toolMain, L"toolMain");
        this->toolMain->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
        this->toolMain->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(9) {
            this->tsbMonitorClipboard,
                this->tsbKeep, this->tsbIgnoreSame, this->tsbTopMost, this->tsbPaste, this->toolStripSeparator1, this->cmbFind, this->tsbFindUp,
                this->tsbFindDown
        });
        this->toolMain->Name = L"toolMain";
        this->toolMain->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
        this->toolMain->VisibleChanged += gcnew System::EventHandler(this, &FormMain::toolMain_VisibleChanged);
        // 
        // tsbMonitorClipboard
        // 
        resources->ApplyResources(this->tsbMonitorClipboard, L"tsbMonitorClipboard");
        this->tsbMonitorClipboard->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
        this->tsbMonitorClipboard->Name = L"tsbMonitorClipboard";
        this->tsbMonitorClipboard->Click += gcnew System::EventHandler(this, &FormMain::tsbMonitorClipboard_Click);
        // 
        // tsbKeep
        // 
        resources->ApplyResources(this->tsbKeep, L"tsbKeep");
        this->tsbKeep->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
        this->tsbKeep->Name = L"tsbKeep";
        this->tsbKeep->Click += gcnew System::EventHandler(this, &FormMain::tsbKeep_Click);
        // 
        // tsbIgnoreSame
        // 
        resources->ApplyResources(this->tsbIgnoreSame, L"tsbIgnoreSame");
        this->tsbIgnoreSame->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
        this->tsbIgnoreSame->Name = L"tsbIgnoreSame";
        this->tsbIgnoreSame->Click += gcnew System::EventHandler(this, &FormMain::tsbIgnoreSame_Click);
        // 
        // tsbTopMost
        // 
        resources->ApplyResources(this->tsbTopMost, L"tsbTopMost");
        this->tsbTopMost->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
        this->tsbTopMost->Name = L"tsbTopMost";
        this->tsbTopMost->Click += gcnew System::EventHandler(this, &FormMain::onTopMost);
        // 
        // tsbPaste
        // 
        resources->ApplyResources(this->tsbPaste, L"tsbPaste");
        this->tsbPaste->BackColor = System::Drawing::Color::LightYellow;
        this->tsbPaste->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
        this->tsbPaste->Name = L"tsbPaste";
        this->tsbPaste->Click += gcnew System::EventHandler(this, &FormMain::tsbPaste_Click);
        // 
        // toolStripSeparator1
        // 
        resources->ApplyResources(this->toolStripSeparator1, L"toolStripSeparator1");
        this->toolStripSeparator1->Name = L"toolStripSeparator1";
        // 
        // cmbFind
        // 
        resources->ApplyResources(this->cmbFind, L"cmbFind");
        this->cmbFind->Name = L"cmbFind";
        this->cmbFind->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &FormMain::CmbFind_KeyDown);
        // 
        // tsbFindUp
        // 
        resources->ApplyResources(this->tsbFindUp, L"tsbFindUp");
        this->tsbFindUp->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
        this->tsbFindUp->Name = L"tsbFindUp";
        this->tsbFindUp->Click += gcnew System::EventHandler(this, &FormMain::TsbFindUp_Click);
        // 
        // tsbFindDown
        // 
        resources->ApplyResources(this->tsbFindDown, L"tsbFindDown");
        this->tsbFindDown->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
        this->tsbFindDown->Name = L"tsbFindDown";
        this->tsbFindDown->Click += gcnew System::EventHandler(this, &FormMain::TsbFindDown_Click);
        // 
        // ctxMenuList
        // 
        resources->ApplyResources(this->ctxMenuList, L"ctxMenuList");
        this->ctxMenuList->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
            this->tsmCompareThisLineWithDocdiffChar,
                this->tsmCompareThisLineWithDocdiffword, this->toolStripMenuItem9, this->tsmiCopyItem
        });
        this->ctxMenuList->Name = L"ctxMenuList";
        // 
        // tsmCompareThisLineWithDocdiffChar
        // 
        resources->ApplyResources(this->tsmCompareThisLineWithDocdiffChar, L"tsmCompareThisLineWithDocdiffChar");
        this->tsmCompareThisLineWithDocdiffChar->Name = L"tsmCompareThisLineWithDocdiffChar";
        this->tsmCompareThisLineWithDocdiffChar->Click += gcnew System::EventHandler(this, &FormMain::tsmCompareThisLineWithDocdiffChar_Click);
        // 
        // tsmCompareThisLineWithDocdiffword
        // 
        resources->ApplyResources(this->tsmCompareThisLineWithDocdiffword, L"tsmCompareThisLineWithDocdiffword");
        this->tsmCompareThisLineWithDocdiffword->Name = L"tsmCompareThisLineWithDocdiffword";
        this->tsmCompareThisLineWithDocdiffword->Click += gcnew System::EventHandler(this, &FormMain::tsmCompareThisLineWithDocdiffword_Click);
        // 
        // toolStripMenuItem9
        // 
        resources->ApplyResources(this->toolStripMenuItem9, L"toolStripMenuItem9");
        this->toolStripMenuItem9->Name = L"toolStripMenuItem9";
        // 
        // tsmiCopyItem
        // 
        resources->ApplyResources(this->tsmiCopyItem, L"tsmiCopyItem");
        this->tsmiCopyItem->Name = L"tsmiCopyItem";
        this->tsmiCopyItem->Click += gcnew System::EventHandler(this, &FormMain::tsmiCopyItem_Click);
        // 
        // FormMain
        // 
        resources->ApplyResources(this, L"$this");
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->Controls->Add(this->spRoot);
        this->Controls->Add(this->toolMain);
        this->Controls->Add(this->stMain);
        this->Controls->Add(this->menuMain);
        this->MainMenuStrip = this->menuMain;
        this->Name = L"FormMain";
        this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &FormMain::FormMain_FormClosing);
        this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &FormMain::FormMain_FormClosed);
        this->Load += gcnew System::EventHandler(this, &FormMain::FormMain_Load);
        this->spRoot->Panel1->ResumeLayout(false);
        (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->spRoot))->EndInit();
        this->spRoot->ResumeLayout(false);
        this->menuMain->ResumeLayout(false);
        this->menuMain->PerformLayout();
        this->stMain->ResumeLayout(false);
        this->stMain->PerformLayout();
        this->toolMain->ResumeLayout(false);
        this->toolMain->PerformLayout();
        this->ctxMenuList->ResumeLayout(false);
        this->ResumeLayout(false);
        this->PerformLayout();

    }

}

