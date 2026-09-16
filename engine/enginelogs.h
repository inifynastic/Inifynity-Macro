#ifndef HANDLEHOTKEY_H
#define HANDLEHOTKEY_H

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum{
    OP_CLICKER_TIMER,
    OP_REGISTER_HOTKEY,
    OP_START_ENGINE,
    OP_STOP_ENGINE
} EngineOperation;

void receivelogs(int statusCode, EngineOperation operationCode);
	
#ifdef __cplusplus
}
#endif

#endif