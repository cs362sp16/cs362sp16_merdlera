/*************************************************
* Random Card Test 1
* Card: smithy
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "assert.h"
#include "../dominion.h"

#define ITERATIONS 10000

int main(int argc, char *argv[]){

	// No command line args provided
	if (argc != 2) {
		printf("Usage: %s <random_seed>\n", argv[0]);
		return 1;
	}
	else {
		struct gameState state;
		time_t seed = NULL;
		seed = strtol(argv[1], NULL, 10);
		srand(time(&seed));
		printf("Random Testing: smithy");

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
	        int players = 2 + rand() % MAX_PLAYERS;
	        int randNum = rand();
	        int currPlayer = 0;
	        int result = NULL;

	        // Initialize new game
	        initializeGame(players, cards, 2, &state);

	        // Setup state attributes
	        state.deckCount[currPlayer] = rand() % MAX_DECK;
	        state.discardCount[currPlayer] = rand() %  MAX_DECK;
	        state.handCount[currPlayer] = rand() %  MAX_HAND;

			// Before values
			int hand_count = state.handCount[currPlayer];

	        // Play card
	        result = cardEffect(smithy, NULL, NULL, NULL, &state, 0, NULL);

	        // Check affected values against saved ones
	        myAssertTrue((result == 0), "Card effect function.");
			myAssertTrue((hand_count + 2 == state.handCount[currPlayer]), "Hand count increased by 2");
	    }

    	checkAsserts();

    	return 0;
	}
}
