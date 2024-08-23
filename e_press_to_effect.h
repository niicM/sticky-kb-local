#pragma once

#include <stdint.h> 
#include <stdbool.h>
#include "effects.h"


#define MAX_MODS 4
#define N_KEYS 36

// Keys go from 0 to 35, so we need a value to indicate key absence.
#define NO_KEY 0xff

// The same is true for the layers.
#define NO_LAYER 0xff


struct press_to_effect {

    // dynamic: Changes with key presses and releasesc
    bool currdown[N_KEYS];
    bool curr_affected[N_KEYS][N_KEYS];
    
    // Once a key has been used to modify another, it can't do an action of it's 
    // own.
    bool cancelled[N_KEYS];

    // If activated, the key-up of that key will need to finish the key-down
    // effect. Any other effect will finish it, possibly before the release of
    // that particular key.
    uint8_t waiting_for_release;
};

// void addkey(struct press_to_effect* pte, struct effect* effect,  
//     uint8_t up, uint8_t key);


bool key_down(struct press_to_effect* pte, struct effect* effect, uint8_t key);

bool key_up(struct press_to_effect* pte, struct effect* effect, uint8_t key);

void init_press_to_effect(struct press_to_effect* pte);
