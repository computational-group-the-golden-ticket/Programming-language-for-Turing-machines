#ifndef TOKEN_H
#define TOKEN_H

// tipos de tokens en los que se dividira el texto de entrada
#define EOF_TOKEN 0
#define QUOTE 1
#define LPAREN 2
#define RPAREN 3
#define STRING 4
#define IDENTIFIER 5
#define ASSIGNAMENT 6
#define TURINGMACHINE 7
#define TWOPOINTS 8
#define NEWLINE 9
#define TAB 10
#define WITH 11
#define INTEGER 12
#define PRINT 13

// un token tiene asociado un tipo y un valor, pero el valor es un string
// por tanto se necesita tambien la longitud de ese string
struct TOKEN{
    int type;

    int length = 0;
    char *value;
};

typedef struct TOKEN Token;

// la structura Token tiene un puntero como atributo, esta funcion facilita el proceso de
// asignacion por copia de valores
void asignate_token(Token &target, const Token &source, bool re_asign=false);

// para mostrar en token con formato en pantalla
void show_token(Token &token);

void liberate_token_space(Token &token);

#endif
