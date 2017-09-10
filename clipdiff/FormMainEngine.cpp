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

// clipdiff.cpp : main project file.

#include "stdafx.h"
#include "FormMain.h"
//#include "difflist.h"
//#include "ListViewForScroll.h"
//#include "LVInfo.h"

using namespace Ambiesoft;

namespace clipdiff {

	void FormMain::UpdateView2()
	{
		if (updatedEngine_ != Engine)
		{
			updatedEngine_ = Engine;
			if (Engine == EngineKind::DiffEngine)
			{
				HWND hChild = GetChildMainFormWindow();
				if (hChild)
				{
					SendNotifyMessage(childHwnd_, WM_CLOSE, 0, 0);
				}
				else if (childProcess_)
				{
					TerminateProcess(childHwnd_, 1);
				}
				ClearHandle(childProcess_);

				spRoot->Panel1Collapsed = false;
				spRoot->Panel2Collapsed = true;

				if (updatedEngineLevel_ != EngineLevel)
				{
					updatedEngineLevel_ = EngineLevel;
					renderAllDiff();
				}
			}
			else if (Engine == EngineKind::DocDiff)
			{
				updatedDocdiffEngineLevel_ = DocDiffEngineLevel;
				RunDocDiff();
			}
			else
			{
				DASSERT(false);
			}
		}
		else
		{
			// same engine, check level
			// in both engine, default is updated
			if (updatedEngineLevel_ != EngineLevel)
			{
				updatedEngineLevel_ = EngineLevel;
				renderAllDiff();
			}

			if (Engine == EngineKind::DocDiff)
			{
				if (updatedDocdiffEngineLevel_ != DocDiffEngineLevel)
				{
					updatedDocdiffEngineLevel_ = DocDiffEngineLevel;
					RunDocDiff();
				}
			}
		}
	}
	void FormMain::UpdateView()
	{
		if (this->IsHandleCreated && !this->IsDisposed)
			this->BeginInvoke(gcnew VVDelegate(this, &FormMain::UpdateView2));
	}
	EngineKind FormMain::Engine::get()
	{
		return engine_;
	}
	void FormMain::Engine::set(EngineKind value)
	{
		if (engine_ == value)
			return;

		engine_ = value;
		UpdateView();
	}



	DifferenceEngine::DiffEngineLevel FormMain::EngineLevel::get()
	{
		return engineLevel_;
	}
	void FormMain::EngineLevel::set(DifferenceEngine::DiffEngineLevel value)
	{
		if (engineLevel_ == value)
			return;

		engineLevel_ = value;
		UpdateView();
	}


	DocDiffEngineKind FormMain::DocDiffEngineLevel::get()
	{
		return docdiffEngineLevel_;
	}
	void FormMain::DocDiffEngineLevel::set(DocDiffEngineKind value)
	{
		if (docdiffEngineLevel_ == value)
			return;
		
		docdiffEngineLevel_ = value;
		UpdateView();
	}

}

