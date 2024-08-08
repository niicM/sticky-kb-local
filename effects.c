#include <stdio.h>
#include "effects.h"

struct effect no_effect = {NO_EFFECT, 0, 0};
struct effect clear = {CLEAR, 0, 0};

void print_effect(struct effect* ef) {
    switch (ef->effect_type)
    {
    case NO_EFFECT:
        printf("No effect\n");
        break;

    case ASCII_TYPE:
        printf("Ascii type %c\n", ef->payload);
        break;

    default:
        printf("Other\n");
        break;
    }
}
