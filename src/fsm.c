
#include <ncurses.h>
#include <string.h> 
#include<unistd.h>
#include"mozg.h"


#include <stdlib.h>
int main(void) {

  initscr();
  timeout(300);
  noecho() ;
  keypad(stdscr, true);
WINDOW* board = newwin(20, 10, 0, 0);
  refresh();
  box(board, 0, 0);
  wrefresh(board);
        mvwaddstr(board, 8, 3, "PRESS");
      mvwaddstr(board, 10, 3, "ENTER");
        // wattroff(board, COLOR_PAIR(COLOR_WORDS));
  wrefresh(board);

  start_color();
init_pair(1, COLOR_RED, COLOR_BLACK);    // Цветовая пара 1: красный
init_pair(2, COLOR_GREEN, COLOR_BLACK);  // Цветовая пара 2: зеленый
init_pair(3, COLOR_YELLOW, COLOR_BLACK); // Цветовая пара 3: желтый




  srand(time(NULL));
  int random = rand() % COUNTFIGURE;
  UserAction_t UserInput;
  GameInfo_t tetris;
  int figure_home[COUNTFIGURE][MAXFIGURE][2] /*{x,y}*/ = {
      {{5, 0}, {0, 0}, {1, 0}, {-1, 0}, {1, 1}},//   -.
      {{5, 1}, {0, 0}, {0, 1}, {0, 2}, {0, -1}}, // |  I 
      {{5, 0}, {0, 0}, {0, 1}, {1, 0}, {-1, 0}},// .|.
      {{5, 0}, {0, 0}, {0, 1}, {1, 1}, {1, 0}},/// ::
      {{5, 0}, {0, 0}, {-1, 0}, {-1, 1}, {1, 0}}, // .-
      {{5, 0}, {0, 0}, {0, 1}, {1, 1}, {-1, 0}},//Z
      {{5, 0}, {0, 0}, {0, 1}, {-1, 1}, {1, 0}} //!Z
      };
  int **figure = (int **)malloc(5 * sizeof(int *));
  for (int i = 0; i < 5; i++) {
    figure[i] = (int *)malloc(2 * sizeof(int));
  }

  int **next = (int **)malloc(5 * sizeof(int *));
  for (int i = 0; i < 5; i++) {
    next[i] = (int *)malloc(2 * sizeof(int));
  }

  Figuring(figure, figure_home[random]);
  random = rand() % COUNTFIGURE;
  Figuring(next, figure_home[random]);

  tetris.field =
      (int **)malloc(MAXROWS * sizeof(int *));  //создание постоянного поля
  for (int i = 0; i < MAXROWS; i++) {
    tetris.field[i] = (int *)malloc(MAXCOLS * sizeof(int));
    for (int j = 0; j < MAXCOLS; j++) {
      tetris.field[i][j] = '.';
    }
  }

  int **temp_field =
      (int **)malloc(MAXROWS * sizeof(int *));  //создание временного поля
  for (int i = 0; i < MAXROWS; i++) {
    temp_field[i] = (int *)malloc(MAXCOLS * sizeof(int));
    for (int j = 0; j < MAXCOLS; j++) {
      temp_field[i][j] = '.';  //=46 //y,x
    }
  }

//   for (int i = 0; i < MAXROWS; i++) {  // первая печать  поля
//     for (int j = 0; j < MAXCOLS; j++) {
//       printw("%c%c", temp_field[i][j], temp_field[i][j]);
//     }
//     printw("\n");
//   }

UserAction_t action = Start;
    while (action!=Terminate){
    int xmax=0;
    zeroing_temp(temp_field);
    refresh();     
    
     action=Uzvering(action);
    }
// // getch();
// sleep(10);
    endwin();
  return 0;
}

 