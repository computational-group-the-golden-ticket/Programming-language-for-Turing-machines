#include <cstdlib>

#include "turing_machine.h"
#include "token.h"
#include "ast.h"

Program::Program(): m_current_length{0}{
    m_nodes = (Node *) malloc((size_t) sizeof(Node) * 0);
}

Program::~Program(){
    free(m_nodes);
}

void Program::get_space(){
    m_nodes = (Node *) realloc(m_nodes, (size_t) sizeof(Node) * (++m_current_length));
}

void Program::add_node(Node node){
    get_space();

    asignate_node(m_nodes[m_current_length - 1], node);
}

DefinitionStatement::DefinitionStatement(){
}

DefinitionStatement::DefinitionStatement(Instruction *instructions, int length, Token identifier):
        m_number_of_instructions{length} {

    m_instructions = (Instruction *) malloc((size_t) sizeof(Instruction) * length);

    for (int i = 0; i < length; i++){
        asignate_instruction(m_instructions[i], instructions[i]);
    }

    asignate_token(m_identifier, identifier);
}

// esto libera el espacio usado para almacenar el simbolo de cada atributo de la instruccion
void DefinitionStatement::liberate_instruction_space(Instruction &instruction){
    free(instruction.current_mind_state.symbol);
    free(instruction.cell_state.symbol);
    free(instruction.action.symbol);
    free(instruction.next_mind_state.symbol);
}

DefinitionStatement::~DefinitionStatement(){
    // se libera el espacio del token
    free(m_identifier.value);

    // se libera la memoria de cada instruccion
    for (int i = 0; i < m_number_of_instructions; i++){
        liberate_instruction_space(m_instructions[i]);
    }

    free(m_instructions);
}


// para los nodos de asignacion
AssignamentStatement::AssignamentStatement(){
}

AssignamentStatement::AssignamentStatement(Token tape_identifier):
        m_tape_identifier{Token {}},
        m_has_node{false} {
    asignate_token(m_tape_identifier, tape_identifier);
}

AssignamentStatement::AssignamentStatement(State *initial_tape_state, int length, Token identifier):
        m_current_length{length},
        m_tape_identifier{Token {}},
        m_has_node{false} {

    m_tape = (State *) malloc((size_t) sizeof(State) * length);

    for (int i = 0; i < length; i++){
        asignate_state(m_tape[i], initial_tape_state[i]);
    }

    asignate_token(m_tape_identifier, identifier);
}

AssignamentStatement::~AssignamentStatement(){
    // free(m_tape_identifier.value);
    if (m_has_node){
        // free(m_node);
    } else {
        
    }

    for (int i = 0; i < m_current_length; i++){
        // free(m_tape[i].symbol);
    }

    // free(m_tape);
}

void AssignamentStatement::add_node(Node node){
    m_node = (Node *) malloc((size_t) sizeof(Node) * 1);

    asignate_node(m_node[0], node);

    m_has_node = true;
}

bool AssignamentStatement::has_node(){
    return m_has_node;
}


// para los nodos de aplicacion
ApplicationStatement::ApplicationStatement(){
}

ApplicationStatement::ApplicationStatement(Token turing_machine_identifier):
        m_has_node{false} {
    
    asignate_token(m_turing_machine_identifier, turing_machine_identifier);
}

ApplicationStatement::ApplicationStatement(Token turing_machine_identifier, Token tape_identifier):
        m_has_node{false} {
    asignate_token(m_turing_machine_identifier, turing_machine_identifier);
    asignate_token(m_tape_identifier, tape_identifier);
}

ApplicationStatement::~ApplicationStatement(){
    free(m_turing_machine_identifier.value);

    if (!m_has_node){
        free(m_tape_identifier.value);
    }

    free(m_node);
}

void ApplicationStatement::add_node(Node node){
    m_node = (Node *) malloc((size_t) sizeof(Node) * 1);

    asignate_node(m_node[0], node);

    m_has_node = true;
}

bool ApplicationStatement::has_node(){
    return m_has_node;
}

void asignate_node(Node &target, Node &source){
    switch (source.type){
    case DEFINITION_STATEMENT:
        target.definition_statement = source.definition_statement;
        break;

    case ASSIGNAMENT_STATEMENT:
        target.assignament_statement = source.assignament_statement;
        break;

    case APPLICATION_STATEMENT:
        target.application_statement = source.application_statement;
        break;

    default:
        break;
    }
}
