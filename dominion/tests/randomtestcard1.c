/*************************************************
* Random Card Test 1
* Card: council_room
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "assert.h"
#include "../dominion.h"

#define ITERATIONS 1000

int main(int argc, char *argv[]){

	// No command line args provided
	if (argc == 0) {
		printf("Usage: %s <random_seed>", argv[0]);
		return 1;
	}
	else {
		struct gameState state;
		time_t seed = NULL;
		seed = strtol(argv[1], NULL, 10);
		srand(time(&seed));
		printf("Random Testing: adventurer");

	    // Set up game
	    int numPlayers = 2;
	    int supplyPos = 1;
	    int cards[] = {
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


		// Run tests
	    for (int i = 0; i < ITERATIONS; i++) {
	        int players = rand() % MAX_PLAYERS;
	        int randNum = rand();
	        int currPlayer = 0;
	        int savedHandCount = NULL;
	        int savedBuyCount = NULL;
	        int result = NULL;

	        // Init new game
	        initializeGame(players, cards, 2, &state);

	        // Setup state
	        state.deckCount[currPlayer] = rand() % MAX_DECK;
	        state.discardCount[currPlayer] = rand() %  MAX_DECK;
	        state.handCount[currPlayer] = rand() %  MAX_HAND;

	        // Save values to be affected by council room
	        savedHandCount = state.handCount[currPlayer];
	        savedBuyCount = state.numBuys;

	        // Play adventurer card
	        result = cardEffect(council_room, NULL, NULL, NULL, &state, 0, NULL);

	        // Check affected values against saved ones
	        myAssertTrue((result == 0), "Card effect function.");
	        myAssertTrue((savedHandCount + 3 == state.handCount[currPlayer]), "Post hand count.");
	        myAssertTrue((savedBuyCount + 1 == state.numBuys), "Post num buys.");
	    }

    	checkAsserts();

    	return 0;
	}
}
