#include "../../inc/backend.h"

/**
 * @brief Обработка состояния Hello.
 *
 * Если пользователь нажимает Terminate — переходит в GameOver.
 * Если нажимает Action (Enter) — переходит в Spawn.
 *
 * @param signal Входной сигнал пользователя.
 * @param state Указатель на текущее состояние автомата.
 */
void HelloState(UserAction_t signal, FSM *state) { 
  if (signal == Terminate) {
    *state = GameOver;
  } else if (signal == Action) {
    *state = Spawn;
  }
}

/**
 * @brief Обрабатывает появление новой фигуры.
 *
 * Выбирает следующую и текущую фигуры, устанавливает их в поле.
 *
 * @param info Указатель на структуру состояния игры.
 * @param state Указатель на текущее состояние автомата.
 */
void SpawnState(GameInfo_t *info, FSM *state) { 
  static int random = -1;                       
  int **figure = UpdateFigure();
  if (random == -1) {
    random = rand() % COUNTFIGURE;
    random = rand() % COUNTFIGURE;
  }
  Figuring(figure, random);
  random = rand() % COUNTFIGURE;
  Figuring(info->next, random);
  SumFigure(info->field, figure);
  *state = Moving; /* code */
}


/**
 * @brief Обрабатывает активное движение фигуры по полю.
 *
 * Перемещение, поворот, падение, переход к приклеиванию.
 *
 * @param info Указатель на состояние игры.
 * @param state Указатель на состояние автомата.
 * @param signal Действие игрока.
 */
void MovingState(GameInfo_t *info, FSM *state, UserAction_t signal) {
  GetSetInfo(info, PULL);
  static clock_t last_fall_time = 0;
  int **figure = UpdateFigure();
  clock_t current_time = clock(); 
  SubFigure(info->field, figure);
  if (signal == Left) {
    MoveCols(info->field, figure, -1);
  } else if (signal == Right) {
    MoveCols(info->field, figure, 1);
  } else if (signal == Action) {
    RotateCols(info->field, figure);
  } else if (signal == Down) {
    while (Curtsy(info->field, figure, 1) == 0);
  }
  if ((current_time - last_fall_time) >=
      ((clock_t)(FALL_DELAY - (3000 * info->level)))) {
    Curtsy(info->field, figure, 1); 
    last_fall_time = current_time;  
  }
  if (FigureDown(info->field, figure) != 0) {
    *state = Attaching;
  }
  SumFigure(info->field, figure);
}

/**
 * @brief Обрабатывает "приклеивание" фигуры к полю.
 *
 * Если фигура на самой верхней строке — игра закончена.
 * Иначе — начисляются очки, обновляется уровень и переходим в Spawn.
 *
 * @param info Указатель на состояние игры.
 * @param state Указатель на текущее состояние автомата.
 */
void AttachingState(GameInfo_t *info, FSM *state) {
  if (info->field[0][5] == 'I') {
    *state = GameOver;
  } else {
    Scoring(info);
    if (info->level <
        10) {  // поправить, может привести к багу с временно 11ым уровнем
      info->level = info->score / 600;
    } else {
      info->level = 10;
    }
    GetSetInfo(info, PUSH);  // не в хедере!!!
    *state = Spawn;
  }
}

/**
 * @brief Состояние проигрыша.
 *
 * Ожидает либо перезапуска, либо выхода.
 *
 * @param info Указатель на структуру игры.
 * @param state Указатель на текущее состояние автомата.
 * @param signal Ввод пользователя.
 */
void GameOverState(GameInfo_t *info, FSM *state, UserAction_t signal) {
  static clock_t lose_time = 0;
  clock_t current_time = clock();
  if (lose_time == 0) {
    lose_time = current_time;
  }
  if (signal == Start) {
    ZeroingAll(info);
    *state = Hello;
  } else if (signal == Terminate || current_time - lose_time > QUIT_DELAY) {
    *state = Goodbye;
  }
}

/**
 * @brief Основной обработчик конечного автомата игры.
 *
 * В зависимости от текущего состояния вызывает соответствующую функцию.
 *
 * @param signal Сигнал от пользователя (ввод).
 * @param info Указатель на игровое состояние.
 * @param hold Было ли удержание клавиши.
 * @return Текущее состояние автомата.
 */
FSM JustState(UserAction_t signal, GameInfo_t *info, bool hold) {
  hold=0;
  static FSM state = Hello;
  GetSetInfo(info, PULL);
  switch (state) {
    case Hello:
      HelloState(signal, &state);
      break;
    case Spawn:
      SpawnState(info, &state);
      break;
    case Moving:
      MovingState(info, &state, signal);
      break;
    case Attaching:
      AttachingState(info, &state);
      break;
    case GameOver:
      /* code */
      ////рисовка окна проигрыша
      //
      GameOverState(info, &state, signal);
      break;
    default:
      if (hold) {
        ;
      }
      break;
  }
  return state;
}