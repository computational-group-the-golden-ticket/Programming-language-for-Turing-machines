#ifndef TURING_MACHINE_H
#define TURING_MACHINE_H

#include <cstring>
#include <map>

#include "types.h"
#include "tape.h"

// esta funcion  es necesaria para que el diccionario cuyas claves son char* pueda realizar
// busquedas por comparacion del valor y no de la direccion
struct cmp_str{
    bool operator()(char const *a, char const *b) const {
        return std::strcmp(a, b) < 0;
    }
};

// representa una maquina de turing
class TuringMachine{
private:
    // estado actual del puntero lectura/escritura
    State m_tape_head_state;

    // numero de instrucciones e instrucciones de la maquina de turing
    int m_number_of_instructions;
    Instruction *m_instructions;

    // diccionario que guarda la informacion de la posicion de una instruccion en el
    // arreglo de instrucciones dado que se conoce el estado de la mente y el estado
    // de la celda ejm: m_instructions_map[q0][s0] = 0, donde la instruccion 0 en la
    // lista de instrucciones es la estructura {{q0, 2}, {s0, 2}, {R, 1}, {q1, 2}}
    std::map<char *, std::map<char *, int, cmp_str>, cmp_str> m_instructions_map;

    // este metodo inicializa el diccionario de instrucciones dado que ya se inicializo
    // la lista de instrucciones
    void initialize_map();
public:
    // para crear una maquina de turing solo se necesita pasar como argumento la lista
    // de instrucciones, la cantidad de estas y un estado inicial de la mente
    TuringMachine(Instruction *instruction, int length, State initial_head_state);
    ~TuringMachine();

    // este metodo ejecuta las instrucciones sobre la cinta que se le pasa como argumento
    void compute(Tape &list);
};

#endif
