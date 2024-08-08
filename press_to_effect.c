#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "press_to_effect.h"
#include "effects.h"


// Returns the layer 
uint8_t key_up(struct press_to_effect* pte, uint8_t key) {
    // key no longer modifies any other keys
    for (int i = 0; i < N_KEYS; i++) {
        pte->curr_affected[i][key] = 0;
    }
    if (pte->cancelled[key]) return NO_LAYER;

    uint8_t mods[MAX_MODS];
    memset(mods, NO_KEY, MAX_MODS);
    int j = 0;
    for (int i = 0; i < N_KEYS && j < MAX_MODS; i++) {
        if (pte->curr_affected[key][i]) {
            printf("m: %d ", i);
            mods[j] = i;
            j++;
        }
    }

    // We only reister if the mods are exactly the same
    for (int layer = 0; layer < N_LAYERS; layer++) {
        int m;
        for (m = 0; m < MAX_MODS; m++) {
            if (pte->mods[key][layer][m] != mods[m]) break;
        }
        if (m == MAX_MODS) {
            for (m = 0; m < MAX_MODS; m++) {
                pte->cancelled[m] = 1;
            }
            return layer;
        }
    }

    // TODO MAybe here we can stop key-down effects (like arrows...)
    // CLEAR efect
    return NO_LAYER;
}

void key_down(struct press_to_effect* pte, uint8_t key) {
    
    // TODO Maybe here we can look for key "press" layer for things like ENTER, UP ect

    pte->currdown[key] = 1;
    pte->cancelled[key] = 0;
    for (int i = 0; i < N_KEYS; i++) {
        pte->curr_affected[key][i] = pte->currdown[i];
    }
}

void addkey(
    struct press_to_effect* pte, 
    struct effect* effect,  // out
    uint8_t up, 
    uint8_t key
) {
    if (up) {
        uint8_t layer = key_up(pte, key);
        printf("layer %d\n", layer);
        *effect = pte->effect_matrix[key][layer];
    } else {
        key_down(pte, key);
        *effect = no_effect;  // For the time being
    } 
}
