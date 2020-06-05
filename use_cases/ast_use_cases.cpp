#include <cstdlib>

#include "types.h"
#include "token.h"
#include "ast.h"

void use_case_1();
void use_case_2_1();
void use_case_2_2();
void use_case_3_1();
void use_case_3_2();
void use_case_4();

int main(){
    // use_case_1();
    // use_case_2_1();
    // use_case_2_2();
    // use_case_3_1();
    // use_case_3_2();
    use_case_4();
}

void use_case_1(){
    // se crea una lista de instrucciones
    State cero = {(char *) "s0", 3};
    State uno = {(char *) "s1", 3};

    State q0 = {(char *) "q0", 3};
    State q1 = {(char *) "q1", 3};

    State R = {(char *) "R", 2};

    Instruction *in = (Instruction *) malloc((size_t) sizeof(Instruction) * 2);
    in[0] = {q0, uno, cero, q1};
    in[1] = {q1, cero, R, q0};

    Token identifier = {IDENTIFIER, 5, (char *) "Zero"};

    // lo siguiente se realiza para verificar que la inicializacion por copia y el operador
    // de asignacion funcion bien, sin causar fugas de memoria
    DefinitionStatement definition_statement1 = DefinitionStatement(in, 2, identifier);

    DefinitionStatement definition_statement2;
    definition_statement2 = definition_statement1;

    DefinitionStatement definition_statement3(definition_statement2);

    definition_statement1 = definition_statement3;

    free(in);
}

void use_case_2_1(){
    // se crea configuracion inicial de la cinta
    State cero = {(char *) "0", 2};
    State uno = {(char *) "1", 2};

    State *initial_tape_state = (State *) malloc((size_t) sizeof(State) * 6);

    initial_tape_state[0] = uno;
    initial_tape_state[1] = uno;
    initial_tape_state[2] = uno;
    initial_tape_state[3] = cero;
    initial_tape_state[4] = uno;
    initial_tape_state[5] = uno;

    Token identifier = {IDENTIFIER, 5, (char *) "tape"};

    // lo siguiente se realiza para verificar que la inicializacion por copia y el operador
    // de asignacion funcion bien, sin causar fugas de memoria
    AssignamentStatement assignament_statement1 = AssignamentStatement(initial_tape_state, 6, identifier);

    AssignamentStatement assignament_statement2;
    assignament_statement2 = assignament_statement1;

    AssignamentStatement assignament_statement3(assignament_statement2);

    assignament_statement1 = assignament_statement3;

    free(initial_tape_state);
}

void use_case_2_2(){
    Token tape_identifier1 = {IDENTIFIER, 5, (char *) "tape1"};
    Token turing_machine_identifier = {IDENTIFIER, 5, (char *) "Zero"};

    // lo siguiente se realiza para verificar que la inicializacion por copia y el operador
    // de asignacion funcion bien, sin causar fugas de memoria
    ApplicationStatement application_statement1 = ApplicationStatement(turing_machine_identifier, tape_identifier1);

    ApplicationStatement application_statement2;
    application_statement2 = application_statement1;

    ApplicationStatement application_statement3(application_statement2);

    application_statement1 = application_statement3;

    Token tape_identifier2 = {IDENTIFIER, 5, (char *) "tape2"};

    // lo siguiente se realiza para verificar que la inicializacion por copia y el operador
    // de asignacion funcion bien, sin causar fugas de memoria
    AssignamentStatement assignament_statement1(tape_identifier2);

    Node node = {{}, {}, application_statement1, APPLICATION_STATEMENT};

    assignament_statement1.add_node(node);
}


void use_case_3_1(){
    Token tape_identifier = {IDENTIFIER, 5, (char *) "tape"};
    Token turing_machine_identifier = {IDENTIFIER, 5, (char *) "Zero"};

    // lo siguiente se realiza para verificar que la inicializacion por copia y el operador
    // de asignacion funcion bien, sin causar fugas de memoria
    ApplicationStatement application_statement1 = ApplicationStatement(turing_machine_identifier, tape_identifier);

    ApplicationStatement application_statement2;
    application_statement2 = application_statement1;

    ApplicationStatement application_statement3(application_statement2);

    application_statement1 = application_statement3;

    Node node = {{}, {}, application_statement1, APPLICATION_STATEMENT};
}

