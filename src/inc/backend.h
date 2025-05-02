#ifndef BACKEND_H
#define BACKEND_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "lib_specification.h"

#define MAXROWS 20
#define MAXCOLS 10
#define COUNTCOORDINATE 5
#define COUNTFIGURE 7
#define COUNTDIMENSION 2
#define CELL_EMPTY '.'
#define CELL_FILLED 'I'
#define FALL_DELAY 50000 // 0,5 sec
#define QUIT_DELAY 6000000 * 10
#define PULL 0
#define PUSH 1
#define COLLIDE 1
#define BAD_ARGUMENT 2 //

typedef enum {
  Hello, // 0
  Spawn,
  Moving,
  Attaching,
  //   Paus,
  GameOver,
  Goodbye // временно
} FSM;

// прибавление фигуры к полю перед отрисовкой
int SumFigure(int **field, int **figure);
// вычитание фигуры из поля обратноd
int SubFigure(int **field, int **figure);
// обнуление поля для отрисовки(да и другого при желании)
void ZeroingTemp(int **field);
// заполнение следующей и текущей фигур изначальными //
// координатами (позже усложнить до одной из 7ми фигур)
void Figuring(int **figure, int index);

int StringDel(int **field);
int FileScore(char *name, GameInfo_t *info);
int FigureDown(int **field, int **figure);

int CheckCollision(int **field, int **figure);
void CopyFigure(int **dest, int **src);
int **CreateCopy();
int DeleteCopy(int ***copy); // where deletefield?
int DeleteField(int ***copy);
int Curtsy(int **field, int **figure, int i);
int RotateCols(int **field, int **figure);
int MoveCols(int **field, int **figure, int i);
int Scoring(GameInfo_t *tetris);
int FileScoreInput(char *name, GameInfo_t *info);
int **CreateField();

void HelloState(UserAction_t signal, FSM *state);
void SpawnState(GameInfo_t *info, FSM *state);
void MovingState(GameInfo_t *info, FSM *state, UserAction_t signal);
void AttachingState(GameInfo_t *info, FSM *state);
void GameOverState(GameInfo_t *info, FSM *state, UserAction_t signal);
FSM JustState(UserAction_t signal, GameInfo_t *info, bool hold);

int **UpdateFigure();
void ZeroingAll(GameInfo_t *tetris);
GameInfo_t GetSetInfo(GameInfo_t *info, int push);
int InitTetris(GameInfo_t *tetris);
#endif // BACKEND_H