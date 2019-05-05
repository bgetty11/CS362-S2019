#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "salvager"

void printCard(char* card) {
	fprintf(stdout, "\n--------------------TESTING %s---------------------\n", card);
}

int assertEquals(int expected, int actual, char* message)
{
	if(expected != actual) {
		fprintf(stderr,"assertion FAILED- expected: %d, actual: %d, message: %s\n", expected, actual, message);
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
	int handPos = 0, choice1 = 1;
	int thisPlayer = 0;
	int newBuys = 0;
	int discarded = 0;
	int cardsTrashed = 0;
	int addCoins = 0;


	initializeGame(numPlayers, k, seed, &G);

	printCard(TESTCARD);
	//starting test 1
	memcpy(&testG, &G, sizeof(struct gameState));

	
	fprintf(stdout, "--------------------TEST 1 Trash Adventurer--------------------\n");
	newBuys = 1;
	discarded = 1;
	cardsTrashed = 1;
	addCoins = 6; 
	testG.hand[thisPlayer][1] = adventurer;
	salvagerFunction(thisPlayer, &testG, handPos, choice1);

	
	assertEquals(G.numBuys + newBuys, testG.numBuys, "checking buys: 1 buy + 1 buy for the salvager card");
	assertEquals(G.deckCount[thisPlayer], testG.deckCount[thisPlayer],  "checking deck count: 10 cards in deck to start - 5 drawn to start");
	assertEquals(G.handCount[thisPlayer] - discarded - cardsTrashed, testG.handCount[thisPlayer],  " checking hand count: 5 drawn to start - 1 discarded - 1 trashed");
	assertEquals(G.coins + addCoins, testG.coins,  "checking coin amount: 4 coins to start +6 coins for trashing adventurer");


	fprintf(stdout, "--------------------TEST 2 Trash Embargo--------------------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	newBuys = 1;
	discarded = 1;
	cardsTrashed = 1;
	addCoins = 2; 
	testG.hand[thisPlayer][1] = embargo;
	salvagerFunction(thisPlayer, &testG, handPos, choice1);

	assertEquals(G.numBuys + newBuys, testG.numBuys, "checking buys: 1 buy + 1 buy for the salvager card");
	assertEquals(G.deckCount[thisPlayer], testG.deckCount[thisPlayer],  "checking deck count: 10 cards in deck to start - 5 drawn to start");
	assertEquals(G.handCount[thisPlayer] - discarded - cardsTrashed, testG.handCount[thisPlayer],  "checking hand count: 5 drawn to start - 1 discarded - 1 trashed");
	assertEquals(G.coins + addCoins, testG.coins,  "checking coin amount: 4 coins to start +2 coins for trashing embargo");


	fprintf(stdout, "--------------------TEST 3 Trash Council Room--------------------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	newBuys = 1;
	discarded = 1;
	cardsTrashed = 1;
	addCoins = 5; 
	testG.hand[thisPlayer][1] = council_room;
	salvagerFunction(thisPlayer, &testG, handPos, choice1);

	assertEquals(G.numBuys + newBuys, testG.numBuys, "checking buys: 1 buy + 1 buy for the salvager card");
	assertEquals(G.deckCount[thisPlayer], testG.deckCount[thisPlayer],  "checking deck count: 10 cards in deck to start - 5 drawn to start");
	assertEquals(G.handCount[thisPlayer] - discarded - cardsTrashed, testG.handCount[thisPlayer],  "checking hand count: 5 drawn to start - 1 discarded - 1 trashed");
	assertEquals(G.coins + addCoins, testG.coins,  "checking coin amount: 4 coins to start +5 coins for trashing council_room");


}