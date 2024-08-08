#include <stdio.h>
#include "effects.h"
#include "press_to_effect.h"
#include "press_to_effect_init.h"

int main(int argc, char const *argv[])
{
    struct press_to_effect pte;
    struct effect ef;

    init_press_to_effect(&pte);
    
    addkey(&pte, &ef, 0, 1);
    addkey(&pte, &ef, 1, 1);
    
    print_effect(&ef);
    printf("hello\n");

    return 0;
}
