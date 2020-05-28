#include <iostream>

#include "read_code.h"
#include "token.h"
#include "lexer.h"

void test1();
void test2();
void test3();
void test4();

int main(){
    test3();

    return 0;
}

void test1(){/*
    char text[] = "c = (\"1\" \"2\" \"3\")\0";

    Lexer lexer(text, 17);

    Token token = Token {};

    // std::cout << text << '\n';
    for (int i = 0; i < 60; i++){
        // std::cout << i << ' ';
        // show_token(lexer.get_next_token());
        lexer.get_next_token(token);

        // printf("%s: %d\n", token.value, token.length);

        free(token.value);
    }*/
}

void test2(){
    /*char text[] = "TuringMachine tm:\n\t\"1\" \"2\" \"3\" \"4\"\n\t\"1\" \"2\" \"3\" \"4\"\n\ncelda1 = (\"2\" \"3\" \"4\")\n\0";

    Lexer lexer(text, 75);

    Token token = Token {};

    // std::cout << text << '\n';
    for (int i = 0; i < 60; i++){
        // std::cout << i << ' ';
        // show_token(lexer.get_next_token());
        lexer.get_next_token(token);

        // printf("%s: %d\n", token.value, token.length);

        free(token.value);
    }*/
}

void liberate(Token &tkn){
    free(tkn.value);
}

void test3(){
    char text[] = "TuringMachine tm:\n\t\"1\" \"2\" \"3\" \"4\"\n\t\"1\" \"2\" \"3\" \"4\"\n\ncelda1 = (\"2\" \"3\" \"4\") with (23 \"q0\" \"s1\")\n\0";

    Lexer lexer(text, 96);

    Token token = Token {};

    lexer.get_next_token(token);

    std::cout << text << '\n';

    show_token(token);
    for (int i = 0; i < 60; i++){
        lexer.get_next_token(token);

        std::cout << i << ' ';
        show_token(token);
    }

    free(token.value);
}


void test4(){
    // se lee el codigo del archivo de texto
    // std::cout << "====================================" << '\n';
    char filename[] = "example_program.tm";

    int length = get_number_of_characters(filename);

    char *output_string = (char *) malloc((size_t) sizeof(char) * length);
    read_code(filename, output_string);

    // std::cout << output_string;

    for (int i = 0; i < length; i++){
        // output_string[i];
        // std::cout << (int) output_string[i] << ' ' << output_string[i] << '\n';
    }
    

    std::cout << "====================================" << '\n';
    Token token = {};

    // se crea el lexer
    Lexer lexer = Lexer(output_string, length);
    lexer.get_next_token(token);
    int index{0};
    while (token.type != EOF_TOKEN){
        std::cout << index++ << ' ';
        show_token(token);

        lexer.get_next_token(token);
    }

    show_token(token);

    free(token.value);
    free(output_string);
}
