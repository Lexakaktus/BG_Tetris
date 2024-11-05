
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
  int figure_home[COUNTFIGURE][MAXFIGURE][2] /*{x,y}*/ = {
      {{5, 0}, {0, 0}, {1, 0}, {-1, 0}, {1, 1}},//   -.
      {{5, 1}, {0, 0}, {0, 1}, {0, 2}, {0, -1}}, // |  I 
      {{5, 0}, {0, 0}, {0, 1}, {1, 0}, {-1, 0}},// .|.
      {{5, 0}, {0, 0}, {0, 1}, {1, 1}, {1, 0}},/// ::
      {{5, 0}, {0, 0}, {-1, 0}, {-1, 1}, {1, 0}}, // .-
      {{5, 0}, {0, 0}, {0, 1}, {1, 1}, {-1, 0}},//Z
      {{5, 0}, {0, 0}, {0, 1}, {-1, 1}, {1, 0}} //!Z
      };
  tetris.figure = (int **)malloc(5 * sizeof(int *));
  for (int i = 0; i < 5; i++) {
    tetris.figure[i] = (int *)malloc(2 * sizeof(int));
  }

  tetris.next = (int **)malloc(5 * sizeof(int *));
  for (int i = 0; i < 5; i++) {
    tetris.next[i] = (int *)malloc(2 * sizeof(int));
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
    zeroing_temp(temp_field);
    refresh();
    // getch();

    // clear();
    
    // zeroing_temp(temp_field);
    sumField(tetris.field, temp_field);


    if (action==Left){
      xmax=moveCols(tetris.field,tetris.figure, -1);
    } else if (action==Right){
      xmax=moveCols(tetris.field,tetris.figure, 1);
    }else if (action==Action){
      xmax=rotateCols(tetris.field,tetris.figure, 1);
      if (xmax)curtsy(tetris.figure, -1);
    //   if (xmax==2){moveCols(tetris.field,tetris.figure, 1);}
    }
    if (sumFigure(temp_field, tetris.figure)) {
      if (xmax){
        //  if (xmax==3) /*moveCols(tetris.field,figure, 1);*/ figure[0][0]+=1;
        //  if (xmax==1) figure[0][0]-=1; //moveCols(tetris.field,figure, -1);
      } else {
      curtsy(tetris.figure, -1);
      sumFigure(tetris.field, tetris.figure);
      Figuring(tetris.figure, figure_home[random]);
      random = rand() % 4;
      Figuring(tetris.next, figure_home[random]);}
    } else {
      curtsy(tetris.figure, 1);
    }
    stringDel(tetris.field);
    wmove(board, 0, 0);
    for (int i = 0; i < MAXROWS;
         i++) {  // первая печать  поля //gjlhfpevtdftncz x,y
      for (int j = 0; j < MAXCOLS; j++) {
        // printw("%c%c", temp_field[i][j], temp_field[i][j]);
                switch (temp_field[i][j]) {
            case '.': // Пример: символ 'X' печатается красным 
                wattron(board,COLOR_PAIR(1));
               wprintw(board,"%c%c", temp_field[i][j], temp_field[i][j]);
                wattroff(board,COLOR_PAIR(1));
                break;
            case 'I': // Пример: символ 'O' печатается зеленым
                wattron(board,COLOR_PAIR(2));
                wprintw(board,"%c%c", temp_field[i][j], temp_field[i][j]);
                wattroff(board,COLOR_PAIR(2));
                break;
            default:  // Другие символы печатаются желтым
                wattron(board,COLOR_PAIR(3));
                wprintw(board,"%c%c", temp_field[i][j], temp_field[i][j]);
                wattroff(board,COLOR_PAIR(3));
                break;
        }
      }
    //   wprintw(board,"\n");
     
    }
   wrefresh(board);
   action=Uzvering(action);

    //  strcat(name, "score");
    //  mvwprintw(infopole, 15,3, "%d",next[0][0]);
     mvwprintw(infopole, 10,1, "%s","username");
     mvwprintw(infopole, 11,2, "%s",name);
     mvwprintw(infopole, 13,1, "%s","highScor");
     mvwprintw(infopole, 14,3, "%03d",tetris.high_score);
     wrefresh(infopole);
     refresh();
    }
// // getch();
// sleep(10);
    endwin();
  return 0;
}

 