#include "enginebridge.hpp"

void EngineBridge::macro_on() {
	emit notify_macro_on();
}

void EngineBridge::macro_off() {
	emit notify_macro_off();
}  
