#ifndef FRONT_H
#define FRONT_H

// #include "backend.h" ///разобраться с этим !!!
#include <ncurses.h>
#include "libspec.h"
#define MAXROWS 20
#define MAXCOLS 10
#define COUNTCOORDINATE 5
#define COUNTFIGURE 7
#define COUNTDIMENSION 2



UserAction_t Uzvering(UserAction_t action ); // void userInput
int infoprint(WINDOW* infopole, GameInfo_t tetris, char* name);
int nfigprint(WINDOW* infopole, GameInfo_t tetris);
int fieldprint(WINDOW* board, GameInfo_t tetris);

#endif