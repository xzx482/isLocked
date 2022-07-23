
#include <Windows.h>
#include <WtsApi32.h>

#pragma comment(lib, "WtsApi32.lib")

using namespace std;

extern "C" __declspec(dllexport) bool isLocked(void);

bool isLocked(void)
{
    WTSINFOEXW* pInfo = NULL;
    WTS_INFO_CLASS wtsic = WTSSessionInfoEx;
    LPTSTR ppBuffer = NULL;
    DWORD dwBytesReturned = 0;
    LONG sessionFlags = WTS_SESSIONSTATE_UNKNOWN; // until we know otherwise. Prevents a false positive since WTS_SESSIONSTATE_LOCK == 0

    DWORD dwSessionID = WTSGetActiveConsoleSessionId();

    if (WTSQuerySessionInformation(WTS_CURRENT_SERVER_HANDLE, dwSessionID, wtsic, &ppBuffer, &dwBytesReturned))
    {
        if (dwBytesReturned > 0)
        {
            pInfo = (WTSINFOEXW*)ppBuffer;
            if (pInfo->Level == 1)
            {
                sessionFlags = pInfo->Data.WTSInfoExLevel1.SessionFlags;
            }
        }
        WTSFreeMemory(ppBuffer);
        ppBuffer = NULL;
    }

    return (sessionFlags == WTS_SESSIONSTATE_LOCK);
}
