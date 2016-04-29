/*************************************************
* Unit Test 1
* Function: initializeGame()
*************************************************/
#include <stdio.h>
#include "assert.h"
#include "../dominion.h"

int main(int argc, int *argv[]) {
  int numPlayers = 2;
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

    // Init game with proper cards and test
    int result = initializeGame(numPlayers, kingdomCards, seed, &game);
    myAssertTrue((result == 0), "Game state initialization.");

    // Init game with improper cards and test
    int kingdomCards2[] = {smithy,smithy,smithy,smithy,smithy,smithy,
                          smithy,smithy,smithy,smithy};
    result = initializeGame(numPlayers, kingdomCards2, seed, &game);
    myAssertTrue((result != 0), "Game state initialization with duplicate cards.");

    checkAsserts();
}