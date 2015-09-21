// GameView.c ... GameView ADT implementation

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "Map.h"

// #include "Map.h" ... if you decide to use the Map ADT

struct gameView {
	//REPLACE THIS WITH YOUR OWN IMPLEMENTATION
	int playerHealth[5];
	int locationID[5];
	int currentPlayer;
	int score;
	Round round;
	Map theMap;

};

//typedef char currentMessage[7];

//setters make code more readable
static void setHealth(GameView, int, int);
static void setScore(GameView, int);
static void setround(GameView, int);
static void setCurrentPlayer(GameView, int);
static void setLocation(GameView, int, int);
static int whoIsThis(char *);

// Creates a new GameView to summarise the current state of the game
GameView newGameView(char *pastPlays, PlayerMessage messages[]) {
	//REPLACE THIS WITH YOUR OWN IMPLEMENTATION
	GameView gameView = malloc(sizeof(struct gameView));
//    char * step = "";
	char * name = "";
//    strncpy(step,pastPlays,7);
//    currentMessage deal;

	int curr = 0;

	while (pastPlays[curr] != '\0') {
		name = "";
		setCurrentPlayer(gameView, whoIsThis(pastPlays[curr]));
		strncy(name, pastPlays[curr + 1], 2);
		setLocation(gameView, getCurrentPlayer(gameView), nameToID(name));

		//assert(step[7] == ' ');

	}

	// IGNORE THINGS BELOW CURRENTLY.
	//set up player's health
	setHealth(gameView, PLAYER_LORD_GODALMING, GAME_START_HUNTER_LIFE_POINTS);
	setHealth(gameView, PLAYER_DR_SEWARD, GAME_START_HUNTER_LIFE_POINTS);
	setHealth(gameView, PLAYER_VAN_HELSING, GAME_START_HUNTER_LIFE_POINTS);
	setHealth(gameView, PLAYER_MINA_HARKER, GAME_START_HUNTER_LIFE_POINTS);
	setHealth(gameView, PLAYER_DRACULA, GAME_START_BLOOD_POINTS);

	//set location
	setLocation(gameView, PLAYER_LORD_GODALMING, UNKNOWN_LOCATION);
	setLocation(gameView, PLAYER_DR_SEWARD, UNKNOWN_LOCATION);
	setLocation(gameView, PLAYER_VAN_HELSING, UNKNOWN_LOCATION);
	setLocation(gameView, PLAYER_MINA_HARKER, UNKNOWN_LOCATION);
	setLocation(gameView, PLAYER_DRACULA, UNKNOWN_LOCATION);

	//set currentPlayer
	setCurrentPlayer(gameView, PLAYER_LORD_GODALMING);

	//set current Round
	setround(gameView, 0);

	//set current score
	setScore(gameView, GAME_START_SCORE);

	return gameView;
}

static int whoIsThis(char * a) {

	switch (a[0]) {
	case 'G':
		return 0;
	case 'S':
		return 1;
	case 'H':
		return 2;
	case 'M':
		return 3;
	case 'D':
		return 4;
	}

	return -1;

}

static void setLocation(GameView view, int player, int locationID) {
	view->locationID[player] = locationID;

}

static void setround(GameView view, int round) {
	view->round = round;
}

static void setCurrentPlayer(GameView view, int player) {
	view->currentPlayer = player;
}

static void setHealth(GameView view, int player, int health) {
	view->playerHealth[player] = health;
}

static void setScore(GameView view, int score) {
	view->score = GAME_START_SCORE;
}

// Frees all memory previously allocated for the GameView toBeDeleted
void disposeGameView(GameView toBeDeleted) {
	//COMPLETE THIS IMPLEMENTATION
	free(toBeDeleted);
}

//// Functions to return simple information about the current state of the game

// Get the current round
Round getRound(GameView currentView) {
	//REPLACE THIS WITH YOUR OWN IMPLEMENTATION
	return currentView->round;
}

// Get the id of current player - ie whose turn is it?
PlayerID getCurrentPlayer(GameView currentView) {
	//REPLACE THIS WITH YOUR OWN IMPLEMENTATION
	return currentView->currentPlayer;
}

// Get the current score
int getScore(GameView currentView) {
	//REPLACE THIS WITH YOUR OWN IMPLEMENTATION
	return currentView->score;
}

// Get the current health points for a given player
int getHealth(GameView currentView, PlayerID player) {
	return currentView->playerHealth[player];
}

// Get the current location id of a given player
LocationID getLocation(GameView currentView, PlayerID player) {
	//REPLACE THIS WITH YOUR OWN IMPLEMENTATION
	return currentView->locationID[player];
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void getHistory(GameView currentView, PlayerID player,
		LocationID trail[TRAIL_SIZE]) {
	//REPLACE THIS WITH YOUR OWN IMPLEMENTATION
}

//// Functions that query the map to find information about connectivity

// Returns an array of LocationIDs for all directly connected locations

LocationID *connectedLocations(GameView currentView, int *numLocations,
		LocationID from, PlayerID player, Round round, int road, int rail,
		int sea) {
	//REPLACE THIS WITH YOUR OWN IMPLEMENTATION
	return NULL;
}
