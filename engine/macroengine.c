#include "enginelogs.h"
#include "macroengine.h"
#include <Windows.h>
#include <winuser.h>

#define MIN_CLICK_INTERVAL_MS 100

#define CLICK_MODE_RIGHT 0
#define CLICK_MODE_LEFT 1
#define CLICK_MODE_MIDDLE 2

#define CLICK_TYPE_SINGLE 0 // THIS SHIT IS WAY TOO COMPLEX BUT POSSIBLE
#define CLICK_TYPE_DOUBLE 1 // For my future self.


static HANDLE thread = NULL;
static LONG timer = 100;
LONG clickingFlag = 0;
static LONG terminateFlag = 0;
static LONG clickMode = CLICK_MODE_LEFT;

static void toggle_mouse_flag(LONG button, DWORD* downflag, DWORD* upflag);

Callback emit_on = NULL;
Callback emit_off = NULL;

DWORD WINAPI ckickingThread(LPVOID unused){
  INPUT input = {0};
  DWORD upflag = MOUSEEVENTF_LEFTDOWN;
  DWORD downflag = MOUSEEVENTF_LEFTDOWN;
  input.type = INPUT_MOUSE; // Choose mouse as input


    while (!InterlockedCompareExchange(&terminateFlag, 0, 0)) {
      if (!InterlockedCompareExchange(&clickingFlag, 0, 0)) {
		Sleep(10);
        continue;
      }

	  toggle_mouse_flag(InterlockedCompareExchange(&clickMode,0,0), &downflag,  &upflag);
        input.mi.dwFlags = downflag;
        if (!SendInput(1, &input, sizeof(INPUT))) {
			send_logs(200); //Failed mouse left down.
        } else {
          send_logs(100); //Successfully mouse left down.
        }
        
        
        input.mi.dwFlags = upflag;
        if (!SendInput(1, &input, sizeof(INPUT))) {
			send_logs(201); //Failed mouse left up.
        } else {
          send_logs(101); // Succesfully mouse left up.
        }
 
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
	  send_logs(202); // Thread not created!
	  return;
  } else {
	  send_logs(102); // Thread Created!
    }
  
}

void exit_clicker_engine() {
  InterlockedExchange(&terminateFlag, 1); 

	WaitForSingleObject(thread, INFINITE);
        if (!CloseHandle(thread)) {
			send_logs(203); // Thread not Closed!
        } else {
			send_logs(103);  // Thread Closed!
        }
        
    thread = NULL;

}  


static void macro_start_click() {
  if (InterlockedCompareExchange(&clickingFlag, 0, 0)) {
	  return;
  }
    InterlockedExchange(&clickingFlag, 1);
}

static void macro_stop_click() {
	  if (!clickingFlag) {
	  return;
          }
	  
    InterlockedExchange(&clickingFlag, 0);
    return;
}

static void toggle_mouse_flag(LONG button, DWORD* downflag, DWORD* upflag) {
  switch (button) {
  case CLICK_MODE_RIGHT:
    *downflag = MOUSEEVENTF_RIGHTDOWN;
    *upflag = MOUSEEVENTF_RIGHTUP;
    return;
  case CLICK_MODE_LEFT:
    *downflag = MOUSEEVENTF_LEFTDOWN;
    *upflag = MOUSEEVENTF_LEFTUP;
    return;
  case CLICK_MODE_MIDDLE:
    *downflag = MOUSEEVENTF_MIDDLEDOWN;
    *upflag = MOUSEEVENTF_MIDDLEUP;
    return;
    		
  default:
	  return;
  }
  
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

void change_click_mode(int mode) {
  if (mode > 3 || mode < 0) {
	  send_logs(207);
    return;
    }

    InterlockedExchange(&clickMode, mode);
	send_logs(107);
}

void change_click_type() {} // For my future self
