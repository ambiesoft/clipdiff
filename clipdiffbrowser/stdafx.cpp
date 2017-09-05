
#include "stdafx.h"


volatile HANDLE ghParent;
volatile HANDLE gWatcher;
volatile ULONG gWatcherWait = 30* 1000;