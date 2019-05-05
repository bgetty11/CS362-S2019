#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "sea_hag"

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
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, great_hall};
	struct gameState G, testG;
	int numPlayers = 2;
	int seed = 1000;
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int thisPlayer = 0;
	int newCards = 0;
	int discarded = 0;
	int newBuys = 0;
	int otherPlayer = 1;

	int otherPlayerNewCard = 0;


	initializeGame(numPlayers, k, seed, &G);

	printCard(TESTCARD);
	//starting test 1
	
	fprintf(stdout, "--------------------Test 1 (two players) ---------------------\n");
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(sea_hag, choice1, choice2, choice3, &testG, handPos, &bonus);
	newCards = 4;
	discarded = 1;
	newBuys = 1;
	otherPlayerNewCard = 1;

	assertEquals(0, testG.deck[otherPlayer][9], "checking curse card is the top card in deck: 0 is the curse card");

	fprintf(stdout, "--------------------Test 2 (four players) ---------------------\n");
	numPlayers = 4;
	initializeGame(numPlayers, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(sea_hag, choice1, choice2, choice3, &testG, handPos, &bonus);
	newCards = 4;
	discarded = 1;
	newBuys = 1;
	int thirdPlayer = 2;
	int fourthPlayer = 3;

	assertEquals(0, testG.deck[otherPlayer][9], "checking curse card is the top card in deck: 0 is the curse card");
	assertEquals(0, testG.deck[thirdPlayer][9], "checking curse card is the top card in deck: 0 is the curse card");
	assertEquals(0, testG.deck[fourthPlayer][9], "checking curse card is the top card in deck: 0 is the curse card");
}