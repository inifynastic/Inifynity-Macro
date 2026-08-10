#define MIN_CLICK_INTERVAL_MS 100

#include "macroengine.h"
#include <Windows.h>
#include "handlehotkey.h"

static HANDLE thread;
static LONG clickingFlag = 0;
static LONG timer = 100;

DWORD WINAPI ckickingThread(LPVOID unused){
  INPUT input = {0};
    input.type = INPUT_MOUSE; // Choose mouse as input
    while (InterlockedCompareExchange(&clickingFlag, 0, 0)){

        input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        SendInput(1, &input, sizeof(INPUT));
        input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
        SendInput(1, &input, sizeof(INPUT));
  
	// The line below uses help from AI since I could not find any solution so be aware of this
		LONG remaining = InterlockedCompareExchange(&timer, 0, 0); // Trickey but is getting timer value
        while (remaining > 0 && InterlockedCompareExchange(&clickingFlag, 0, 0)){
            DWORD chunk = remaining > 50 ? 50 : (DWORD)remaining;
            Sleep(chunk);
            remaining -= chunk;
        }
    }
	
    return 0;
}


// SendInput(number_of_inputs, input_array, size_of_input_struct);
static void macro_start_click() {
  if (clickingFlag) {
	  return;
  }
    InterlockedExchange(&clickingFlag, 1);
    thread = CreateThread(NULL, 0, ckickingThread, NULL, 0, NULL);
    return;
}

static void macro_stop_click() {
	  if (!clickingFlag) {
	  return;
          }
	  
    InterlockedExchange(&clickingFlag, 0);
    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);
    thread = NULL;
    return;
}

void macro_toggle() {
  if (clickingFlag) {
    macro_stop_click();
	return;
  }
  macro_start_click();
}

void macro_set_timer(int milliseconds){
  if (milliseconds < MIN_CLICK_INTERVAL_MS) {
	  InterlockedExchange(&timer, 100);
          return;
  }
  InterlockedExchange(&timer, milliseconds);
}

void start_hotkey_engine() {
	static int called = 0;
        if (called)
          return;
        called = 1;
		start_global_hotkey_thread();
}

void stop_hotkey_engine() {
	static int called = 0;
        if (called)
          return;
        called = 1;
		stop_global_hotkey_thread();
}

void register_new_hotkey(void* qKey) {
	register_hotkey(qKey);
}  
