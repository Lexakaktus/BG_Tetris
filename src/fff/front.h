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



UserAction_t Uzvering(UserAction_t action, bool * hold ); // void userInput
int infoprint(WINDOW* infopole, GameInfo_t tetris, char* name);
int nfigprint(WINDOW* infopole, GameInfo_t tetris);
int fieldprint(WINDOW* board, GameInfo_t tetris);

void drawUI(WINDOW **board, WINDOW **infopole);
int gameprint(WINDOW *board,WINDOW *infopole, GameInfo_t tetris, char *name );

#endif