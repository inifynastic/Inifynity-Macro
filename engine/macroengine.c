#define MIN_CLICK_INTERVAL_MS 100

#include "macroengine.h"
#include <Windows.h>

static HANDLE thread;
static LONG timer = 100;
LONG clickingFlag = 0;
static LONG terminateFlag = 0;

Callback emit_on = NULL;
Callback emit_off = NULL;

DWORD WINAPI ckickingThread(LPVOID unused){
  INPUT input = {0};
    input.type = INPUT_MOUSE; // Choose mouse as input
    while (!InterlockedCompareExchange(&terminateFlag, 0, 0)) {
      if (!InterlockedCompareExchange(&clickingFlag, 0, 0)) {
		Sleep(10);
        continue;
      }
      

        input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        SendInput(1, &input, sizeof(INPUT));
        input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
        SendInput(1, &input, sizeof(INPUT));
  
	// The line below uses help from AI since I could not find any solution so be aware of this
		LONG remaining = InterlockedCompareExchange(&timer, 0, 0); // Trickey but is getting timer value
        while (remaining > 0 && InterlockedCompareExchange(&clickingFlag, 0, 0 )){
            DWORD chunk = remaining > 50 ? 50 : (DWORD)remaining;
            Sleep(chunk); //There is a delay in miliseconds rn. It can be ignored for now but if it creates a problem use another method
            remaining -= chunk;
			if (!InterlockedCompareExchange(&clickingFlag, 0, 0)) break;
        }

    }
	
    return 0;
}

void init_clicker_engine() {
  thread = CreateThread(NULL, 0, ckickingThread, NULL, 0, NULL);
  if (!thread) {
	  return;
  }    
}

void exit_clicker_engine() {
	InterlockedExchange(&terminateFlag, 1);
	WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);
    thread = NULL;

}  


// SendInput(number_of_inputs, input_array, size_of_input_struct);
static void macro_start_click() {
  if (InterlockedCompareExchange(&clickingFlag, 0, 0)) {
	  return;
  }
    InterlockedExchange(&clickingFlag, 1);
    return;
}

static void macro_stop_click() {
	  if (!clickingFlag) {
	  return;
          }
	  
    InterlockedExchange(&clickingFlag, 0);
    return;
}

void toggle_macro() {
  if (InterlockedCompareExchange(&clickingFlag,0,0)) {
    macro_stop_click();
	if (emit_off != NULL) {
		emit_off();
	}
	return;
  }
  macro_start_click();
  if (emit_on != NULL) {
		emit_on();
	}
  }
 

void macro_set_timer(int milliseconds){
  if (milliseconds < MIN_CLICK_INTERVAL_MS) {
	  InterlockedExchange(&timer, 100);
          return;
  }
  InterlockedExchange(&timer, milliseconds);
}

