#include <cstdlib>

#include "token.h"
#include "lexer.h"

#define MALLOC_CHECK_ 2

// la clase solo necesita informacion del texto, es decir el texto como tal y la longitud
Lexer::Lexer(char *text, int length):
        m_length{length}, m_position{0}, m_in_quote{false} {

    // se debe hacer una copia del texto
    m_text = (char *) malloc((size_t) sizeof(char) * length);

    for (int i = 0; i < length; i++){
        m_text[i] = text[i];
    }
}

Lexer::~Lexer(){
    free(m_text);
}

// metodos que ayuda a obtener informacion del caracter actual(aquel referenciado m_position)

bool Lexer::is_current_char_whitespace(){
    return m_text[m_position] == ' ';
}

bool Lexer::is_current_char_digit(){
    // en ascii los caracteres de los numeros estan en el intervalo (47, 58)
    return 47 < m_text[m_position] && m_text[m_position] < 58;
}

bool Lexer::is_current_char_lower_letter(){
    // en ascii los caracteres de las letras minusculas estan en el intervalo (96, 123)
    return 96 < m_text[m_position] && m_text[m_position] < 123;
}

bool Lexer::is_current_char_upper_letter(){
    // en ascii los caracteres de las letras mayusculas estan en el intervalo (64, 91)
    return 64 < m_text[m_position] && m_text[m_position] < 91;
}

bool Lexer::is_current_char_identifier_character(){
    // un identifier character es una letra minuscula o una letra mayuscula o un numero o
    // el guion bajo
    return m_text[m_position] == '_' || is_current_char_digit() ||
        is_current_char_lower_letter() || is_current_char_upper_letter();
}

// este metodo retorna una keyword asociada al valor en value, si value no corresponde
// con ninguna keyword entonces se retorna 0
int Lexer::keyword(char *string, int length){
    // los posibles valores de string a los que se le puede asociar un keyword es a
    // TuringMachine o a with
    const char turing_machine_key_word[] = "TuringMachine";
    const char with_keyword[] = "with";

    // with tiene longitud 4
    if (length < 5){
        bool it_broke = false;
        for (int i = 0; i < length; i++){
            if (with_keyword[i] != string[i]){
                it_broke = true;
                break;
            }
        }

        if (!it_broke){
            // si el ciclo no se rompe es porque es igual componente a componente
            return WITH;
        }
    }
    
    // TuringMachine tiene longitud 13
    if(length < 14){
        bool it_broke = false;
        for (int i = 0; i < length; i++){
            if (turing_machine_key_word[i] != string[i]){
                it_broke = true;
                break;
            }
        }

        if (!it_broke){
            // si el ciclo no se rompe es porque es igual componente a componente
            return TURINGMACHINE;
        }
    }

    return 0;
}

void Lexer::scape_whitespace(){
    while (is_current_char_whitespace()){
        m_position++;
    }
}

Token Lexer::eat_single_char(char symbol, Token &output_token){
    // como se esta consumiendo un caracter del texto se debe pasar al siguiente
    m_position++;

    // cada caracter arroja un tipo de token diferente
    // se hace conversion a (char *) porque "" tiene tipo const (char *)
    Token token = {};
    Token dummy_token = {};

    switch (symbol){
        case '(':
            dummy_token = Token{LPAREN, 2, (char *) "("};
            break;
        
        case ')':
            dummy_token = Token{RPAREN, 2, (char *) ")"};
            break;

        case '\"':
            m_in_quote = !m_in_quote;
            dummy_token = Token{QUOTE, 2, (char *) "\""};
            break;

        case ':':
            dummy_token = Token{TWOPOINTS, 2, (char *) ":"};
            break;

        case '=':
            dummy_token = Token{ASSIGNAMENT, 2, (char *) "="};
            break;

        case '\n':
            dummy_token = Token{NEWLINE, 3, (char *) "\\n"};
            break;

        case '\t':
            dummy_token = Token{TAB, 3, (char *) "\\t"};
            break;

        default:
            // Nunca va a llegar aqui, porque la funcion eat_single_char siempre
            // se llama con alguno de los argumentos de arriba
            dummy_token = Token{-1, 1, (char *) "\0"};
            break;
    }

    asignate_token(output_token, dummy_token, true);

    return token;
}

