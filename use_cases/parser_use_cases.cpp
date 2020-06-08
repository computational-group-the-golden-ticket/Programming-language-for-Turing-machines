#include <iostream>

#include "read_code.h"
#include "lexer.h"
#include "parser.h"

void test1();

int main(){
    test1();

    return 0;
}

void test1(){
    // se lee el codigo del archivo de texto
    // std::cout << "====================================" << '\n';
    char filename[] = "../programs/example_program_2.tm";

    char *output_string;
    int length = read_code(filename, output_string);

    // std::cout << output_string;

    // std::cout << "====================================" << '\n';
    /*Token token = {};

    // se crea el lexer
    Lexer lexer = Lexer(output_string, length);
    lexer.get_next_token(token);
    int index{0};
    while (token.type != EOF_TOKEN){
        std::cout << index++ << ' ';
        show_token(token);

        lexer.get_next_token(token);
    }

    free(token.value);*/

    // se crea el parser
    Parser parser = Parser(output_string, length);
    
    for (int i = 0; i < 5; i++){
        Node node = parser.get_next_node();
        // parser.get_next_node();

        std::cout << node << '\n';
    }

    free(output_string);
}