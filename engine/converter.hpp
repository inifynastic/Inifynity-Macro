// Why did I do this to myself. THIS THING TOOK FORVER TO MAKE
// BECASUE I WANTED TO MAKE IT CLEAN BUT AT THE COST OF MY SANITY
// I had to build an entire conversion layer

#pragma once
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

UINT convert_QKey_UINT(const void* QKey);

#ifdef __cplusplus
}
#endif
