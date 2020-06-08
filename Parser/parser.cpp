#include <cstdlib>
#include <cstdio>

#include "types.h"
#include "token.h"
#include "lexer.h"
#include "ast.h"
#include "parser.h"

Parser::Parser(char *text, int length):
        m_lexer{Lexer(text, length)},
        m_current_token{Token {}} {

    // se inicializa el m_current_token con el primer token del codigo
    m_lexer.get_next_token(m_current_token);
}

Parser::~Parser(){
    liberate_token_space(m_current_token);
}

DefinitionStatement Parser::definition_statement(){
    // en el definition statement antes de indicar las instrucciones, va la cabecera del
    // estamento, que tiene la forma: TuringMachine machine_name:
    int expected_introduction_tokens[] = {TURINGMACHINE, IDENTIFIER, TWOPOINTS, NEWLINE};

    // se debe guardar una referencia a la maquina, esto es el nombre
    Token identifier_token;

    // se chequea que la cabecera del estamento este en orden
    for (int i = 0; i < 4; i++){
        // si el token no es el esperado se debe lanzar un error
        if(m_current_token.type != expected_introduction_tokens[i]){
            // TODO: agregar excepciones en caso de error
        }

        // se obtiene el nombre de la maquina de turing
        if(m_current_token.type == IDENTIFIER){
            asignate_token(identifier_token, m_current_token);
        }

        // al terminar el for, m_current_token estara en el siguiente tab
        m_lexer.get_next_token(m_current_token, true);
    }

    // lista de instrucciones, inicialmente no hay instrucciones
    Instruction *instructions = (Instruction *) malloc((size_t) sizeof(Instruction) * 0);

    // cada instruccion debe tener el formato especificado por los tokens esperados
    int expected_body_tokens[] = {TAB, QUOTE, STRING, QUOTE,
                                       QUOTE, STRING, QUOTE,
                                       QUOTE, STRING, QUOTE,
                                       QUOTE, STRING, QUOTE, NEWLINE};

    // esta variable guarda la cantidad de instrucciones
    int length = 0;

    // in_statement es falso si en algun momento se se encuentra algun token diferente a los
    // de la lista expexted_body_tokens
    bool in_statement = true;
    while (in_statement){
        // en cada iteracion del ciclo while se agrega una instruccion nueva
        instructions = (Instruction *) realloc(instructions, (size_t) sizeof(Instruction) * (++length));

        // esta variable almacenara el valor de la nueva instruccion a agregar
        Instruction instruction;
        for (int i = 0; i < 14; i++){
            // si el token no es el esperado se debe agregar execpcion
            if (m_current_token.type != expected_body_tokens[i]){
                // TODO: agregar condiciones para caso de error
            }

            // cuando el token es un string es porque se esta especificando informacion de
            // la instruccion actual
            if (m_current_token.type == STRING){
                // en esta variable se guarda la informacion de los atributos de una instruccion
                State dummy_state = {m_current_token.value, m_current_token.length};

                // los casos corresponden a los posibles indices de los tokens string
                switch (i){
                    case 2:
                        asignate_state(instruction.current_mind_state, dummy_state);
                        break;

                    case 5:
                        asignate_state(instruction.cell_state, dummy_state);
                        break;

                    case 8:
                        asignate_state(instruction.action, dummy_state);
                        break;

                    case 11:
                        asignate_state(instruction.next_mind_state, dummy_state);
                        break;
                    
                    default:
                        break;
                }
            }

            // se obtiene el siguiente token
            m_lexer.get_next_token(m_current_token, true);
        }

        // se agrega la nueva instruccion a la lista
        asignate_instruction(instructions[length - 1], instruction);
        liberate_instruction_space(instruction);

        // si el siguiente token es diferente de TAB es porque se esta iniciando
        // nuevo tipo de estamento
        if (m_current_token.type != TAB){
            in_statement = false;
        }
    }

    DefinitionStatement def_statement = DefinitionStatement(instructions, length, identifier_token);

    // se libera el espacio de las instrucciones
    for (int i = 0; i < length; i++){
        liberate_instruction_space(instructions[i]);
    }

    free(instructions);
    liberate_token_space(identifier_token);

    return def_statement;
}

