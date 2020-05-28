#ifndef TURING_MACHINE_H
#define TURING_MACHINE_H

#include <cstring>
#include <map>

#include "tape.h"

// esto representa una instruccion en una maquina de turing, se esta usando la notacion
// en cuadruplas
struct {
    State current_mind_state;
    State cell_state;
    State action;
    State next_mind_state;
} typedef Instruction;

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
    // estado actual de la mente
    State m_tape_head_state;

    // numero de instrucciones e instrucciones de la maquina de turing
    int m_number_of_instructions;
    Instruction *m_instructions;  // este puntero debe ser eliminado con free

    // diccionario que guarda la informacion de la posicion de una instruccion en el
    // arreglo de instrucciones dado que se conoce el estado de la mente y el estado
    // de la celda ejm: m_instructions_map[q0][s0] = 0, donde la instruccion 0 en la
    // lista de instrucciones es la estructura {{q0, 2}, {s0, 2}, {R, 1}, {q1, 2}}
    std::map<char *, std::map<char *, int, cmp_str>, cmp_str> m_instructions_map;

    // este metodo inicializa el diccionario de instrucciones dado que ya se inicializo
    // la lista de instrucciones
    void initialize_map();

    // esto libera el espacio usado para almacenar el simbolo de cada atributo de la instruccion
    void liberate_instruction_space(Instruction &instruction);
public:
    // para crear una maquina de turing solo se necesita pasar como argumento la lista
    // de instrucciones, la cantidad de estas y un estado inicial de la mente
    TuringMachine(Instruction *instruction, int length, State initial_head_state);
    ~TuringMachine();

    // este metodo ejecuta las instrucciones sobre la cinta que se le pasa como argumento
    void compute(Tape &list);
};

// la structura Instruction tiene estructuras State como valores,
// esta funcion facilita el proceso de asignacion por copia de valores
void asignate_instruction(Instruction &target, Instruction &source, bool re_asign=false);

#endif
