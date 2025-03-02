#ifndef LIBSPEC_H
#define LIBSPEC_H
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
  int** temp_field;
  int** figure;
  int** next;      /// следующая фигура
  int score;       /// счёт игры
  int high_score;  /// счёт из файла "ИмяИгрока" или максимальный в игре
  int level;
  int speed;
  int pause;
} GameInfo_t;

#endif