#ifndef LIB_SPECIFICATION_H
#define LIB_SPECIFICATION_H

/**
 * @file lib_specification.h
 * @brief Определяет структуру данных GameInfo_t и перечисление UserAction_t,
 * используемые в игре Tetris.
 */

#include <stdbool.h>

/**
 * @enum UserAction_t
 * @brief Перечисление возможных действий пользователя.
 */
typedef enum {
  Start,     ///< Начало игры или продолжение.
  Pause,     ///< Пауза.
  Terminate, ///< Завершение игры.
  Left,      ///< Движение фигуры влево.
  Right,     ///< Движение фигуры вправо.
  Up, ///< Действие "вверх" (зарезервировано или для поворота).
  Down,  ///< Движение фигуры вниз.
  Action ///< Основное действие (например, поворот фигуры).
} UserAction_t;

/**
 * @struct GameInfo_t
 * @brief Структура, содержащая текущее состояние игры.
 */
typedef struct {
  int **field;    ///< Игровое поле.
  int **next;     ///< Следующая фигура.
  int score;      ///< Текущий счёт игрока.
  int high_score; ///< Рекорд (высший счёт).
  int level;      ///< Уровень сложности.
  int speed; ///< Скорость игры (не используется в текущей версии).
  int pause; ///< Флаг паузы (1 — игра на паузе, 0 — активна).
} GameInfo_t;

/**
 * @brief Обрабатывает пользовательский ввод.
 *
 * @param action Действие пользователя.
 * @param hold Флаг, указывающий, удерживается ли клавиша.
 */
void userInput(UserAction_t action, bool hold);

/**
 * @brief Обновляет и возвращает текущее состояние игры.
 *
 * @return Актуальное состояние игры.
 */
GameInfo_t updateCurrentState();

#endif // LIB_SPECIFICATION_H