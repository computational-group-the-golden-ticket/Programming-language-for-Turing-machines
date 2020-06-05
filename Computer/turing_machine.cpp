#include <cstdlib>

#include "types.h"
#include "tape.h"
#include "turing_machine.h"

// para crear una maquina de turing solo se necesita pasar como argumento la lista
// de instrucciones, la cantidad de estas y un estado inicial de la mente
TuringMachine::TuringMachine(Instruction *instructions, int length, State initial_head_state):
        m_number_of_instructions{length} {

    // se configura el estado inicial de la mente, el simbolo del estado de la mente tambien
    // debe ser liberado
    asignate_state(m_tape_head_state, initial_head_state);

    // se debe liberar esta memoria en el destructor
    m_instructions = (Instruction *) malloc((size_t) sizeof(Instruction) * length);
    for (int i = 0; i < length; i++){
        asignate_instruction(m_instructions[i], instructions[i]);
    }

    // se inicializa el mapa
    initialize_map();
}

TuringMachine::~TuringMachine(){
    liberate_state_space(m_tape_head_state);

    // se libera la memoria de cada instruccion
    for (int i = 0; i < m_number_of_instructions; i++){
        liberate_instruction_space(m_instructions[i]);
    }

    free(m_instructions);
}

// este metodo inicializa el diccionario de instrucciones dado que ya se inicializo
// la lista de instrucciones
void TuringMachine::initialize_map(){
    for (int i = 0; i < m_number_of_instructions; i++){
        // en el primer diccionario se indexa por el estado de la mente de la instruccion, y en el 
        // segundo diccionario se indexa por el estado de la celda, el valor final debe ser el indice de
        // la instruccion en la lista de instrucciones 
        m_instructions_map[m_instructions[i].current_mind_state.symbol][m_instructions[i].cell_state.symbol] = i;
    }
}

// este metodo ejecuta las instrucciones sobre la cinta que se le pasa como argumento
void TuringMachine::compute(Tape &list){
    // esta variable tiene el valor de la instruccion actual, como no se obtiene
    // usando la funcion asignate_instruction(que pide espacio nuevo) no necesita
    // liberarse la memoria asociada a esta varible porque se estaria borrando
    // informacion de una instruccion de la lista
    Instruction dummy_instruction = {};

    State dummy_state;
    
    list.read_symbol(dummy_state);
    // se itera mientras hayan instrucciones por ejecutar
    while (true){
        // si el estado de la mente no tiene instruccion asociada en la lista de instrucciones
        if(m_instructions_map.find(m_tape_head_state.symbol) == m_instructions_map.end()){
            break;
        }

        // si el estado de la mente no tiene instruccion en la lista asociada con el estado actual de la celda
        if (m_instructions_map[m_tape_head_state.symbol].find(dummy_state.symbol) == m_instructions_map[m_tape_head_state.symbol].end()){
            break;
        }

        // se obtiene la insturccion actual
        dummy_instruction = m_instructions[m_instructions_map[m_tape_head_state.symbol][dummy_state.symbol]];

        if (dummy_instruction.action.symbol[0] == 'R'){
            // el caracter R corresponde con la accion de moverse a la derecha
            list.move_tape_head_to_right();
        } else if (dummy_instruction.action.symbol[0] == 'L'){
            // el caracter L corresponde con la accion de moverse a la izquierda
            list.move_tape_head_to_left();
        } else{
            // en cualquier otro caso la accion corresponde a copiar el string almacenado en la accion
            list.write_symbol(dummy_instruction.action);
        }

        // la mente cambia de estado una vez se ha ejecutado una instruccion
        asignate_state(m_tape_head_state, dummy_instruction.next_mind_state, true);

        list.read_symbol(dummy_state, true);
    }

    liberate_state_space(dummy_state);
}
