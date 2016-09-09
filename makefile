CC=gcc
CFLAGS=-Wall
LDFLAGS=
LIBS=
LD_LIBRARY_PATH=/usr/local/lib
SOURCES=$(shell find src/. -maxdepth 1 ! -name main.c -name "*.c")
CLI_SOURCES=$(shell find src/. -maxdepth 1 ! -name all_tests.c -name "*.c")
CLI_TARGET=romani

CHKLIB=-lcheck
CHECKMK=checkmk
CHECKS=$(shell find test/. -maxdepth 1 -name "*.check" | sort)

TEST_SOURCES=$(shell find test/. -maxdepth 1 ! -name main.c -name "*.c")
TEST_CFLAGS=-Wall `pkg-config --cflags check`
TEST_LIBS=`pkg-config --libs --static check`
TEST_TARGET=all_tests

GCOV=gcov
GCOV_FLAGS=-fprofile-arcs -ftest-coverage
GCOV_TEST_TARGET=all_tests_gcov

SPLINT=splint
SPLINT_FLAGS=+unixlib -compdef -mayaliasunique -immediatetrans

all: splint test coverage

have_check:
	if [ -e $(LD_LIBRARY_PATH)/libcheck.a ]; then echo "libcheck.a ok!"; else echo "libcheck.a is not in $(LD_LIBRARY_PATH) as expected"; exit 1; fi;

checkmk: have_check
	$(CHECKMK) $(CHECKS) > test/all_tests.c

test: checkmk
	$(CC) $(TEST_CFLAGS) -o $(TEST_TARGET) $(SOURCES) $(TEST_SOURCES) $(CHKLIB) $(TEST_LIBS) -I src 
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) ./$(TEST_TARGET)

coverage: checkmk
	$(CC) $(TEST_CFLAGS) $(GCOV_FLAGS) -o $(GCOV_TEST_TARGET) $(SOURCES) $(TEST_SOURCES) $(CHKLIB) $(TEST_LIBS) -I src 
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) ./$(GCOV_TEST_TARGET)
	$(GCOV) calculator.c
	$(GCOV) convert_roman.c
	$(GCOV) validate.c
	$(GCOV) adjust_roman.c
	$(GCOV) validate_rn.c  

splint:
	$(SPLINT) $(SPLINT_FLAGS) -I src $(SOURCES) | tee all.splint

cli: 
	$(CC) $(CFLAGS) -o $(CLI_TARGET) $(CLI_SOURCES) demo/main.c $(LIBS) -I src

.PHONY: clean
clean:
	rm -f $(TEST_TARGET)
	rm -f $(GCOV_TEST_TARGET)
	rm -f $(CLI_TARGET)
	rm -f test/*_tests.c
	rm -f *.g???
	rm -f *.splint
