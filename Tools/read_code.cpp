#include <cstdlib>
#include <cstdio>


#include "read_code.h"

int get_number_of_characters(const char *filename){
    FILE *file = fopen(filename, "r");

    int length{0};

    char c = fgetc(file);
    while (c != EOF){
        c = fgetc(file);

        length++;
    }

    fclose(file);

    return length;
}

// esta funcion lee un archivo y retorna la cantidad de caracteres
// en el mismo
int read_code(const char *filename, char *&output_string){
    int length = get_number_of_characters(filename);

    output_string = (char *) malloc((size_t) sizeof(char) * length);

    FILE *file = fopen(filename, "r");

    char c = fgetc(file);

    int index = 0;
    // este ciclo no esta almacenando el caracter EOF
    while (index < length){
        output_string[index++] = c;

        c = fgetc(file);
    }

    fclose(file);

    return length;
}
