# 600.120 Assignment 4
# Makefile
# Name: Joon Hyuck Choi
# email: jchoi100@jhu.edu
# Date: 03/10/2015
# Phone: 667-239-0288
# BB Login: jchoi100
#

CC = gcc
#CFLAGS = -std=c99 -Wextra -Wall -pedantic
CFLAGS = -std=c99 -g -Wextra -Wall -pedantic

bin: hw4

test: testList.c list.o
	echo "Test in progress..."
	./testList
	echo "All tests over."

testList: list.o testList.c
	$(CC) $(CFLAGS) -o testList -O testList.c list.o

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

hw4.0: hw4.c list.h
	$(CC) $(CFLAGS) -c hw4.c

hw4: list.o hw4.o
	$(CC) $(CFLAGS) -o hw4 -O hw4.o list.o

clean:
	rm -f *.o hw4 testList *~
