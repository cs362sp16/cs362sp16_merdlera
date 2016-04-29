/*************************************************
* Card Unit Test 2
* Card: council_room
*************************************************/
#include <stdio.h>
#include "assert.h"
#include "../dominion.h"

int main(int argc, char *argv[]){
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
    int seed = 1234;
    struct gameState game;
    int result = initializeGame(numPlayers, kingdomCards, seed, &game);

    int numCardsStart = numHandCards(&game);

    result = cardEffect(village, NULL, NULL, NULL, &game, 0, NULL);
    myAssertTrue((result == 0), "cardEffect: village");

    int numCardsPost = numHandCards(&game);

    myAssertTrue((numCardsPost == (numCardsStart)), "One card drawn and one card discarded.");

    checkAsserts();
}
