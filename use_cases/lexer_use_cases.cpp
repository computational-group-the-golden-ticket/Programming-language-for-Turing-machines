#include <iostream>

#include "read_code.h"
#include "token.h"
#include "lexer.h"

void use_case_1();
void use_case_2();

int main(){
    // use_case_1();
    use_case_2();

    return 0;
}

void use_case_1(){
    char code[] = "TuringMachine tm:\n\t\"1\" \"2\" \"3\" \"4\"\n\t\"1\" \"2\" \"3\" \"4\"\n\ncelda1 = (\"2\" \"3\" \"4\") with (23 \"q0\" \"s1\")\n\0";

    Lexer lexer(code, 97);

    Token token = Token {};

    lexer.get_next_token(token);

    std::cout << code << '\n';

    show_token(token);
    for (int i = 0; i < 60; i++){
        lexer.get_next_token(token, true);

        std::cout << i << ' ';
        show_token(token);
    }

    liberate_token_space(token);
}

void use_case_2(){
    char *code;

    int length = read_code("../programs/example_program_1.tm", code);
    std::cout << code << '\n';


    Lexer lexer(code, length);

    Token token = Token {};

    lexer.get_next_token(token);

    show_token(token);
    for (int i = 0; i < 75; i++){
        lexer.get_next_token(token, true);

        std::cout << i << ' ';
        show_token(token);
    }

    liberate_token_space(token);

    free(code);
}
