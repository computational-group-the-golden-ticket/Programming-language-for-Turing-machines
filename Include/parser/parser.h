#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "lexer.h"
#include "ast.h"

class Parser{
private:
    // este objeto se encarga de generar los tokens
    Lexer m_lexer;
    Token m_current_token;

    // funciones que se encargan de descifrar el tipo de estamentos del programa
    DefinitionStatement definition_statement();
    AssignamentStatement assignament_statement(Token firs_token);
    ApplicationStatement application_statement(Token firs_token);
public:
    Parser(char *text, int length);
    ~Parser();

    Program parse();
};

#endif
