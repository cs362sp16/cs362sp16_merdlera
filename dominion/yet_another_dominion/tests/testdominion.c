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

int _CARD[] = {
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

// char* enumToStr(int card){
//     switch(card){
//         case adventurer: return "Adventurer";
// 		case council_room: return "Council Room";
// 		case feast: return "Feast";
// 		case great_hall: return "Great Hall";
// 		case mine: return "Mine";
// 		case remodel: return "Remodel";
// 		case smithy: return "Smithy";
// 		case curse: return "Curse";
// 		case estate: return "Estate";
// 		case duchy: return "Duchy";
// 		case ambassador: return "Ambassador";
// 		case cutpurse: return "Cutpurse";
// 		case embargo: return "Embargo";
// 		case outpost: return "Outpost";
// 		case salvager: return "Salvager";
// 		case sea_hag: return "Sea Hag";
// 		case province: return "Province";
// 		case copper: return "Copper";
// 		case silver: return "Silver";
// 		case gold: return "Gold";
// 		case gardens: return "Gardens";
// 		case village: return "Village";
// 		case baron: return "Baron";
// 		case minion: return "Minion";
// 		case steward: return "Steward";
// 		case tribute: return "Tribute";
// 		case treasure_map: return "Treasure Map";
// 		default: return 0;
//     }
// }

// Fill deck with unique cards
void initDeck(int *cards){
    int _CARDPICKED[27] = {0};

    for (int i = 0; i < 10; i++){
        while (1) {
            int candidate = _CARD[rand() % 27];

            // If card not already selected
            if(_CARDPICKED[candidate] == 0){
                // Set card and mark as selected
                cards[i] = candidate;
                _CARDPICKED[candidate] = 1;

                break;
            }
        }
    }
}

// Setup new game
void initGameParams(int *numPlayers, int *cards, int seed, struct gameState *state){
    *numPlayers = (rand() % 3) + 2; // Between 2-4 players
    initDeck(cards);
    initializeGame(*numPlayers, cards, seed, state);
}

// Play round
void playRound(struct gameState *state){
    int player = whoseTurn(state);

    while (state->numActions > 0){
        int actionCards = 0;
        int handPos = 0;
        int card = 0;
        int available_coins = 0;

        /* Play card phase */

        // Calculate number of actions available
        for (int i = 0; i < numHandCards(state); i++) {
            if(state->hand[player][i] >= K_MIN && state->hand[player][i] <= K_MAX) {
                actionCards++;
            }
        }

        // If actions available
        if(actionCards > 0) {
            // Pick random card in hand
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
                        //playCard(handPos, (rand() % (duchy + 1 - 26) + 26), -1, -1, state);
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

        /* Play buy phase */

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

    // Check argument for seed
    if(argc != 2){
        perror("Usage: ./testdominion [seed]\n");
        return 1;
    }

    seed = strtol(argv[1], NULL, 10);
    srand(time(&seed));

    printf("[Beginning Dominion tests]\n");
    for (int i = 0; i < ITERATIONS; i++) {
        if (i == 0) {
            printf("%0.2f%% complete.", ((i + 1) / (float)ITERATIONS) * 100);
        } else{
            printf("\r%0.2f%% complete.", ((i + 1) / (float)ITERATIONS) * 100);
        }

        // Setup new game
        struct gameState state;
        int numPlayers = 0;
        int cards[10] = {0};
        initGameParams(&numPlayers, cards, seed, &state);

        // Play until finished
        while (!isGameOver(&state)){
            playRound(&state);
        }
    }


    return 0;
}
