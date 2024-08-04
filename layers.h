
#ifndef LAYERS_H_
#define LAYERS_H_

// #include <stdlib.h>

enum {
    DEL = 0,
    ESC,
    ENT,
    OOO,
};

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
    OOO, '&', '*', '?', OOO,   DEL, '7', '8', '9', OOO,
    OOO, '$', '%', '^', ESC,   ESC, '4', '5', '6', '0',
    OOO, '!', '@', '#', OOO,   OOO, '1', '2', '3', OOO
};

char in_layer_msim[30] = {
    '+', '/', '(', ')', '~',   OOO, OOO, OOO, OOO, OOO,
    '-', '\\','[', ']', '`',   OOO, OOO, OOO, OOO, OOO,
    '_', '|', '{', '}', '=',   OOO ,OOO, OOO, OOO, OOO
};

char is_left(char key) {

    // Slot way:
    // if (key <= 4) return 1;
    // if (key <= 9) return 0;
    // if (key <= 14) return 1;
    // if (key <= 19) return 0;
    // if (key <= 24) return 1;
    // if (key <= 29) return 0;
    // if (key <= 32) return 1;
    // if (key <= 35) return 0;

    // This comparison is only needed if the last (six key) row is used in layers
    // if (key >= 33) return 0;

    return key % 10 < 5;
}

char is_ascii(char key) {
    return (' ' <= key) && (key >= '~');
}
#endif