#include "mozg.h"

void Figuring(int** figure, int index) { //не изменено
  for (int k = 0; k < COUNTCOORDINATE; k++) {
    figure[k][0] = figure_home[index][k][0];
    figure[k][1] = figure_home[index][k][1];
  }
}

int curtsy2(int** Field, int** Figure, int i) {
    int clop = 0;
    int** tempFigure=createcopy(&tempFigure);
    copyFigure(tempFigure, Figure);

    if (i < 0 || !checkCollision(Field, tempFigure)) {
        tempFigure[0][1] += i;
        clop = checkCollision(Field, tempFigure);
        if (!clop) {
            copyFigure(Figure, tempFigure);
        }
    }
    deletecopy(tempFigure); 

    return clop;
}

void zeroing_temp(int** Field) { //"обнуление" поля
  for (int i = 0; i < MAXROWS; i++) {
    for (int j = 0; j < MAXCOLS; j++) {
      Field[i][j] = '.';
    }
  }
}

// не используется можно удалять 
int sumAhalay(int** Field, int** Figure) { 
  for (int k = 4; k > 0; k--) {
    Field[Figure[0][1] + Figure[k][1]][Figure[0][0] + Figure[k][0]] = '0';
  }
  return 0;
}

void sumField(int** Field, int** FieldTwo) { //складывание полей(можно(?) удалить)
  for (int i = 0; i < MAXROWS; i++) {
    for (int j = 0; j < MAXCOLS; j++) {
      FieldTwo[i][j] = Field[i][j];
    }
  }
}


int sumFigure(int** Field, int** Figure) { //добавление фигуры на полев
    int clop = 0;

    // Проверка на выход за границы поля или столкновение с другой фигурой
    for (int k = 4; k > 0 && !clop; k--) {
        int new_x = Figure[0][0] + Figure[k][0];  // Новая координата по x
        int new_y = Figure[0][1] + Figure[k][1];  // Новая координата по y

        // Проверяем вертикальные границы (y) и горизонтальные (x)
        if (new_y >= MAXROWS || new_y < 0 || new_x >= MAXCOLS || new_x < 0) {
            clop = 1;  // Если фигура выходит за границы, останавливаемся
        } 
        // Проверка на столкновение с уже существующими блоками на поле
        else if (Field[new_y][new_x] != '.') {  
            clop = 1;
        }
    }

    // Если не было столкновений и выхода за границы, обновляем поле
    for (int k = 4; k > 0 && !clop; k--) {
        int new_x = Figure[0][0] + Figure[k][0];  // Новая координата по x
        int new_y = Figure[0][1] + Figure[k][1];  // Новая координата по y
        Field[new_y][new_x] = 'I';  // Устанавливаем фигуру на поле
    }

    return clop;  // Возвращаем флаг столкновения
}

int subFigure(int** Field, int** Figure) { //стирание фигуры с поля ( непроверенное!)
    int clop = 0;


    // Если не было столкновений и выхода за границы, обновляем поле
    for (int k = 4; k > 0 ; k--) {
        int new_x = Figure[0][0] + Figure[k][0];  // Новая координата по x
        int new_y = Figure[0][1] + Figure[k][1]; 
        if(!(new_y >= MAXROWS || new_y < 0 || new_x >= MAXCOLS || new_x < 0))
        Field[new_y][new_x] = '.';  // Устанавливаем фигуру на поле
    }

    return clop;  // Возвращаем флаг столкновения//откуда оно здесь?
}

int moveCols(int** Field,int** Figure, int i) { ///перемещение по горизонтали 
int clop = 0;
for (int k = COUNTCOORDINATE-1; k > 0 && !clop; k--) {
            int new_x = Figure[k][0] + Figure[0][0]; // Новая позиция по горизонтали
      if (new_x <= 0 || new_x >= MAXCOLS-1 || Field[Figure[0][1]+Figure[k][1]][new_x] != '.') {

          clop = new_x <= 0? 3:new_x >= MAXCOLS-1? 1: 2; // Останавливаем сдвиг, если фигура выходит за пределы
  }}
  if ((clop==3&&i>0)||(clop==1&&i<0)||(clop==0)){
Figure[0][0] +=i;}
return clop;

}

