# Makefile for pinFinder project
# Originally created by Joel Adams, Calvin University
# Modified by Steven McKelvey, Calvin University
# To build, enter: make

# Variables
TARGET 		= pinFinder
LIB 		= helperFunctions
TESTS 		= tests

SRC 		= $(TARGET).cpp
LIB_SRC     = $(LIB).cpp
TEST_SRC	= $(TESTS).cpp
MD5 		= md5.cpp

DEPENDENCIES = $(LIB_SRC) $(LIB).hpp $(MD5)

CC 			= nvc++

# Uncomment -Minfo=mp for details about GPU offloading
CFLAGS 	= -fast -mp=gpu -O1# -Minfo=mp 

SHELL = /bin/bash
MODULE_LOAD = module load nvhpc-hpcx-cuda12/24.3

# Rules
.PHONY: all clean

all: $(TARGET) $(TESTS)

# Compile source files
# For OpenMP GPU offloading, it appears that compilation needs to occur in one go
# (rather than compiling to object files and linking those files).
$(TARGET): $(SRC) $(DEPENDENCIES)
	@echo "Compiling $@..."
	@$(MODULE_LOAD) && $(CC) $(CFLAGS) $(OMPFLAGS) -o $@ $< $(LIB_SRC) \
	|| { echo "Compiliation failed for $@"; exit 1; }
	@echo "Finished compiling $@"
	@echo " "

$(TESTS): $(TEST_SRC) $(DEPENDENCIES)
	@echo "Compiling $@..."
	@$(MODULE_LOAD) && $(CC) $(CFLAGS) $(OMPFLAGS) -o $@ $< $(LIB_SRC) \
	|| { echo "Compiliation failed for $@"; exit 1; }
	@echo "Finished compiling $@"
	@echo " "

clean:
	rm -f $(TARGET) $(TESTS) *.o *~ *#