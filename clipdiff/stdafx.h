// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
#pragma once

// TODO: reference additional headers your program requires here
#include <windows.h>

#include <vcclr.h>

#include "../../lsMisc/DebugMacro.h"
#include "../../lsMisc/browseFolder.h"
#include "../../lsMisc/OpenCommon.h"
#include "../../lsMisc/stdwin32/stdwin32.h"
#include "../../lsMisc/HandleUtility.h"

#include "../../../gitdev/SessionGlobalMemory/SessionGlobalMemory.h"

#include "../Common/defines.h"

#define I18N(t) t

enum class EngineKind {
			EngineNone,
			DiffEngine,
			DocDiff,
};
enum class DocDiffEngineKind {
	DocDiffNone,
	DocDiffWord,
	DocDiffChar,
};

delegate void VVDelegate();