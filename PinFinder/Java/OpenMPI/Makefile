# Makefile for pinFinder MPI+Java
# to build, enter: make

# Variables
TARGET = pinFinder
LIB		= Hash
TESTS = tests

SRC 	= $(TARGET).java
LIB_SRC = $(LIB).java
TESTS_SRC = $(TESTS).java

CC        = mpijavac
CLASSPATH = .

# Rules
.PHONY: all clean pinFinder tests

all: $(TARGET) $(TESTS)

# Used to specifically make one file or the other.
pinFinder: $(TARGET).class
tests: $(TESTS).class

$(TARGET).class: $(SRC) $(LIB_SRC)
	@echo "Compiling $(TARGET)..."
	@$(CC) -deprecation -cp $(CLASSPATH) $^ \
	|| { echo "Compilation failed for $(TARGET)"; exit 1; }

$(TESTS).class: $(TESTS_SRC) $(LIB_SRC)
	@echo "Compiling $(TESTS)..."
	@$(CC) -deprecation -cp $(CLASSPATH) $^ \
	|| { echo "Compilation failed for $(TESTS)"; exit 1; }

clean:
	rm -f *.class *~ *# 