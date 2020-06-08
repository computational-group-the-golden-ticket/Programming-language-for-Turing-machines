#include <cstdlib>
#include <cstdio>

#include "token.h"

// la structura Token tiene un puntero como atributo, esta funcion facilita el proceso de
// asignacion por copia de valores
void asignate_token(Token &target, const Token &source, bool re_asign){
    target.type = source.type;
    target.length = source.length;

    // si se pasa r_asign como argumento, es porque source ya almacenaba otro token, entonces
    // solo es necesario reasignar espacio para el nuevo valor
    if (re_asign){
        free(target.value);
    }

    target.value = (char *) malloc((size_t) sizeof(char) * source.length);

    for (int i = 0; i < source.length; i++){
        target.value[i] = source.value[i];
    }
}

// para mostrar en token con formato en pantalla
void show_token(Token &token){
    // como se muestre en pantalla depende del tipo de token, pero en todos
    // se imprime el tipo de token y el valor que este almacena
    switch (token.type){
        case EOF_TOKEN:
            printf("Token(EOF_TOKEN, '%s')\n", token.value);
            break;

        case QUOTE:
            printf("Token(QUOTE, '%s')\n", token.value);
            break;

        case LPAREN:
            printf("Token(LPAREN, '%s')\n", token.value);
            break;

        case RPAREN:
            printf("Token(RPAREN, '%s')\n", token.value);
            break;

        case STRING:
            printf("Token(STRING, '%s')\n", token.value);
            break;

        case IDENTIFIER:
            printf("Token(IDENTIFIER, '%s')\n", token.value);
            break;

        case ASSIGNAMENT:
            printf("Token(ASSIGNAMET, '%s')\n", token.value);
            break;

        case TURINGMACHINE:
            printf("Token(TURINGMACHINE, '%s')\n", token.value);
            break;

        case TWOPOINTS:
            printf("Token(TWOPOINTs, '%s')\n", token.value);
            break;

        case NEWLINE:
            printf("Token(NEWLINE, '%s')\n", token.value);
            break;

        case TAB:
            printf("Token(TAB, '%s')\n", token.value);
            break;

        case WITH:
            printf("Token(WITH, '%s')\n", token.value);
            break;

        case INTEGER:
            printf("Token(INTEGER, '%s')\n", token.value);
            break;

        case PRINT:
            printf("Token(PRINT, '%s')\n", token.value);
            break;
        
        default:
            break;
    }
}

void liberate_token_space(Token &token){
    free(token.value);
}
