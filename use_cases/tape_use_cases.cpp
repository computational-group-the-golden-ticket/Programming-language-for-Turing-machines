#include <cstdlib>
#include <iostream>

#include "tape.h"

void use_case_1();

int main(){
    use_case_1();

    return 0;
}

// ejemplo de como usar la libreria para crear cintas
void use_case_1(){
    // simbolos que se usaran en la cinta
    State cero = {(char *) "0", 2};
    State uno = {(char *) "1", 2};

    // arreglo usado para pasar la configuracion inicial de la cinta
    State *initial_tape_state = (State *) malloc((size_t) sizeof(State) * 6);

    initial_tape_state[0] = uno;
    initial_tape_state[1] = uno;
    initial_tape_state[2] = uno;
    initial_tape_state[3] = cero;
    initial_tape_state[4] = uno;
    initial_tape_state[5] = uno;

    // simbolo usado para la lectura
    State read_state;

    // por defecto en la cinta se escribira el cero
    Tape tape(initial_tape_state, 6, cero);

    // se imprime la configuracion inicial de la cinta y el estado de la celda actual, 
    // se hace para verificar que la inicializacion fue perfecta
    tape.read_symbol(read_state);
    std::cout << tape << ", " << read_state.symbol << '\n';

    // se mueve el puntero a la izquierda para comprobar que la cinta si crece cuando
    // el puntero se sale del intervalo [0, current_length], debe crecer en una casilla
    tape.move_tape_head_to_left();
    tape.read_symbol(read_state, true);  // se pasa true porque read_state ya almacena un valor
    std::cout << tape << ", " << read_state.symbol << '\n';

    // se escribe el simbolo uno, para ver que el puntero si esta en la posicion correcta
    tape.write_symbol(uno);
    tape.read_symbol(read_state, true);
    std::cout << tape << ", " << read_state.symbol << '\n';

    // para hacer la comprobocion de que la celda tambien crece hacia la derecha
    for (int i = 0; i < 7; i++){
        tape.move_tape_head_to_right();
    }

    // se imprime la cinta
    std::cout << tape << '\n';

    // se libera el espacio usado
    liberate_state_space(read_state);
    free(initial_tape_state);
}
