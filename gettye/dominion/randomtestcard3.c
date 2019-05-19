#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

void printCard(char* card) {
	fprintf(stdout, "--------------------TESTING %s---------------------\n", card);
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
	int k[10] = {great_hall, smithy, minion, adventurer, cutpurse, salvager, council_room, embargo, village, baron};
	struct gameState G, testG;
	int numPlayers = 2;
	int seed = 1000;
	int handPos = 0;
	int thisPlayer = 0;
	int newCards = 2;
	int discarded = 0;
	int newActions = 0;
	int drawnTreasure = 0;
	int z = 0;
	int tempHand[500];
	



	initializeGame(numPlayers, k, seed, &G);
	
	int cardChoice[10] = {great_hall, smithy, copper, gold, silver, salvager, copper, silver, village, gold};

	printCard(TESTCARD);
	//starting test 1
	int i = 0;
	while( i < 50)
	{
	fprintf(stdout, "--------------------Test %d---------------------\n", i);
	int sempHand[500];
	
	memcpy(&testG, &G, sizeof(struct gameState));
	int c = 0;
	while(c < 10)
	{
	testG.deck[thisPlayer][c] = cardChoice[c];
	c++;
	}

int tryAgain = 0;

	do {	
		shuffle(thisPlayer, &testG);
		int numCoins = 0;
		int index = 4;
		while(numCoins < 2 && index >= 0)
		{
			if(testG.deck[thisPlayer][index] == copper || testG.deck[thisPlayer][index] == silver || testG.deck[thisPlayer][index] == gold)
				numCoins++;
			index--;

		}
		if (numCoins != 2) {
			tryAgain = 1;
		}
	}
	while (tryAgain);
	



	int drawnCoins = 0;
	int discardedOnes = 0;
	int totalCoins = 0;
	int index = 4;
	while(drawnCoins < 2 && index >= 0)
	{
		if(testG.deck[thisPlayer][index] == copper || testG.deck[thisPlayer][index] == silver || testG.deck[thisPlayer][index] == gold )
		{
			drawnCoins++;
		}
		else
		{
			discardedOnes++;
		}

		index--;
	}


	adventurerFunction(drawnTreasure, z, thisPlayer, &testG, sempHand);

	
	assertEquals(G.handCount[thisPlayer] + newCards, testG.handCount[thisPlayer], "checking hand count: 5 cards in hand to start + 2 drawn for treasures");
	assertEquals(G.deckCount[thisPlayer] - newCards - discardedOnes, testG.deckCount[thisPlayer], "checking deck count: 10 cards in deck - 5 cards in drawn to start - 2 drawn for treasures - unknown drawn nontreasures");

	i++;
	}
	
	
	

}
