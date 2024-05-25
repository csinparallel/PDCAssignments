# Makefile for pinFinder project
# To build pinFinder, enter: make
# To build tests, enter: make tests
  
TARGET      = pinFinder
SRC         = $(TARGET).c
LIB         = helperFunctions
LIB_SRC     = $(LIB).c
OBJ_FILES   = $(TARGET).o $(LIB).o

CC          = gcc
CFLAGS      = -c -Wall -ansi -pedantic -std=gnu11 -fopenmp
LFLAGS      = -o pinFinder -fopenmp -lcrypto -lm

TESTS       = tests
TEST_LFLAGS =  -o tests -fopenmp -lcrypto -lm


$(TARGET): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LFLAGS)

$(TARGET).o: $(SRC) $(LIB).h
	$(CC) $(SRC) $(CFLAGS)

$(LIB).o: $(LIB_SRC) $(LIB).h
	$(CC) $(LIB_SRC) $(CFLAGS)

$(TESTS): $(TESTS).o $(LIB).o
	$(CC) $(TESTS).o $(LIB).o $(TEST_LFLAGS)

$(TESTS).o: $(TESTS).c $(LIB).h
	$(CC) $(TESTS).c $(CFLAGS)

clean:
	rm -f $(TARGET) $(TESTS) *.o *~ *#

