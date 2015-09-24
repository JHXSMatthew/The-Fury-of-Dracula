// GameView.c ... GameView ADT implementation

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "Map.h"
#include "linkList.h"

#define MAX_CONNECTION 600
#define FIRST_ACTION 3
#define ALIVE 1
#define DEAD 0



// #include "Map.h" ... if you decide to use the Map ADT

struct gameView {
	//REPLACE THIS WITH YOUR OWN IMPLEMENTATION
	int playerHealth[5];
	int locationID[5];
	int currentPlayer;
	int score;
	Round round ;
	int Playerstatus[5];
	List history[5];
    Map map;
    int * freeOutPut[MAX_CONNECTION];
    int currentFreeOutPut;
};

//typedef char currentMessage[7];

//setters make code more readable
static void setHealth(GameView, int, int);
static void setScore(GameView, int);
static void setround(GameView, int);
static void setCurrentPlayer(GameView, int);
static void setLocation(GameView, int, int);
static int isAlive(GameView ,int);
static int whoIsThis(char *);
static void setInitials(GameView);
static void setAliveOrDie(GameView gameView,int player, int status);
static void addHistory(GameView gameView,int player ,int location);
static int getId(GameView,char * placeName);
static int doubleBackSea(GameView gameView ,int back);

// Creates a new GameView to summarise the current state of the game
GameView newGameView(char *pastPlays, PlayerMessage messages[]) {
	//REPLACE THIS WITH YOUR OWN IMPLEMENTATION
	GameView gameView = malloc(sizeof(struct gameView));
//    char * step = "";
	char  placeName[3];
	char  action[5];
	int turn = 0;
    int id=0;
//    strncpy(step,pastPlays,7);
//    currentMessage deal;

	int curr = 0;

//	if(*pastPlays != '\0'){
	if(*pastPlays == '\0'){
        
		setInitials(gameView);
        printf("GameView -> initial conditions now \n");
	}else{
		while (pastPlays[curr] == 'G' || pastPlays[curr] =='M' ||pastPlays[curr] =='S' || pastPlays[curr] =='D'||pastPlays[curr] =='H' ) {
            printf("TMEP DEBUG ==> %c \n",pastPlays[curr]);
			//placeName = "...";
			//action = "....";
            printf("GameView -> Turn Begin  \n");
			if(curr == 0){
				setInitials(gameView);
                printf("GameView -> initial conditions now \n");
			}

				//change current player for future use
			setCurrentPlayer(gameView, whoIsThis(&pastPlays[curr]));

printf("GameView -> setCurrent Player : %d\n",whoIsThis(&pastPlays[curr]));

			assert(gameView->currentPlayer != -1);

				//set the place name
			strncpy(placeName, &pastPlays[curr + 1], 2);
            placeName[2] = '\0';
            id = getId(gameView,placeName);

printf("GameView -> setCurrent Place Name:%s,ID:%d\n",placeName,id);
				// set location now

			if(isAlive(gameView,getCurrentPlayer(gameView))){
printf("GameView -> MOVE FINISH \n");

                setLocation(gameView, getCurrentPlayer(gameView), id);				
				addHistory(gameView,getCurrentPlayer(gameView),id);
				strncpy(action,&pastPlays[curr + 3],4);
                action[4] = '\0';
printf("GameView -> Action String :%s\n",action);
				//check who is the player and do actions
				if(getCurrentPlayer(gameView) <= 3){
					//hunter acrtions
printf("GameView -> Player action \n");
					//check traps
					int i;
					for (i=0; i < strlen(action); i++ ){
						if(action[i] == 'T'){
							setHealth(gameView,getCurrentPlayer(gameView),getHealth(gameView,getCurrentPlayer(gameView)) - 2);
                            printf("GameView -> Trap encountered for %d ,After health : %d \n",gameView->currentPlayer, getHealth(gameView,getCurrentPlayer(gameView)));
						}else if(action[i] == 'V'){
							//wow, no effect to huntet OK.
						}else if(action[i] == 'D'){
							setHealth(gameView,getCurrentPlayer(gameView),getHealth(gameView,getCurrentPlayer(gameView) )- 4);
							setHealth(gameView,PLAYER_DRACULA,getHealth(gameView,PLAYER_DRACULA )- 10);
printf("GameView -> Dracula Encountered for %d ,After health : %d \n",gameView->currentPlayer, getHealth(gameView,getCurrentPlayer(gameView)));
						}
					}

					if(!isAlive(gameView, getCurrentPlayer(gameView))){
						setLocation(gameView,getCurrentPlayer(gameView),ST_JOSEPH_AND_ST_MARYS);
						setHealth(gameView,getCurrentPlayer(gameView),0);
						setAliveOrDie(gameView,getCurrentPlayer(gameView), DEAD);
						setScore(gameView,gameView->score -6);
					}
				}else{
					// dracula's actions
					int i;
					for (i=0; i < strlen(action); i++ ){
						if(action[i] == 'V'){
							setScore(gameView,gameView->score -13);
						}
					}


				}
			}else{
				if(getCurrentPlayer(gameView) <= 3){
					setAliveOrDie(gameView,getCurrentPlayer(gameView),ALIVE);
					setHealth(gameView,getCurrentPlayer(gameView),GAME_START_HUNTER_LIFE_POINTS);
				}
			}
            
				//assert(step[7] == ' ');

			curr += 8;
			turn ++;
			if(turn == 5){
				//gameView.round++;
				gameView->round++;
				gameView->score --;
				turn = 0;
			}
        if(gameView->currentPlayer > 3 ){
            gameView->currentPlayer = 0;

        }else{
            gameView->currentPlayer ++;
        }
		}
	}

	return gameView;
}

