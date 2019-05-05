#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

void printCard(char* card) {
	fprintf(stdout, "\n--------------------TESTING %s---------------------\n", card);
}

void assertEquals(int expected, int actual, char* message)
{
	if(expected != actual)
		fprintf(stderr,"assertion FAILED- expected: %d, actual: %d, message: %s\n", expected, actual, message);
	else
		fprintf(stdout,"assertion PASSED- expected: %d, actual: %d, message: %s\n", expected, actual, message);
}

int main()
{
	int k[10] = {adventurer, embargo, smithy, minion, mine, cutpurse, sea_hag, tribute, council_room, great_hall};
	struct gameState G, testG;
	int numPlayers = 2;
	int seed = 1000;
	int handPos = 0;
	int thisPlayer = 0;
	int newCards = 0;
	int discarded = 0;
	int newActions = 0;
	int otherPlayer = 1; 
	

	initializeGame(numPlayers, k, seed, &G);

	printCard(TESTCARD);
	//starting test 1
	memcpy(&testG, &G, sizeof(struct gameState));

	villageFunction(thisPlayer, &testG, handPos);
	newCards = 1;
	discarded = 1;
	newActions = 2; 

	assertEquals(G.handCount[thisPlayer] + newCards - discarded, testG.handCount[thisPlayer], "checking hand count: 5 cards in hand to start + 1 drawn for village - 1 discarded");
	assertEquals(G.numActions + newActions, testG.numActions,  "checking actions: 1 action to start + 2 for village");
	assertEquals(G.deckCount[thisPlayer] - newCards , testG.deckCount[thisPlayer],  "checking deck count: 10 cards in deck to start - 5 to start - 1 drawn for village");


	fprintf(stdout, "--------------------Negative Assertion---------------------\n");
	assertEquals(G.deckCount[otherPlayer], testG.deckCount[otherPlayer],  "checking other player deck count: 10 cards in deck to start");
	assertEquals(G.handCount[otherPlayer], testG.handCount[otherPlayer],  "checking other player hand count: 0 cards in hand to start");

}