int rotateCols(int** Field,int** Figure, int i) { ///поворот, убрать и // и? 
  int clop = 0;

  for (int k = 4; k > 0 && !clop; k--) {
        if ((Figure[0][1] + Figure[k][0] >= MAXROWS /*? ||*/ ///тут что-то не так
    /* Figure[1][0] + Figure[1][k] < 0) ?*/ )||((Figure[0][0] + -1*Figure[k][1])>=MAXCOLS||(Figure[0][0] + -1*Figure[k][1])<0)
      || Field[(Figure[0][0] + -1*Figure[k][1])][Figure[0][1] + Figure[k][0]] != /*???*/
            '.') {
      clop = 1;
      } 
  }
  for (int k = 4; k > 0 && !clop; k--) {
        int tempx=Figure[k][0];
  Figure[k][0] =-Figure[k][1];
  Figure[k][1]=tempx;
  }

  
  return clop;
}

int stringDel(int** Field){ //удаляет заполненные строки и возвращает их количество
  int delcounter=0;
  for (int i = 0; i < MAXROWS; i++) { 
  int zerstring=1;
 
    for (int j = 0; j < MAXCOLS; j++) {
     if(Field[i][j]=='.'){
      zerstring=0;
     }
    }
    if (zerstring) {
    for (int n = i; n >0 ;n--) { 
    for (int k = 0; k < MAXCOLS; k++) {
      Field[n][k]=Field[n-1][k];
    }
    }
    for (int k = 0; k < MAXCOLS; k++) {
      Field[0][k]='.';
    }
    delcounter++;
    }
    // printw("\n");
  }
  return delcounter;
}


UserAction_t Uzvering(UserAction_t action ){ //переименовать 
  UserAction_t push;//=action;
  int a = getch();
  switch(a){
  case 'a':
    push = Left;
    break;
  case KEY_LEFT:
    push = Left;
    break;
  case 'd':
    push = Right;
    break;
  case KEY_RIGHT:
    push = Right;
    break;
  case 'p':
    push=Pause;
    break;
  case 'q':
    push=Terminate;
    break;  
  case 27:      //escape
    push=Terminate;
    break;  
  case '\n':
    push = Action;
    break;    
  case 's':
    push = Down;
    break;   
  case KEY_DOWN:
    push = Down;
    break;       
  case '\\':
    push = Start;
    break;
  case 'w':
    push = Up;
    break;  
  case KEY_UP:
    push = Up;
    break;   
  default:
    push=Start;
    break;
  }
  return push;
}

//возможно убрать score внутрь функции
int fileScore(char* name, char* score,  GameInfo_t* info){ //добавить сразу замену счёта в файле или игре(смотря что больше) и в конце закрывать файл
  FILE *fp;
  strcat(name, ".txt");

  // if ((fp = fopen("test", "w"))==NULL) {
  // printf("Cannot open file.\n");
  // }
  if ((fp = fopen(name, "r+"))==NULL){
    fp = fopen(name, "w+");
  } //добавить проверок на всякое
  fgets(score, 100, fp);
  int fs=atoi(score);
  if (fs>=info->high_score){
    info->high_score=fs;
  } 
  return 0;
}


void initg(){ //не работает
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
}

int FigureDown(int** Field, int** Figure){
  int clop=0;
   for (int k = 4; k > 0 && !clop; k--){     
        int new_x = Figure[0][0] + Figure[k][0];  // Новая координата по x
        int new_y = Figure[0][1] + Figure[k][1];  // Новая координата по y
        if (new_y==MAXROWS-1) clop=1;
        if (Field[new_y][new_x]!='.') clop =2;
      }
      return clop;
}

int FigureDown2(int** Field, int** Figure){
  int clop=0;
   for (int k = 4; k > 0 && !clop; k--){     
        int new_x = Figure[0][0] + Figure[k][0];  // Новая координата по x
        int new_y = Figure[0][1] + Figure[k][1]+1;  // Новая координата по y
        if (new_y==MAXROWS||Field[new_y][new_x] != '.') clop=1;//!!!!
      }
      return clop;
}



void copyFigure(int** dest, int** src) {
    for (int k = 0; k < COUNTCOORDINATE; k++) {
        dest[k][0] = src[k][0];
        dest[k][1] = src[k][1];
    }
}

int checkCollision(int** Field, int** Figure) {
  int clop=0;
    for (int k = 4; k > 0&&!clop; k--) {
        int new_x = Figure[0][0] + Figure[k][0];  // Новая координата по x
        int new_y = Figure[0][1] + Figure[k][1];  // Новая координата по y

        // Проверка на выход за границы или на столкновение с другими фигурами
        if (new_y >= MAXROWS || new_y < 0 || new_x >= MAXCOLS || new_x < 0 || Field[new_y][new_x] != '.') {
            clop=1;  // Столкновение произошло
        }
    }
    return clop;  
}

