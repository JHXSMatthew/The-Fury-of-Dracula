CC = gcc
CFLAGS = -Wall -Werror -g
BINS = testGameView testHunterView testDracView

all : $(BINS)

testGameView : testGameView.o GameView.o Map.o Places.o linkList.o
testGameView.o : testGameView.c Globals.h Game.h linkList.o

#testHunterView : testHunterView.o HunterView.o Map.o Places.o linkList.o
#testHunterView.o : testHunterView.c Map.c Places.h linkList.o

#testDracView : testDracView.o DracView.o Map.o Places.o linkList.o
#testDracView.o : testDracView.c Map.c Places.h linkList.o

Places.o : Places.c Places.h
Map.o : Map.c Map.h Places.h
GameView.o : GameView.c GameView.h
HunterView.o : HunterView.c HunterView.h
DracView.o : DracView.c DracView.h
linkList.o : linkList.c linkList.h

clean :
	rm -f $(BINS) *.o core

