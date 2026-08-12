#include "handlehotkey.h"
#include "converter.hpp"
#include "macroengine.h"

#define HOTKEY_ID 1
#define THREADSTOP_MSG (WM_APP + 1)
#define REGISYER_HOTKEY_MSG (WM_APP + 2)


static HANDLE thread;
static DWORD thread_id;

DWORD WINAPI global_hotkey_thread(LPVOID unused){
  MSG msg;
  if (!RegisterHotKey(NULL, HOTKEY_ID, 0, VK_F6))
    return 1;
  while (GetMessage(&msg, NULL, 0, 0) > 0) {

    if (msg.message == WM_HOTKEY && msg.wParam == HOTKEY_ID) {
      toggle_macro();
	  // TODO QT Function class let QT know its enabled
	  continue;
    }

    if (msg.message == REGISYER_HOTKEY_MSG){
      UnregisterHotKey(NULL, HOTKEY_ID);
      if (!RegisterHotKey(NULL, HOTKEY_ID, 0, (UINT)msg.wParam))
        return 1;
      
	  continue;
      }
    if (msg.message == THREADSTOP_MSG) {
		break;
    }
  }
  UnregisterHotKey(NULL,HOTKEY_ID);
  return 0;
}

void start_global_hotkey_thread() {
	 thread = CreateThread(NULL, 0, global_hotkey_thread, NULL, 0, &thread_id);
    return;
}
void stop_global_hotkey_thread() {
	PostThreadMessage(thread_id, THREADSTOP_MSG, 0, 0);
    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);
    thread = NULL;
    return;
}
int register_hotkey(const void *qtHotKey) {
  UINT data = convert_QKey_UINT(qtHotKey);
  PostThreadMessage(thread_id, REGISYER_HOTKEY_MSG,data,0);
  return 0;
}
