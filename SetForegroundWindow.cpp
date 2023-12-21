#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    DWORD dwProcessId;
    GetWindowThreadProcessId(hwnd, &dwProcessId);
    if (dwProcessId == (DWORD)lParam)
    {
        // 找到匹配PID的窗口，然后将其置前
        SetForegroundWindow(hwnd);
    }
    return TRUE; // 继续枚举窗口
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <PID>\n", argv[0]);
        return 1;
    }

    DWORD pid = strtoul(argv[1], NULL, 10);

    // 枚举所有顶级窗口，直到找到匹配PID的窗口
    EnumWindows(EnumWindowsProc, (LPARAM)pid);

    return 0;
}
