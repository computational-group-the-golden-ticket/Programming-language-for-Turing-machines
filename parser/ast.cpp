#include <cstdlib>
#include <cstdio>

#include "types.h"
#include "token.h"
#include "ast.h"

DefinitionStatement::DefinitionStatement():
        m_number_of_instructions{0},
        m_instructions{nullptr}{
}

// se esta usando inicializacion por copia
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

void DefinitionStatement::liberate_memory(){
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

DefinitionStatement::~DefinitionStatement(){
    liberate_memory();
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
    m_node{nullptr},
    m_has_node{false}{
}

// una cinta se puede crear desde una aplicacion de funcion, este es el caso,
// solo se necesita una referencia a la cinta que se va a crear
AssignamentStatement::AssignamentStatement(Token tape_identifier): AssignamentStatement(){
    asignate_token(m_tape_identifier, tape_identifier);
}

AssignamentStatement::AssignamentStatement(State *initial_tape_state, int length, Token tape_identifier):
        AssignamentStatement(tape_identifier){
    
    m_current_length = length;
    m_tape = (State *) malloc((size_t) sizeof(State) * length);

    for (int i = 0; i < length; i++){
        asignate_state(m_tape[i], initial_tape_state[i]);
    }
}

// se esta usando inicializacion por copia
AssignamentStatement::AssignamentStatement(const AssignamentStatement &assignament_statement):
        AssignamentStatement(){
    asignate_token(m_tape_identifier, assignament_statement.m_tape_identifier);

    if (assignament_statement.m_has_node){
        m_has_node = true;

        m_node = (Node *) malloc((size_t) sizeof(Node));
        asignate_node(m_node[0], assignament_statement.m_node[0]);
    }

    if (assignament_statement.m_tape != nullptr){
        m_current_length = assignament_statement.m_current_length;
        m_tape = (State *) malloc((size_t) sizeof(State) * m_current_length);

        for (int i = 0; i < m_current_length; i++){
            asignate_state(m_tape[i], assignament_statement.m_tape[i]);
        }
    }
}

void AssignamentStatement::liberate_memory(){
    if (m_tape_identifier.value != nullptr){
        liberate_token_space(m_tape_identifier);
    }

    if (m_has_node){
        m_has_node = false;

        liberate_node_space(m_node[0]);
        free(m_node);
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

    m_current_length = 0;
    m_tape = nullptr;
    m_node = nullptr;
    m_has_node = false;

    asignate_token(m_tape_identifier, assignament_statement.m_tape_identifier);

    if (assignament_statement.m_has_node){
        m_has_node = true;

        m_node = (Node *) malloc((size_t) sizeof(Node));

        m_node[0].type = APPLICATION_STATEMENT;
        m_node[0].application_statement = assignament_statement.m_node[0].application_statement;

        m_has_node = true;
    }

    if (m_tape != nullptr){
        m_current_length = assignament_statement.m_current_length;
        m_tape = (State *) malloc((size_t) sizeof(State) * m_current_length);

        for (int i = 0; i < m_current_length; i++){
            asignate_state(m_tape[i], assignament_statement.m_tape[i]);
        }
    }

    return *this;
}

void AssignamentStatement::add_node(const Node &node){
    m_node = (Node *) malloc((size_t) sizeof(Node));
    // m_node[0] = {};

    asignate_node(m_node[0], node);

    m_has_node = true;
}

bool AssignamentStatement::has_node() const{
    return m_has_node;
}

Node AssignamentStatement::get_node() const{
    return m_node[0];
}


// un nodo en el arbol que representa a el programa se define como una estructura con
// campos para datos de tipo: DefinitionStatement, AssignamentStatement y ApplicationStatement
// dado que solo puede haber un valor a la vez, se necesita tener un constructor sin parametros
// para inicializar los campos vacios
ApplicationStatement::ApplicationStatement():
    m_node{nullptr},
    m_has_node{false} {
}

// este constructor se usa para el caso en el que la cinta es el resultado de la
// aplicacion de una maquina de turing a una cinta ya existente
ApplicationStatement::ApplicationStatement(Token turing_machine_identifier):
        ApplicationStatement(){
    asignate_token(m_turing_machine_identifier, turing_machine_identifier);
}

ApplicationStatement::ApplicationStatement(Token turing_machine_identifier, Token tape_identifier):
        ApplicationStatement() {
    asignate_token(m_turing_machine_identifier, turing_machine_identifier);
    asignate_token(m_tape_identifier, tape_identifier);
}

// se esta usando inicializacion por copia
ApplicationStatement::ApplicationStatement(const ApplicationStatement &application_statement):
        ApplicationStatement() {
    if (application_statement.m_has_node){
        m_has_node = true;

        m_node = (Node *) malloc((size_t) sizeof(Node));
        asignate_node(m_node[0], application_statement.m_node[0]);
    }
    
    if (application_statement.m_tape_identifier.value != nullptr){
        asignate_token(m_tape_identifier, application_statement.m_tape_identifier);
    }

    if(application_statement.m_turing_machine_identifier.value != nullptr){
        asignate_token(m_turing_machine_identifier, application_statement.m_turing_machine_identifier);
    }
}

void ApplicationStatement::liberate_memory(){
    if (m_has_node){
        m_has_node = false;
        liberate_node_space(m_node[0]);
        free(m_node);
    }

    if (m_tape_identifier.value != nullptr){
        liberate_token_space(m_tape_identifier);
    }

    if(m_turing_machine_identifier.value != nullptr){
        liberate_token_space(m_turing_machine_identifier);
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

    m_node = nullptr;
    m_has_node = false;

    if (application_statement.m_has_node){
        m_has_node = true;

        m_node = (Node *) malloc((size_t) sizeof(Node));
        asignate_node(m_node[0], application_statement.m_node[0]);

        // TODO: se debe mirar si los atributos de m_node tiene subnodos
        /*if (application_statement.m_node[0].assignament_statement.has_node()){
            asignate_node();
        }

        if (application_statement.m_node[0].applications_statement.has_node()){
        }*/
    }

    if (application_statement.m_tape_identifier.value != nullptr){
        asignate_token(m_tape_identifier, application_statement.m_tape_identifier);
    }

    if(application_statement.m_turing_machine_identifier.value != nullptr){
        asignate_token(m_turing_machine_identifier, application_statement.m_turing_machine_identifier);
    }

    return *this;
}

void ApplicationStatement::add_node(Node &node){
    m_node = (Node *) malloc((size_t) sizeof(Node));
    // m_node[0] = {};

    asignate_node(m_node[0], node);

    m_has_node = true;
}

bool ApplicationStatement::has_node() const{
    return m_has_node;
}

Node ApplicationStatement::get_node() const{
    return m_node[0];
}

Program::Program(): m_current_length{0}{
    m_nodes = (Node *) malloc((size_t) sizeof(Node) * 0);
}

Program::~Program(){
    for (int i = 0; i < m_current_length; i++){
        liberate_node_space(m_nodes[i]);
    }

    free(m_nodes);
}

void Program::get_space(){
    m_nodes = (Node *) realloc(m_nodes, (size_t) sizeof(Node) * (++m_current_length));
}

void Program::add_node(Node &node){
    get_space();

    asignate_node(m_nodes[m_current_length - 1], node);
}

// TODO: esta funcion debe ser refactorizada para poder usarse
void asignate_node(Node &target, const Node &source){
    /*printf("ENTRO\n");

    std::cout << source << '\n';
    std::cout << target << '\n';

    printf("NODE?: %d %d\n", target.application_statement.has_node(), target.type);*/

    target.type = source.type;

    switch (source.type){
        case DEFINITION_STATEMENT:
            // printf("AQUI 1\n");
            target.definition_statement = source.definition_statement;
            break;

        case ASSIGNAMENT_STATEMENT:
            // printf("AQUI 2\n");
            target.assignament_statement = source.assignament_statement;
            break;

        case APPLICATION_STATEMENT:
            /*printf("AQUI 3\n");
            std::cout << source << '\n';
            std::cout << target << '\n';*/
            target.application_statement = source.application_statement;
            // printf("ERROR\n");
            break;

        default:
            break;
    }

    // printf("SALIO\n");
}

std::ostream& operator<< (std::ostream &out, const Node &node){
    switch (node.type){
        case DEFINITION_STATEMENT:
            out << "DEFINITION STATEMENT";
            break;

        case ASSIGNAMENT_STATEMENT:
            out << "ASSIGNAMENT STATEMENT";

            if (node.assignament_statement.has_node()){
                out << "\n    " << node.assignament_statement.get_node();
            }

            break;

        case APPLICATION_STATEMENT:
            out << "APPLICATION STATEMENT";

            if (node.application_statement.has_node()){
                out << "\n    " << node.application_statement.get_node();
            }

            break;

        default:
            out << "NULL NODE";
            break;
    }

    return out;
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
