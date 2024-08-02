# Makefile for pinFinder project
# Originally created by Joel Adams, Calvin University
# Modified by Steven McKelvey, Calvin University
# To build, enter: make
  
# Variables
TARGET      = pinFinder
LIB         = helperFunctions
TESTS       = tests

OBJ_FILES   = $(TARGET).o $(LIB).o
TEST_OBJ    = $(TESTS).o $(LIB).o

CC          = gcc

CFLAGS      = -Wall -ansi -pedantic -std=gnu11 -fopenmp -lthread
LFLAGS      = -fopenmp -lcrypto -lm

# Rules
.PHONY: all clean

all: $(TARGET) $(TESTS)

# Link object files
$(TARGET): $(OBJ_FILES)
	@echo "Linking $@..."
	@$(CC) $^ $(LFLAGS) -o $@ \
	|| { echo "Linking failed for $@"; exit 1; }
	@echo "Finished building $@"
	@echo " "

$(TESTS): $(TEST_OBJ)
	@echo "Linking $@..."
	@$(CC) $^ $(LFLAGS) -o $@ \
	|| { echo "Linking failed for $@"; exit 1; }
	@echo "Finished building $@"
	@echo " "

# Compile source files to object files
%.o: %.c
	@echo "Compiling $< to $@..."
	@$(CC) $(CFLAGS) -c $< -o $@ \
	|| { echo "Compiliation failed for $<"; exit 1; }
	@echo "Finished compiling $<"
	@echo " "

# Dependencies
helperFunctions.o: helperFunctions.c helperFunctions.h

clean:
	rm -f $(TARGET) $(TESTS) *.o *~ *#

