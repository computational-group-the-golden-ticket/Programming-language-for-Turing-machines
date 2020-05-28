#include <cstdio>

#include "read_code.h"

int get_number_of_characters(char *filename){
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
void read_code(char *filename, char *output_string){
    FILE *file = fopen(filename, "r");

    char c = fgetc(file);

    int index = 0;
    while (c != EOF){
        output_string[index++] = c;
    
        c = fgetc(file);
    }

    fclose(file);
}