int** createcopy(){
    int** tempFigure = malloc(COUNTCOORDINATE * sizeof(int*));
    for (int k = 0; k < COUNTCOORDINATE; k++) {
        tempFigure[k] = malloc(2 * sizeof(int));
    }
    return tempFigure;
}
int** createpole(){
    int** tempFigure =
      (int **)malloc(MAXROWS * sizeof(int *));  //создание постоянного поля
  for (int i = 0; i < MAXROWS; i++) {
    tempFigure[i] = (int *)malloc(MAXCOLS * sizeof(int));
    for (int j = 0; j < MAXCOLS; j++) {
      tempFigure[i][j] = '.';
    }
  }
  return tempFigure;
}
int deletecopy(int**copy){
    for (int k = 0; k < COUNTCOORDINATE; k++) {
        free(copy[k]);
    }
    free(copy);
}

int rotateCols2(int** Field, int** Figure) {
    int clop = 0;
    int** tempFigure = createcopy();
    copyFigure(tempFigure, Figure);

    for (int k = 1; k < COUNTCOORDINATE; k++) {
        int tempx = tempFigure[k][0];
        tempFigure[k][0] = -tempFigure[k][1];
        tempFigure[k][1] = tempx;
    }

    clop = checkCollision(Field, tempFigure);
    if (!clop) {
        copyFigure(Figure, tempFigure);
    }

    deletecopy(tempFigure);
    return clop;
}

int moveCols2(int** Field, int** Figure, int i) {
    int clop = 0;
    int** tempFigure = createcopy();
    copyFigure(tempFigure, Figure);

    tempFigure[0][0] += i;
    clop = checkCollision(Field, tempFigure);
    if (!clop) {
        copyFigure(Figure, tempFigure);
    }

    deletecopy(tempFigure);
    return clop;
}

int scoring(GameInfo_t* tetris){
  int a=stringDel(tetris->field);
  switch (a) {
    case 1:
    tetris->score+=100;
    break;
    case 2:
    tetris->score+=300;
    break;
    case 3:
    tetris->score+=700;
    break;
    case 4:
    tetris->score+=1500;
    break;
    default:
    break;
  }
  if (tetris->score>tetris->high_score){
    tetris->high_score=tetris->score;
  }
  return 0;
}

//score deletai
int fileScoreinput(char* name,  GameInfo_t* info){ //добавить сразу замену счёта в файле или игре(смотря что больше) и в конце закрывать файл
  FILE *fp;
  // strcat(name, ".txt");
  
  if ((fp = fopen(name, "r+"))==NULL){
    fp = fopen(name, "w+");
  } //добавить проверок на всякое
  // fgets(score, 100, fp);
  int fs;//=atoi(score);
  // if (fs<info->high_score){
  //   fs=info->high_score;
  // } 
  // itoa(info->high_score, score,10);
  // fputs(score, fp);
  fprintf(fp, "%d",info->high_score );
   fclose (fp);
  return 0;
}














//енто чисто отрисовка
int fieldprint(WINDOW* board, GameInfo_t tetris ){
      wmove(board, 0, 0);
    for (int i = 0; i < MAXROWS;
         i++) {  // первая печать  поля //gjlhfpevtdftncz x,y
      for (int j = 0; j < MAXCOLS; j++) {
        // printw("%c%c", temp_field[i][j], temp_field[i][j]);
                switch (tetris.field[i][j]) {
            case '.': // Пример: символ 'X' печатается красным 
                wattron(board,COLOR_PAIR(1));
                wprintw(board,"%c%c", tetris.field[i][j], tetris.field[i][j]);
                wattroff(board,COLOR_PAIR(1));
                break;
            case 'I': // Пример: символ 'O' печатается зеленым
                wattron(board,COLOR_PAIR(2));
                wprintw(board,"%c%c", tetris.field[i][j], tetris.field[i][j]);
                wattroff(board,COLOR_PAIR(2));
                break;
            default:  // Другие символы печатаются желтым
                wattron(board,COLOR_PAIR(3));
                wprintw(board,"%c%c", tetris.field[i][j], tetris.field[i][j]);
                wattroff(board,COLOR_PAIR(3));
                break;
        }
      }
    }
   wrefresh(board);
}

int infoprint(WINDOW* infopole, GameInfo_t tetris, char* name ){
     mvwprintw(infopole, 7,1, "%s","score");
     mvwprintw(infopole, 8,2, "%d",tetris.score);
     mvwprintw(infopole, 10,1, "%s","username");
     mvwprintw(infopole, 11,2, "%s",name);
     mvwprintw(infopole, 13,1, "%s","highScor");
     mvwprintw(infopole, 14,3, "%d",tetris.high_score);
     wrefresh(infopole);
}