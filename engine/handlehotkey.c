#include "handlehotkey.h"
#include "converter.hpp"
#include "enginelogs.h"
#include "macroengine.h"

#define HOTKEY_ID 1
#define THREADSTOP_MSG (WM_APP + 1)
#define REGISYER_HOTKEY_MSG (WM_APP + 2)


static HANDLE thread = NULL;
static DWORD thread_id = 0;

DWORD WINAPI global_hotkey_thread(LPVOID unused){
  MSG msg;
  if (!RegisterHotKey(NULL, HOTKEY_ID, 0, VK_F6)){
	send_logs(204); // Hot Key not registered.
        return 1;
  }
  send_logs(104); // Hotkey registered.
  while (GetMessage(&msg, NULL, 0, 0) > 0) {

    if (msg.message == WM_HOTKEY && msg.wParam == HOTKEY_ID) {
      toggle_macro();
	  continue;
    }

    if (msg.message == REGISYER_HOTKEY_MSG){
      UnregisterHotKey(NULL, HOTKEY_ID);
      if (!RegisterHotKey(NULL, HOTKEY_ID, 0, (UINT)msg.wParam)){
        send_logs(203); // HotKey Not registered.
        return 1;
      }      
      send_logs(104); // Hotkey registered.
	  continue;
      }
    if (msg.message == THREADSTOP_MSG) {
		break;
    }
  }
  if(!UnregisterHotKey(NULL,HOTKEY_ID)){
	  send_logs(205); // Hotkey not Unregistered.
  }  
 
  send_logs(105); // Hotkey Thread Ended Successfully
  return 0;
}

void start_global_hotkey_thread() {
  thread = CreateThread(NULL, 0, global_hotkey_thread, NULL, 0, &thread_id);
  if (!thread) {
    send_logs(202); // Thread Not created!!
  } else {
	  send_logs(102);// Thread Created Successfully
    }
  
    return;
}
void stop_global_hotkey_thread() {
  if (!PostThreadMessage(thread_id, THREADSTOP_MSG, 0, 0)) {
    send_logs(206); // Thread message not created!
  } else {
    send_logs(106); // Thread Message Created Successfully
  }

  WaitForSingleObject(thread, INFINITE);

    if (!CloseHandle(thread)) {
      send_logs(203); // Thread Not CLOSED!
    } else {
      send_logs(103); // Thread Closed Successfully
    }    
    thread = NULL;
    return;
}
int register_hotkey(const void *qtHotKey) {
  UINT data = convert_QKey_UINT(qtHotKey);
  if (PostThreadMessage(thread_id, REGISYER_HOTKEY_MSG, data, 0)) {
    send_logs(206);
  } else {
    send_logs(106);
  }  
  return 0;
}
