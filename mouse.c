#include <windows.h>
#include <stdio.h>
#include <time.h>
void main( int argc, const char* argv[] )
{
    DWORD cNumRead, fdwMode, fdwSaveOldMode, iEvents;
    INPUT_RECORD irInBuf;
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hStdin, &fdwSaveOldMode);
    fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    SetConsoleMode(hStdin, fdwMode);
    clock_t tStart = 0, tStop = 0;
    int tWait = -1;
    if(argc > 1) {
        tWait = atoi(argv[1]);
        tStart = clock();
    }
    irInBuf.Event.MouseEvent.dwButtonState = irInBuf.Event.MouseEvent.dwMousePosition.X = irInBuf.Event.MouseEvent.dwMousePosition.Y = -1;
    while(tWait == -1 || ((float)(tStop - tStart))/CLOCKS_PER_SEC*1000 < tWait) {
        tStop = clock();
        GetNumberOfConsoleInputEvents(hStdin, &iEvents);
        if(iEvents) {
            ReadConsoleInput(hStdin, &irInBuf, 1, &cNumRead);
            if(cNumRead && irInBuf.EventType == MOUSE_EVENT) break;
        }
    }
    printf("%i %i %i", irInBuf.Event.MouseEvent.dwButtonState, irInBuf.Event.MouseEvent.dwMousePosition.X, irInBuf.Event.MouseEvent.dwMousePosition.Y);
    SetConsoleMode(hStdin, fdwSaveOldMode);
}
