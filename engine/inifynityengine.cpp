#include "inifynityengine.hpp"
#include "macroengine.h"
#include "handlehotkey.h"

EngineBridge bridge;

static void emit_macro_on() { bridge.macro_on(); }

static void emit_macro_off() { bridge.macro_off(); }


void clicker_engine_toggle() {
	toggle_macro();
  }

void clicker_engine_timer(int milliseconds){ // I didnt add it here cuz it can cause some annoying problems.
	macro_set_timer(milliseconds);
  }

  void start_engine(void) {
    emit_on = &emit_macro_on;
	emit_off = &emit_macro_off;
  start_global_hotkey_thread();

  
}

void stop_engine(void) {
		stop_global_hotkey_thread();
}

void register_new_hotkey(void* qKey) {
  register_hotkey(qKey); // I forgot about QT Slots while building this T_T and now its too late. Since it works  
}  

EngineBridge* get_engine_bridge(){
	return &bridge;
}
