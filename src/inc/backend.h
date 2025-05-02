#ifndef BACKEND_H
#define BACKEND_H

/**
 * @file backend.h
 * @brief Заголовочный файл с бэкенд-логикой тетриса: обработка игрового поля,
 * фигур и состояний.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "lib_specification.h"

/// @brief Количество строк игрового поля.
#define MAXROWS 20
/// @brief Количество столбцов игрового поля.
#define MAXCOLS 10
/// @brief Количество координат в фигуре (центральная + 4 блока).
#define COUNTCOORDINATE 5
/// @brief Количество разных фигур
#define COUNTFIGURE 7
/// @brief Размерность координат (x, y).
#define COUNTDIMENSION 2
/// @brief Символ пустой ячейки.
#define CELL_EMPTY '.'
/// @brief Символ занятой ячейки.
#define CELL_FILLED 'I'
/// @brief Задержка между падениями (в миллисекундах).
#define FALL_DELAY 50000 // 0,5 sec
/// @brief Задержка перед выходом из игры после поражения.
#define QUIT_DELAY 6000000 * 10
/// @brief Флаг для получения информации.
#define PULL 0
/// @brief Флаг для записи информации.
#define PUSH 1
/// @brief Флаг столкновения.
#define COLLIDE 1
/// @brief Код ошибки аргумента
#define BAD_ARGUMENT 2
/// @brief Код ошибки выделения памяти
#define BAD_MALLOC -1

/**
 * @brief Состояния конечного автомата игры.
 */
typedef enum {
  Hello,     // 0 ///< Приветственный экран.
  Spawn,     ///< Спавн новой фигуры.
  Moving,    ///< Движение текущей фигуры.
  Attaching, ///< Прикрепление фигуры к полю.
  //   Paus,
  GameOver, ///< Состояние конца игры.
  Goodbye   ///< Финальное завершение игры.
} FSM;

// === Основная логика поля и фигур ===

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

// === Состояния конечного автомата ===

void HelloState(UserAction_t signal, FSM *state);
void SpawnState(GameInfo_t *info, FSM *state);
void MovingState(GameInfo_t *info, FSM *state, UserAction_t signal);
void AttachingState(GameInfo_t *info, FSM *state);
void GameOverState(GameInfo_t *info, FSM *state, UserAction_t signal);
FSM JustState(UserAction_t signal, GameInfo_t *info, bool hold);

// === Глобальные данные и инициализация ===

int **UpdateFigure();
void ZeroingAll(GameInfo_t *tetris);
GameInfo_t GetSetInfo(GameInfo_t *info, int push);
int InitTetris(GameInfo_t *tetris);
#endif // BACKEND_H