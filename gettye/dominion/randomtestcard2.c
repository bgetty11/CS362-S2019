#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "council_room"

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
	srand(time(NULL));
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, great_hall};
	struct gameState G, testG;
	int numPlayers = 2;
	int seed = 1000;
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int thisPlayer = 0;
	int newCards = 4;
	int discarded = 1;
	int newBuys = 1;
	int otherPlayerNewCard = 1;

	initializeGame(numPlayers, k, seed, &G);

	printCard(TESTCARD);
	
	int i = 0; 
	while(i < 100)
	{
	
	numPlayers = rand() % 3 + 1 ; 
	initializeGame(numPlayers, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));


	fprintf(stdout, "--------------------Testing %d Players ---------------------\n", numPlayers + 1);

	cardEffect(council_room, choice1, choice2, choice3, &testG, handPos, &bonus);
	
	assertEquals(G.handCount[thisPlayer] + newCards - discarded, testG.handCount[thisPlayer], "checking hand count: 5 cards in hand to start + 4 drawn for council_room - 1 discarded");
	assertEquals(G.deckCount[thisPlayer] - newCards, testG.deckCount[thisPlayer],  "checking deck count: 10 cards in deck to start - 5 drawn to start - 4 drawn for council_room");
	assertEquals(G.numBuys + newBuys, testG.numBuys,  "checking buys: 1 buy to start + 1 buy for council_room");

	int j = 1;
	while( j < numPlayers)
	{
	assertEquals(G.handCount[j] + otherPlayerNewCard, testG.handCount[j],  "checking other player  hand count: +1 drawn for council_room");
	assertEquals(G.deckCount[j] - otherPlayerNewCard, testG.deckCount[j],  "checking other player deckcount: -1 drawn for council_room");
	j++;
	}
	
	i++;

	}

	
}