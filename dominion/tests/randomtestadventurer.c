/*************************************************
* Random Card Test 1
* Card: adventurer
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "assert.h"
#include "../dominion.h"

int main(int argc, char *argv[]){
	int seed;

	if (argc == 0) {
		printf("Usage: %s <random_seed>", argv[0]);
	}
	else {
		seed = atoi(argv[1]);
		srand(seed);
		printf("Testing, %d", seed);
	}
    // Set up game
    int numPlayers = 2;
    int supplyPos = 1;
    int kingdomCards[] = {
        smithy,
        adventurer,
        gardens,
        embargo,
        cutpurse,
        mine,
        ambassador,
        outpost,
        baron,
        tribute
    };
    struct gameState game;
    int result = initializeGame(numPlayers, kingdomCards, seed, &game);

    result = cardEffect(adventurer, NULL, NULL, NULL, &game, NULL, NULL);
    myAssertTrue((result == 0), "Adventurer card effects.");

    checkAsserts();
}
