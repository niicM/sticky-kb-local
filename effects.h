#pragma once
#include <stdint.h>

enum effect_type {

    NO_EFFECT,

    // Printable standard ascii chars (affected by layers e.g. Querty)
    ASCII_TYPE,
    ASCII_DOWN,

    // Other symbols not pressent in standard ascii (also affected by layers)
    EXTENDED_TYPE,
    EXTENDED_DOWN,

    // Refered to the actuall keycode (for keys like enter, tab...)
    KEY_TYPE,
    KEY_DOWN,

    // To release all keys that are being hold down, whithout sending a new key
    CLEAR,

    // Effects that change the state of the algorithm 
    // (e.g. change from Querty to Dvorak)
    INTERNAL    
};

struct effect {

    enum effect_type effect_type;
    
    // The meaning of payload depends on the type (ascii, hid-key, internal)
    uint8_t payload; 
    
    // ctrl (1), left alt (4), right alt (64) ...
    // Not used in clear or internal
    uint8_t mods; 
};

struct effect no_effect = {NO_EFFECT, 0, 0};