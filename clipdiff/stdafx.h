// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
#pragma once

// TODO: reference additional headers your program requires here
#include <windows.h>


#include "../../MyUtility/DebugMacro.h"

enum {
	WM_APP_LISTVIEWSCROLLPOSCHANGED = WM_APP+1,
};

#define I18N(t) t