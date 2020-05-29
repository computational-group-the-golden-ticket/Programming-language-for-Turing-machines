#ifndef AST_H
#define AST_H

#include "turing_machine.h"
#include "token.h"

// hay 3 tipos de nodos, declarament statement(para creacion de maquinas de turing)
// assignament statement(para la creacion de cintas a mano), y application statement
// (para la aplicacion de maquinas de turing a las cintas). El stamento
// "PRINT tape_identifier" se considera como un application statement donde se tiene
// una maquina de turing que escribe a la memorio de la pantalla

// especifica el tipo de nodo
#define DEFINITION_STATEMENT 0
#define ASSIGNAMENT_STATEMENT 1
#define APPLICATION_STATEMENT 2

struct NODE;
typedef struct NODE Node;

// Es la raiz del arbol y representa a todo el programa
class Program {
private:
    // numero y arreglo con los nodos del arbol
    int m_current_length;
    Node *m_nodes;

    // para hacer mas grande la lista m_nodes
    void get_space();
public:
    Program();
    ~Program();

    // esta funcion agrega un nodo al programa
    void add_node(Node node);
};

// tiene la informacion necesaria para simular una maquina de turing
class DefinitionStatement {
private:
    // numero de instrucciones e instrucciones de la maquina de turing
    int m_number_of_instructions;
    Instruction *m_instructions;

    // token con la informacion del nombre de la maquina de turing
    Token m_turing_machine_identifier;
public:
    // un nodo en el arbol que representa a el programa se define como una estructura con
    // campos para datos de tipo: DefinitionStatement, AssignamentStatement y ApplicationStatement
    // dado que solo puede haber un valor a la vez, se necesita tener un constructor sin parametros
    // para inicializar los campos vacios
    DefinitionStatement();

    // se esta usando inicializacion por copia
    DefinitionStatement(const DefinitionStatement &definition_statement);

    // para crear este nodo se necesita pasar como argumento la lista
    // de instrucciones, la cantidad de estas y un token de tipo identifier
    DefinitionStatement(Instruction *instructions, int length, Token turing_machine_identifier);
    ~DefinitionStatement();

    // se esta haciendo uso del operador de asignacion
    DefinitionStatement& operator=(const DefinitionStatement& definition_statement);
};


// tiene la informacion necesario para simular una cinta
class AssignamentStatement {
private:
    // longitud inicial de la cinta y configuracion inicial
    int m_current_length;
    State *m_tape;

    // token con la informacion del nombre de la cinta
    Token m_tape_identifier;

    // una cinta se puede crear desde una aplicacion de funcion, esto guarda el nodo
    // asociado a una posible aplicacion de funcion
    Node *m_node;

    // indica si a la variable m_node se le ha asignado algun valor
    bool m_has_node;

    void liberate_memory();
public:
    // un nodo en el arbol que representa a el programa se define como una estructura con
    // campos para datos de tipo: DefinitionStatement, AssignamentStatement y ApplicationStatement
    // dado que solo puede haber un valor a la vez, se necesita tener un constructor sin parametros
    // para inicializar los campos vacios
    AssignamentStatement();

    // este constructor se usa para el caso en el que la cinta es el resultado de la
    // aplicacion de una maquina de turing a una cinta ya existente
    AssignamentStatement(Token tape_identifier);

    // este nodo se crea pasando una configuracion inicial de la cinta esta por
    // medio del parametro initial_tape_state, la longitud de esta configuracion
    // y un token de tipo identifier
    AssignamentStatement(State *initial_tape_state, int length, Token tape_identifier);

    // se esta usando inicializacion por copia
    AssignamentStatement(const AssignamentStatement &assignament_statement);
    ~AssignamentStatement();

    // se esta haciendo uso del operador de asignacion
    AssignamentStatement& operator=(const AssignamentStatement& assignament_statement);

    // este metodo agrega un nodo al programa
    void add_node(Node &node);

    // este metodo retorna true si este nodo tiene un nodo hijo
    bool has_node();
};


// tiene la informacion necesario para aplicar una maquina de turing a una cinta
class ApplicationStatement {
private:
    // token con la informacion de la maquina de turing que se va a aplicar
    Token m_turing_machine_identifier;

    // token con la informacion de la cinta a la que se va a aplicar la maquina de turing
    Token m_tape_identifier;

    // la aplicacion de funcion se hace sobre una cinta, pero esta cinta puede venir de
    // otra cinta
    Node *m_node;

    // indica si a la variable m_node se le ha asignado algun valor
    bool m_has_node;

    void liberate_memory();
public:
    // un nodo en el arbol que representa a el programa se define como una estructura con
    // campos para datos de tipo: DefinitionStatement, AssignamentStatement y ApplicationStatement
    // dado que solo puede haber un valor a la vez, se necesita tener un constructor sin parametros
    // para inicializar los campos vacios
    ApplicationStatement();

    // este constructor se usa para el caso en el que la cinta es el resultado de la
    // aplicacion de una maquina de turing a una cinta ya existente
    ApplicationStatement(Token turing_machine_identifier);

    // esta clase se inicializa solo pasando como parametro el token identifier de la
    // maquina de turing y el token identifier de la cinta
    ApplicationStatement(Token turing_machine_identifier, Token tape_identifier);

    // se esta usando inicializacion por copia
    ApplicationStatement(const ApplicationStatement &application_statement);
    ~ApplicationStatement();

    // se esta haciendo uso del operador de asignacion
    ApplicationStatement& operator=(const ApplicationStatement& application_statement);

    // esta funcion agrega un nodo al programa
    void add_node(Node node);

    // esta funcion retorna true si este nodo tiene un nodo hijo
    bool has_node();
};

struct NODE {
    // en esta estructura uno y solo uno de estos campos guarda informacion
    DefinitionStatement definition_statement;
    AssignamentStatement assignament_statement;
    ApplicationStatement application_statement;

    // indica el tipo del campo que guarga la informacion
    int type;
};

// para facilitar la asignacion de estructuras por copia de valores
void asignate_node(Node &target, const Node &source);
void liberate_node_space(Node &node);

#endif
