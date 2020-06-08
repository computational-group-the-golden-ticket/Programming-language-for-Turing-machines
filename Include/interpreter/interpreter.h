#ifndef INTERPRETER_H
#define INTERPRETER_H

class Interpreter{
private:
    Node m_current_node;
public:
    Interpreter();
    ~Interpreter();

    void execute(char *code, int length);
};

#endif
