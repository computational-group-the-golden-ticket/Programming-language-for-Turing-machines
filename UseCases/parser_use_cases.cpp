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
    char filename[] = "programs/example_program2.tm";

    int length = get_number_of_characters(filename);

    char *output_string = (char *) malloc((size_t) sizeof(char) * length);
    read_code(filename, output_string);

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

    // std::cout << "====================================" << '\n';
    parser.parse();

    free(output_string);
}