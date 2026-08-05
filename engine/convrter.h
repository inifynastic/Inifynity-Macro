// This is useless for now. but will work in future so am gonna leave it like this

#ifndef CONVERTER_H
#define CONVERTER_H

//Headers

#ifdef __cplusplus
extern "C" {
#endif

#define X(name) KEY_##name,

typedef enum {
    #include "keylist.def"
} KeyboardKeys;

#undef X

#ifdef __cplusplus
}
#endif

#endif