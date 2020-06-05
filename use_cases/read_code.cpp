#include <cstdlib>
#include <cstdio>

#include "read_code.h"

int main(){
    char filename[] = "example_program.tm";
    // char filename[] = "makefile";

    int length = get_number_of_characters(filename);

    char *output_string = (char *) malloc((size_t) sizeof(char) * length);
    read_code(filename, output_string);

    // printf("%s", output_string);

    free(output_string);

    return 0;
}
