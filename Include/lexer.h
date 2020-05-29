#ifndef LEXER_H
#define LEXER_H

#include "token.h"

// esta clase se encarga de generar los tokens de un texto
class Lexer {
private:
    // longitud del texto de entrada
    const int m_length;
    // variable en la que se guardara el texto
    char *m_text;
    // posicion actual del puntero que ira leyendo el texto empieza en 0
    int m_position;

    // esta variable guarda la informacion de si el puntero esta en una posicion del texto
    // por ejemplo con valor c en la que se cumple que "c" es decir antes y despues de c
    // se tiene el caracter "
    bool m_in_quote;

    // metodos que ayuda a obtener informacion del caracter actual(aquel referenciado por
    // m_position)
    bool is_current_char_whitespace();
    bool is_current_char_digit();
    bool is_current_char_lower_letter();
    bool is_current_char_upper_letter();
    bool is_current_char_identifier_character();

    // este metodo retorna una keyword(tipo de token) asociada al valor en value, si value
    // no corresponde con ninguna keyword entonces se retorna 0
    int keyword(char *value, int length);

    // este metodo se salta todos los espacios en blanco del texto, pues estos no representan nada
    void scape_whitespace();

    // estos metodos retornan el siguiente token con el tipo de token de acuerdo al nombre de la
    // funcion
    void eat_single_char(char symbol, Token &output_token, bool re_asign=false);
    void eat_string(Token &output_token, bool re_asign=false);
    void eat_identifier(Token &output_token, bool re_asign=false);
    void eat_integer(Token &output_token, bool re_asign=false);
public:
    // la clase solo necesita informacion del texto, es decir el texto como tal y la longitud
    Lexer(char *text, int length);
    ~Lexer();

    // este metodo retorna el siguiente token
    void get_next_token(Token &output_token, bool re_asign=false);
};

#endif
