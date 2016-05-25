#!/bin/bash

CFLAGS = -std=c99 -Wall -fpic -coverage -lm
TEST_SEED = 42

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

assert.o: $(tests/assert.h) $(tests/assert.c)
	gcc -c tests/assert.c -g $(CFLAGS)

unittestresults.out: $(tests/unittest*.c) $(tests/cardtest*.c)  assert.o dominion.o
	gcc -o tests/unittest1 tests/unittest1.c -g assert.o dominion.o rngs.o $(CFLAGS)
	gcc -o tests/unittest2 tests/unittest2.c -g assert.o dominion.o rngs.o $(CFLAGS)
	gcc -o tests/unittest3 tests/unittest3.c -g assert.o dominion.o rngs.o $(CFLAGS)
	gcc -o tests/unittest4 tests/unittest4.c -g assert.o dominion.o rngs.o $(CFLAGS)
	gcc -o tests/cardtest1 tests/cardtest1.c -g assert.o dominion.o rngs.o $(CFLAGS)
	gcc -o tests/cardtest2 tests/cardtest2.c -g assert.o dominion.o rngs.o $(CFLAGS)
	gcc -o tests/cardtest3 tests/cardtest3.c -g assert.o dominion.o rngs.o $(CFLAGS)
	gcc -o tests/cardtest4 tests/cardtest4.c -g assert.o dominion.o rngs.o $(CFLAGS)
	rm -f unittestresults.out
	./tests/unittest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	./tests/unittest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	./tests/unittest3 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	./tests/unittest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	./tests/cardtest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	./tests/cardtest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	./tests/cardtest3 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	./tests/cardtest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

randomtest: assert.o dominion.o
	rm -f randomtestadventurer.out randomtestcard1.out
	gcc -o tests/randomtestadventurer tests/randomtestadventurer.c -g assert.o dominion.o rngs.o $(CFLAGS)
	gcc -o tests/randomtestcard1 tests/randomtestcard1.c -g assert.o dominion.o rngs.o $(CFLAGS)
	gcc -o tests/randomtestcard2 tests/randomtestcard2.c -g assert.o dominion.o rngs.o $(CFLAGS)

	./tests/randomtestadventurer $(TEST_SEED) >> randomtestadventurer.out
	gcov -f dominion.c >> randomtestadventurer.out
	./tests/randomtestcard1 $(TEST_SEED) >> randomtestcard1.out
	gcov -f dominion.c >> randomtestcard1.out
	./tests/randomtestcard2 $(TEST_SEED) >> randomtestcard2.out
	gcov -f dominion.c >> randomtestcard2.out

testdominion.out: $(tests/testdominion.c) clean dominion.o
	gcc -o tests/testdominion tests/testdominion.c -g dominion.o rngs.o $(CFLAGS)
	./tests/testdominion $(TEST_SEED) >> testdominion.out
	gcov dominion.c >> testdominion.out

all: playdom player unittestresults.out

clean:
	rm -f *.o playdom.exe playdom test.exe test player tests/unittest1 tests/unittest2 tests/unittest3 tests/unittest4 tests/*.o tests/cardtest1 tests/cardtest2 tests/cardtest3 tests/cardtest4 tests/randomtestadventurer tests/randomtestcard1 tests/randomtestcard2 tests/testdominion testdominion_coverage.out testdominion.out player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.a *.dSYM unittestresults.out randomtestadventurer.out randomtestcard1.out randomtestcard2.out temp.out
