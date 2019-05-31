#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

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
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, great_hall};
	struct gameState G, testG;
	int numPlayers = 2;
	int seed = 1000;
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int thisPlayer = 0;
	int otherPlayer = 1;

	int otherPlayerNewCard = 0;


	initializeGame(numPlayers, k, seed, &G);

	printCard(TESTCARD);
	//starting test 1
	
	fprintf(stdout, "--------------------Test 1 (two players) ---------------------\n");
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(adventurer, choice1, choice2, choice3, &testG, handPos, &bonus);

	assertEquals(G.deckCount[otherPlayer], testG.deckCount[otherPlayer], "checking other player deck count: 10 cards in deck to start game");
	assertEquals(G.handCount[otherPlayer], testG.handCount[otherPlayer], "checking other player hand count: 0 cards in hand to start game");


	fprintf(stdout, "--------------------Test 2 (four players) ---------------------\n");
	numPlayers = 4;
	initializeGame(numPlayers, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(adventurer, choice1, choice2, choice3, &testG, handPos, &bonus);
	
	int thirdPlayer = 2;
	int fourthPlayer = 3;

	assertEquals(G.deckCount[otherPlayer], testG.deckCount[otherPlayer], "checking 2nd player deck count: 10 cards in deck to start game");
	assertEquals(G.handCount[otherPlayer], testG.handCount[otherPlayer], "checking 2nd player hand count: 0 cards in hand to start game");
	assertEquals(G.deckCount[thirdPlayer], testG.deckCount[thirdPlayer], "checking 3rd player deck count: 10 cards in deck to start game");
	assertEquals(G.handCount[thirdPlayer], testG.handCount[thirdPlayer], "checking 3rd player hand count: 0 cards in hand to start game");
	assertEquals(G.deckCount[fourthPlayer], testG.deckCount[fourthPlayer], "checking 4th player deck count: 10 cards in deck to start game");
	assertEquals(G.handCount[fourthPlayer], testG.handCount[fourthPlayer], "checking 4th player hand count: 0 cards in hand to start game");



}