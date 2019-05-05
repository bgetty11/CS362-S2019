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
	int k[10] = {great_hall, smithy, minion, adventurer, cutpurse, salvager, council_room, embargo, village, baron};
	struct gameState G, testG;
	int numPlayers = 2;
	int seed = 1000;
	int handPos = 0;
	int thisPlayer = 0;
	int newCards = 0;
	int discarded = 0;
	int newActions = 0;
	int drawnTreasure = 0;
	int z = 0;
	int tempHand[500];
	



	initializeGame(numPlayers, k, seed, &G);

	printCard(TESTCARD);
	//starting test 1

	fprintf(stdout, "--------------------Test 1 (copper, copper)---------------------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	testG.deck[thisPlayer][0] = copper;
	testG.deck[thisPlayer][1] = copper;
	
	adventurerFunction(drawnTreasure, z, thisPlayer, &testG, tempHand);
	newCards = 2;
	discarded = 1;
	

	assertEquals(G.handCount[thisPlayer] + newCards, testG.handCount[thisPlayer], "checking hand count: 5 cards in hand to start + 2 drawn for coppers");
	assertEquals(G.deckCount[thisPlayer] - newCards, testG.deckCount[thisPlayer], "checking deck count: 10 cards in deck - 5 cards in drawn to start - 2 drawn for coppers");
	assertEquals(copper, testG.hand[thisPlayer][5], "checking that the copper card is in the player's hand (#4 represents copper)");
	assertEquals(copper, testG.hand[thisPlayer][6], "checking that the copper card is in the player's hand (#4 represents copper)");
	


	fprintf(stdout, "--------------------Test 2 (silver, copper)---------------------\n");
		int dempHand[500];

	memcpy(&testG, &G, sizeof(struct gameState));
	testG.deck[thisPlayer][4] = silver;
	testG.deck[thisPlayer][3] = copper;
	
	adventurerFunction(drawnTreasure, z, thisPlayer, &testG, dempHand);


	newCards = 2;
	discarded = 1;

	assertEquals(G.handCount[thisPlayer] + newCards, testG.handCount[thisPlayer], "checking hand count: 5 cards in hand to start + 2 drawn for treasures");
	assertEquals(G.deckCount[thisPlayer] - newCards, testG.deckCount[thisPlayer], "checking deck count: cards in deck - 5 cards in drawn to start - 2 drawn for treasures");
	assertEquals(silver, testG.hand[thisPlayer][5], "checking that the silver card is in the player's hand (#5 represents silver)");
	assertEquals(copper, testG.hand[thisPlayer][6], "checking that the copper card is in the player's hand (#4 represents copper)");
	
	fprintf(stdout, "--------------------Test 3 (silver, gold)---------------------\n");
	int pempHand[500];

	memcpy(&testG, &G, sizeof(struct gameState));

	testG.deck[thisPlayer][4] = silver;
	testG.deck[thisPlayer][3] = gold;
	
	adventurerFunction(drawnTreasure, z, thisPlayer, &testG, pempHand);

	newCards = 2;
	discarded = 1;

	assertEquals(G.handCount[thisPlayer] + newCards, testG.handCount[thisPlayer], "checking hand count: 5 cards in hand to start + 2 drawn for treasures");
	assertEquals(G.deckCount[thisPlayer] - newCards, testG.deckCount[thisPlayer], "checking deck count: 10 cards in deck - 5 cards in drawn to start - 2 drawn for treasures");
	assertEquals(silver, testG.hand[thisPlayer][5], "checking that the silver card is in the player's hand (#5 represents silver)");
	assertEquals(gold, testG.hand[thisPlayer][6], "checking that the gold card is in the player's hand (#6 represents gold)");
	
	fprintf(stdout, "--------------------Test 4 (silver, gold, silver)---------------------\n");
	int rempHand[500];

	memcpy(&testG, &G, sizeof(struct gameState));

	testG.deck[thisPlayer][4] = silver;
	testG.deck[thisPlayer][3] = gold;
	testG.deck[thisPlayer][2] = silver;

	adventurerFunction(drawnTreasure, z, thisPlayer, &testG, rempHand);

	newCards = 2;
	discarded = 1;

	assertEquals(G.handCount[thisPlayer] + newCards, testG.handCount[thisPlayer], "checking hand count: 5 cards in hand to start + 2 drawn for treasures");
	assertEquals(G.deckCount[thisPlayer] - newCards, testG.deckCount[thisPlayer], "checking deck count: 10 cards in deck - 5 cards in drawn to start - 2 drawn for treasures");
	assertEquals(silver, testG.hand[thisPlayer][5], "checking that the silver card is in the player's hand (#5 represents silver)");
	assertEquals(gold, testG.hand[thisPlayer][6], "checking that the gold card is in the player's hand (#6 represents gold)");
		

	fprintf(stdout, "--------------------Test 5 (silver, adventurer, copper)---------------------\n");
	int lempHand[500];
	int nonTreasureCard = 1; 

	memcpy(&testG, &G, sizeof(struct gameState));

	testG.deck[thisPlayer][4] = silver;
	testG.deck[thisPlayer][3] = adventurer;
	testG.deck[thisPlayer][2] = copper;
	
	adventurerFunction(drawnTreasure, z, thisPlayer, &testG, lempHand);

	newCards = 2;
	discarded = 1;

	assertEquals(G.handCount[thisPlayer] + newCards, testG.handCount[thisPlayer], "checking hand count: 5 cards in hand to start + 2 drawn for treasures");
	assertEquals(G.deckCount[thisPlayer] - newCards - nonTreasureCard, testG.deckCount[thisPlayer], "checking deck count: 10 cards in deck - 5 cards in drawn to start - 2 drawn for treasures - 1 for nontreasure card");
	assertEquals(silver, testG.hand[thisPlayer][5], "checking that the silver card is in the player's hand (#5 represents silver)");
	assertEquals(copper, testG.hand[thisPlayer][6], "checking that the copper card is in the player's hand (#4 represents copper)");



	fprintf(stdout, "--------------------Test 6(silver, adventurer, embargo, copper)---------------------\n");
	int sempHand[500];
	nonTreasureCard = 2; 

	memcpy(&testG, &G, sizeof(struct gameState));

	testG.deck[thisPlayer][4] = 5;
	testG.deck[thisPlayer][3] = adventurer;
	testG.deck[thisPlayer][2] = embargo;
	testG.deck[thisPlayer][1] = 4;

	adventurerFunction(drawnTreasure, z, thisPlayer, &testG, sempHand);

	newCards = 2;
	discarded = 1;

	assertEquals(G.handCount[thisPlayer] + newCards, testG.handCount[thisPlayer], "checking hand count: 5 cards in hand to start + 2 drawn for treasures");
	assertEquals(G.deckCount[thisPlayer] - newCards - nonTreasureCard, testG.deckCount[thisPlayer], "checking deck count: 10 cards in deck - 5 cards in drawn to start - 2 drawn for treasures - 2 for nontreasure card");
	assertEquals(silver, testG.hand[thisPlayer][5], "checking that the silver card is in the player's hand (#5 represents silver)");
	assertEquals(copper, testG.hand[thisPlayer][6], "checking that the copper card is in the player's hand (#4 represents copper)");
	
	
	
	

}