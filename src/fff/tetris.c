#include "backend.h"
#include "front.h"



GameInfo_t updateCurrentState(UserAction_t * action) {
  static int random = 0;
  static int flag=1;
  static GameInfo_t tetris={0};
  if (flag ) {
    //!!!!
    tetris.score = 0;
    tetris.high_score = 0;
    tetris.level = 0;

    tetris.field = createpole();
    tetris.figure = createcopy(); // заменить
    tetris.next = createcopy();  
    random = rand() % COUNTFIGURE;
    // второй раз потому что первая фигура всегда одна и та же
    Figuring(tetris.figure, random);
    random = rand() % COUNTFIGURE;
    Figuring(tetris.next, random);
    flag=0;
    //update(&tetris, 0);
  } 
      static clock_t lastFallTime = 0;
      clock_t currentTime = clock();  // обновление времени с последнего падения
      int xmax = 0;//??
      subFigure(tetris.field, tetris.figure);
      if ((currentTime - lastFallTime) >=
          (FALL_DELAY - (3000 * tetris.level))) {
        curtsy2(tetris.field, tetris.figure, 1);  // Спускаем фигуру вниз
        lastFallTime = currentTime;  // Обновляем время последнего падения
      }

      if (xmax = FigureDown2(tetris.field, tetris.figure) ==
                 1) {  // проверка на падение фигуры
        sumFigure(tetris.field, tetris.figure);
        if (tetris.figure[0][1] <= 1) {  // проверка на проигрыш
          *action = Terminate;
        }
        scoring(&tetris);  // удаление строк и подсчёт очков
        if (tetris.level < 10) {
          tetris.level = tetris.score / 600;
        } else {
          tetris.level = 10;
        }
        Figuring(tetris.figure, random);
        random = rand() % COUNTFIGURE;
        Figuring(tetris.next, random);}
      if (*action == Left) {
        xmax = moveCols2(tetris.field, tetris.figure, -1);
      } else if (*action == Right) {
        xmax = moveCols2(tetris.field, tetris.figure, 1);
      } else if (*action == Action) {
        xmax = rotateCols2(tetris.field, tetris.figure);
      } else if (*action == Down) {
        while (curtsy2(tetris.field, tetris.figure, 1)==0);
      } 
      sumFigure(tetris.field, tetris.figure);
  return tetris;    
}
int main(void) {
  // отсюда отрисовка
  WINDOW *board, *infopole;
  drawUI(&board, &infopole);
  
  // clock_t lastFallTime = clock();  // для отслеживания таймера падения
  srand(time(NULL));
  static UserAction_t action = Start;
  GameInfo_t tetris=updateCurrentState(&action);



 
  // fsm_t fsm=Start;
  char *score = (char *)calloc(10, sizeof(char));//для счёта
  char *name = (char *)calloc(10, sizeof(char));
  scanf("%s", name);
  fileScore(name, score, &tetris);
  noecho();  // отрисовочное
 while (action != Terminate) {
    if (action != Pause) {
      refresh;
      int tempscore=tetris.high_score;
      tetris=updateCurrentState(&action);
      if (tetris.high_score<tempscore)
      {tetris.high_score=tempscore;}
      // отсюда отрисовка
      fieldprint(board, tetris);
      infoprint(infopole, tetris, name);
    }
    if (action != Terminate) action = Uzvering(action);
    // досюда отрисовка(фронтенд)}
  }
  
  fileScoreinput(name, &tetris);

  endwin();
  printf("%s %s %d\n", name, "\n", tetris.high_score);//убрать
  printf("%s %d", "you lose\nyour score: ", tetris.score);//убрать
  return 0;
}

 