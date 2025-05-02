#include "../../inc/backend.h"
#include "../../inc/front.h"

/**
 * @brief Получает или устанавливает текущее состояние конечного автомата.
 *
 * @param state Указатель на переменную состояния.
 * @param push Если 1 — устанавливает состояние, если 0 — возвращает текущее.
 */
void get_state(FSM *state, int push) {
  static FSM stat = -1;
  if (push) {
    stat = *state;
  } else {
    *state = stat;
  }
}


/**
 * @brief Обрабатывает пользовательский ввод.
 *
 * Управляет состоянием игры: пауза, завершение, передаёт действие в автомата состояний.
 *
 * @param action Событие, вызванное нажатием клавиши пользователем.
 * @param hold Было ли удержание клавиши (не используется пока).
 */
void userInput(UserAction_t action, bool hold) {  // not declaration
  GameInfo_t game_info = GetSetInfo(&game_info, PULL);
  FSM state=Hello;
  if (!(state == Goodbye || game_info.pause)) {
    state = JustState(action, &game_info, hold);
  }
  if (action == Pause) {
    game_info.pause = !game_info.pause;
  }
  if (action == Terminate) {
    state = Goodbye;
  }
  GetSetInfo(&game_info, PUSH);
  get_state(&state, PUSH);
}


/**
 * @brief Возвращает актуальное состояние игры.
 *
 * Используется для фронтенда: обновляет отображение игры.
 *
 * @return Текущий `GameInfo_t`.
 */
GameInfo_t updateCurrentState() {
  GameInfo_t info_t;
  //  GetSetInfo(&info_t, PULL);

  return GetSetInfo(&info_t, PULL);
}


/**
 * @brief Главная точка входа в игру.
 *
 * Инициализирует ncurses, структуру игры, обрабатывает цикл ввода/рендеринга.
 *
 * @return Код завершения (0).
 */
int main(void) {
  WINDOW *board, *info_field;
  Draw(&board, &info_field);
  srand(time(NULL));
  
  FSM state = Hello;
  UserAction_t signal = ERR;

  GameInfo_t tetris;
  InitTetris(&tetris);
  GetSetInfo(&tetris, PUSH);
  while (state != Goodbye) {
    bool hold = 0;
    signal = Uzvering(signal, &hold);
    userInput(signal, hold);
    get_state(&state, PULL);
    GamePrint(board, info_field, updateCurrentState(), "user");  // char *name
  }

  FileScoreInput("user", &tetris);

  endwin();
  printf("%s %s %d\n", "user", "\n", tetris.high_score);    // убрать
  printf("%s %d", "you lose\nyour score: ", tetris.score);  // убрать

  return 0;
}