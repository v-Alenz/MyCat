
EXEC = mycat
CC = gcc
CFLAGS = -Wall -pedantic -Werror
DEBUGFLAGS = -g -fsanitize=address -fsanitize=undefined
TESTFILES = test0 test1 test2 test3 test4
all: $(EXEC)

mycat:  mycat.c
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $@ $^

test_files:
	touch $(TESTFILES)

clean:
	rm -f $(EXEC) $(TESTFILES)


.PHONY: test_files clean all




