
#include "mozg.h"
// #include <unistd.h>

int main(void) {
  initscr();
  timeout(300);
  // noecho() 
  // keypad(stdscr, true);

  start_color();
init_pair(1, COLOR_RED, COLOR_YELLOW);    // Цветовая пара 1: красный
init_pair(2, COLOR_GREEN, COLOR_GREEN);  // Цветовая пара 2: зеленый
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

  for (int i = 0; i < MAXROWS; i++) {  // первая печать  поля
    for (int j = 0; j < MAXCOLS; j++) {
      printw("%c%c", temp_field[i][j], temp_field[i][j]);
    }
    printw("\n");
  }
  int a=0;
  while ((a=getch())!='q') {
    // int d=a;
    // while (a=getch()=='p'){
    //   timeout(-1);
    //   ;
    // }
    // timeout(300);
    int xmax=0;
    zeroing_temp(temp_field);
    refresh();
    // getch();
    clear();
    // zeroing_temp(temp_field);
    sumField(tetris.field, temp_field);
    if (a=='a'){
      xmax=moveCols(tetris.field,figure, -1);
    } else if (a=='d'){
      xmax=moveCols(tetris.field,figure, 1);
    }else if (a=='r'){
      xmax=rotateCols(tetris.field,figure, 1);
    }
    if (sumFigure(temp_field, figure)) {
      if (xmax){
        //  if (xmax==3) /*moveCols(tetris.field,figure, 1);*/ figure[0][0]+=1;
        //  if (xmax==1) figure[0][0]-=1; //moveCols(tetris.field,figure, -1);
      } else {
      curtsy(figure, -1);
      sumFigure(tetris.field, figure);
      Figuring(figure, figure_home[random]);
      random = rand() % 4;
      Figuring(next, figure_home[random]);}
    } else {
      curtsy(figure, 1);
    }
    stringDel(tetris.field);
    for (int i = 0; i < MAXROWS;
         i++) {  // первая печать  поля //gjlhfpevtdftncz x,y
      for (int j = 0; j < MAXCOLS; j++) {
        // printw("%c%c", temp_field[i][j], temp_field[i][j]);
                switch (temp_field[i][j]) {
            case '.': // Пример: символ 'X' печатается красным 
                attron(COLOR_PAIR(1));
               printw("%c%c", temp_field[i][j], temp_field[i][j]);
                attroff(COLOR_PAIR(1));
                break;
            case 'I': // Пример: символ 'O' печатается зеленым
                attron(COLOR_PAIR(2));
                printw("%c%c", temp_field[i][j], temp_field[i][j]);
                attroff(COLOR_PAIR(2));
                break;
            default:  // Другие символы печатаются желтым
                attron(COLOR_PAIR(3));
                printw("%c%c", temp_field[i][j], temp_field[i][j]);
                attroff(COLOR_PAIR(3));
                break;
        }
      }
      printw("\n");
    }
  }

  endwin();
  return 0;
}
