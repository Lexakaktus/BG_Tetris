#include "mozg.h"

void Figuring(int** figure, int Fdonor[][2]) {
  for (int k = 0; k < MAXFIGURE; k++) {
    figure[k][0] = Fdonor[k][0];
    figure[k][1] = Fdonor[k][1];
  }
}

int curtsy(int** Figure, int i) {
  Figure[0][1] += i;
  return 0;
}

void zeroing_temp(int** Field) {
  for (int i = 0; i < MAXROWS; i++) {
    for (int j = 0; j < MAXCOLS; j++) {
      Field[i][j] = '.';
    }
  }
}

// не используется можно удалять 
int sumAhalay(int** Field, int** Figure) { 
  for (int k = 4; k > 0; k--) {
    Field[Figure[0][0] + Figure[k][1]][Figure[0][1] + Figure[k][0]] = 'I';
  }
  return 0;
}

void sumField(int** Field, int** FieldTwo) {
  for (int i = 0; i < MAXROWS; i++) {
    for (int j = 0; j < MAXCOLS; j++) {
      FieldTwo[i][j] = Field[i][j];
    }
  }
}


int sumFigure(int** Field, int** Figure) {
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

int subFigure(int** Field, int** Figure) {
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
        // else if (Field[new_y][new_x] != '.') {  
        //     clop = 1;
        // }
    }

    // Если не было столкновений и выхода за границы, обновляем поле
    for (int k = 4; k > 0 && !clop; k--) {
        int new_x = Figure[0][0] + Figure[k][0];  // Новая координата по x
        int new_y = Figure[0][1] + Figure[k][1];  // Новая координата по y
        Field[new_y][new_x] = '.';  // Устанавливаем фигуру на поле
    }

    return clop;  // Возвращаем флаг столкновения
}

int moveCols(int** Field,int** Figure, int i) { ///перемещение по горизонтали 
int clop = 0;
for (int k = MAXFIGURE-1; k > 0 && !clop; k--) {
            int new_x = Figure[k][0] + Figure[0][0]; // Новая позиция по горизонтали
      if (new_x <= 0 || new_x >= MAXCOLS-1 || Field[Figure[0][1]+Figure[k][1]][new_x] != '.') {

          clop = new_x <= 0? 3:new_x >= MAXCOLS-1? 1: 2; // Останавливаем сдвиг, если фигура выходит за пределы
          // break;
    // clop = 1;
  }}
  // if (clop ==2){

  // }    
  if ((clop==3&&i>0)||(clop==1&&i<0)||(clop==0)){
Figure[0][0] +=i;}
return clop;

}

int rotateCols(int** Field,int** Figure, int i) { ///поворот, убрать и
int clop = 0;
for (int k = 4; k > 0 && !clop; k--) {
  // if ((Figure[0][0] + Figure[k][1] >= MAXROWS /*? ||*/ ///тут что-то не так
  //     /* Figure[1][0] + Figure[1][k] < 0) ?*/ )
  //     || Field[(Figure[0][0] + -1*Figure[k][1])][Figure[0][1] + Figure[k][0]] != /*???*/
  //            '.') {
  //   clop = 1;
  // }}

      if ((Figure[0][0] + Figure[k][0] >= MAXROWS /*? ||*/ ///тут что-то не так
  /* Figure[1][0] + Figure[1][k] < 0) ?*/ )
    || Field[(Figure[0][0] + -1*Figure[k][1])][Figure[0][1] + Figure[k][0]] != /*???*/
          '.') {
    clop = 1;
    } 
    // && !clop && Field[(Figure[0][0] + -1*Figure[k][1])][Figure[0][1] + Figure[k][0]] != '.'
  while (Figure[0][0] - Figure[k][1] >= MAXCOLS && !clop) {
    // moveCols( Field, Figure, 1);
    Figure[0][0]-=1;
  }
  while (Figure[0][0] - Figure[k][1] < 0 && !clop) {
    Figure[0][0]+=1;
    // moveCols( Field, Figure, -1);
  }

}
for (int k = 4; k > 0 && !clop; k--) {
      int tempx=Figure[k][0];
Figure[k][0] =-Figure[k][1];
Figure[k][1]=tempx;
}
return 0;

}

int stringDel(int** Field){
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
    }}
    // printw("\n");
  }
}


UserAction_t Uzvering(UserAction_t action ){
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
  fp = fopen(name, "r+"); //добавить проверок на всякое
  fgets(score, 100, fp);
  int fs=atoi(score);
  if (fs>=info->high_score){
    info->high_score=fs;
  } 
}
