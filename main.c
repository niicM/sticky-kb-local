#include <stdio.h>
#include "effects.h"
#include "press_to_effect.h"

int main(int argc, char const *argv[])
{
    struct press_to_effect pte;
    struct effect ef;

    init_press_to_effect(&pte);
    
    key_down(&pte, &ef, 11);
    print_effect(&ef);

    key_down(&pte, &ef, 12);
    print_effect(&ef);


    key_down(&pte, &ef, 13);
    print_effect(&ef);

    key_up(&pte, &ef, 16);
    print_effect(&ef);

    key_up(&pte, &ef, 12);
    print_effect(&ef);

    key_up(&pte, &ef, 11);
    print_effect(&ef);

    key_up(&pte, &ef, 13);
    print_effect(&ef);

    return 0;
}
