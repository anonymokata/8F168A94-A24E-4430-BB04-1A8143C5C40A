CC=gcc
CFLAGS=-Wall
LDFLAGS=
LIBS=-lm -pthread -lrt
LD_LIBRARY_PATH=/usr/local/lib

CHKLIB=-lcheck
CHECKMK=checkmk

CHECKS=$(shell find test/. -maxdepth 1 -name "*.check" | sort)
SOURCES=$(shell find src/. -maxdepth 1 ! -name main.c -name "*.c")
TEST_SOURCES=$(shell find test/. -maxdepth 1 ! -name main.c -name "*.c")
TEST_TARGET=all_tests

CLI_SOURCES=$(shell find src/. -maxdepth 1 ! -name all_tests.c -name "*.c")
CLI_TARGET=romani

GCOV_TEST_TARGET=all_tests_gcov

SPLINT=splint
SPLINT_FLAGS=+unixlib -compdef -mayaliasunique

GCOV=gcov
GCOV_FLAGS=-fprofile-arcs -ftest-coverage

all: splint test coverage

have_check:
	if [ -e $(LD_LIBRARY_PATH)/libcheck.a ]; then echo "libcheck.a ok!"; else echo "libcheck.a is not in $(LD_LIBRARY_PATH) as expected"; exit 1; fi;

checkmk: have_check
	$(CHECKMK) $(CHECKS) > test/all_tests.c

test: checkmk
	export LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) 
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(SOURCES) $(TEST_SOURCES) $(CHKLIB) $(LIBS) -I src 
	./$(TEST_TARGET)

coverage: checkmk
	export LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) 
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -o $(GCOV_TEST_TARGET) $(SOURCES) $(TEST_SOURCES) $(CHKLIB) $(LIBS) -I src 
	./$(GCOV_TEST_TARGET)
	$(GCOV) calculator.c
	$(GCOV) convert_roman.c
	$(GCOV) validate.c
	$(GCOV) adjust_roman.c

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
