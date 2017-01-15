// clipdiff.cpp : main project file.

#include "stdafx.h"
#include "FormMain.h"
#include "ListViewForScroll.h"

namespace clipdiff {

	// (gcnew System::Windows::Forms::ListView());
	// gcnew ListViewForScroll();

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
		this->lv1 = gcnew ListViewForScroll();
		this->chLine1 = (gcnew System::Windows::Forms::ColumnHeader());
		this->chText1 = (gcnew System::Windows::Forms::ColumnHeader());
		this->lv2 = gcnew ListViewForScroll();
		this->chLine2 = (gcnew System::Windows::Forms::ColumnHeader());
		this->chText2 = (gcnew System::Windows::Forms::ColumnHeader());
		this->tlpMain = (gcnew System::Windows::Forms::TableLayoutPanel());
		this->stMain = (gcnew System::Windows::Forms::StatusStrip());
		this->stlMain = (gcnew System::Windows::Forms::ToolStripStatusLabel());
		this->menuMain->SuspendLayout();
		this->tlpMain->SuspendLayout();
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
		// lv1
		// 
		this->lv1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->chLine1, this->chText1});
		this->lv1->Dock = System::Windows::Forms::DockStyle::Fill;
		this->lv1->FullRowSelect = true;
		this->lv1->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
		this->lv1->HideSelection = false;
		this->lv1->Location = System::Drawing::Point(3, 3);
		this->lv1->Name = L"lv1";
		this->lv1->Size = System::Drawing::Size(305, 361);
		this->lv1->TabIndex = 0;
		this->lv1->UseCompatibleStateImageBehavior = false;
		this->lv1->View = System::Windows::Forms::View::Details;
		// 
		// chLine1
		// 
		this->chLine1->Text = L"Line";
		// 
		// chText1
		// 
		this->chText1->Text = L"Text";
		this->chText1->Width = 213;
		// 
		// lv2
		// 
		this->lv2->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->chLine2, this->chText2});
		this->lv2->Dock = System::Windows::Forms::DockStyle::Fill;
		this->lv2->FullRowSelect = true;
		this->lv2->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
		this->lv2->HideSelection = false;
		this->lv2->Location = System::Drawing::Point(314, 3);
		this->lv2->Name = L"lv2";
		this->lv2->Size = System::Drawing::Size(305, 361);
		this->lv2->TabIndex = 1;
		this->lv2->UseCompatibleStateImageBehavior = false;
		this->lv2->View = System::Windows::Forms::View::Details;
		// 
		// chLine2
		// 
		this->chLine2->Text = L"Line";
		// 
		// chText2
		// 
		this->chText2->Text = L"Text";
		this->chText2->Width = 213;
		// 
		// tlpMain
		// 
		this->tlpMain->ColumnCount = 2;
		this->tlpMain->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 50)));
		this->tlpMain->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 50)));
		this->tlpMain->Controls->Add(this->lv2, 1, 0);
		this->tlpMain->Controls->Add(this->lv1, 0, 0);
		this->tlpMain->Dock = System::Windows::Forms::DockStyle::Fill;
		this->tlpMain->Location = System::Drawing::Point(0, 24);
		this->tlpMain->Name = L"tlpMain";
		this->tlpMain->RowCount = 2;
		this->tlpMain->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
		this->tlpMain->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
		this->tlpMain->Size = System::Drawing::Size(622, 387);
		this->tlpMain->TabIndex = 3;
		this->tlpMain->SizeChanged += gcnew System::EventHandler(this, &FormMain::tlpMain_SizeChanged);
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
		// FormMain
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(622, 411);
		this->Controls->Add(this->stMain);
		this->Controls->Add(this->tlpMain);
		this->Controls->Add(this->menuMain);
		this->MainMenuStrip = this->menuMain;
		this->Name = L"FormMain";
		this->Text = L"FormMain";
		this->Load += gcnew System::EventHandler(this, &FormMain::FormMain_Load);
		this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &FormMain::FormMain_FormClosed);
		this->menuMain->ResumeLayout(false);
		this->menuMain->PerformLayout();
		this->tlpMain->ResumeLayout(false);
		this->stMain->ResumeLayout(false);
		this->stMain->PerformLayout();
		this->ResumeLayout(false);
		this->PerformLayout();

	}

}

