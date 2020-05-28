#include <cstdlib>
#include <iostream>

#include "tape.h"

// la cinta se crea pasando una configuracion inicial de esta por medio del parametro
// initial_tape_state, la longitud de esta configuracion y el valor por defecto que
// se escribe en cada celda de la cinta
Tape::Tape(State *initial_tape_state, int length, State default_value):
        m_tape_head_position{0},
        m_current_length{length}{

    // se pide el espacio inicial para guardar la configuracion inicial de la cinta
    m_tape = (State *) malloc((size_t) sizeof(State) * length);

    for (int i = 0; i < length; i++){
        // se asigna el valor de cada celda a la cinta con la funcion helper
        asignate_state(m_tape[i], initial_tape_state[i]);
    }

    asignate_state(m_default_value, default_value);
}

Tape::~Tape(){
    liberate_state_space(m_default_value);

    // se libera el espacio pedido de forma dinamico
    for (int i = 0; i < m_current_length; i++){
        liberate_state_space(m_tape[i]);
    }

    free(m_tape);
}

// la cinta se va ampliando a medida que se visitan nuevas celdas, con esta funcion
// se obtiene espacio, a la izquierda si se pasa el parametro LEFT y a la derecha de
// la cinta si se pasa RIGHT en to
void Tape::get_space(int length, int to){
    // el espacio a la derecha y a la izquierda se piden de la misma forma, la diferencia
    // es en la asignacion del nuevo valor
    m_tape = (State *) realloc(m_tape, (size_t) sizeof(State) * length);
    m_current_length++;

    // por defecto realloc deja el arreglo como estaba inicialmente, y el espacio se agrega
    // al final
    if (to == RIGHT){
        // se debe escribir el estado por defecto en la celda agregada al final
        asignate_state(m_tape[m_current_length - 1], m_default_value);
    }

    if (to == LEFT){
        // cuando el espacio se pide a la derecha se debe correr todo el arreglo una
        // celda a la derecha
        asignate_state(m_tape[m_current_length - 1], m_tape[m_current_length - 2]);

        for (int i = m_current_length - 2; i > 1; i--){
            asignate_state(m_tape[i], m_tape[i - 1], true);
        }

        // una vez se corrio todo el arreglo se copia el valor por defecto en la primera celda
        asignate_state(m_tape[0], m_default_value, true);
    }
}

// lee el simbolo que esta en la celda actual, el especificado por m_tape_head_position
State Tape::read_symbol(){
    return m_tape[m_tape_head_position];
}

// escribe es simbolo que se pasa como argumento en la celda actual
void Tape::write_symbol(State symbol){
    asignate_state(m_tape[m_tape_head_position], symbol, true);
}

// este metodo mueve la mente a la derecha
void Tape::move_tape_head_to_right(){
    // si m_tape_head_position es mayor que la longitud actual de la cinta
    // entonces se necesita pedir espacio para la nueva celda en la que estara la mente
    if (m_tape_head_position >= m_current_length - 1){
        get_space(m_current_length + 1, RIGHT);
    }

    m_tape_head_position++;
}

// este metodo mueve la mente a la izquierda
void Tape::move_tape_head_to_left(){
    m_tape_head_position--;

    // si m_tape_head_position es menor que cero entonces se necesita pedir espacio
    // para la nueva celda en la que estara la mente
    if (m_tape_head_position < 0){
        get_space(m_current_length + 1, LEFT);

        m_tape_head_position = 0;
    }
}

// la structura State tiene un puntero como valor, esta funcion facilita el proceso de
// asignacion por copia de valores
std::ostream& operator<< (std::ostream &out, const Tape &list){
    // se imprime la cinta como una tupla separado por espacios con cada elemento
    // encerrado por comillas ejm: ("s0" "s1" "s2")
    std::cout << '(';
    for (int i = 0; i < list.m_current_length; i++){
        std::cout << '"' << list.m_tape[i].symbol << '"';

        if (i < list.m_current_length - 1){
            std::cout << ' ';
        }
    }

    std::cout << ')';

    return out;
}

// la structura State tiene un puntero como atributo, esta funcion facilita el proceso de
// asignacion por copia de valores
void asignate_state(State &target, State source, bool re_asign){
    target.length = source.length;

    if (re_asign){
        free(target.symbol);
    }

    // este espacio debe ser liberado con free luego que la ejecucion del programa acabe
    target.symbol = (char *) malloc((size_t) sizeof(char) * target.length);

    for (int i = 0; i < target.length; i++){
        target.symbol[i] = source.symbol[i];
    }
}

void liberate_state_space(State &state){
    free(state.symbol);
}
