CC = g++
CFLAGS = -g -Wall -Wextra
INCLUDE = \
	-I../Include/tools \
	-I../Include/computer \
	-I../Include/parser \

READLIBRARIE = read_code.o
TYPESLIBRARIE = types.o
TAPELIBRARIE = tape.o
TURINGMACHINELIBRARIE = turing_machine.o
TOKENLIBRARIE = token.o
LEXERLIBRARIE = lexer.o
ASTLIBRARIE = ast.o

#librerias
ReadLibrarie:
	$(CC) $(INCLUDE) $(CFLAGS) -c ../tools/read_code.cpp -o read_code.o

TypesLibrarie:
	$(CC) $(INCLUDE) $(CFLAGS) -c ../tools/types.cpp -o $(TYPESLIBRARIE)

TapeLibrarie:
	$(CC) $(INCLUDE) $(CFLAGS) -c ../computer/tape.cpp -o $(TAPELIBRARIE)

TuringMachineLibrarie:
	$(CC) $(INCLUDE) $(CFLAGS) -c ../computer/turing_machine.cpp -o $(TURINGMACHINELIBRARIE)

TokenLibrarie:
	$(CC) $(INCLUDE) $(CFLAGS) -c ../parser/token.cpp -o token.o

LexerLibrarie:
	$(CC) $(INCLUDE) $(CFLAGS) -c ../parser/lexer.cpp -o lexer.o

AstLibrarie:
	$(CC) $(INCLUDE) $(CFLAGS) -c ../parser/ast.cpp -o ast.o

# casos de uso
TapeUseCases: TypesLibrarie TapeLibrarie
	$(CC) $(INCLUDE) $(CFLAGS) -c tape_use_cases.cpp -o tape_use_cases.o
	$(CC) $(CFLAGS) $(TYPESLIBRARIE) $(TAPELIBRARIE) tape_use_cases.o -o tape_use_cases
	$(MAKE) clean_object_files

TuringMachineUseCases: TypesLibrarie TapeLibrarie TuringMachineLibrarie
	$(CC) $(INCLUDE) $(CFLAGS) -c turing_machine_use_cases.cpp -o turing_machine_use_cases.o
	$(CC) $(CFLAGS) $(TYPESLIBRARIE) $(TAPELIBRARIE) $(TURINGMACHINELIBRARIE) turing_machine_use_cases.o -o turing_machine_use_cases
	$(MAKE) clean_object_files

LexerUseCases: ReadLibrarie TokenLibrarie LexerLibrarie
	$(CC) $(INCLUDE) $(CFLAGS) -c lexer_use_cases.cpp -o lexer_use_cases.o
	$(CC) $(CFLAGS) $(READLIBRARIE) $(TOKENLIBRARIE) $(LEXERLIBRARIE) lexer_use_cases.o -o lexer_use_cases
	$(MAKE) clean_object_files

AstUseCases: TypesLibrarie TokenLibrarie AstLibrarie
	$(CC) $(INCLUDE) $(CFLAGS) -c ast_use_cases.cpp -o ast_use_cases.o
	$(CC) $(CFLAGS) $(TYPESLIBRARIE) $(TOKENLIBRARIE) $(ASTLIBRARIE) ast_use_cases.o -o ast_use_cases
	$(MAKE) clean_object_files

clean_object_files:
	rm *.o

clean:
	rm *use_cases

clean_all: clean_object_files clean
