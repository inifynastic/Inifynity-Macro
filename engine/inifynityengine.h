#ifndef INIFYNITYENGINE_H
#define INIFYNITYENGINE_H

#ifdef __cplusplus
extern "C" {
#endif


void clicker_engine_toggle();
void clicker_engine_timer(int milliseconds);

void start_hotkey_engine(void* bridge);
void stop_hotkey_engine();
void register_new_hotkey(void* qKey);

#ifdef __cplusplus
}
#endif

#endif
