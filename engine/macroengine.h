#ifndef MACROENGINE_H
#define MACROENGINE_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void macro_start_click();
void macro_stop_click();
void macro_set_timer(int milliseconds);

#ifdef __cplusplus
}
#endif

#endif
