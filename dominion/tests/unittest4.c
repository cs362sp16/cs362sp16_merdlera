/*************************************************
* Unit Test 4
* Function: updateCoins
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

    // Set testing paramaters
    int bonus = 20;
    int player = 1;
    game.handCount[player] = 0;

    result = updateCoins(player, &game, bonus);

    myAssertTrue(result == 0, "function returned 0");
    myAssertTrue(game.coins == bonus, "coins incremented by bonus amount");

    checkAsserts();
}
