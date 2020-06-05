#include <cstdlib>

#include "types.h"

// la structura State tiene un puntero como atributo, esta funcion facilita el proceso de
// asignacion por copia de valores
void asignate_state(State &target, State &source, bool re_asign){
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

// la structura Instruction tiene estructuras State como valores,
// esta funcion facilita el proceso de asignacion por copia de valores
void asignate_instruction(Instruction &target, Instruction &source, bool re_asign){
    // asignar una instruccion corresponde a asignar componente a componente
    asignate_state(target.current_mind_state, source.current_mind_state, re_asign);
    asignate_state(target.cell_state, source.cell_state, re_asign);
    asignate_state(target.action, source.action, re_asign);
    asignate_state(target.next_mind_state, source.next_mind_state, re_asign);
}

void liberate_instruction_space(Instruction &instruction){
    free(instruction.current_mind_state.symbol);
    free(instruction.cell_state.symbol);
    free(instruction.action.symbol);
    free(instruction.next_mind_state.symbol);
}
