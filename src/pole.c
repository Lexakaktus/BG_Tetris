#include <ncurses.h>
#include <string.h> 
#include "mozg.h"

int main(void){
  initscr();
// //       int row, col;
// //   getmaxyx(stdscr, row, col)
//   move(getmaxy(stdscr)/ 2, getmaxx(stdscr)/ 2);
// //  WINDOW *mwindow;
// //  mwindow=newwin(20, 10, 0, 0);
//  printw("%c ", tetris.field[i][j]);
//  refresh(); // обновить экран
//  move(getmaxy(stdscr)/ 4, getmaxx(stdscr)/ 4);
//  printw("%s", "gdjdh");
//  refresh(); 
//  getch();
    UserAction_t UserInput;
    GameInfo_t tetris;
  tetris.field = (int **)malloc(20 * sizeof(int *));
  for (int i = 0; i < 20; i++) {
    tetris.field[i] = (int *)malloc(10 * sizeof(int));
    for (int j = 0; j < 10; j++) {
    tetris.field[i][j] = '.';
  }
  }
for (int i=0; i<MAXROWS;i++){
    for (int j=0;j<MAXCOLS;j++){
        printw("%c ", tetris.field[i][j]);
        
    }
    printw("\n");
}

 refresh(); 
  getch();
clear();
//  getch();
 for (int i=0; i<MAXROWS;i++){
    for (int j=0;j<MAXCOLS;j++){
        printw("%cе", tetris.field[i][j]);
        
    }
    printw("\n");
}
getch();
endwin();
    return 0;
}