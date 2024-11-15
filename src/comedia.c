
#include <ncurses.h>
#include <string.h> 
#include <unistd.h>
#include  "mozg.h"


#include <stdlib.h>
int main(void) {
 // отсюда отрисовка
  initscr();
  timeout(300);
  // noecho();
  keypad(stdscr, true);
 WINDOW* board = newwin(20, 20, 0, 0);
  refresh();
  box(board, 0, 0);
  wrefresh(board);
  mvwaddstr(board, 2, 3, "Hello, enter");
  mvwaddstr(board, 3, 3, "your username");
  mvwaddstr(board, 6, 1, "Pss, the SQUARE ");
  mvwaddstr(board, 7, 3, " ...rotates... ");
  // wattroff(board, COLOR_PAIR(COLOR_WORDS));
  wrefresh(board);
 WINDOW* infopole = newwin(20, 13, 0, 21);
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
  // досюда отрисовка



  srand(time(NULL));
  int random = rand() % COUNTFIGURE;
  UserAction_t UserInput;
  GameInfo_t tetris;
  tetris.score=0;
  tetris.high_score=0;

  tetris.figure = createcopy();
  tetris.next = createcopy();
  Figuring(tetris.figure, random);
  random = rand() % COUNTFIGURE;
  Figuring(tetris.next, random);

  tetris.field =createpole();

UserAction_t action = Start;
// fsm_t fsm=Start;
     char* score= (char*)calloc(10, sizeof(char));
     char* name= (char*)calloc(10, sizeof(char));
     scanf("%s", name);
     fileScore(name, score, &tetris);
     noecho();//отрисовочное
    while (action!=Terminate){


    int xmax=0;
    refresh();//отрисовочное

    subFigure(tetris.field, tetris.figure);
   if (xmax=FigureDown2(tetris.field,tetris.figure)==1) { //проверка на падение фигуры
      sumFigure(tetris.field, tetris.figure);
      if (tetris.figure[0][1]<=1){ //проверка на проигрыш
        action=Terminate;
      }
      scoring(&tetris);//удаление строк и подсчёт очков
      Figuring(tetris.figure, random); 
      random = rand() % 4;
      Figuring(tetris.next,  random);
    } else if (xmax==0) {
      // subFigure(tetris.field, tetris.figure);
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
    // отсюда отрисовка
    fieldprint(board, tetris );
    infoprint(infopole,tetris,  name );
    if (action!=Terminate)
    action=Uzvering(action);
    
     refresh();
    // досюда отрисовка(фронтенд)
    }

    fileScoreinput( name,  &tetris);
// // getch();
// sleep(10);
    endwin();

    printf("%s %d", "you lose\n your score: ", tetris.high_score);
  return 0;
}

 