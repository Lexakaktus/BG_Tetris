#include <ncurses.h>
#include <string.h> 
#include "mozg.h"

int main(void){
  initscr();
  // int ** figure = (int **)malloc(5 * sizeof(int *));
  // for (int i = 0; i < 5; i++) {
  //   figure[i] = (int *)malloc(2 * sizeof(int));
  //   for (int j = 0; j < 2; j++) {
  //   figure[i][j] = '1';
  // }
  // }
  //     figure[0][0]=5;
      
int figure[5][2] = {{5,0},
          {0,0},
          {1,0},
          {2,0},
          {3,0}};

    UserAction_t UserInput;
    GameInfo_t tetris;
  tetris.field = (int **)malloc(20 * sizeof(int *));
  for (int i = 0; i < 20; i++) {
    tetris.field[i] = (int *)malloc(10 * sizeof(int));
    for (int j = 0; j < 10; j++) {
    tetris.field[i][j] = '.';
  }
  }

   int ** temp_field = (int **)malloc(20 * sizeof(int *));
  for (int i = 0; i < 20; i++) {
    temp_field[i] = (int *)malloc(10 * sizeof(int));
    for (int j = 0; j < 10; j++) {
    temp_field[i][j] = '.'; //=46
  }
  }



for (int i=0; i<MAXROWS;i++){
    for (int j=0;j<MAXCOLS;j++){
        printw("%c%c", temp_field[i][j],temp_field[i][j]);        
    }
    printw("\n");
}

refresh(); 
getch();
clear();
 for (int i=0; i<MAXROWS;i++){
    for (int j=0;j<MAXCOLS;j++){
        printw("%c%c", temp_field[i][j],temp_field[i][j]);
    }
    printw("\n");
}
getch();
clear();
sumFigure(temp_field, figure);
 for (int i=0; i<MAXROWS;i++){
    for (int j=0;j<MAXCOLS;j++){
        printw("%c%c", temp_field[i][j],temp_field[i][j]);
    }
    printw("\n");
}
refresh(); 
getch();
clear();
endwin();
    return 0;
}


void sumField(int ** Field, int ** FieldTwo ){
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
    Field[i][j] = Field[i][j];
  }
  }
}

int sumFigure(int ** Field, int Figure[][2]){ //оптимизировать эту кашу!!!!
  int clop=0;
  for (int i=0;i<MAXROWS&&!clop ;i++){ //Figure[0][0]-1 или -2
  for (int j=0; j<MAXCOLS&&!clop; j++){
    for(int k=0;k<MAXFIGURE&&!clop; k++){
      if (Field[Figure[0][0]+Figure[1][0]][Figure[0][1]+Figure[k][1]]!='.'){
        clop=1;
      } else Field[Figure[0][0]+Figure[k][1]][Figure[0][1]+Figure[k][0]]='t';
    }
  }}
  return clop;
}