#include "handlehotkey.h"
#include "converter.hpp"
#define HOSTKEY_ID 1

int register_hotkey(const void *qtHotKey) {
  UINT data = convert_QKey_UINT(qtHotKey);
  RegisterHotKey((HWND)HOSTKEY_ID, 1, 0, data);
  return 0;
}

/* TODO:
 A worker thread that waits for the windows to msg when hotkey is pressed.
 Somehow make it compatable with main.cpp*/
