/*************************************************
* Unit Test 2
* Function: buyCard
*************************************************/
#include <stdio.h>
#include "assert.h"
#include "../dominion.h"

int main(int argc, char *argv[]){
    // Set up game
    int numPlayers = 2;
    int supplyPos = 1;
    int kingdomCards[] = {
        smithy,adventurer,
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
    initializeGame(numPlayers, kingdomCards, seed, &game);

    // Set testing parameters
    game.numBuys = 0;

    int result = buyCard(supplyPos, &game);

    myAssertTrue(result == -1, "Cannot buy card if no buys left.");

    checkAsserts();
}
