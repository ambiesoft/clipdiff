#pragma once


#include <windows.h>

#include <string>

#include "../../lsMisc/DebugMacro.h"
#include "../../lsMisc/OpenCommon.h"
#include "../../lsMisc/stdwin32/stdwin32.h"

#include "../../SessionGlobalMemory/SessionGlobalMemory.h"

#include "../Common/defines.h"

#define I18N(s) (s)

delegate void VSDelegate(System::String^);

extern volatile HANDLE ghParent;
extern volatile HANDLE gWatcher;
extern volatile ULONG gWatcherWait;