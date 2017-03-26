// clipdiff.cpp : main project file.

#include "stdafx.h"
#include "FormMain.h"


namespace clipdiff {


	void FormMain::InitializeComponent(void)
	{
		System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FormMain::typeid));
		this->menuMain = (gcnew System::Windows::Forms::MenuStrip());
		this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->editToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->addColumnToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->removeColumnToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripSeparator());
		this->optionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->tsmKeep = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->tsmIgnoreSame = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->windowToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->tsmTopMost = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->tsmAbout = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->stMain = (gcnew System::Windows::Forms::StatusStrip());
		this->stlMain = (gcnew System::Windows::Forms::ToolStripStatusLabel());
		this->panelClient = (gcnew System::Windows::Forms::Panel());
		this->toolMain = (gcnew System::Windows::Forms::ToolStrip());
		this->tsbKeep = (gcnew System::Windows::Forms::ToolStripButton());
		this->tsbIgnoreSame = (gcnew System::Windows::Forms::ToolStripButton());
		this->tsbTopMost = (gcnew System::Windows::Forms::ToolStripButton());
		this->stlResult = (gcnew System::Windows::Forms::ToolStripStatusLabel());
		this->menuMain->SuspendLayout();
		this->stMain->SuspendLayout();
		this->panelClient->SuspendLayout();
		this->toolMain->SuspendLayout();
		this->SuspendLayout();
		// 
		// menuMain
		// 
		this->menuMain->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->fileToolStripMenuItem, 
			this->editToolStripMenuItem, this->optionToolStripMenuItem, this->windowToolStripMenuItem, this->helpToolStripMenuItem});
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
		this->editToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->addColumnToolStripMenuItem, 
			this->removeColumnToolStripMenuItem, this->toolStripMenuItem1});
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
		// toolStripMenuItem1
		// 
		this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
		this->toolStripMenuItem1->Size = System::Drawing::Size(167, 6);
		// 
		// optionToolStripMenuItem
		// 
		this->optionToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->tsmKeep, 
			this->tsmIgnoreSame});
		this->optionToolStripMenuItem->Name = L"optionToolStripMenuItem";
		this->optionToolStripMenuItem->Size = System::Drawing::Size(57, 20);
		this->optionToolStripMenuItem->Text = L"&Option";
		// 
		// tsmKeep
		// 
		this->tsmKeep->Name = L"tsmKeep";
		this->tsmKeep->Size = System::Drawing::Size(150, 22);
		this->tsmKeep->Text = L"&KeepLeft";
		// 
		// tsmIgnoreSame
		// 
		this->tsmIgnoreSame->Name = L"tsmIgnoreSame";
		this->tsmIgnoreSame->Size = System::Drawing::Size(150, 22);
		this->tsmIgnoreSame->Text = L"&Ignore Same";
		this->tsmIgnoreSame->Click += gcnew System::EventHandler(this, &FormMain::tsmIgnoreSame_Click);
		// 
		// windowToolStripMenuItem
		// 
		this->windowToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->tsmTopMost});
		this->windowToolStripMenuItem->Name = L"windowToolStripMenuItem";
		this->windowToolStripMenuItem->Size = System::Drawing::Size(65, 20);
		this->windowToolStripMenuItem->Text = L"&Window";
		this->windowToolStripMenuItem->DropDownOpening += gcnew System::EventHandler(this, &FormMain::windowToolStripMenuItem_DropDownOpening);
		// 
		// tsmTopMost
		// 
		this->tsmTopMost->Name = L"tsmTopMost";
		this->tsmTopMost->Size = System::Drawing::Size(127, 22);
		this->tsmTopMost->Text = L"&Top Most";
		this->tsmTopMost->Click += gcnew System::EventHandler(this, &FormMain::onTopMost);
		// 
		// helpToolStripMenuItem
		// 
		this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->tsmAbout});
		this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
		this->helpToolStripMenuItem->Size = System::Drawing::Size(45, 20);
		this->helpToolStripMenuItem->Text = L"&Help";
		// 
		// tsmAbout
		// 
		this->tsmAbout->Name = L"tsmAbout";
		this->tsmAbout->Size = System::Drawing::Size(152, 22);
		this->tsmAbout->Text = L"&About...";
		this->tsmAbout->Click += gcnew System::EventHandler(this, &FormMain::tsmAbout_Click);
		// 
		// stMain
		// 
		this->stMain->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->stlMain, this->stlResult});
		this->stMain->Location = System::Drawing::Point(0, 389);
		this->stMain->Name = L"stMain";
		this->stMain->Size = System::Drawing::Size(622, 22);
		this->stMain->TabIndex = 4;
		// 
		// stlMain
		// 
		this->stlMain->Name = L"stlMain";
		this->stlMain->Size = System::Drawing::Size(576, 17);
		this->stlMain->Spring = true;
		// 
		// panelClient
		// 
		this->panelClient->Controls->Add(this->toolMain);
		this->panelClient->Dock = System::Windows::Forms::DockStyle::Fill;
		this->panelClient->Location = System::Drawing::Point(0, 24);
		this->panelClient->Margin = System::Windows::Forms::Padding(0);
		this->panelClient->Name = L"panelClient";
		this->panelClient->Size = System::Drawing::Size(622, 365);
		this->panelClient->TabIndex = 5;
		// 
		// toolMain
		// 
		this->toolMain->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->tsbKeep, this->tsbIgnoreSame, 
			this->tsbTopMost});
		this->toolMain->Location = System::Drawing::Point(0, 0);
		this->toolMain->Name = L"toolMain";
		this->toolMain->Size = System::Drawing::Size(622, 25);
		this->toolMain->TabIndex = 0;
		this->toolMain->Text = L"toolStrip1";
		// 
		// tsbKeep
		// 
		this->tsbKeep->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
		this->tsbKeep->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsbKeep.Image")));
		this->tsbKeep->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->tsbKeep->Name = L"tsbKeep";
		this->tsbKeep->Size = System::Drawing::Size(67, 22);
		this->tsbKeep->Text = L"Keep Left";
		this->tsbKeep->Click += gcnew System::EventHandler(this, &FormMain::toolStripButton1_Click);
		// 
		// tsbIgnoreSame
		// 
		this->tsbIgnoreSame->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
		this->tsbIgnoreSame->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsbIgnoreSame.Image")));
		this->tsbIgnoreSame->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->tsbIgnoreSame->Name = L"tsbIgnoreSame";
		this->tsbIgnoreSame->Size = System::Drawing::Size(87, 22);
		this->tsbIgnoreSame->Text = L"Ignore Same";
		this->tsbIgnoreSame->Click += gcnew System::EventHandler(this, &FormMain::tsbIgnoreSame_Click);
		// 
		// tsbTopMost
		// 
		this->tsbTopMost->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
		this->tsbTopMost->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsbTopMost.Image")));
		this->tsbTopMost->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->tsbTopMost->Name = L"tsbTopMost";
		this->tsbTopMost->Size = System::Drawing::Size(64, 22);
		this->tsbTopMost->Text = L"Top Most";
		this->tsbTopMost->Click += gcnew System::EventHandler(this, &FormMain::onTopMost);
		// 
		// stlResult
		// 
		this->stlResult->Name = L"stlResult";
		this->stlResult->Size = System::Drawing::Size(0, 17);
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
		this->Load += gcnew System::EventHandler(this, &FormMain::FormMain_Load);
		this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &FormMain::FormMain_FormClosed);
		this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &FormMain::FormMain_FormClosing);
		this->menuMain->ResumeLayout(false);
		this->menuMain->PerformLayout();
		this->stMain->ResumeLayout(false);
		this->stMain->PerformLayout();
		this->panelClient->ResumeLayout(false);
		this->panelClient->PerformLayout();
		this->toolMain->ResumeLayout(false);
		this->toolMain->PerformLayout();
		this->ResumeLayout(false);
		this->PerformLayout();

	}

}

