CFLAGS= -Wall -fpic -coverage -lm -std=c99

unittestresults: testme.c
	gcc -o testme testme.c $(CFLAGS)
	./testme; true
	gcov -fb testme.c 