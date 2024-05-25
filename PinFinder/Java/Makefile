TARGET = pinFinder
TESTS = tests

$(TARGET): $(TARGET).java
	javac -deprecation $(TARGET).java

$(TESTS): $(TESTS).java
	javac -deprecation $(TESTS).java

clean:
	rm -f $(TARGET).class $(TESTS).class *~ *# 