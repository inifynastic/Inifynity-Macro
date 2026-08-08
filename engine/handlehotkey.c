#include "handlehotkey.h"
#include "converter.hpp"
#include <winuser.h>
#define HOTKEY_ID 1

int register_hotkey(const void *qtHotKey) {
  UINT data = convert_QKey_UINT(qtHotKey);
  RegisterHotKey((HWND)HOTKEY_ID, HOTKEY_ID, 0, data);
  return 0;
}

static HANDLE thread;

DWORD WINAPI global_hotkey_thread(LPVOID unused){
	int flag = 0;
	MSG msg;
  while (GetMessage(&msg, NULL, 0, 0) > 0) {
    if (msg.message == WM_HOTKEY) {
      if (msg.wParam == HOTKEY_ID) {
        if (flag) {
			
        }
      }
    }
  }
}

void detect_global_hotkey_press() {
	 thread = CreateThread(NULL, 0, global_hotkey_thread, NULL, 0, NULL);
    return;
}
