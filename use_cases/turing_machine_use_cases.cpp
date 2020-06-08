#include <cstdlib>
#include <iostream>

#include "types.h"
#include "tape.h"
#include "turing_machine.h"

// como casos de uso se programan algunas funciones numericas(en los naturales)
// donde se uso como representacion de un numero n ---> 0 0 ... 0 1 1 ... 1 0 ...
// donde se usa 1 n-veces(se uso asi porque no se va a evaluar en 0)
void zero_constant_function();
void succesor_function();
void addition_function();

int main(){
    zero_constant_function();
    std::cout << '\n';

    succesor_function();
    std::cout << '\n';

    addition_function();
    return 0;
}

void zero_constant_function(){
    std::cout << "Funcion constante cero\n";

    // se crea la cinta
    State cero = {(char *) "0", 2};
    State uno = {(char *) "1", 2};

    // se creara la cinta que representa al numero 6
    State *initial_tape_state = (State *) malloc((size_t) sizeof(State) * 6);
    initial_tape_state[0] = uno;
    initial_tape_state[1] = uno;
    initial_tape_state[2] = uno;
    initial_tape_state[3] = uno;
    initial_tape_state[4] = uno;   
    initial_tape_state[5] = uno;

    Tape lista(initial_tape_state, 6, cero);
    std::cout << "6 = " <<  lista << '\n';

    // maquina de turing
    State q0 = {(char *) "q0", 3};
    State q1 = {(char *) "q1", 3};

    State R = {(char *) "R", 2};

    // instrucciones para la maquina que computa la funcion constante cero
    Instruction *in = (Instruction *) malloc((size_t) sizeof(Instruction) * 2);
    in[0] = {q0, uno, cero, q1};
    in[1] = {q1, cero, R, q0};

    // se inicializa la maquina
    TuringMachine tm(in, 2, q0);

    // se realiza el computo
    tm.compute(lista);
    std::cout << "Zero(6) = " << lista << " = 0\n";

    free(initial_tape_state);
    free(in);
}

void succesor_function(){
    std::cout << "Funcion sucesor\n";

    // se crea la cinta que representa el numero 6
    State cero = {(char *) "0", 2};
    State uno = {(char *) "1", 2};

    State *initial_tape_state = (State *) malloc((size_t) sizeof(State) * 6);
    initial_tape_state[0] = uno;
    initial_tape_state[1] = uno;
    initial_tape_state[2] = uno;
    initial_tape_state[3] = uno;
    initial_tape_state[4] = uno;   
    initial_tape_state[5] = uno;

    Tape lista(initial_tape_state, 6, cero);
    std::cout << "6 = " << lista << '\n';

    State q0 = {(char *) "q0", 3};
    State q1 = {(char *) "q1", 3};

    State R = {(char *) "R", 2};

    // instrucciones para la maquina de turing que computa la funcion sucesor
    Instruction *in = (Instruction *) malloc((size_t) sizeof(Instruction) * 2);
    in[0] = {q0, uno, R, q0};
    in[1] = {q0, cero, uno, q1};

    TuringMachine tm(in, 2, q0);

    // se realiza el computo
    tm.compute(lista);
    std::cout << "Succ(6) = " << lista << " = 7\n";

    free(initial_tape_state);
    free(in);
}

void addition_function(){
    // funcion suma. La suma es una funcion numerica de 2 parametros, para codificar
    // una tupla (n1, n2, ..., nk), se concatena la representacion de cada ni separando
    // por cero, ejm: (2, 3) = ... 0 0 1 1 0 1 1 1 0 ...
    std::cout << "Funcion suma\n";

    // se crea la cinta
    State cero = {(char *) "0", 3};
    State uno = {(char *) "1", 3};

    // se va a realizar la suma entre 3 y 2, entonces la tupla de parametros se representa
    // como (1, 1, 1, 0, 1, 1)
    State *initial_tape_state = (State *) malloc((size_t) sizeof(State) * 6);
    initial_tape_state[0] = uno;
    initial_tape_state[1] = uno;
    initial_tape_state[2] = uno;
    initial_tape_state[3] = cero;
    initial_tape_state[4] = uno;   
    initial_tape_state[5] = uno;

    Tape lista(initial_tape_state, 6, cero);
    std::cout << "(3, 2) = " << lista << '\n';

    // maquina de turing
    State q0 = {(char *) "q0", 3};
    State q1 = {(char *) "q1", 3};
    State q2 = {(char *) "q2", 3};

    State R = {(char *) "R", 2};
    State L = {(char *) "L", 2};

    // instrucciones para la maquina de turing que computa la suma entre 2 numeros
    Instruction *in = (Instruction *) malloc((size_t) sizeof(Instruction) * 5);
    in[0] = {q0, uno, R, q0};
    in[1] = {q0, cero, uno, q1};
    in[2] = {q1, uno, R, q1};
    in[3] = {q1, cero, L, q2};
    in[4] = {q2, uno, cero, q2};

    TuringMachine tm(in, 5, q0);

    // se realiza el computo
    tm.compute(lista);
    std::cout << "3 + 2 = " << lista << " = 5\n";

    free(initial_tape_state);
    free(in);
}