static int getId(GameView gameView,char* placeName){
    if(strcmp(placeName,"C?") == 0  || strcmp(placeName,"S?") == 0  ||strcmp(placeName,"HI") == 0  ||strcmp(placeName,"D1") == 0  ||strcmp(placeName,"D2") == 0  ||strcmp(placeName,"D3") == 0  ||strcmp(placeName,"D4") == 0  ||strcmp(placeName,"D5") == 0  ||strcmp(placeName,"TP") == 0 ) {

        if(strcmp(placeName,"C?") == 0){
            return CITY_UNKNOWN;
        }else if(strcmp(placeName,"S?") == 0){
            return SEA_UNKNOWN;
        }else if(strcmp(placeName,"HI") == 0){
            return HIDE;
        }else if(strcmp(placeName,"D1") == 0){
            if(doubleBackSea(gameView,1) ){
                setHealth(gameView,PLAYER_DRACULA,getHealth(gameView,PLAYER_DRACULA) - 4 );
            }
            return DOUBLE_BACK_1;
        }else if(strcmp(placeName,"D2") == 0){
            if(doubleBackSea(gameView,2) ){
                setHealth(gameView,PLAYER_DRACULA,getHealth(gameView,PLAYER_DRACULA) - 4 );
            }
            return DOUBLE_BACK_2;
        }else if(strcmp(placeName,"D3") == 0){
            if(doubleBackSea(gameView,3) ){
                setHealth(gameView,PLAYER_DRACULA,getHealth(gameView,PLAYER_DRACULA) - 4 );
            }
            return DOUBLE_BACK_3;
        }else if(strcmp(placeName,"D4") == 0){
            if(doubleBackSea(gameView,4) ){
                setHealth(gameView,PLAYER_DRACULA,getHealth(gameView,PLAYER_DRACULA) - 4 );
            }
            return DOUBLE_BACK_4;
        }else if(strcmp(placeName,"D5") == 0){
            if(doubleBackSea(gameView,5) ){
                setHealth(gameView,PLAYER_DRACULA,getHealth(gameView,PLAYER_DRACULA) - 4 );
            }
            return DOUBLE_BACK_5;
        }else if(strcmp(placeName,"TP") == 0){
            return CASTLE_DRACULA;
        }
/*
                    switch (placeName) {
                        case "C?" :
                            return CITY_UNKNOWN;
                    
                        case "S?" :
                            return SEA_UNKNOWN;
            
                         case "HI" :
                            return HIDE;
                   
                        case "D1" :
                            return DOUBLE_BACK_1;
                    
                        case "D2" :
                            return DOUBLE_BACK_2;
                 
                        case "D3" :
                            return DOUBLE_BACK_3;

                        case "D4" :
                            return DOUBLE_BACK_4;

                        case "D5" :
                            return DOUBLE_BACK_5;

                        case "TP" :
                            return TELEPORT;
                        }
*/
                                   
     }
        return abbrevToID(placeName);
     
}

static void addHistory(GameView gameView,int player ,int location){
	append(gameView->history[player],location);
}

static int doubleBackSea(GameView gameView ,int back){
	printf("GameView -> %d \n",getValue(gameView->history[PLAYER_DRACULA],back -1));
	if(getValue(gameView->history[PLAYER_DRACULA],back-1) == SEA_UNKNOWN){
		return TRUE;
	}
	if(getValue(gameView->history[PLAYER_DRACULA],back-1) == CITY_UNKNOWN){
		return FALSE;
	}
	if(getValue(gameView->history[PLAYER_DRACULA],back)-1 == HIDE){
		return FALSE;
	}
    if(idToType(getValue(gameView->history[PLAYER_DRACULA],back-1)) == SEA ){
        return TRUE;
    }
    return FALSE;
}


static void setAliveOrDie(GameView gameView,int player, int status){
	gameView->Playerstatus[player] = status;
}

static int isAlive(GameView gameView , int player){
	if(getHealth(gameView, player) > 0){
		return ALIVE;
	}
	return DEAD;

}

