#include "front.h"

UserAction_t Uzvering(UserAction_t action) {  // переименовать //и отправить на контроллер!!!
  UserAction_t push;                          //=action;
  int a = getch();
  if (action != Pause) {
    switch (a) {
      case 'a':
      case KEY_LEFT:
        push = Left;
        break;
      case 'd':
      case KEY_RIGHT:
        push = Right;
        break;
      case 'p':
        push = Pause;
        break;
      case 'q':
        push = Terminate;
        break;
      case 27:  // escape
        push = Terminate;
        break;
      case '\n':
        push = Action;
        break;
      case 's':
      case KEY_DOWN:
        push = Down;
        break;
      case '\\':
        push = Start;
        break;
      case 'w':
      case KEY_UP:
        push = Up;
        break;
      default:
        push = Start;
        break;
    }
  } else if (a != 'p' && a != 'q') {
    push = Pause;
  } else if (a == 'q') {
    push = Terminate;
  } else {
    push = Start;
  }
  return push;
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
}

