#include <cstdlib>
#include <iostream>

#include "tape.h"
#include "turing_machine.h"

void zero_constant_function();
void succesor_function();
void addition_function();

int main(){
    // addition_function();
    zero_constant_function();

    return 0;
}

void zero_constant_function(){
    // cinta
    char *cero = (char *) "s0";
    char *uno = (char *) "s1";

    State default_state = {cero, 3};

    State *initial_tape_state = (State *) malloc((size_t) sizeof(State) * 6);
    initial_tape_state[0] = {uno, 3};
    initial_tape_state[1] = {uno, 3};
    initial_tape_state[2] = {uno, 3};
    initial_tape_state[3] = {uno, 3};
    initial_tape_state[4] = {uno, 3};   
    initial_tape_state[5] = {uno, 3};

    Tape lista(initial_tape_state, 6, default_state);
    std::cout << lista << '\n';

    // maquina de turing
    State q0 = {(char *) "q0", 3};
    State q1 = {(char *) "q1", 3};

    State R = {(char *) "R", 2};

    Instruction *in = (Instruction *) malloc((size_t) sizeof(Instruction) * 2);
    in[0] = {q0, {uno, 3}, {cero, 3}, q1};
    in[1] = {q1, {cero, 3}, R, q0};

    TuringMachine tm(in, 2, q0);

    tm.compute(lista);
    std::cout << lista << '\n';

    free(initial_tape_state);
    free(in);
}

void succesor_function(){
    // cinta
    char *cero = (char *) "s0";
    char *uno = (char *) "s1";

    State default_state = {cero, 3};

    State *initial_tape_state = (State *) malloc((size_t) sizeof(State) * 6);
    initial_tape_state[0] = {uno, 3};
    initial_tape_state[1] = {uno, 3};
    initial_tape_state[2] = {uno, 3};
    initial_tape_state[3] = {uno, 3};
    initial_tape_state[4] = {uno, 3};   
    initial_tape_state[5] = {uno, 3};

    Tape lista(initial_tape_state, 6, default_state);
    std::cout << lista << '\n';

    // maquina de turing
    State q0 = {(char *) "q0", 3};
    State q1 = {(char *) "q1", 3};

    State R = {(char *) "R", 2};

    Instruction *in = (Instruction *) malloc((size_t) sizeof(Instruction) * 2);
    in[0] = {q0, {uno, 3}, R, q0};
    in[1] = {q0, {cero, 3}, {uno, 3}, q1};

    TuringMachine tm(in, 2, q0);

    tm.compute(lista);
    std::cout << lista << '\n';

    free(initial_tape_state);
    free(in);
}

void addition_function(){
    // cinta
    char *cero = (char *) "s0";
    char *uno = (char *) "s1";

    State default_state = {cero, 3};

    State *initial_tape_state = (State *) malloc((size_t) sizeof(State) * 6);
    initial_tape_state[0] = {uno, 3};
    initial_tape_state[1] = {uno, 3};
    initial_tape_state[2] = {uno, 3};
    initial_tape_state[3] = {cero, 3};
    initial_tape_state[4] = {uno, 3};   
    initial_tape_state[5] = {uno, 3};

    Tape lista(initial_tape_state, 6, default_state);
    std::cout << lista << '\n';

    // maquina de turing
    State q0 = {(char *) "q0", 3};
    State q1 = {(char *) "q1", 3};
    State q2 = {(char *) "q2", 3};

    State R = {(char *) "R", 2};
    State L = {(char *) "L", 2};

    Instruction *in = (Instruction *) malloc((size_t) sizeof(Instruction) * 5);
    in[0] = {q0, {uno, 3}, R, q0};
    in[1] = {q0, {cero, 3}, {uno, 3}, q1};
    in[2] = {q1, {uno, 3}, R, q1};
    in[3] = {q1, {cero, 3}, L, q2};
    in[4] = {q2, {uno, 3}, {cero, 3}, q2};

    TuringMachine tm(in, 5, q0);

    tm.compute(lista);
    std::cout << lista << '\n';

    free(initial_tape_state);
    free(in);
}
