# Makefile for pinFinder project
# To build pinFinder, enter: make
# To build tests, enter: make tests
  
TARGET      = pinFinder
SRC         = $(TARGET).cpp
LIB         = Hash
LIB_SRC     = $(LIB).cpp
OBJ_FILES   = $(TARGET).o $(LIB).o

CC          = g++
CFLAGS      = -c -Wall -ansi -pedantic -std=c++11 -fopenmp
LFLAGS      = -o pinFinder -fopenmp -lcrypto -lm

TESTS       = tests
TESTS_SRC	= $(TESTS).cpp
TEST_LFLAGS =  -o tests -fopenmp -lcrypto -lm


$(TARGET): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LFLAGS)

$(TARGET).o: $(SRC) $(LIB).hpp
	$(CC) $(SRC) $(CFLAGS)

$(LIB).o: $(LIB_SRC) $(LIB).hpp
	$(CC) $(LIB_SRC) $(CFLAGS)

$(TESTS): $(TESTS).o $(LIB).o
	$(CC) $(TESTS).o $(LIB).o $(TEST_LFLAGS)

$(TESTS).o: $(TESTS_SRC) $(LIB).hpp
	$(CC) $(TESTS_SRC) $(CFLAGS)

clean:
	rm -f $(TARGET) $(TESTS) *.o *~ *#

