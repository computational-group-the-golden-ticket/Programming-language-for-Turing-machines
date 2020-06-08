#include <iostream>

#include "read_code.h"
#include "token.h"
#include "lexer.h"

void use_case(int use_case, const char *filename);

int main(){
    use_case(1, "../programs/example_program_1.tm");
    std::cout << '\n';

    use_case(2, "../programs/example_program_2.tm");
    std::cout << '\n';

    use_case(3, "../programs/example_program_3.tm");
    std::cout << '\n';

    use_case(4, "../programs/example_program_4.tm");

    return 0;
}

void use_case(int use_case, const char *filename){
    std::cout << "Codigo " << use_case << ":\n";

    char *code;

    int length = read_code(filename, code);
    std::cout << code << '\n';

    // se crea el tokenizador o lexer
    Lexer lexer(code, length);

    Token token = Token {};

    // primer token
    lexer.get_next_token(token);

    // a medida que se obtienen los tokens se van mostrando en pantalla
    std::cout << 0 << ' ';
    show_token(token);

    int counter = 1;
    while (token.type != EOF_TOKEN){
        // en la variable token ya hay un valor guardado, se pasa true para que
        // el espacio donde se guarda ese valor sea liberado antes de obtener nuevo espacio
        lexer.get_next_token(token, true);

        // antes de iniciar el ciclo ya se leyo un token
        std::cout << counter++ << ' ';
        show_token(token);
    }

    // se debe liberar el espacio pedido con malloc
    liberate_token_space(token);
    free(code);
}
