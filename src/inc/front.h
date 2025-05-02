#ifndef FRONT_H
#define FRONT_H

/**
 * @file front.h
 * @brief Заголовочный файл с функциями интерфейса для отображения Tetris с
 * использованием ncurses.
 */

#include <ncurses.h>

#include "lib_specification.h"

/// @brief Количество строк игрового поля.
#define MAXROWS 20
/// @brief Количество столбцов игрового поля.
#define MAXROWS 20
/// @brief Количество столбцов игрового поля.
#define MAXCOLS 10
/// @brief Количество координат в фигуре.
#define COUNTCOORDINATE 5
/// @brief Количество различных фигур.
#define COUNTFIGURE 7
/// @brief Количество измерений (x, y)
#define COUNTDIMENSION 2

/**
 * @brief Обрабатывает ввод пользователя с клавиатуры.
 *
 * @param action Предыдущее действие пользователя.
 * @param hold Указатель на флаг "зажатия" клавиши.
 * @return Новое действие пользователя.
 */
UserAction_t Uzvering(UserAction_t action, bool *hold);  // void userInput

/**
 * @brief Отображает дополнительную информацию об игре.
 *
 * @param info_window Окно ncurses для информации.
 * @param tetris Текущее состояние игры.
 * @param name Имя игрока.
 * @return 0 при успехе.
 */
int InfoPrint(WINDOW *info_window, GameInfo_t tetris, char *name);

/**
 * @brief Отображает следующую фигуру.
 *
 * @param info_window Окно ncurses для информации.
 * @param tetris Текущее состояние игры.
 * @return 0 при успехе.
 */
int NewFigurePrint(WINDOW *info_window, GameInfo_t tetris);

/**
 * @brief Отображает основное поле игры.
 *
 * @param board Окно ncurses с полем.
 * @param tetris Текущее состояние игры.
 * @return 0 при успехе.
 */
int FieldPrint(WINDOW *board, GameInfo_t tetris);

/**
 * @brief Инициализирует и рисует интерфейс: поле и информационную панель.
 *
 * @param board Указатель на окно поля.
 * @param info_window Указатель на окно информации.
 */
void Draw(WINDOW **board, WINDOW **info_window);

/**
 * @brief Отрисовывает всю игровую информацию.
 *
 * @param board Окно поля.
 * @param info_window Окно информации.
 * @param tetris Структура с состоянием игры.
 * @param name Имя игрока.
 * @return 0 при успехе.
 */
int GamePrint(WINDOW *board, WINDOW *info_window, GameInfo_t tetris,
              char *name);

#endif  // FRONT_H