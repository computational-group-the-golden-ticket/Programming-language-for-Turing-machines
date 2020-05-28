CC = g++
CFLAGS = -g -Wall -Wextra -Werror
INCLUDE = -I./Include

TAPELIBRARIE = tape.o

TAPEOBJECTS = \
	tape.o \
	tape_use_cases.o

TURINGMACHINELIBRARIE = turing_machine.o

TURINGMACHINEOBJECTS = \
	turing_machine.o \
	turing_machine_use_cases.o

READLIBRARIE = read_code.o
TOKENLIBRARIE = token.o

LEXERLIBRARIE = lexer.o

LEXEROBJECTS = \
	lexer.o \
	lexer_use_cases.o

ASTLIBRARIE = ast.o

PARSEROBJECTS = \
	parser.o \
	parser_use_cases.o

# ejecuta todas las reglas correspondiente a los tests
UseCases:
	$(MAKE) TapeUseCases
	$(MAKE) TuringMachineUseCases
	$(MAKE) LexerUseCases
	$(MAKE) ParserUseCases

# Para testear funcionalidad del modulo tape
TapeLibrarie:
	$(CC) $(INCLUDE) $(CFLAGS) -c Computer/tape.cpp -o tape.o

TapeObjectFiles: TapeLibrarie
	$(CC) $(INCLUDE) $(CFLAGS) -c UseCases/tape_use_cases.cpp -o tape_use_cases.o

TapeUseCases: TapeObjectFiles
	$(CC) $(CFLAGS) $(TAPEOBJECTS) -o tape_use_cases
	$(MAKE) clean_object_files

# para testear la funcionalidad del modulo turing machine
TuringMachineLibrarie:
	$(CC) $(INCLUDE) $(CFLAGS) -c Computer/turing_machine.cpp -o turing_machine.o

TuringMachineObjectFiles: TuringMachineLibrarie
	$(CC) $(INCLUDE) $(CFLAGS) -c UseCases/turing_machine_use_cases.cpp -o turing_machine_use_cases.o

TuringMachineUseCases: TapeLibrarie TuringMachineObjectFiles
	$(CC) $(CFLAGS) $(TURINGMACHINEOBJECTS) $(TAPELIBRARIE) -o turing_machine_use_cases
	$(MAKE) clean_object_files

# para testear funcionalidad del modulo lexer
ReadLibrarie:
	$(CC) $(INCLUDE) $(CFLAGS) -c Tools/read_code.cpp -o read_code.o

TokenLibrarie:
	$(CC) $(INCLUDE) $(CFLAGS) -c Parser/token.cpp -o token.o

LexerLibrarie:
	$(CC) $(INCLUDE) $(CFLAGS) -c Parser/lexer.cpp -o lexer.o

LexerObjectFiles: LexerLibrarie
	$(CC) $(INCLUDE) $(CFLAGS) -c UseCases/lexer_use_cases.cpp -o lexer_use_cases.o

LexerUseCases: ReadLibrarie TokenLibrarie LexerObjectFiles
	$(CC) $(CFLAGS) $(READLIBRARIE) $(TOKENLIBRARIE) $(LEXEROBJECTS) -o lexer_use_cases
	$(MAKE) clean_object_files

# para testear la funcionalidad del modulo parser
AstLibrarie:
	$(CC) $(INCLUDE) $(CFLAGS) -c Parser/ast.cpp -o ast.o

ParserLibrarie:
	$(CC) $(INCLUDE) $(CFLAGS) -c Parser/parser.cpp -o parser.o

ParserObjectFiles: ParserLibrarie
	$(CC) $(INCLUDE) $(CFLAGS) -c UseCases/parser_use_cases.cpp -o parser_use_cases.o

ParserUseCases: TapeLibrarie TuringMachineLibrarie ReadLibrarie \
		TokenLibrarie LexerLibrarie AstLibrarie ParserObjectFiles
	$(CC) $(CFLAGS) $(TAPELIBRARIE) $(TURINGMACHINELIBRARIE) \
		$(READLIBRARIE) $(TOKENLIBRARIE) $(LEXERLIBRARIE) \
		$(ASTLIBRARIE) $(PARSEROBJECTS) -o parser_use_cases

	$(MAKE) clean_object_files

clean_object_files:
	rm *.o

clean_use_cases_files:
	rm *_use_cases

# para los test
# Please tweak the following variable definitions as needed by your

# Points to the root of Google Test
GTEST_DIR = /usr/src/gtest

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = tape_unittest

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = /usr/include/gtest/*.h \
                /usr/include/gtest/internal/*.h

# House-keeping build targets.

all: $(TESTS)

check: all
	./tape_unittest

# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
		$(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
		$(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# Builds a sample test.  A test should link with either gtest.a or
# gtest_main.a, depending on whether it defines its own main()
# function.

tape.o:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDE) -c Computer/tape.cpp

tape_unittest.o:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDE) -c Tests/tape_unittest.cpp

tape_unittest : tape.o tape_unittest.o gtest.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

clean_test_files: clean_object_files
	rm *gtest*
	rm *_unittest*
