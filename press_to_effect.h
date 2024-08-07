#pragma once

#include <stdint.h>
#include "effects.h"

#define N_LAYERS 4
#define N_KEY_DOWN_LAYERS 1

#define MAX_MODS 3
#define N_KEYS 36

// Keys go from 0 to 35, so we need a value to indicate key absence.
#define NO_KEY 0xff

// The same is true for the layers.
#define NO_LAYER 0xff


struct press_to_effect {

    // static: Once configurated it stays the samet 
    uint8_t mods[N_KEYS][N_LAYERS][MAX_MODS];
    struct effect effect_matrix[N_KEYS][N_LAYERS];


    // dynamic: Changes with key presses and releasesc
    uint8_t currdown[N_KEYS];
    uint8_t curr_affected[N_KEYS][N_KEYS];
    
    // Once a key has been used to modify another, it can't do an action of it's 
    // own.
    uint8_t cancelled[N_KEYS];

    // If activated, the key-up of that key will need to finish the key-down
    // effect. Any other effect will finish it, possibly before the release of
    // that particular key.
    uint8_t waiting_for_release;
};

void addkey(struct press_to_effect* pte, struct effect* effect,  
    uint8_t up, uint8_t key);