Token Lexer::eat_string(Token &output_token){
    int current_length = 1;
    char *value = (char *) malloc((size_t) sizeof(char) * current_length);

    value[current_length++ - 1] = m_text[m_position++];
    while (m_text[m_position] != '"'){
        value = (char *) realloc(value, (size_t) sizeof(char) * current_length);

        value[current_length++ - 1] = m_text[m_position++];
    }

    value = (char *) realloc(value, (size_t) sizeof(char) * current_length);
    value[current_length - 1] = '\0';

    Token token = {};
    Token dummy_token = {STRING, current_length - 1, value};
    
    asignate_token(output_token, dummy_token, true);
    free(dummy_token.value);

    return token;
}

Token Lexer::eat_identifier(Token &output_token){
    int current_length = 1;
    char *value = (char *) malloc((size_t) sizeof(char) * current_length);

    value[current_length++ - 1] = m_text[m_position++];
    while (is_current_char_identifier_character()){
        value = (char *) realloc(value, (size_t) sizeof(char) * current_length);

        value[current_length++ - 1] = m_text[m_position++];
    }

    value = (char *) realloc(value, (size_t) sizeof(char) * current_length);
    value[current_length - 1] = '\0';

    int token_id = keyword(value, current_length - 1);

    Token token = {};

    Token dummy_token = {};
    if(token_id){
        dummy_token = Token {token_id, current_length - 1, value};
    } else {
        dummy_token = {IDENTIFIER, current_length - 1, value};
    }

    asignate_token(output_token, dummy_token, true);

    free(dummy_token.value);

    return token;
}

Token Lexer::eat_integer(Token &output_token){
    int current_length = 1;
    char *value = (char *) malloc((size_t) sizeof(char) * current_length);

    value[current_length++ - 1] = m_text[m_position++];
    while (is_current_char_digit()){
        value = (char *) realloc(value, (size_t) sizeof(char) * current_length);

        value[current_length++ - 1] = m_text[m_position++];
    }

    value = (char *) realloc(value, (size_t) sizeof(char) * current_length);

    value[current_length - 1] = '\0';

    Token token = {};
    Token dummy_token = {INTEGER, current_length - 1, value};
    
    asignate_token(output_token, dummy_token, true);
    free(dummy_token.value);

    return token;
}

// este metodo retorna el siguiente token
Token Lexer::get_next_token(Token &output_token){
    // para obtener el token se va iterando sobre todos los caracteres
    // y se consume el token adecuado de acuerdo al valor del caracter actual
    while (m_position < m_length){
        if (is_current_char_whitespace()){
            scape_whitespace();
        }

        if (m_text[m_position] == '('){
            return eat_single_char('(', output_token);
        }

        if (m_text[m_position] == ')'){
            return eat_single_char(')', output_token);
        }

        if (m_text[m_position] == '"'){
            return eat_single_char('"', output_token);
        }

        if (m_text[m_position] == ':'){
            return eat_single_char(':', output_token);
        }

        if (m_text[m_position] == '='){
            return eat_single_char('=', output_token);
        }
    
        if(m_text[m_position] == '\n'){
            return eat_single_char('\n', output_token);
        }

        if(m_text[m_position] == '\t'){
            return eat_single_char('\t', output_token);
        }

        if(!m_in_quote){
            // si no se esta en un scope quote, es decir, si el puntero esta en una
            // posicion del texto por ejemplo con valor c en la que se cumple que "c"
            // es decir antes y despues de c se tiene el caracter "", entonces el token
            // corresponde a un numero entero a algun identificador
            if (is_current_char_digit()){

                return eat_integer(output_token);
            }

            if (is_current_char_identifier_character()){
                return eat_identifier(output_token);
            }
        }else{
            return eat_string(output_token);
        }
    }

    Token dummy_token = Token {EOF_TOKEN, 10, (char *) "EOF_TOKEN"};
    
    asignate_token(output_token, dummy_token, true);

    return dummy_token;
}
