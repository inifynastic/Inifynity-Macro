#pragma once

#include "enginebridge.hpp"


void clicker_engine_toggle();
void clicker_engine_timer(int milliseconds);

EngineBridge* get_engine_bridge();
void start_engine(void);
void stop_engine(void);
void register_new_hotkey(void* qKey);
