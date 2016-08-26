LD_LIBRARY_PATH=/usr/local/lib
CC=gcc
CFLAGS=-Wall
LDFLAGS=
LIBS=-lm -pthread -lrt
CHKLIB=-lcheck
CHECKMK=checkmk
CLI_SOURCES=$(shell find src/. -maxdepth 1 ! -name all_tests.c -name "*.c")
SOURCES=$(shell find src/. -maxdepth 1 ! -name main.c -name "*.c")
TEST_SOURCES=$(shell find test/. -maxdepth 1 ! -name main.c -name "*.c")
CHECKS=$(shell find test/. -maxdepth 1 -name "*.check" | sort)
CLI_TARGET=romani
TEST_TARGET=all_tests
GCOV_TEST_TARGET=all_tests_gcov
SPLINT=splint
SPLINT_FLAGS=+unixlib -compdef -mayaliasunique

GCOV=gcov
GCOV_FLAGS=-fprofile-arcs -ftest-coverage

all: cli splint test coverage

checkmk: 
	$(CHECKMK) $(CHECKS) > test/all_tests.c

test: checkmk
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(SOURCES) $(TEST_SOURCES) $(CHKLIB) $(LIBS) -I src
	./$(TEST_TARGET)

coverage: checkmk
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -o $(GCOV_TEST_TARGET) $(SOURCES) $(TEST_SOURCES) $(CHKLIB) $(LIBS) -I src
	./$(GCOV_TEST_TARGET)
	$(GCOV) calculator.c
	$(GCOV) convert_roman.c
	$(GCOV) validate.c
	$(GCOV) adjust_roman.c

splint:
	$(SPLINT) $(SPLINT_FLAGS) -I src $(SOURCES) | tee all.splint

cli: clean
	$(CC) $(CFLAGS) -o $(CLI_TARGET) $(CLI_SOURCES) $(LIBS) -I src

.PHONY: clean
clean:
	rm -f $(TEST_TARGET)
	rm -f $(GCOV_TEST_TARGET)
	rm -f $(CLI_TARGET)
	rm -f test/*_tests.c
	rm -f *.g???
	rm -f *.splint
