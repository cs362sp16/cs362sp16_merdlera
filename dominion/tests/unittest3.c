/*************************************************
* Unit Test 3
* Function: supplyCount
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
    int result = initializeGame(numPlayers, kingdomCards, seed, &game);

    // Set testing parameters
    int card = 3;

    result = supplyCount(card, &game);
    myAssertTrue(result == 8, "Checks the supply count is correct");


    checkAsserts();
}
