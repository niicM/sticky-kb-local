#include <stdio.h>
#include "e_effects.h"
#include "e_press_to_effect.h"

void t_type_H() {

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
}

void t_type_o() {

    struct press_to_effect pte;
    struct effect ef;
    init_press_to_effect(&pte);

    key_down(&pte, &ef, 11);
    print_effect(&ef);

    key_up(&pte, &ef, 11);
    print_effect(&ef);
    
    key_down(&pte, &ef, 19);
    print_effect(&ef);

    key_down(&pte, &ef, 11);
    print_effect(&ef);
 
    key_up(&pte, &ef, 11);
    print_effect(&ef);
 
    key_up(&pte, &ef, 19);
    print_effect(&ef);
}

void t_steping_bjk() {

    struct press_to_effect pte;
    struct effect ef;
    init_press_to_effect(&pte);

    key_down(&pte, &ef, 25);
    print_effect(&ef);

    key_down(&pte, &ef, 23);
    print_effect(&ef);
    
    key_up(&pte, &ef, 25);
    print_effect(&ef);

    key_down(&pte, &ef, 24);
    print_effect(&ef);
 
    key_up(&pte, &ef, 23);
    print_effect(&ef);
 
    key_up(&pte, &ef, 24);
    print_effect(&ef);
}



int main(int argc, char const *argv[])
{
    // t_type_o();
    t_steping_bjk();
    return 0;
}