static void setInitials(GameView gameView){

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
	//set they are alive
	gameView->Playerstatus[PLAYER_LORD_GODALMING]=ALIVE;
	gameView->Playerstatus[PLAYER_DR_SEWARD]=ALIVE;
	gameView->Playerstatus[PLAYER_VAN_HELSING]=ALIVE;
	gameView->Playerstatus[PLAYER_MINA_HARKER]=ALIVE;
	gameView->Playerstatus[PLAYER_DRACULA]=ALIVE;
	//initial their history list
	gameView->history[PLAYER_LORD_GODALMING] = newList();
	gameView->history[PLAYER_DR_SEWARD] = newList();
	gameView->history[PLAYER_VAN_HELSING] = newList();
	gameView->history[PLAYER_MINA_HARKER] = newList();
	gameView->history[PLAYER_DRACULA] = newList();
	int count;
	for (count = 0; count <5 ; count ++){
		append(gameView->history[PLAYER_LORD_GODALMING],-1);
		append(gameView->history[PLAYER_DR_SEWARD],-1);
		append(gameView->history[PLAYER_VAN_HELSING],-1);
		append(gameView->history[PLAYER_MINA_HARKER],-1);
		append(gameView->history[PLAYER_DRACULA],-1);
	}
    gameView->map = newMap();

    gameView->currentFreeOutPut = 0;
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
	int i;
	for(i = 0; i< 5 ; i++){
    //    printf("GameView -> Free list Num.%d \n",i);
		freeList(toBeDeleted->history[i]);
	}
    disposeMap(toBeDeleted->map);
    for(i=0;i < toBeDeleted->currentFreeOutPut; i++){
    	free(toBeDeleted->freeOutPut[i]);
    }
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
	int i ;
	for (i = 0;i < TRAIL_SIZE; i++ ){
		trail[i] = getValue(currentView->history[player],i);
	}
	//REPLACE THIS WITH YOUR OWN IMPLEMENTATION
}

//// Functions that query the map to find information about connectivity

// Returns an array of LocationIDs for all directly connected locations

LocationID *connectedLocations(GameView currentView, int *numLocations,
		LocationID from, PlayerID player, Round round, int road, int rail,
		int sea) {

	LocationID loc [MAX_CONNECTION] ;
printf("GameView -> Connection function start   \n");

//dead?
	if(isAlive(currentView,player) == DEAD){
		printf("GameView -> DEAD,nothing to do    \n");
	     numLocations = 0;
	     return NULL;
	 }
//dracula cannot move rail
    if(player > 3){
    	printf("GameView -> Dracula cannot move by RAIL    \n");
        if(rail == TRUE){
            rail = FALSE;
        }
    }

printf("GameView -> RAIL: %d \n", rail);
	if(rail){
		int depth = currentView->round + currentView->currentPlayer;
		outputConnections(currentView->map, from , RAIL , numLocations,loc, depth);
	}
	printf("GameView -> ROAD: %d \n", road);
	if(road){
		outputConnections(currentView->map, from , ROAD , numLocations,loc, 0);
	}
	printf("GameView -> SEA: %d \n", sea);
	if(sea){
		outputConnections(currentView->map, from , BOAT , numLocations,loc, 0);
	}


//malloc output array
	int * output;
	output = (int*) malloc(sizeof(int) * *numLocations);
	int i;
	for(i = 0; i < * numLocations; i++){
		output[i] = loc[i];
	}
	currentView->freeOutPut[currentView->currentFreeOutPut] = output;
	currentView->currentFreeOutPut++;
	return output;
/*
    int transID[MAX_CONNECTION];
    LocationID loc[MAX_CONNECTION];
    int returnValue[MAX_CONNECTION];
    int n,i,count;

    numLocations = 0;
// no move when player is dead
   if(isAlive(currentView,player) == DEAD){
        numLocations = 0;
        return NULL;
    }

    count = 0;

//Dracula cannot move by rail
    if(player > 3){
        if(rail == TRUE){
            rail = FALSE;
        }
    }else if(rail == TRUE){
// calculate DFS depths
            int searchDepths = currentView->round + currentView->currentPlayer;
    }

 
//see normal connections i.e. howManyConnections do not take rail connections into account !
    int cn = howManyConnections(currentView->map);
    while(cn){
        n = connections(current->map, from, i, transID[]);
        for( i = 0 , i < n , i++){

            if(road){
                if(transID[i] == ROAD){
                   returnValue[numLocations] = loc[i]
                   numLocations ++; 
                }
            }
            if(sea){
                if(transID[i] == SEA){
                   returnValue[numLocations] = loc[i]
                   numLocations ++;
                }
            }
        }
        cn--;
    }

//Take rail connections into account
    if(rail){
        //function here
    }

	//REPLACE THIS WITH YOUR OWN IMPLEMENTATION
	return returnValue;
	*/

}