AssignamentStatement Parser::assignament_statement(Token &identifier){
    // esta funcion empieza con el m_current_token con un tipo de ASSIGNAMENT el
    // primer token corresponde al identificador de la variable que se esta creando
    int expected_introduction_tokens[] = {ASSIGNAMENT, LPAREN};

    // los tokens esperados deben corresponder con los de la lista
    for (int i = 0; i < 2; i++){
        // si algun token difiere del esperado se debe lanzar una excepcion
        if(m_current_token.type != expected_introduction_tokens[i]){
            // un estamento de asignacion crea una cinta, la cual puede ser pasada a mano
            // o puede ser el resultado de aplicar una maquina de turing a una cinta ya creada
            // si en vez de LPAREN se encuentra con un token de tipo IDENTIFIER entonces se
            // tiene un statement de aplicacion
            if (i == 1 && m_current_token.type == IDENTIFIER){
                // la asignacion puede hacerse desde una aplicacion de funcion o desde
                // un identificador de una cinta
                Token dummy_identifier = {};
                asignate_token(dummy_identifier, m_current_token);

                // si el siguiente token es distinto a un identificador, entonces la asignacion no
                // es desde una aplicacion de funcion
                m_lexer.get_next_token(m_current_token, true);

                if(m_current_token.type != IDENTIFIER){
                    // TODO: este caso debe ser implementado
                }

                AssignamentStatement assign_statement(identifier);

                Node node = {{}, {}, application_statement(dummy_identifier), APPLICATION_STATEMENT};

                // printf("EVALUACION\n");
                assign_statement.add_node(node);

                liberate_token_space(dummy_identifier);

                return assign_statement;
            }

            // TODO: agregar excepciones en caso de error
        }

        // al terminar el for, m_current_token estara en el siguiente quote
        m_lexer.get_next_token(m_current_token, true);
    }

    // inicialmente en la cinta no hay ninguna celda
    State *initial_tape_state = (State *) malloc((size_t) sizeof(State) * 0);

    // este es el formato en el que se pasan los estados de la cinta
    int expected_body_tokens[] = {QUOTE, STRING, QUOTE};

    // esta variable almacena la cantidad de estados
    int length = 0;

    // in_statement es falso si en algun momento se llega al token de cierre de parentesis
    bool in_statement = true;
    while (in_statement){
        // en cada iteracion se debe aunmentar en 1 el tamaño de la cinta
        initial_tape_state = (State *) realloc(initial_tape_state, (size_t) sizeof(State) * (++length));

        // se itera sobre los tokens esperados
        for (int i = 0; i < 3; i++){
            // si algun token difiere se debe lanzar una excepcion
            if (m_current_token.type != expected_body_tokens[i]){
                // TODO: manejar excepciones
            }

            // esto token es el que guarda la informacion del estado
            if (m_current_token.type == STRING){
                State dummy_state = State {m_current_token.value, m_current_token.length};

                // se asigna el estado en la ultima componente de la celda
                asignate_state(initial_tape_state[length - 1], dummy_state);
            }

            // se obtiene el siguiente token
            m_lexer.get_next_token(m_current_token, true);
        }

        // esto indica que ya se leyeron todos los estados iniciales de la lista
        if (m_current_token.type == RPAREN){
            in_statement = false;

            // se obtiene el siguiente token, se espera que sea un NEWLINE
            m_lexer.get_next_token(m_current_token, true);

            if (m_current_token.type != NEWLINE){
                // TODO: manejar excepciones
            } 
        }
    }

    AssignamentStatement assign_statement(initial_tape_state, length, identifier);

    // se libera la memoria utilizada
    for (int i = 0; i < length; i++){
        free(initial_tape_state[i].symbol);
    }

    free(initial_tape_state);

    return assign_statement;
}

ApplicationStatement Parser::application_statement(Token &identifier){
    // identifier token debe corresponder con el identificador de una maquina de turing

    // este guardara el valor del siguiente token
    Token dummy_identifier;

    // se obtiene el siguiente token, que bien puede ser el identificador de una cinta
    // o de una maquina de turing(si el siguiente a este tambien es un token de tipo
    // IDENTIFIER)
    m_lexer.get_next_token(m_current_token, true);

    if(m_current_token.type != IDENTIFIER){
        // TODO: manejar excepciones
    }

    asignate_token(dummy_identifier, m_current_token);

    // se avanza al siguiente token, se necesita saber si el proceso de aplicacion continua
    m_lexer.get_next_token(m_current_token, true);

    // la precedencia mas alta es la de aplicacion de una maquina de turing,
    // se asocia por izquierda, entonces si se tiene algo de este estilo:
    // machine1 machine2 machine3 cinta1, esto es equivalente a:
    // machine1 (machine2 (machine3 cinta1)), entonces se debe leer mientras
    // el current_token sea de tipo IDENTIFIER
    if (m_current_token.type == IDENTIFIER){
        ApplicationStatement appli_statement(identifier);

        Node node = {{}, {}, application_statement(dummy_identifier), APPLICATION_STATEMENT};

        appli_statement.add_node(node);

        return appli_statement;
    }else{
        // TODO: se deben implementaro los demas casos(en los que se usa la palabra clave with)
    }

    // el ultimo token debe ser de tipo NEWLINE
    if (m_current_token.type != NEWLINE){
        // TODO: manejar excepciones
    }

    ApplicationStatement appli_statement(identifier, dummy_identifier);

    liberate_token_space(dummy_identifier);

    return appli_statement;
}

Node Parser::get_next_node(){
    // el ciclo se ejecuta mientras hayan tokens por procesar
    while (m_current_token.type != EOF_TOKEN){
        // en este caso se debe proceder a crear un nodo de tipo DefinitionStatement
        if (m_current_token.type == TURINGMACHINE){
            Node node = {definition_statement(), {}, {}, DEFINITION_STATEMENT};

            return node;
        }

        if (m_current_token.type == IDENTIFIER){
            // se debe averiguar si ese identificador que se inicio es de asignacion o de applicacion
            Token identifier = {};
            asignate_token(identifier, m_current_token);

            // siguiente token en la lista, para identificar en que tipo de estamento se esta
            m_lexer.get_next_token(m_current_token, true);

            if (m_current_token.type == ASSIGNAMENT){
                Node node = {{}, assignament_statement(identifier), {}, ASSIGNAMENT_STATEMENT};

                liberate_token_space(identifier);

                return node;
            }else if(m_current_token.type == IDENTIFIER){
                Node node = {{}, {}, application_statement(identifier), APPLICATION_STATEMENT};

                liberate_token_space(identifier);

                return node;
            }else{
                // TODO: se debe manejar exepciones
            }

            liberate_token_space(identifier);
        }

        m_lexer.get_next_token(m_current_token, true);
    }

    return Node {};
}
