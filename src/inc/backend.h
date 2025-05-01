#ifndef BACKEND_H
#define BACKEND_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "libspec.h"

#define MAXROWS 20
#define MAXCOLS 10
#define COUNTCOORDINATE 5
#define COUNTFIGURE 7
#define COUNTDIMENSION 2
#define FALL_DELAY 50000  // 0,5 sec?
#define QUIT_DELAY 6000000 * 10
#define PULL 0
#define PUSH 1
#define COLLIDE 1
#define BAD_ARGUMENT 2

static const int figure_home[COUNTFIGURE][COUNTCOORDINATE][2] /*{x,y}*/ = {
    {{5, 0}, {0, 0}, {1, 0}, {-1, 0}, {1, 1}},   //   -.
    {{5, 1}, {0, 0}, {0, 1}, {0, 2}, {0, -1}},   // |  I
    {{5, 0}, {0, 0}, {0, 1}, {1, 0}, {-1, 0}},   // .|.
    {{5, 0}, {0, 0}, {0, 1}, {1, 1}, {1, 0}},    /// ::
    {{5, 0}, {0, 0}, {-1, 0}, {-1, 1}, {1, 0}},  // .-
    {{5, 0}, {0, 0}, {0, 1}, {1, 1}, {-1, 0}},   // Z
    {{5, 0}, {0, 0}, {0, 1}, {-1, 1}, {1, 0}}    //! Z
};

typedef enum {
  Hello,  // 0
  Spawn,
  Moving,
  Attaching,
  //   Paus,
  Gameover,
  Goodbye  // временно
} fsm_t;

void sumField(
    int** Field,
    int** FieldTwo);  // прибавление поля с приклеившимися фигурами ///
/// к полю для отрисовки использовать перед sumfigure!!!

int sumFigure(int** Field,
              int** figure);  // прибавление фигуры к полю перед отрисовкой
int subFigure(int** Field, int** Figure);  // вычитание фигуры из поля обратноd
int curtsy(int** Figure, int i);  // понижение фигуры
void zeroing_temp(
    int** Field);  // обнуление поля для отрисовки(да и другого при желании)
void Figuring(
    int** figure,
    int index);  // заполнение следующей и текущей фигур изначальными //
// координатами (позже усложнить до одной из 7ми фигур)

int stringDel(int** Field);
int fileScore(char* name, char* score, GameInfo_t* info);
// int FigureDown(int** Field, int** Figure);

int FigureDown2(int** Field, int** Figure);

int checkCollision(int** Field, int** Figure);
void copyFigure(int** dest, int** src);
int** createcopy();
int deletecopy(int*** copy);  // where deleteField?
int deletepole(int*** copy);
int curtsy2(int** Field, int** Figure, int i);
int rotateCols2(int** Field, int** Figure);
int moveCols2(int** Field, int** Figure, int i);
int scoring(GameInfo_t* tetris);
int fileScoreinput(char* name, GameInfo_t* info);
int** createpole();

void Hellostate(UserAction_t signal, fsm_t* state);
void Spawnstate(GameInfo_t* info, fsm_t* state);
void Movingstate(GameInfo_t* info, fsm_t* state, UserAction_t signal);
void Attachingstate(GameInfo_t* info, fsm_t* state);
void Gameoverstate(GameInfo_t* info, fsm_t* state, UserAction_t signal);
fsm_t just_state(UserAction_t signal, GameInfo_t* info, bool hold);

int** updatefigure();
void zeroing_all(GameInfo_t* x);
GameInfo_t get_set_info(GameInfo_t* info, int push);
int init_tetris(GameInfo_t* tetris);
#endif