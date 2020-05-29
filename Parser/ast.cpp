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

DefinitionStatement::DefinitionStatement():
        m_number_of_instructions{0},
        m_instructions{nullptr}{
}


DefinitionStatement::DefinitionStatement(const DefinitionStatement &definition_statement):
        m_number_of_instructions{0},
        m_instructions{nullptr}{
    // en el caso en el que si se tengan instrucciones
    if(definition_statement.m_number_of_instructions != 0){
        m_number_of_instructions = definition_statement.m_number_of_instructions;

        m_instructions = (Instruction *) malloc((size_t) sizeof(Instruction) * m_number_of_instructions);
        for (int i = 0; i < m_number_of_instructions; i++){
            asignate_instruction(m_instructions[i], definition_statement.m_instructions[i]);
        }

        asignate_token(m_turing_machine_identifier, definition_statement.m_turing_machine_identifier);
    }
}

DefinitionStatement::DefinitionStatement(Instruction *instructions, int length, Token identifier):
        m_number_of_instructions{length} {

    m_instructions = (Instruction *) malloc((size_t) sizeof(Instruction) * length);

    for (int i = 0; i < length; i++){
        asignate_instruction(m_instructions[i], instructions[i]);
    }

    asignate_token(m_turing_machine_identifier, identifier);
}

DefinitionStatement::~DefinitionStatement(){
    if(m_number_of_instructions != 0){
        // se libera el espacio del token
        liberate_token_space(m_turing_machine_identifier);

        // se libera la memoria de cada instruccion
        for (int i = 0; i < m_number_of_instructions; i++){
            liberate_instruction_space(m_instructions[i]);
        }

        free(m_instructions);
    }
}

DefinitionStatement& DefinitionStatement::operator=(const DefinitionStatement& definition_statement){
    // se verifica si se esta haciendo autoasignacion
	if (this == &definition_statement){
        return *this;
    }

    // en este caso se debe liberar la memoria que se tenga
    if(m_number_of_instructions){
        // se libera el espacio del token
        liberate_token_space(m_turing_machine_identifier);

        // se libera la memoria de cada instruccion
        for (int i = 0; i < m_number_of_instructions; i++){
            liberate_instruction_space(m_instructions[i]);
        }

        free(m_instructions);
    }

    m_number_of_instructions = definition_statement.m_number_of_instructions;

    m_instructions = (Instruction *) malloc((size_t) sizeof(Instruction) * m_number_of_instructions);
    for (int i = 0; i < m_number_of_instructions; i++){
        asignate_instruction(m_instructions[i], definition_statement.m_instructions[i]);
    }

    asignate_token(m_turing_machine_identifier, definition_statement.m_turing_machine_identifier);

    return *this;
}

// para los nodos de asignacion
AssignamentStatement::AssignamentStatement():
    m_current_length{0},
    m_tape{nullptr},
    m_has_node{false}{
}

// una cinta se puede crear desde una aplicacion de funcion, este es el caso,
// solo se necesita una referencia a la cinta que se va a crear
AssignamentStatement::AssignamentStatement(Token tape_identifier):
        m_current_length{0},
        m_tape{nullptr},
        m_has_node{false} {
    asignate_token(m_tape_identifier, tape_identifier);
}

AssignamentStatement::AssignamentStatement(State *initial_tape_state, int length, Token identifier):
        m_current_length{length},
        m_has_node{false} {

    m_tape = (State *) malloc((size_t) sizeof(State) * length);

    for (int i = 0; i < length; i++){
        asignate_state(m_tape[i], initial_tape_state[i]);
    }

    asignate_token(m_tape_identifier, identifier);
}

// se esta usando inicializacion por copia
AssignamentStatement::AssignamentStatement(const AssignamentStatement &assignament_statement){
    // si se esta creando una cinta a mano
    if(assignament_statement.m_tape != nullptr){
        m_has_node = false;

        m_current_length = assignament_statement.m_current_length;
        m_tape = (State *) malloc((size_t) sizeof(State) * m_current_length);

        for (int i = 0; i < m_current_length; i++){
            asignate_state(m_tape[i], assignament_statement.m_tape[i]);
        }

        asignate_token(m_tape_identifier, assignament_statement.m_tape_identifier);
    } else if(assignament_statement.m_has_node){
        // en este caso se esta creando una cinta desde una aplicacion de funcion
        asignate_token(m_tape_identifier, assignament_statement.m_tape_identifier);
    } else{
        // este es el caso de un campo vacio en el nodo
        m_current_length = 0;
        m_tape = nullptr;
        m_has_node = false;
    }

    if (assignament_statement.m_has_node){
        add_node(assignament_statement.m_node[0]);
    }
}

void AssignamentStatement::liberate_memory(){
    if (m_has_node){
        liberate_node_space(m_node[0]);

        m_has_node = false;
        free(m_node);
    }

    if (m_tape_identifier.length != 0){
        liberate_token_space(m_tape_identifier);
    }

    if(m_tape != nullptr){
        for (int i = 0; i < m_current_length; i++){
            liberate_state_space(m_tape[i]);
        }

        free(m_tape);
    }
}

AssignamentStatement::~AssignamentStatement(){
    liberate_memory();
}

