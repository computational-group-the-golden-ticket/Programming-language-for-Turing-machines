#include <cstdlib>
#include <iostream>

#include "tape.h"

void use_case_1();
void use_case_2();


int main(){
    use_case_1();
    // use_case_2();

    return 0;
}

void use_case_1(){
    char *a = (char *) "a";
    char *b = (char *) "b";

    State default_symbol = {a, 1};
    State second_symbol = {b, 1};

    char *cero = (char *) "0";
    char *uno = (char *) "1";

    State *initial_tape_state = (State *) malloc((size_t) sizeof(State) * 6);

    initial_tape_state[0] = {uno, 1};
    initial_tape_state[1] = {uno, 1};
    initial_tape_state[2] = {uno, 1};
    initial_tape_state[3] = {cero, 1};
    initial_tape_state[4] = {uno, 1};
    initial_tape_state[5] = {uno, 1};

    Tape lista(initial_tape_state, 6, default_symbol);
    std::cout << lista << ", " << lista.read_symbol().symbol << '\n';

    lista.move_tape_head_to_left();
    std::cout << lista << ", " << lista.read_symbol().symbol << '\n';

    lista.write_symbol(second_symbol);
    std::cout << lista << ", " << lista.read_symbol().symbol << '\n';

    for (int i = 0; i < 10; i++){
        lista.move_tape_head_to_right();
    }

    std::cout << lista << ", " << lista.read_symbol().symbol << '\n';

    lista.write_symbol(second_symbol);
    std::cout << lista << ", " << lista.read_symbol().symbol << '\n';
    
    free(initial_tape_state);
}

void use_case_2(){
    char *a = (char *) "prueba1";
    char *b = (char *) "prueba2";

    State default_symbol = {a, 7};
    State second_symbol = {b, 7};

    char *cero = (char *) "s0";
    char *uno = (char *) "s1";

    State *initial_tape_state = (State *) malloc((size_t) sizeof(State) * 6);
    initial_tape_state[0] = {uno, 2};
    initial_tape_state[1] = {uno, 2};
    initial_tape_state[2] = {uno, 2};
    initial_tape_state[3] = {cero, 2};
    initial_tape_state[4] = {uno, 2};
    initial_tape_state[5] = {uno, 2};

    Tape lista(initial_tape_state, 6, default_symbol);
    // std::cout << lista << ' ' << lista.read_symbol().symbol << '\n';

    lista.move_tape_head_to_left();
    // std::cout << lista << ' ' << lista.read_symbol().symbol << '\n';

    lista.write_symbol(second_symbol);
    // std::cout << lista << ' ' << lista.read_symbol().symbol << '\n';

    for (int i = 0; i < 10; i++){
        lista.move_tape_head_to_right();
    }

    // std::cout << lista << ' ' << lista.read_symbol().symbol << '\n';

    lista.write_symbol(second_symbol);
    // std::cout << lista << ' ' << lista.read_symbol().symbol << '\n';

    free(initial_tape_state);
}


void test3(){
    State *initial_tape_state = (State *) malloc((size_t) sizeof(State) * 4);
    initial_tape_state[0] = {(char *) "l", 1};
    initial_tape_state[1] = {(char *) "u", 1};
    initial_tape_state[2] = {(char *) "i", 1};
    initial_tape_state[3] = {(char *) "s", 1};  
}