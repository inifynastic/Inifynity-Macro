#include "inifynityengine.h"
#include "macroengine.h"
#include "handlehotkey.h"


void clicker_engine_toggle() {

	macro_toggle();
  }

void clicker_engine_timer(int milliseconds){ // I didnt add it here cuz it can cause some annoying problems.
	macro_set_timer(milliseconds);
  }

void start_hotkey_engine(void* bridge) {
		start_global_hotkey_thread();
}

void stop_hotkey_engine() {
		stop_global_hotkey_thread();
}

void register_new_hotkey(void* qKey) {
  register_hotkey(qKey); // I forgot about QT Slots while building this T_T and now its too late. Since it works  
}  
