#include "ast.h"
#include "parser.h"
#include "interpreter.h"

Interpreter::Interpreter(/* args */){
}

Interpreter::~Interpreter(){
}

void Interpreter::execute(char *code, int length){
    Parser parser = Parser(code, length);

    Node m_current_node = parser.get_next_node();

    while (m_current_node.type != NULL_NODE){
        switch (m_current_node.type){
        case DEFINITION_STATEMENT:
            /* code */
            break;

        case ASSIGNAMENT_STATEMENT:
            /* code */
            break;

        case APPLICATION_STATEMENT:
            /* code */
            break;
        
        default:
            break;
        }

        m_current_node = parser.get_next_node();
    }
}