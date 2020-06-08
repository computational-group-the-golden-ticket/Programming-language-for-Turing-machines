#ifndef TYPES_H
#define TYPES_H

// direcciones en las que se puede mover el puntero de lectura/escritura
#define LEFT 0
#define RIGHT 1

// esto representa o un estado de la mente o un estado de una celda en una
// maquina de turing
struct {
    char *symbol;
    // la longitud debe ser tal que en symbol se almacena el valor como tal
    // y el caracter de terminacion del string ('\0')
    int length;
} typedef State;

// esto representa una instruccion en una maquina de turing, se esta usando la notacion
// en cuadruplas. "qi sj A qk", donde 'qi' es el estado actual de la mente, 'sj' es el
// estado de la celda actual, 'A' es la accion a realizar y 'qk' es el nuevo estado de la mente
struct {
    State current_mind_state;
    State cell_state;
    State action;
    State next_mind_state;
} typedef Instruction;

// la structura State tiene un puntero como atributo, esta funcion facilita el proceso de
// asignacion por copia de valores
void asignate_state(State &target, State &source, bool re_asign=false);
void liberate_state_space(State &target);

// la structura Instruction tiene estructuras State como valores,
// esta funcion facilita el proceso de asignacion por copia de valores
void asignate_instruction(Instruction &target, Instruction &source, bool re_asign=false);
void liberate_instruction_space(Instruction &instruction);

#endif
