#ifndef LIBSPEC_H
#define LIBSPEC_H
#include <stdbool.h>
typedef enum {
  Start,  // 0
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action  // 7
} UserAction_t;

typedef struct {
  int** field;  /// поле для отрисовки
  // int** figure;
  int** next;      /// следующая фигура
  int score;       /// счёт игры
  int high_score;  /// счёт из файла "ИмяИгрока" или максимальный в игре
  int level;
  int speed;
  int pause;
} GameInfo_t;

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

#endif