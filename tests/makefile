CC = g++
CFLAGS = -g -Wall -Wextra
INCLUDE = \
	-I../Include/tools \
	-I../Include/computer \
	-I../Include/parser \

# libraries
TYPESLIBRARIE = types.o
TAPELIBRARIE = tape.o

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

# libraries
TypesLibrarie:
	$(CC) $(INCLUDE) $(CFLAGS) -c ../tools/types.cpp -o $(TYPESLIBRARIE)

TapeLibrarie:
	$(CC) $(INCLUDE) $(CFLAGS) -c ../computer/tape.cpp -o $(TAPELIBRARIE)

tape.o:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDE) -c ../computer/tape.cpp

tape_unittest.o:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDE) -c tape_unittest.cpp

tape_unittest : tape.o tape_unittest.o gtest.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $(TYPESLIBRARIE) $^ -o $@

clean_test_files: clean_object_files
	rm *gtest*
	rm *_unittest*