#include "../../inc/backend.h"
void HelloState(UserAction_t signal, FSM *state) {  // not include!!!
  if (signal == Terminate) {
    *state = GameOver;
  } else if (signal == Action) {
    *state = Spawn;
  }
}

void SpawnState(GameInfo_t *info, FSM *state) {  // not include!!!
  static int random = -1;                          // наблюдаем
  int **figure = UpdateFigure();
  if (random == -1) {
    random = rand() % COUNTFIGURE;
  }
  Figuring(figure, random);
  random = rand() % COUNTFIGURE;
  Figuring(info->next, random);
  SumFigure(info->field, figure);
  *state = Moving; /* code */
}

void MovingState(GameInfo_t *info, FSM *state, UserAction_t signal) {
  GetSetInfo(info, PULL);
  static clock_t last_fall_time = 0;
  int **figure = UpdateFigure();
  clock_t current_time = clock();  // обновление времени с последнего падения
  SubFigure(info->field, figure);
  if (signal == Left) {
    MoveCols(info->field, figure, -1);
  } else if (signal == Right) {
    //   info->field[19][9]='R';
    MoveCols(info->field, figure, 1);
  } else if (signal == Action) {
    // info->field[19][9]='B';
    RotateCols(info->field, figure);
  } else if (signal == Down) {
    while (Curtsy(info->field, figure, 1) == 0);
  }
  if ((current_time - last_fall_time) >=
      ((clock_t)(FALL_DELAY - (3000 * info->level)))) {
    Curtsy(info->field, figure, 1);  // Спускаем фигуру вниз
    last_fall_time = current_time;  // Обновляем время последнего падения
  }
  if (FigureDown(info->field, figure) != 0) {
    *state = Attaching;
  }
  SumFigure(info->field, figure);
}

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

void GameOverState(GameInfo_t *info, FSM *state, UserAction_t signal) {
  // info->field[19][9]='G';
  static clock_t lose_time = 0;
  clock_t current_time = clock();
  if (lose_time == 0) {
    lose_time = current_time;
  }
  if (signal == Start) {
    // info->score=0;
    ZeroingAll(info);
    *state = Hello;
  } else if (signal == Terminate || current_time - lose_time > QUIT_DELAY) {
    *state = Goodbye;
  }
}

FSM JustState(UserAction_t signal, GameInfo_t *info, bool hold) {
  hold=0;
  static FSM state = Hello;
  GetSetInfo(info, PULL);
  switch (state) {
    case Hello:
      HelloState(signal, &state);
      break;
    case Spawn:
      // если спавнится одна и та же первая фигура добавить ещё этап рандома
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