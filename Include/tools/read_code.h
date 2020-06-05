#ifndef READ_CODE_H
#define READ_CODE_H

// obtiene el numero de caracteres en un archivo de texto
int get_number_of_characters(const char *filename);

// esta funcion lee un archivo
int read_code(const char *filename, char *&output_string);

#endif
