// clipdiff.cpp : main project file.

#include "stdafx.h"
#include "FormMain.h"
//#include "difflist.h"
//#include "ListViewForScroll.h"
//#include "LVInfo.h"

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

