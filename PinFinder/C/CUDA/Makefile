# Makefile for pinFinder project
# Originally created by Joel Adams, Calvin University
# Modified by Steven McKelvey, Calvin University
# To build, enter: make
  
# Variables
TARGET      = pinFinder
LIB         = helperFunctions
TESTS       = tests

OBJ_FILES   = $(TARGET).o $(LIB).o
TEST_OBJ 	= $(TESTS).o $(LIB).o

NVCC        = nvcc

CFLAGS      = -Werror all-warnings -lgomp
LFLAGS      = -lgomp

# Rules
.PHONY: all clean

all: $(TARGET) $(TESTS)

# Link object files
$(TARGET): $(OBJ_FILES)
	@echo "Linking $@..."
	@$(NVCC) -o $@ $^ $(LFLAGS) \
	|| { echo "Linking failed for $@"; exit 1; }
	@echo "Finished building $@"
	@echo " "

$(TESTS): $(TEST_OBJ)
	@echo "Linking $@..."
	@$(NVCC) -o $@ $^ $(LFLAGS) \
	|| { echo "Linking failed for $@"; exit 1; }
	@echo "Finished building $@"
	@echo " "

# Compile source files to object files
%.o: %.cu
	@echo "Compiling $< to $@..."
	@$(NVCC) $(CFLAGS) -c $< -o $@ $(CFLAGS) \
	|| { echo "Compilation failed for $<"; exit 1; }
	@echo "Finished compiling $<"
	@echo " "

# Dependencies
helperFunctions.o: helperFunctions.cu helperFunctions.cuh

clean:
	rm -f $(TARGET) $(TESTS) *.o *~ *#