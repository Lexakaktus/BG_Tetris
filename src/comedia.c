
#include <ncurses.h>
#include <string.h> 
#include<unistd.h>
#include"mozg.h"


#include <stdlib.h>
int main(void) {

  initscr();
  timeout(300);
  noecho();
  keypad(stdscr, true);
 WINDOW* board = newwin(20, 20, 0, 0);
  refresh();
  box(board, 0, 0);
  wrefresh(board);
  mvwaddstr(board, 8, 3, "PRESS");
  mvwaddstr(board, 10, 3, "ENTER");
      // wattroff(board, COLOR_PAIR(COLOR_WORDS));
  wrefresh(board);
 WINDOW* infopole = newwin(20, 10, 0, 21);
  refresh();
  box(infopole, 0, 0);
  wrefresh(infopole);
        mvwaddstr(infopole, 8, 3, "SS");
      mvwaddstr(infopole, 10, 3, "ER");
        // wattroff(infopole, COLOR_PAIR(COLOR_WORDS));
  wrefresh(infopole);
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);    // Цветовая пара 1: красный
  init_pair(2, COLOR_GREEN, COLOR_BLACK);  // Цветовая пара 2: зеленый
  init_pair(3, COLOR_YELLOW, COLOR_BLACK); // Цветовая пара 3: желтый




  srand(time(NULL));
  int random = rand() % COUNTFIGURE;
  UserAction_t UserInput;
  GameInfo_t tetris;
  int figure_home[COUNTFIGURE][COUNTCOORDINATE][2] /*{x,y}*/ = {
      {{5, 0}, {0, 0}, {1, 0}, {-1, 0}, {1, 1}},//   -.
      {{5, 1}, {0, 0}, {0, 1}, {0, 2}, {0, -1}}, // |  I 
      {{5, 0}, {0, 0}, {0, 1}, {1, 0}, {-1, 0}},// .|.
      {{5, 0}, {0, 0}, {0, 1}, {1, 1}, {1, 0}},/// ::
      {{5, 0}, {0, 0}, {-1, 0}, {-1, 1}, {1, 0}}, // .-
      {{5, 0}, {0, 0}, {0, 1}, {1, 1}, {-1, 0}},//Z
      {{5, 0}, {0, 0}, {0, 1}, {-1, 1}, {1, 0}} //!Z
      };
  tetris.figure = (int **)malloc(COUNTCOORDINATE * sizeof(int *));
  for (int i = 0; i < COUNTCOORDINATE; i++) {
    tetris.figure[i] = (int *)malloc(COUNTDIMENSION * sizeof(int));
  }

  tetris.next = (int **)malloc(COUNTCOORDINATE * sizeof(int *));
  for (int i = 0; i < COUNTCOORDINATE; i++) {
    tetris.next[i] = (int *)malloc(COUNTDIMENSION * sizeof(int));
  }

  Figuring(tetris.figure, figure_home[random]);
  random = rand() % COUNTFIGURE;
  Figuring(tetris.next, figure_home[random]);

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





UserAction_t action = Start;
// fsm_t fsm=Start;
     char* score= (char*)calloc(10, sizeof(char));
     char* name= (char*)calloc(10, sizeof(char));
     scanf("%s", name);
     fileScore(name, score, &tetris);
    while (action!=Terminate){


    int xmax=0;
    refresh();

    subFigure(tetris.field, tetris.figure);
    
   if (xmax=FigureDown2(tetris.field,tetris.figure)==1) {
      sumFigure(tetris.field, tetris.figure);
      stringDel(tetris.field);
      Figuring(tetris.figure, figure_home[random]);
      random = rand() % 4;
      Figuring(tetris.next, figure_home[random]);
    } else if (xmax==0) {
      subFigure(tetris.field, tetris.figure);
    }
    curtsy2(tetris.field,tetris.figure, 1);
    if (action==Left){
      xmax=moveCols2(tetris.field,tetris.figure, -1);
    } else if (action==Right){
      xmax=moveCols2(tetris.field,tetris.figure, 1);
    }else if (action==Action){
      xmax=rotateCols2(tetris.field,tetris.figure);
    }
    sumFigure(tetris.field, tetris.figure);
    fieldprint(board, tetris );

   action=Uzvering(action);
  infoprint(infopole,tetris,  name );
    //  mvwprintw(infopole, 10,1, "%s","username");
    //  mvwprintw(infopole, 11,2, "%s",name);
    //  mvwprintw(infopole, 13,1, "%s","highScor");
    //  mvwprintw(infopole, 14,3, "%03d",tetris.high_score);
    //  wrefresh(infopole);
     refresh();
    }
// // getch();
// sleep(10);
    endwin();
  return 0;
}

 