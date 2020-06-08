#ifndef BIDIRECTIONAL_LIST_H
#define BIDIRECTIONAL_LIST_H

#include <iostream>

#include "types.h"

// representacion de una cinta en una maquina de turing
class Tape {
private:
    // posicion del puntero de lectura/escritura en la cinta
    int m_tape_head_position;
    // longitud de la cinta(longitud visible) en algun paso
    int m_current_length;
    // cinta
    State *m_tape;

    // cuando se visita una nueva celda en la cinta, a menos que el usuario no
    // halla establecido un valor esta tendra un valor por defecto
    State m_default_value;

    // la cinta se va ampliando a medida que se visitan nuevas celdas, con esta funcion
    // se obtiene espacio, a la izquierda si se pasa el parametro LEFT o a la derecha de
    // la cinta si se pasa RIGHT
    void get_space(int direction);
public:
    // la cinta se crea pasando una configuracion inicial de esta por medio del parametro
    // initial_tape_state, la longitud de esta configuracion y el valor por defecto que
    // se escribe en cada celda de la cinta
    Tape(State *initial_tape_state, int length, State default_value);
    ~Tape();

    // una maquina de turing necesita escribir, leer y moverse en la cinta

    // lee el simbolo que esta en la celda actual, el especificado por m_tape_head_position
    void read_symbol(State &output_state, bool re_asign=false);
    // escribe es simbolo que se pasa como argumento en la celda actual
    void write_symbol(State symbol);

    // metodos que permiten moverse a traves de la celda
    void move_tape_head_to_right();
    void move_tape_head_to_left();

    // para imprimir la cinta con formato
    friend std::ostream& operator<< (std::ostream &out, const Tape &list);
};

#endif
