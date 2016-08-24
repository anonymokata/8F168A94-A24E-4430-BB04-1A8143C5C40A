LD_LIBRARY_PATH=/usr/local/lib
CC=gcc
CFLAGS=-Wall
LDFLAGS=
LIBS=-lcheck -lm -pthread -lrt
CHECKMK=checkmk
SOURCES=$(shell find src/. -maxdepth 1 -name "*.c")
TEST_SOURCES=$(shell find test/. -maxdepth 1 -name "*.c")
CHECKS=$(shell find test/. -maxdepth 1 -name "*.check")
TARGET=all_tests

GCOV=gcov
GCOV_FLAGS=-fprofile-arcs -ftest-coverage

all: $(TARGET)

checkmk: 
	$(CHECKMK) $(CHECKS) > test/all_tests.c

$(TARGET): checkmk
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(TEST_SOURCES) $(LIBS) -I src
	make run

coverage: checkmk
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -o $(TARGET)_gcov $(SOURCES) $(TEST_SOURCES) $(LIBS) -I src
	./$(TARGET)_gcov
	$(GCOV) calculator.c
	$(GCOV) convert_roman.c
	$(GCOV) validate.c
	$(GCOV) adjust_roman.c

run:
	./$(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)
	rm -f $(TARGET)_gcov
	rm -f test/*_tests.c
	rm -f *.g???
