#ifndef MACROENGINE_H
#define MACROENGINE_H

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

extern LONG clickingFlag;

typedef void (*Callback)(void);

extern Callback emit_on;
extern Callback emit_off;

void toggle_macro();

void macro_set_timer(int milliseconds);

#ifdef __cplusplus
}
#endif

#endif
