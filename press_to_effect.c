#include <stdlib.h>
#include <string.h>

#include "press_to_effect.h"
#include "effects.h"


// Returns the layer 
char key_up(struct press_to_effect* pte, char key) {
    // key no longer modifies any other keys
    for (int i = 0; i < N_KEYS; i++) {
        pte->curr_affected[i][key] = 0;
    }
    if (pte->cancelled[key]) return NO_LAYER;

    char mods[MAX_MODS] = {NO_KEY};
    for (int i, j = 0; i < N_KEYS && j < MAX_MODS; i++) {
        if (pte->curr_affected[i]) {
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

void key_down(struct press_to_effect* pte, char key) {
    
    // TODO Maybe here we can look for key "press" layer for things like ENTER, UP ect

    pte->currdown[key] = 1;
    pte->cancelled[key] = 0;
    for (int i = 0; i < N_KEYS; i++) {
        pte->curr_affected[key][i] = pte->currdown[i];
    }
}

void addkey(struct press_to_effect* pte, char up, char key) {
    if (up) key_up(pte, key);
    else key_down(pte, key);
}
