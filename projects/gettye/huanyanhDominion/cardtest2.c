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
	
	fprintf(stdout, "--------------------Test 1 (one other player) ---------------------\n");
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(council_room, choice1, choice2, choice3, &testG, handPos, &bonus);
	newCards = 4;
	discarded = 1;
	newBuys = 1;
	otherPlayerNewCard = 1;

	assertEquals(G.handCount[thisPlayer] + newCards - discarded, testG.handCount[thisPlayer], "checking hand count: 5 cards in hand to start + 4 drawn for council_room - 1 discarded");
	assertEquals(G.deckCount[thisPlayer] - newCards, testG.deckCount[thisPlayer],  "checking deck count: 10 cards in deck to start - 5 drawn to start - 4 drawn for council_room");
	assertEquals(G.numBuys + newBuys, testG.numBuys,  "checking buys: 1 buy to start + 1 buy for council_room");
	assertEquals(G.handCount[otherPlayer] + otherPlayerNewCard, testG.handCount[otherPlayer],  "checking other player  hand count: +1 drawn for council_room");
	assertEquals(G.deckCount[otherPlayer] - otherPlayerNewCard, testG.deckCount[otherPlayer],  "checking other player deckcount: -1 drawn for council_room");

	fprintf(stdout, "--------------------Test 2 (three other players) ---------------------\n");
	numPlayers = 4;
	initializeGame(numPlayers, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(council_room, choice1, choice2, choice3, &testG, handPos, &bonus);
	newCards = 4;
	discarded = 1;
	newBuys = 1;
	otherPlayerNewCard = 1;
	int thirdPlayer = 2;
	int fourthPlayer = 3; 

	assertEquals(G.handCount[thisPlayer] + newCards - discarded, testG.handCount[thisPlayer], "checking hand count: 5 cards in hand to start + 4 drawn for council_room - 1 discarded");
	assertEquals(G.deckCount[thisPlayer] - newCards, testG.deckCount[thisPlayer],  "checking deck count: 10 cards in deck to start - 5 drawn to start - 4 drawn for council_room");
	assertEquals(G.numBuys + newBuys, testG.numBuys,  "checking buys: 1 buy to start + 1 buy for council_room");
	assertEquals(G.handCount[otherPlayer] + otherPlayerNewCard, testG.handCount[otherPlayer],  "checking second player  hand count: +1 drawn for council_room");
	assertEquals(G.deckCount[otherPlayer] - otherPlayerNewCard, testG.deckCount[otherPlayer],  "checking second player deckcount: -1 drawn for council_room");
	assertEquals(G.handCount[thirdPlayer] + otherPlayerNewCard, testG.handCount[otherPlayer],  "checking third player  hand count: +1 drawn for council_room");
	assertEquals(G.deckCount[thirdPlayer] - otherPlayerNewCard, testG.deckCount[otherPlayer],  "checking third player deckcount: -1 drawn for council_room");
	assertEquals(G.handCount[fourthPlayer] + otherPlayerNewCard, testG.handCount[otherPlayer],  "checking fourth player  hand count: +1 drawn for council_room");
	assertEquals(G.deckCount[fourthPlayer] - otherPlayerNewCard, testG.deckCount[otherPlayer],  "checking fourth player deckcount: -1 drawn for council_room");
}