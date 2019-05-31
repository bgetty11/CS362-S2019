#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

void printCard(char* card) {
	fprintf(stdout, "\n--------------------TESTING %s---------------------\n", card);
}

int assertEquals(int expected, int actual, char* message)
{
	if(expected != actual) {
		fprintf(stdout,"assertion FAILED- expected: %d, actual: %d, message: %s\n", expected, actual, message);
		return -1;
	}
	else {
		fprintf(stdout,"assertion PASSED- expected: %d, actual: %d, message: %s\n", expected, actual, message);
		return 0;
	}
}


int main()
{
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, council_room, great_hall};
	struct gameState G, testG;
	int numPlayers = 2;
	int seed = 1000;
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int thisPlayer = 0;
	int newCards = 0;
	int discarded = 0;
	int otherPlayer = 1; 
	initializeGame(numPlayers, k, seed, &G);

	printCard(TESTCARD);
	//starting test 1
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(smithy, choice1, choice2, choice3, &testG, handPos, &bonus);
	newCards = 3;
	discarded = 1;

	assertEquals(G.handCount[thisPlayer] + newCards - discarded, testG.handCount[thisPlayer], "checking hand count: 5 cards in hand to start + 3 drawn for smithy - 1 discarded");
	assertEquals(G.deckCount[thisPlayer] - newCards, testG.deckCount[thisPlayer],  "checking deck count: 10 cards in deck to start - 5 drawn to start - 3 drawn for smithy");

	fprintf(stdout, "--------------------Negative Assertion---------------------\n");
	assertEquals(G.deckCount[otherPlayer], testG.deckCount[otherPlayer],  "checking other player deck count: 10 cards in deck to start");
	assertEquals(G.handCount[otherPlayer], testG.handCount[otherPlayer],  "checking other player hand count: 0 cards in hand to start");



}