#include <cstring.h>
#include "layers.h"


#define MAX_LAYERS 5
#define MAX_KEY_DOWN_LAYERS 1

#define MAX_MODS 3
#define N_KEYS 36

// Keys go from 0 to 35, so we need a value to indicate key absence.
#define NO_KEY 0xff

// The same is true for the layers.
#define NO_LAYER 0xff


struct press_to_combo {

    // static: Once configurated it stays the samet 
    char mods[N_KEYS][MAX_LAYERS][MAX_MODS];


    // dynamic: Changes with key presses and releasesc
    char currdown[N_KEYS];
    char curr_affected[N_KEYS][N_KEYS];
    
    // Once a key has been used to modify another, it can't do an action of it's 
    // own.
    char cancelled[N_KEYS];

    // If activated, the key-up of that key will need to finish the key-down
    // effect. Any other effect will finish it, possibly before the release of
    // that particular key.
    char waiting_for_release;
};

void init_press_to_combo(struct press_to_combo* ptc) {
    // Don't assume any order in the struct to avoid errors.

    memset(&ptc->mods, NO_KEY, N_KEYS * MAX_LAYERS * MAX_MODS);
    memset(&ptc->currdown, 0, N_KEYS);
    memset(&ptc->curr_affected, 0, N_KEYS * N_KEYS);
    ptc->waiting_for_release = NO_KEY;
    
    // "canceled" doesn't really need to be initialed but it's good practice.
    memset(&ptc->cancelled, 0, N_KEYS); 
}

// Returns the layer 
char key_up(struct press_to_combo* ptc, char key) {
    // key no longer modifies any other keys
    for (int i = 0; i < N_KEYS; i++) {
        ptc->curr_affected[i][key] = 0;
    }
    if (ptc->cancelled[key]) return NO_LAYER;

    char mods[MAX_MODS] = {NO_KEY};
    for (int i, j = 0; i < N_KEYS && j < MAX_MODS; i++) {
        if (ptc->curr_affected[i]) {
            mods[j] = i;
            j++;
        }
    }

    // We only reister if the mods are exactly the same
    for (int layer = 0; layer < MAX_LAYERS; layer++) {
        int m;
        for (m = 0; m < MAX_MODS; m++) {
            if (ptc->mods[key][layer][m] != mods) break;
        }
        if (m == MAX_MODS) {
            for (m = 0; m < MAX_MODS; m++) {
                ptc->cancelled[m] = 1;
            }
            return layer;
        }
    }

    // TODO MAybe here we can stop key-down effects (like arrows...)
    return NO_LAYER;
}

void key_down(struct press_to_combo* ptc, char key) {
    
    // TODO Maybe here we can look for key "press" layer for things like ENTER, UP ect

    ptc->currdown[key] = 1;
    ptc->cancelled[key] = 0;
    for (int i = 0; i < N_KEYS; i++) {
        ptc->curr_affected[key][i] = ptc->currdown[i];
    }
}

void addkey(struct press_to_combo* ptc, char up, char key) {
    if (up) key_up(ptc, key);
    else key_down(ptc, key);
}
