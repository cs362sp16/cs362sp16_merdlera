/******************************************************************************
 * Dominon Tester
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../dominion.h"

#define ITERATIONS 20
#define K_MIN adventurer
#define K_MAX treasure_map

int kingdom_cards[] = {
    curse,
    estate,
    duchy,
    province,
    copper,
    silver,
    gold,
    adventurer,
    council_room,
    feast,
    gardens,
    mine,
    remodel,
    smithy,
    village,
    baron,
    great_hall,
    minion,
    steward,
    tribute,
    ambassador,
    cutpurse,
    embargo,
    outpost,
    salvager,
    sea_hag,
    treasure_map
};

// Initialize deck with cards
void initializeDeck(int *cards){
    int selected_cards[27] = {0};

    for (int i = 0; i < 10; i++){
        while (1) {
            int rand_card = kingdom_cards[rand() % 27];

            if(selected_cards[rand_card] == 0){
                // Set card and mark as selected
                cards[i] = rand_card;
                selected_cards[rand_card] = 1;

                break;
            }
        }
    }
}

// Setup new game
void initializeGameParameters(int *number_of_players, int *cards, int seed, struct gameState *state){
    *number_of_players = (rand() % 3) + 2; // Between 2-4 players
    initializeDeck(cards);
    initializeGame(*number_of_players, cards, seed, state);
}

// Play round
void playGame(struct gameState *state){
    int player = whoseTurn(state);

    while (state->numActions > 0){
        int actionCards = 0;
        int handPos = 0;
        int card = 0;
        int available_coins = 0;

        // Calculate the number of actions available
        for (int i = 0; i < numHandCards(state); i++) {
            if(state->hand[player][i] >= K_MIN && state->hand[player][i] <= K_MAX) {
                actionCards++;
            }
        }

        // If there are actions available
        if(actionCards > 0) {
            handPos = rand() % state->handCount[player];
            card = state->hand[player][handPos];


            // If kingdom card
            if (card >= K_MIN && card <= K_MAX) {
                switch (card){
                    case ambassador:
                        playCard(handPos, (rand() % numHandCards(state)), 1, -1, state);
                        break;
                    case baron:
                        playCard(handPos, 0, -1, -1, state);
                        break;
                    case embargo:
                        playCard(handPos, (rand() % (1 - 26) + 26), -1, -1, state);
                        break;
                    case feast:
                        break;
                    case minion:
                        playCard(handPos, 1, -1, -1, state);
                        break;
                    case remodel:
                        playCard(handPos, (rand() % numHandCards(state)), (rand() % (estate + 1 - 26) + 26), -1, state);
                        playCard(handPos, (rand() % numHandCards(state)), -1, -1, state);
                        break;
                    case steward:
                        playCard(handPos, ((rand() % 3) + 1), -1, -1, state);
                        break;
                    default:
                        playCard(handPos, 0, 0, 0, state);
                        break;
                }
                actionCards--;
            }
			else {

			}
        }
		else {

        }

        updateCoins(player, state, NULL);
        available_coins = state->coins;

        while(available_coins > 0){
            int tmpCard = rand() % 27;
            int cost = getCost(tmpCard);

            if(cost <= available_coins){
                available_coins = buyCard(tmpCard, state);
            }
        }

        endTurn(state);
        break;
    }
}

int main(int argc, char *argv[]){
    time_t seed = NULL;

    // Check command line arguments
    if(argc != 2){
        perror("Usage: ./testdominion [seed]\n");
        return 1;
    }

    seed = strtol(argv[1], NULL, 10);
    srand(time(&seed));

    printf("[Dominion Testing Start]\n");
    for (int i = 0; i < ITERATIONS; i++) {
        if (i == 0) {
            printf("%0.2f%% complete.", ((i + 1) / (float)ITERATIONS) * 100);
        } else{
            printf("\r%0.2f%% complete.", ((i + 1) / (float)ITERATIONS) * 100);
        }

        struct gameState state;
        int number_of_players = 0;
        int cards[10] = {0};
        initializeGameParameters(&number_of_players, cards, seed, &state);

        while (!isGameOver(&state)){
            playGame(&state);
        }
    }


    return 0;
}
