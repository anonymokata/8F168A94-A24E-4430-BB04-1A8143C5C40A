LD_LIBRARY_PATH=/usr/local/lib
CC=gcc
CFLAGS=-Wall -std=c99
LDFLAGS=
LIBS=-lcheck -lm -pthread -lrt
CHECKMK=checkmk
SOURCES=$(shell find src/. -maxdepth 1 -name "*.c")
CHECKS=$(shell find test/. -maxdepth 1 -name "*.check")
TARGET=all_tests

all: $(TARGET)

checkmk: 
	$(CHECKMK) $(CHECKS) > src/all_tests.c

$(TARGET): checkmk
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LIBS)
	make run

run:
	./$(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)
	rm -f src/*_tests.c
