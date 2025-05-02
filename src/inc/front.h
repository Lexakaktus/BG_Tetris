#ifndef FRONT_H
#define FRONT_H

#include <ncurses.h>

#include "lib_specification.h"

#define MAXROWS 20
#define MAXCOLS 10
#define COUNTCOORDINATE 5
#define COUNTFIGURE 7
#define COUNTDIMENSION 2

UserAction_t Uzvering(UserAction_t action, bool *hold);  // void userInput
int InfoPrint(WINDOW *info_window, GameInfo_t tetris, char *name);
int NewFigurePrint(WINDOW *info_window, GameInfo_t tetris);
int FieldPrint(WINDOW *board, GameInfo_t tetris);
void Draw(WINDOW **board, WINDOW **info_window);
int GamePrint(WINDOW *board, WINDOW *info_window, GameInfo_t tetris,
              char *name);

#endif  // FRONT_H