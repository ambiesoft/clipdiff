// clipdiff.cpp : main project file.

#include "stdafx.h"
#include "FormMain.h"


namespace clipdiff {


	void FormMain::InitializeComponent(void)
	{
		this->menuMain = (gcnew System::Windows::Forms::MenuStrip());
		this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->editToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->addColumnToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->removeColumnToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->optionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->ignoreWhenClipboardTextsAreSameToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->windowToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->alwaysOnTopToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->stMain = (gcnew System::Windows::Forms::StatusStrip());
		this->stlMain = (gcnew System::Windows::Forms::ToolStripStatusLabel());
		this->panelClient = (gcnew System::Windows::Forms::Panel());
		this->menuMain->SuspendLayout();
		this->stMain->SuspendLayout();
		this->SuspendLayout();
		// 
		// menuMain
		// 
		this->menuMain->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->fileToolStripMenuItem, 
			this->editToolStripMenuItem, this->optionToolStripMenuItem, this->windowToolStripMenuItem});
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
		this->exitToolStripMenuItem->Size = System::Drawing::Size(96, 22);
		this->exitToolStripMenuItem->Text = L"&Exit";
		this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::exitToolStripMenuItem_Click);
		// 
		// editToolStripMenuItem
		// 
		this->editToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->addColumnToolStripMenuItem, 
			this->removeColumnToolStripMenuItem});
		this->editToolStripMenuItem->Name = L"editToolStripMenuItem";
		this->editToolStripMenuItem->Size = System::Drawing::Size(41, 20);
		this->editToolStripMenuItem->Text = L"&Edit";
		// 
		// addColumnToolStripMenuItem
		// 
		this->addColumnToolStripMenuItem->Name = L"addColumnToolStripMenuItem";
		this->addColumnToolStripMenuItem->Size = System::Drawing::Size(170, 22);
		this->addColumnToolStripMenuItem->Text = L"&Add Column";
		this->addColumnToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::addColumnToolStripMenuItem_Click);
		// 
		// removeColumnToolStripMenuItem
		// 
		this->removeColumnToolStripMenuItem->Name = L"removeColumnToolStripMenuItem";
		this->removeColumnToolStripMenuItem->Size = System::Drawing::Size(170, 22);
		this->removeColumnToolStripMenuItem->Text = L"&Remove Column";
		this->removeColumnToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::removeColumnToolStripMenuItem_Click);
		// 
		// optionToolStripMenuItem
		// 
		this->optionToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->ignoreWhenClipboardTextsAreSameToolStripMenuItem});
		this->optionToolStripMenuItem->Name = L"optionToolStripMenuItem";
		this->optionToolStripMenuItem->Size = System::Drawing::Size(57, 20);
		this->optionToolStripMenuItem->Text = L"&Option";
		// 
		// ignoreWhenClipboardTextsAreSameToolStripMenuItem
		// 
		this->ignoreWhenClipboardTextsAreSameToolStripMenuItem->Name = L"ignoreWhenClipboardTextsAreSameToolStripMenuItem";
		this->ignoreWhenClipboardTextsAreSameToolStripMenuItem->Size = System::Drawing::Size(296, 22);
		this->ignoreWhenClipboardTextsAreSameToolStripMenuItem->Text = L"&Ignore when clipboard texts are same";
		this->ignoreWhenClipboardTextsAreSameToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::ignoreWhenClipboardTextsAreSameToolStripMenuItem_Click);
		// 
		// windowToolStripMenuItem
		// 
		this->windowToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->alwaysOnTopToolStripMenuItem});
		this->windowToolStripMenuItem->Name = L"windowToolStripMenuItem";
		this->windowToolStripMenuItem->Size = System::Drawing::Size(65, 20);
		this->windowToolStripMenuItem->Text = L"&Window";
		this->windowToolStripMenuItem->DropDownOpening += gcnew System::EventHandler(this, &FormMain::windowToolStripMenuItem_DropDownOpening);
		// 
		// alwaysOnTopToolStripMenuItem
		// 
		this->alwaysOnTopToolStripMenuItem->Name = L"alwaysOnTopToolStripMenuItem";
		this->alwaysOnTopToolStripMenuItem->Size = System::Drawing::Size(158, 22);
		this->alwaysOnTopToolStripMenuItem->Text = L"&Always on Top";
		this->alwaysOnTopToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::alwaysOnTopToolStripMenuItem_Click);
		// 
		// stMain
		// 
		this->stMain->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->stlMain});
		this->stMain->Location = System::Drawing::Point(0, 389);
		this->stMain->Name = L"stMain";
		this->stMain->Size = System::Drawing::Size(622, 22);
		this->stMain->TabIndex = 4;
		// 
		// stlMain
		// 
		this->stlMain->Name = L"stlMain";
		this->stlMain->Size = System::Drawing::Size(0, 17);
		// 
		// panelClient
		// 
		this->panelClient->Dock = System::Windows::Forms::DockStyle::Fill;
		this->panelClient->Location = System::Drawing::Point(0, 24);
		this->panelClient->Name = L"panelClient";
		this->panelClient->Size = System::Drawing::Size(622, 365);
		this->panelClient->TabIndex = 5;
		// 
		// FormMain
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(622, 411);
		this->Controls->Add(this->panelClient);
		this->Controls->Add(this->stMain);
		this->Controls->Add(this->menuMain);
		this->MainMenuStrip = this->menuMain;
		this->Name = L"FormMain";
		this->Text = L"FormMain";
		this->Load += gcnew System::EventHandler(this, &FormMain::FormMain_Load);
		this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &FormMain::FormMain_FormClosed);
		this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &FormMain::FormMain_FormClosing);
		this->menuMain->ResumeLayout(false);
		this->menuMain->PerformLayout();
		this->stMain->ResumeLayout(false);
		this->stMain->PerformLayout();
		this->ResumeLayout(false);
		this->PerformLayout();

	}

}

