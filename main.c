#include <stdio.h>
#include "effects.h"
#include "press_to_effect.h"
#include "press_to_effect_init.h"

int main(int argc, char const *argv[])
{
    struct press_to_effect pte;
    struct effect ef;

    init_press_to_effect(&pte);
    
    addkey(&pte, &ef, 0, 19);
    print_effect(&ef);

    addkey(&pte, &ef, 0, 10);
    print_effect(&ef);

    addkey(&pte, &ef, 1, 10);
    print_effect(&ef);

    addkey(&pte, &ef, 1, 19);
    print_effect(&ef);

    return 0;
}
