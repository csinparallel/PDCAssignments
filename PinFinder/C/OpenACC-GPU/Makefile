# Makefile for pinFinder project
# Originally created by Joel Adams, Calvin University
# Modified by Steven McKelvey, Calvin University
# To build, enter: make

# Variables
TARGET 		= pinFinder
LIB 		= helperFunctions
TESTS 		= tests

OBJ_FILES   = $(TARGET).o $(LIB).o
TEST_OBJ    = $(TESTS).o $(LIB).o

CC 			= nvc

# Uncomment -Minfo=accel for details about GPU offloading
CFLAGS 	= -fast -acc=gpu# -Minfo=accel

SHELL = /bin/bash
MODULE_LOAD = module load nvhpc-hpcx-cuda12/24.3

# Rules
.PHONY: all clean

all: $(TARGET) $(TESTS)

# Link object files
$(TARGET): $(OBJ_FILES)
	@echo "Compiling $@..."
	@$(MODULE_LOAD) && $(CC) $(CFLAGS) -o $@ $^ \
	|| { echo "Compiliation failed for $@"; exit 1; }
	@echo "Finished compiling $@"
	@echo " "

$(TESTS): $(TEST_OBJ)
	@echo "Compiling $@..."
	@$(MODULE_LOAD) && $(CC) $(CFLAGS) -o $@ $^ \
	|| { echo "Compiliation failed for $@"; exit 1; }
	@echo "Finished compiling $@"
	@echo " "

# Compile source files to object files
%.o: %.c
	@echo "Compiling $< to $@..."
	@$(MODULE_LOAD) && $(CC) $(CFLAGS) -c $< -o $@ \
	|| { echo "Compiliation failed for $<"; exit 1; }
	@echo "Finished compiling $<"
	@echo " "

# Dependencies
helperFunctions.o: helperFunctions.c helperFunctions.h

clean:
	rm -f $(TARGET) $(TESTS) *.o *~ *#