#ifndef HANDLEHOTKEY_H
#define HANDLEHOTKEY_H

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

int register_hotkey(const void* qtHotkey);
void detect_global_hotkey_press();
	
#ifdef __cplusplus
}
#endif

#endif
