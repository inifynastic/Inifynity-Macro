#ifndef HANDLEHOTKEY_H
#define HANDLEHOTKEY_H

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

int register_hotkey(const void* qtHotkey);
void start_global_hotkey_thread();
void stop_global_hotkey_thread();
	
#ifdef __cplusplus
}
#endif

#endif