// se esta haciendo uso del operador de asignacion
AssignamentStatement& AssignamentStatement::operator=(const AssignamentStatement& assignament_statement){
    // se verifica si se esta haciendo autoasignacion
	if (this == &assignament_statement){
        return *this;
    }

    // en el caso en que se tenga memoria ocupada
    liberate_memory();

    // al igual que con el constructor de copia se tienen 3 casos
    if(assignament_statement.m_tape != nullptr){
        m_has_node = false;

        m_current_length = assignament_statement.m_current_length;
        m_tape = (State *) malloc((size_t) sizeof(State) * m_current_length);

        for (int i = 0; i < m_current_length; i++){
            asignate_state(m_tape[i], assignament_statement.m_tape[i]);
        }

        asignate_token(m_tape_identifier, assignament_statement.m_tape_identifier);
    } else if(assignament_statement.m_has_node){
        // en este caso se esta creando una cinta desde una aplicacion de funcion
        add_node(assignament_statement.m_node[0]);

        asignate_token(m_tape_identifier, assignament_statement.m_tape_identifier);
    } else{
        // este es el caso de un campo vacio en el nodo
        m_current_length = 0;
        m_tape = nullptr;
        m_has_node = false;
    }

    return *this;
}

void AssignamentStatement::add_node(Node &node){
    m_node = (Node *) malloc((size_t) sizeof(Node));
    asignate_node(m_node[0], node);

    m_has_node = true;
}

bool AssignamentStatement::has_node(){
    return m_has_node;
}

// un nodo en el arbol que representa a el programa se define como una estructura con
// campos para datos de tipo: DefinitionStatement, AssignamentStatement y ApplicationStatement
// dado que solo puede haber un valor a la vez, se necesita tener un constructor sin parametros
// para inicializar los campos vacios
ApplicationStatement::ApplicationStatement():
    m_has_node{false} {
}

// este constructor se usa para el caso en el que la cinta es el resultado de la
// aplicacion de una maquina de turing a una cinta ya existente
ApplicationStatement::ApplicationStatement(Token turing_machine_identifier):
        m_has_node{false} {
    
    asignate_token(m_turing_machine_identifier, turing_machine_identifier);
}

ApplicationStatement::ApplicationStatement(Token turing_machine_identifier, Token tape_identifier):
        m_has_node{false} {
    asignate_token(m_turing_machine_identifier, turing_machine_identifier);
    asignate_token(m_tape_identifier, tape_identifier);
}

// se esta usando inicializacion por copia
ApplicationStatement::ApplicationStatement(const ApplicationStatement &application_statement):
        m_has_node{false}{
    if (application_statement.m_has_node){
        m_has_node = true;

        m_node = (Node *) malloc((size_t) sizeof(Node));
        asignate_node(m_node[0], application_statement.m_node[0]);
    }
    
    if (application_statement.m_tape_identifier.length != 0){
        asignate_token(m_turing_machine_identifier, application_statement.m_turing_machine_identifier);
        asignate_token(m_tape_identifier, application_statement.m_tape_identifier);
    } else if(application_statement.m_turing_machine_identifier.length != 0){
        asignate_token(m_turing_machine_identifier, application_statement.m_turing_machine_identifier);
    }else{
    }
}

void ApplicationStatement::liberate_memory(){
    if (m_has_node){
        liberate_node_space(m_node[0]);
        free(m_node);
    }

    if (m_tape_identifier.length != 0){
        liberate_token_space(m_turing_machine_identifier);
        liberate_token_space(m_tape_identifier);
    } else if(m_turing_machine_identifier.length != 0){
        liberate_token_space(m_turing_machine_identifier);
    } else{
        // no se necesita liberar nada
    }
}

ApplicationStatement::~ApplicationStatement(){
    liberate_memory();
}

// se esta haciendo uso del operador de asignacion
ApplicationStatement& ApplicationStatement::operator=(const ApplicationStatement& application_statement){
    // se verifica si se esta haciendo autoasignacion
	if (this == &application_statement){
        return *this;
    }

    // en el caso que se tenga memoria ocupada
    liberate_memory();

    if (application_statement.m_has_node){
        add_node(application_statement.m_node[0]);
    }

    if (application_statement.m_tape_identifier.length != 0){
        asignate_token(m_turing_machine_identifier, application_statement.m_turing_machine_identifier);
        asignate_token(m_tape_identifier, application_statement.m_tape_identifier);
    } else if(application_statement.m_turing_machine_identifier.length != 0){
        asignate_token(m_turing_machine_identifier, application_statement.m_turing_machine_identifier);
    }else{
    }

    return *this;
}

void ApplicationStatement::add_node(Node node){
    m_node = (Node *) malloc((size_t) sizeof(Node));
    asignate_node(m_node[0], node);

    m_has_node = true;
}

bool ApplicationStatement::has_node(){
    return m_has_node;
}

void asignate_node(Node &target, const Node &source){
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

void liberate_node_space(Node &node){
    switch (node.type){
        case DEFINITION_STATEMENT:
            node.definition_statement.~DefinitionStatement();
            break;

        case ASSIGNAMENT_STATEMENT:
            node.assignament_statement.~AssignamentStatement();
            break;

        case APPLICATION_STATEMENT:
            node.application_statement.~ApplicationStatement();
            break;

        default:
            break;
    }
}
