#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "effects.h"
#include "press_to_effect.h"


// To denote empty possitions in the helper layout arrays.
// Can be used as transparent, to search in other tables.
#define OOO 0x00


// in_layer_x[key] = 'n' I want to type key 'n' (maybe modified by ctrl or alt)
char in_layer_base[30] = {
    ',', '.', 'p', 'y', 'x',   'f', 'g', 'c', 'r', 'l',
    'a', 'o', 'e', 'u', 'i',   'd', 'h', 't', 'n', 's',
    '\'',';', 'q', 'j', 'k',   'b', 'm', 'w', 'v', 'z'
};

char in_layer_base_caps[30] = {
    '<', '>', 'P', 'Y', 'X',   'F', 'G', 'C', 'R', 'L',
    'A', 'O', 'E', 'U', 'I',   'D', 'H', 'T', 'N', 'S',
    '"', ':', 'Q', 'J', 'K',   'B', 'M', 'W', 'V', 'Z'
};

char in_layer_nums[30] = {
    OOO, '&', '*', '?', OOO,   OOO, '7', '8', '9', OOO,
    OOO, '$', '%', '^', OOO,   OOO, '4', '5', '6', '0',
    OOO, '!', '@', '#', OOO,   OOO, '1', '2', '3', OOO
};

char in_layer_msim[30] = {
    '+', '/', '(', ')', '~',   OOO, OOO, OOO, OOO, OOO,
    '-', '\\','[', ']', '`',   OOO, OOO, OOO, OOO, OOO,
    '_', '|', '{', '}', '=',   OOO ,OOO, OOO, OOO, OOO
};

uint8_t is_left(uint8_t key) {

    // This comparison is only needed if the last (six key) row is used in layers
    return (key < 33) && (key % 10 < 5);
    // return key % 10 < 5;
}

// char ch_ascii_key_no(char key) {
//     if ((' ' <= key) && (key <= '~')) return ASCII_TYPE; 
//     if (key == OOO) return NO_EFFECT;
//     return KEY_TYPE;
// }

//   00 01 02 03 04   05 06 07 08 09 
//   10 11 12 13 14   15 16 17 18 19 
//   20 21 22 23 24   25 26 27 28 29 
//         30 31 32   33 34 35

//   __ __ __ __ __   __ __ __ __ __ 
//   __ __ __ __ __   __ __ __ __ __ 
//   01 __ __ 02 03   03 02 __ __ 01 
//   __ __ __ __ __   __ __ __ __ __ 
//         __ __ __   __ __ __ 



void configure_layout(    
    uint8_t mods[N_KEYS][N_LAYERS][MAX_MODS],
    struct effect effect_matrix[N_KEYS][N_LAYERS]
) {
    // Layers don't need to appear only once as they can have different ctrl_alt
    char *layers[] = {
        in_layer_base, in_layer_base_caps, in_layer_nums, in_layer_msim
    };
    
    // Assumptions: for a given layer, for a given side, the ctrl_alt are shared
    uint8_t ctrl_alt [N_LAYERS] = {0};
    memset(ctrl_alt, 0, N_LAYERS);
    
    // Assumptions: for a given layer, for a given side, the modifiers are shared
    uint8_t layer_modifiers[N_LAYERS][2][MAX_MODS] = {
        //            (0) for right  (1) for left
        {{NO_KEY, NO_KEY, NO_KEY},  {NO_KEY, NO_KEY, NO_KEY}},  // base
        {{10,     NO_KEY, NO_KEY},  {19,     NO_KEY, NO_KEY}},  // caps
        {{13,     NO_KEY, NO_KEY},  {16,     NO_KEY, NO_KEY}},  // nums
        {{14,     NO_KEY, NO_KEY},  {15,     NO_KEY, NO_KEY}},  // msim
    };

    for (int layer = 0; layer < N_LAYERS; layer++) {
        for (int key_pos = 0; key_pos < 30; key_pos++) {

            char key_symbol = layers[layer][key_pos];
            if (key_symbol == OOO) continue;

            struct effect ef = {ASCII_TYPE, (uint8_t) key_symbol, ctrl_alt[layer]};
            effect_matrix[key_pos][layer] = ef;

            for (int mod = 0; mod < MAX_MODS; mod++) {
                uint8_t m = layer_modifiers[layer][is_left(key_pos)][mod]; 
                mods[key_pos][layer][mod] = m;
            }
        }
    }
}


void init_press_to_effect(struct press_to_effect* pte) {
    // Don't assume any order in the struct to avoid errors.

    memset(&pte->mods, NO_KEY, N_KEYS * N_LAYERS * MAX_MODS);
    memset(&pte->currdown, 0, N_KEYS);
    memset(&pte->curr_affected, 0, N_KEYS * N_KEYS);
    pte->waiting_for_release = NO_KEY;
    
    // "canceled" doesn't really need to be initialed but it's good practice.
    memset(&pte->cancelled, 0, N_KEYS); 

    configure_layout(pte->mods, pte->effect_matrix);
}