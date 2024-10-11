
#include "mozg.h"
// #include <unistd.h>


int main(void){
  initscr();
   timeout(1000);
  // int ** figure = (int **)malloc(5 * sizeof(int *));
  // for (int i = 0; i < 5; i++) {
  //   figure[i] = (int *)malloc(2 * sizeof(int));
  //   for (int j = 0; j < 2; j++) {
  //   figure[i][j] = '1';
  // }
  // }
  //     figure[0][0]=5;
  srand(time(NULL));
int random=rand()%4;
    UserAction_t UserInput;
    GameInfo_t tetris;
int figure_home[6][5][2]/*{y,x}????*/ ={ {{5,0},{0,0},{1,0},{2,0},{2,1}}, {{5,0},{0,0},{0,1},{0,2},{0,3}}, {{5,0},{0,0},{0,1},{1,1},{-1,1}},  {{5,0},{0,0},{0,1},{1,1},{1,0}}};
int ** figure=(int **)malloc(5 * sizeof(int *));
  for (int i = 0; i < 5; i++) {
    figure[i] = (int *)malloc(2 * sizeof(int));}

int ** next=(int **)malloc(5 * sizeof(int *));
  for (int i = 0; i < 5; i++) {
    next[i] = (int *)malloc(2 * sizeof(int));}


Figuring(figure, figure_home[random]);
random=rand()%4;
Figuring(next, figure_home[random]);

  tetris.field = (int **)malloc(20 * sizeof(int *)); //создание постоянного поля
  for (int i = 0; i < 20; i++) {
    tetris.field[i] = (int *)malloc(10 * sizeof(int));
    for (int j = 0; j < 10; j++) {
    tetris.field[i][j] = '.';
  }
  }

   int ** temp_field = (int **)malloc(20 * sizeof(int *)); //создание временного поля
  for (int i = 0; i < 20; i++) {
    temp_field[i] = (int *)malloc(10 * sizeof(int));
    for (int j = 0; j < 10; j++) {
    temp_field[i][j] = '.'; //=46 //y,x
  }
  }

  for (int i=0; i<MAXROWS;i++){ // первая печать  поля
    for (int j=0;j<MAXCOLS;j++){
        printw("%c%c", temp_field[i][j],temp_field[i][j]);        
    }
    printw("\n");
}
while (getch()!='q')
{
zeroing_temp(temp_field);
refresh(); 
// getch();
clear();
  // zeroing_temp(temp_field);
  sumField(tetris.field, temp_field );
  if (sumFigure(temp_field, figure)){
  //   curtsy(figure, -1);
  curtsy(figure, -1);
  sumFigure(tetris.field, figure);
  Figuring(figure, figure_home[random]);
  random=rand()%4;
  Figuring(next, figure_home[random]);
  }
  else {
  curtsy(figure, 1);}
  for (int i=0; i<MAXROWS;i++){ // первая печать  поля //gjlhfpevtdftncz x,y
    for (int j=0;j<MAXCOLS;j++){
        printw("%c%c", temp_field[i][j],temp_field[i][j]);        
    }
    printw("\n");
  }
  // zeroing_temp(temp_field);
// sleep(2.509);


}

endwin();
    return 0;
}



