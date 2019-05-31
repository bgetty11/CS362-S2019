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
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, council_room, great_hall};
	struct gameState G, testG;
	int numPlayers = 2;
	int seed = 1000;
	int handPos = 0, choice1 = 1;
	int thisPlayer = 0;
	int newBuys = 1;
	int discarded = 1;
	int cardsTrashed = 1;
	int addCoins = 0;
	int choice2 = 0, choice3 = 0, bonus = 0;



	initializeGame(numPlayers, k, seed, &G);

	printCard(TESTCARD);
	
	int i = 0;
	while(i < 100)
	{

	memcpy(&testG, &G, sizeof(struct gameState));
	int handPlace = rand() % 4 + 1;
	int random = k[rand() % 10];
	testG.hand[thisPlayer][handPlace] = random;
	cardEffect(salvager, choice1, choice2, choice3, &testG, handPos, &bonus);

	
	switch(random) {
		case adventurer:
			fprintf(stdout, "\n--------------------TESTING adventurer---------------------\n");
			break;
		case embargo:
			fprintf(stdout, "\n--------------------TESTING embargo---------------------\n");
			break;
		case village:
			fprintf(stdout, "\n--------------------TESTING village---------------------\n");
			break;
		case minion:
			fprintf(stdout, "\n--------------------TESTING minion---------------------\n");
			break;
		case mine:
			fprintf(stdout, "\n--------------------TESTING mine---------------------\n");
			break;
		case cutpurse:
			fprintf(stdout, "\n--------------------TESTING cutpurse---------------------\n");
			break;
		case sea_hag:
			fprintf(stdout, "\n--------------------TESTING sea_hag---------------------\n");
			break;	
		case tribute:
			fprintf(stdout, "\n--------------------TESTING tribute---------------------\n");
			break;
		case council_room:
			fprintf(stdout, "\n--------------------TESTING council_room---------------------\n");
			break;
		case great_hall:
			fprintf(stdout, "\n--------------------TESTING great_hall---------------------\n");
			break;

	}

	assertEquals(G.numBuys + newBuys, testG.numBuys, "checking buys: 1 buy + 1 buy for the salvager card");
	assertEquals(G.deckCount[thisPlayer], testG.deckCount[thisPlayer],  "checking deck count: 10 cards in deck to start - 5 drawn to start");
	assertEquals(G.handCount[thisPlayer] - discarded - cardsTrashed, testG.handCount[thisPlayer],  " checking hand count: 5 drawn to start - 1 discarded - 1 trashed");
	assertEquals(G.coins + getCost(random), testG.coins,  "checking coin amount");

	i++;
	}

}