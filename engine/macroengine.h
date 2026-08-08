#ifndef MACROENGINE_H
#define MACROENGINE_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


void macro_toggle();
void macro_set_timer(int milliseconds);
void start_hotkey_engine();
void stop_hotkey_engine();

#ifdef __cplusplus
}
#endif

#endif
