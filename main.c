#include <stdio.h>
#include "press_to_effect.h"
#include "press_to_effect_init.h"

int main(int argc, char const *argv[])
{
    struct press_to_effect pte;
    init_press_to_effect(&pte);

    printf("hello\n");

    return 0;
}
