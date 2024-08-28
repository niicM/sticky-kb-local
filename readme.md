# Compile

gcc -g -o main main.c e_press_to_effect.c e_key_mod_effect.c e_effects.c && ./main

cp ../rp2040/my-keyboard/source/e_*@(.h|.c) .

# For interactive testing 

gcc -g -o main_inter interactive_test.c e_press_to_effect.c e_key_mod_effect.c e_effects.c  


gcc -g -o main_inter interactive_test.c e_press_to_effect.c e_key_mod_effect.c e_effects.
c && ./key_echo.sh | ./main_inter

p, E, 
echo ppseesabab | ./main_inter n  