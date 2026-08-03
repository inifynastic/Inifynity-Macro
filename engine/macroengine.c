#define MIN_CLICK_INTERVAL_MS 100

#include "macroengine.h"
#include <Windows.h>


static HANDLE thread;
static LONG clickingFlag = 0;
static int timer = 500;

DWORD WINAPI macroThread(LPVOID unused){
    INPUT input = {0};
    input.type = INPUT_MOUSE; // Choose mouse as input
    while (InterlockedCompareExchange(&clickingFlag, 0, 0)){

        input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        SendInput(1, &input, sizeof(INPUT));
        input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
        SendInput(1, &input, sizeof(INPUT));
        Sleep(timer);
    }
    return 0;
}


// SendInput(number_of_inputs, input_array, size_of_input_struct);
void macro_start_click(){
    InterlockedExchange(&clickingFlag, 1);
    thread = CreateThread(NULL, 0, macroThread, NULL, 0, NULL);
    return;
}

void macro_stop_click(){
    InterlockedExchange(&clickingFlag, 0);
    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);
    thread = NULL;
    return;
}

void macro_set_timer(int milliseconds){
    if(milliseconds < MIN_CLICK_INTERVAL_MS){
        timer = MIN_CLICK_INTERVAL_MS;
        return;
    }
    timer = milliseconds;
}