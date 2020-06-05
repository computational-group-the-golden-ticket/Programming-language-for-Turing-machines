#include <cstdlib>
#include <iostream>

#include "types.h"
#include "tape.h"
#include "turing_machine.h"

void zero_constant_function();
void succesor_function();
void addition_function();

int main(){
    addition_function();
    zero_constant_function();
    succesor_function();

    return 0;
}

void zero_constant_function(){
    // se crea la cinta
    State cero = {(char *) "s0", 3};
    State uno = {(char *) "s1", 3};

    State *initial_tape_state = (State *) malloc((size_t) sizeof(State) * 6);
    initial_tape_state[0] = uno;
    initial_tape_state[1] = uno;
    initial_tape_state[2] = uno;
    initial_tape_state[3] = uno;
    initial_tape_state[4] = uno;   
    initial_tape_state[5] = uno;

    Tape lista(initial_tape_state, 6, cero);
    std::cout << lista << '\n';

    // maquina de turing
    State q0 = {(char *) "q0", 3};
    State q1 = {(char *) "q1", 3};

    State R = {(char *) "R", 2};

    Instruction *in = (Instruction *) malloc((size_t) sizeof(Instruction) * 2);
    in[0] = {q0, uno, cero, q1};
    in[1] = {q1, cero, R, q0};

    TuringMachine tm(in, 2, q0);

    tm.compute(lista);
    std::cout << lista << '\n';

    free(initial_tape_state);
    free(in);
}

void succesor_function(){
    // se crea la cinta
    State cero = {(char *) "s0", 3};
    State uno = {(char *) "s1", 3};

    State *initial_tape_state = (State *) malloc((size_t) sizeof(State) * 6);
    initial_tape_state[0] = uno;
    initial_tape_state[1] = uno;
    initial_tape_state[2] = uno;
    initial_tape_state[3] = uno;
    initial_tape_state[4] = uno;   
    initial_tape_state[5] = uno;

    Tape lista(initial_tape_state, 6, cero);
    std::cout << lista << '\n';

    // maquina de turing
    State q0 = {(char *) "q0", 3};
    State q1 = {(char *) "q1", 3};

    State R = {(char *) "R", 2};

    Instruction *in = (Instruction *) malloc((size_t) sizeof(Instruction) * 2);
    in[0] = {q0, uno, R, q0};
    in[1] = {q0, cero, uno, q1};

    TuringMachine tm(in, 2, q0);

    tm.compute(lista);
    std::cout << lista << '\n';

    free(initial_tape_state);
    free(in);
}

void addition_function(){
    // se crea la cinta
    State cero = {(char *) "s0", 3};
    State uno = {(char *) "s1", 3};

    State *initial_tape_state = (State *) malloc((size_t) sizeof(State) * 6);
    initial_tape_state[0] = uno;
    initial_tape_state[1] = uno;
    initial_tape_state[2] = uno;
    initial_tape_state[3] = cero;
    initial_tape_state[4] = uno;   
    initial_tape_state[5] = uno;

    Tape lista(initial_tape_state, 6, cero);
    std::cout << lista << '\n';

    // maquina de turing
    State q0 = {(char *) "q0", 3};
    State q1 = {(char *) "q1", 3};
    State q2 = {(char *) "q2", 3};

    State R = {(char *) "R", 2};
    State L = {(char *) "L", 2};

    Instruction *in = (Instruction *) malloc((size_t) sizeof(Instruction) * 5);
    in[0] = {q0, uno, R, q0};
    in[1] = {q0, cero, uno, q1};
    in[2] = {q1, uno, R, q1};
    in[3] = {q1, cero, L, q2};
    in[4] = {q2, uno, cero, q2};

    TuringMachine tm(in, 5, q0);

    tm.compute(lista);
    std::cout << lista << '\n';

    free(initial_tape_state);
    free(in);
}
