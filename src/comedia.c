
#include "mozg.h"
#include <ncurses.h>
#include <string.h>
#include <unistd.h>

#include <stdlib.h>
int main(void) {
  // отсюда отрисовка
  initscr();
  timeout(1);
  curs_set(0);
  // noecho();
  keypad(stdscr, true);
  WINDOW *board = newwin(20, 20, 0, 0);
  refresh();
  // nodelay (board, 1);//////////////
  box(board, 0, 0);
  wrefresh(board);
  mvwaddstr(board, 2, 3, "Hello, enter");
  mvwaddstr(board, 3, 3, "your username");
  mvwaddstr(board, 6, 1, "Pss, the SQUARE ");
  mvwaddstr(board, 7, 3, " ...rotates... ");
  // wattroff(board, COLOR_PAIR(COLOR_WORDS));
  wrefresh(board);
  WINDOW *infopole = newwin(20, 13, 0, 21);
  // refresh();
  box(infopole, 0, 0);
  wrefresh(infopole);
  // mvwaddstr(infopole, 8, 3, "SS");
  // mvwaddstr(infopole, 10, 3, "ER");
  // wattroff(infopole, COLOR_PAIR(COLOR_WORDS));
  // wrefresh(infopole);
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK); // Цветовая пара 1: красный
  init_pair(2, COLOR_GREEN, COLOR_BLACK); // Цветовая пара 2: зеленый
  init_pair(3, COLOR_YELLOW, COLOR_BLACK); // Цветовая пара 3: желтый
  // досюда отрисовка

  clock_t lastFallTime = clock(); // для отслеживания таймера падения
  srand(time(NULL));
  int random = rand() % COUNTFIGURE;
  UserAction_t UserInput;
  GameInfo_t tetris;
  tetris.score = 0;
  tetris.high_score = 0;
  tetris.level = 0;

  tetris.figure = createcopy();
  tetris.next = createcopy();
  random =
      rand() %
      COUNTFIGURE; // второй раз потому что первая фигура всегда одна и та же
  Figuring(tetris.figure, random);
  random = rand() % COUNTFIGURE;
  Figuring(tetris.next, random);

  tetris.field = createpole();

  UserAction_t action = Start;
  // fsm_t fsm=Start;
  char *score = (char *)calloc(10, sizeof(char));
  char *name = (char *)calloc(10, sizeof(char));
  scanf("%s", name);
  fileScore(name, score, &tetris);
  noecho(); // отрисовочное
  while (action != Terminate) {
    if (action != Pause) {
      clock_t currentTime = clock(); // обновление времени с последнего падения

      int xmax = 0;
      // wrefresh(infopole);
      // wrefresh(board);
      // wclear(infopole);
      refresh(); // отрисовочное
      subFigure(tetris.field, tetris.figure);

      if (xmax = FigureDown2(tetris.field, tetris.figure) ==
                 1) { // проверка на падение фигуры
        sumFigure(tetris.field, tetris.figure);
        if (tetris.figure[0][1] <= 1) { // проверка на проигрыш
          action = Terminate;
        }
        scoring(&tetris); // удаление строк и подсчёт очков
        if (tetris.level < 10) {
          tetris.level = tetris.score / 600;
        } else {
          tetris.level = 10;
          }
        Figuring(tetris.figure, random);
        random = rand() % COUNTFIGURE;
        Figuring(tetris.next, random);
      } else if (xmax == 0) {
        // subFigure(tetris.field, tetris.figure);
      }
      // timeout((FALL_DELAY - (30 * tetris.level))*2);
      if ((currentTime - lastFallTime) >= (FALL_DELAY - (3000 * tetris.level))) {
        curtsy2(tetris.field, tetris.figure, 1); // Спускаем фигуру вниз
        lastFallTime = currentTime; // Обновляем время последнего падения
      }
      // curtsy2(tetris.field,tetris.figure, 1);
      if (action == Left) {
        xmax = moveCols2(tetris.field, tetris.figure, -1);
      } else if (action == Right) {
        xmax = moveCols2(tetris.field, tetris.figure, 1);
      } else if (action == Action) {
        xmax = rotateCols2(tetris.field, tetris.figure);
      }
      sumFigure(tetris.field, tetris.figure);
      // отсюда отрисовка
      fieldprint(board, tetris);
      infoprint(infopole, tetris, name);
    }
    if (action != Terminate)
      action = Uzvering(action);

    // refresh();
    // досюда отрисовка(фронтенд)}
  }

  fileScoreinput(name, &tetris);
  // // getch();
  // sleep(10);
  endwin();

  printf("%s %d", "you lose\nyour score: ", tetris.score);
  return 0;
}
