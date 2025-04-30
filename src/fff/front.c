#include "front.h"

UserAction_t Uzvering(UserAction_t action, bool * hold) {  // переименовать //и отправить на контроллер!!!
  static UserAction_t push;                          //=action;
  push=action;
  int a = getch();
  // if (action != Pause) {
    switch (a) {
      case 'a':
      case KEY_LEFT:
        action = Left;
        break;
      case 'd':
      case KEY_RIGHT:
        action = Right;
        break;
      case 'p':
        action = Pause;
        break;
      case 'q':
        action = Terminate;
        break;
      case 27:  // escape
        action = Terminate;
        break;
      case '\n':
        action = Action;
        break;
      case 's':
      case KEY_DOWN:
        action = Down;
        break;
      case '\\':
        action = Start;
        break;
      case 'w':
      case KEY_UP:
        action = Up;
        break;
      default:
        action = -1;
        break;
    
    }
  // } else if (a != 'p' && a != 'q') {
  //   push = Pause;
  // } else if (a == 'q') {
  //   push = Terminate;
  // } else {
  //   push = Start;
  // }
  * hold = (push==action&&push!=Up);
  return action;
}
int nfigprint(WINDOW *infopole, GameInfo_t tetris) { //фронт
  int x = tetris.next[0][0] - 3;
  int y = tetris.next[0][1] + 1;

  for (int i = 1; i < COUNTCOORDINATE; i++) {
    //  wclrtoeol(infopole);
    mvwprintw(infopole, i, 1, "%c   ", ' ');
  }
  mvwprintw(infopole, y, x, "%c", '*');
  for (int i = 2; i < COUNTCOORDINATE; i++) {
    //  wclrtoeol(infopole);
    // mvwprintw(infopole, y+tetris.next[i][1], 1, "%c   ", ' ');
    mvwprintw(infopole, y + tetris.next[i][1], x + tetris.next[i][0], "%c",
              '*');
  }
  return 0;
}

int infoprint(WINDOW *infopole, GameInfo_t tetris, char *name) {
  // wclear(infopole);
  box(infopole, 0, 0);
  // clear();
  // wrefresh(infopole);
  nfigprint(infopole, tetris);

  mvwprintw(infopole, 7, 1, "%s", "score");
  mvwprintw(infopole, 8, 2, "%d", tetris.score);
  mvwprintw(infopole, 10, 1, "%s", "username");
  mvwprintw(infopole, 11, 2, "%s", name);
  mvwprintw(infopole, 13, 1, "%s", "highScor");
  mvwprintw(infopole, 14, 3, "%d", tetris.high_score);
  mvwprintw(infopole, 5, 1, "%s", "LEVEL");
  mvwprintw(infopole, 6, 3, "%d", tetris.level);
  wrefresh(infopole);
  return 0;
}

// енто чисто отрисовка
int fieldprint(WINDOW *board, GameInfo_t tetris) {
  wmove(board, 0, 0);
  for (int i = 0; i < MAXROWS;
       i++) {  // первая печать  поля //gjlhfpevtdftncz x,y
    for (int j = 0; j < MAXCOLS; j++) {
      // printw("%c%c", temp_field[i][j], temp_field[i][j]);
      switch (tetris.field[i][j]) {
        case '.':  // Пример: символ 'X' печатается красным
          wattron(board, COLOR_PAIR(1));
          wprintw(board, "%c%c", tetris.field[i][j], tetris.field[i][j]);
          wattroff(board, COLOR_PAIR(1));
          break;
        case 'I':  // Пример: символ 'O' печатается зеленым
          wattron(board, COLOR_PAIR(2));
          wprintw(board, "%c%c", tetris.field[i][j], tetris.field[i][j]);
          wattroff(board, COLOR_PAIR(2));
          break;
        default:  // Другие символы печатаются желтым
          wattron(board, COLOR_PAIR(3));
          wprintw(board, "%c%c", tetris.field[i][j], tetris.field[i][j]);
          wattroff(board, COLOR_PAIR(3));
          break;
      }
    }
  }
  wrefresh(board);
  return 0;
}

void drawUI(WINDOW **board, WINDOW **infopole) {
    initscr();
    timeout(1);
    curs_set(0);
    keypad(stdscr, true);
    noecho();

    // Создаем игровое поле
    *board = newwin(20, 20, 0, 0);
    box(*board, 0, 0);
    mvwaddstr(*board, 2, 3, "Hello, enter");
    mvwaddstr(*board, 3, 3, "your username");
    mvwaddstr(*board, 6, 1, "Pss, the SQUARE ");
    mvwaddstr(*board, 7, 3, " ...rotates... ");
    wrefresh(*board);

    // Создаем информационное поле
    *infopole = newwin(20, 13, 0, 21);
    box(*infopole, 0, 0);
    wrefresh(*infopole);

    // Цвета
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
}

int gameprint(WINDOW *board,WINDOW *infopole, GameInfo_t tetris, char *name ){
  fieldprint(board, tetris);
  infoprint(infopole, tetris, name);
  // refresh();
  return 0;
}