void use_case_3_2(){
    Token tape_identifier1 = {IDENTIFIER, 5, (char *) "tape1"};
    Token turing_machine_identifier1 = {IDENTIFIER, 5, (char *) "Zero"};

    Token turing_machine_identifier2 = {IDENTIFIER, 5, (char *) "tape2"};

    // lo siguiente se realiza para verificar que la inicializacion por copia y el operador
    // de asignacion funcion bien, sin causar fugas de memoria
    ApplicationStatement application_statement1 = ApplicationStatement(turing_machine_identifier1, tape_identifier1);

    ApplicationStatement application_statement2 = ApplicationStatement(turing_machine_identifier2);

    Node node = {{}, {}, application_statement2, APPLICATION_STATEMENT};

    application_statement2.add_node(node);
}

void use_case_4(){
    // nodo 1
    // se crea una lista de instrucciones
    State cero = {(char *) "s0", 3};
    State uno = {(char *) "s1", 3};

    State q0 = {(char *) "q0", 3};
    State q1 = {(char *) "q1", 3};

    State R = {(char *) "R", 2};

    Instruction *in = (Instruction *) malloc((size_t) sizeof(Instruction) * 2);
    in[0] = {q0, uno, cero, q1};
    in[1] = {q1, cero, R, q0};

    Token identifier1 = {IDENTIFIER, 5, (char *) "Zero"};

    // lo siguiente se realiza para verificar que la inicializacion por copia y el operador
    // de asignacion funcion bien, sin causar fugas de memoria
    DefinitionStatement definition_statement = DefinitionStatement(in, 2, identifier1);
    Node node1 = {definition_statement, {}, {}, DEFINITION_STATEMENT};

    // nodo 2
    // se crea configuracion inicial de la cinta
    State *initial_tape_state = (State *) malloc((size_t) sizeof(State) * 6);

    initial_tape_state[0] = uno;
    initial_tape_state[1] = uno;
    initial_tape_state[2] = uno;
    initial_tape_state[3] = cero;
    initial_tape_state[4] = uno;
    initial_tape_state[5] = uno;

    Token identifier2 = {IDENTIFIER, 5, (char *) "tape"};

    // lo siguiente se realiza para verificar que la inicializacion por copia y el operador
    // de asignacion funcion bien, sin causar fugas de memoria
    AssignamentStatement assignament_statement1 = AssignamentStatement(initial_tape_state, 6, identifier2);
    Node node2 = {{}, assignament_statement1, {}, ASSIGNAMENT_STATEMENT};

    // nodo 3
    Token tape_identifier1 = {IDENTIFIER, 5, (char *) "tape1"};
    Token turing_machine_identifier = {IDENTIFIER, 5, (char *) "Zero"};

    // lo siguiente se realiza para verificar que la inicializacion por copia y el operador
    // de asignacion funcion bien, sin causar fugas de memoria
    ApplicationStatement application_statement1 = ApplicationStatement(turing_machine_identifier, tape_identifier1);

    Token tape_identifier2 = {IDENTIFIER, 5, (char *) "tape2"};

    // lo siguiente se realiza para verificar que la inicializacion por copia y el operador
    // de asignacion funcion bien, sin causar fugas de memoria
    AssignamentStatement assignament_statement2(tape_identifier2);

    Node dummy_node = {{}, {}, application_statement1, APPLICATION_STATEMENT};

    assignament_statement2.add_node(dummy_node);
    Node node3 = {{}, assignament_statement2, {}, ASSIGNAMENT_STATEMENT};

    // nodo 4
    Token tape_identifier3 = {IDENTIFIER, 5, (char *) "tape"};
    Token turing_machine_identifier2 = {IDENTIFIER, 5, (char *) "Zero"};

    // lo siguiente se realiza para verificar que la inicializacion por copia y el operador
    // de asignacion funcion bien, sin causar fugas de memoria
    ApplicationStatement application_statement2 = ApplicationStatement(turing_machine_identifier2, tape_identifier3);
    Node node4 = {{}, {}, application_statement2, APPLICATION_STATEMENT};

    Program program;
    program.add_node(node1);
    program.add_node(node2);
    program.add_node(node3);
    program.add_node(node4);

    free(in);
    free(initial_tape_state);
}