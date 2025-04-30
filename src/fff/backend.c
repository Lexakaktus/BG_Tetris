#include "backend.h"


void Figuring(int **figure, int index) {  // не изменено
  for (int k = 0; k < COUNTCOORDINATE; k++) {
    figure[k][0] = figure_home[index][k][0];
    figure[k][1] = figure_home[index][k][1];
  }
}

int curtsy2(int **Field, int **Figure, int i) {//бэк спуск фигуры
  int clop = 0;
  int **tempFigure = createcopy();
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

void zeroing_temp(int **Field) {  //"обнуление" поля //использовать в клине (gameover)
  for (int i = 0; i < MAXROWS; i++) {
    for (int j = 0; j < MAXCOLS; j++) {
      Field[i][j] = '.';
    }
  }
}


int sumFigure(int **Field, int **Figure) {  // добавление фигуры на полев
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

int subFigure(int **Field,
              int **Figure) {  // стирание фигуры с поля 
  int clop = 0;
  // Если не было столкновений и выхода за границы, обновляем поле
  for (int k = 4; k > 0; k--) {
    int new_x = Figure[0][0] + Figure[k][0];  // Новая координата по x
    int new_y = Figure[0][1] + Figure[k][1];
    if (!(new_y >= MAXROWS || new_y < 0 || new_x >= MAXCOLS || new_x < 0))
      Field[new_y][new_x] = '.';  // возвращаем отсутствие фигуры
  }

  return clop;  // Возвращаем флаг столкновения//откуда оно здесь?//начать следить за клопом
}


int stringDel(
    int **Field) {  // удаляет заполненные строки и возвращает их количество
  int delcounter = 0;
  for (int i = 0; i < MAXROWS; i++) {
    int zerstring = 1;

    for (int j = 0; j < MAXCOLS; j++) {
      if (Field[i][j] == '.') {
        zerstring = 0;
      }
    }
    if (zerstring) {
      for (int n = i; n > 0; n--) {
        for (int k = 0; k < MAXCOLS; k++) {
          Field[n][k] = Field[n - 1][k];
        }
      }
      for (int k = 0; k < MAXCOLS; k++) {
        Field[0][k] = '.';
      }
      delcounter++;
    }
    // printw("\n");
  }
  return delcounter;
}



// возможно убрать score внутрь функции
int fileScore(
    char *name, char *score,
    GameInfo_t *info) {  // добавить сразу замену счёта в файле или игре(смотря
                         // что больше) и в конце закрывать файл
  FILE *fp;
  strcat(name, ".txt");

  // if ((fp = fopen("test", "w"))==NULL) {
  // printf("Cannot open file.\n");
  // }
  if ((fp = fopen(name, "r+")) == NULL) {
    fp = fopen(name, "w+");
  }  // добавить проверок на всякое
  fgets(score, 100, fp);
  int fs = atoi(score);
  if (fs >= info->high_score) {
    info->high_score = fs;
  }
  get_set_info(info, PUSH);
  fclose(fp);
  return 0;
}


int FigureDown2(int **Field, int **Figure) {
  int clop = 0;
  for (int k = 4; k > 0 && !clop; k--) {
    int new_x = Figure[0][0] + Figure[k][0];  // Новая координата по x
    int new_y = Figure[0][1] + Figure[k][1] + 1;  // Новая координата по y
    if (new_y == MAXROWS || Field[new_y][new_x] != '.') clop = 1;  //!!!!
  }
  return clop;
}

void copyFigure(int **dest, int **src) {
  for (int k = 0; k < COUNTCOORDINATE; k++) {
    dest[k][0] = src[k][0];
    dest[k][1] = src[k][1];
  }
}

int checkCollision(int **Field, int **Figure) {
  int clop = 0;
  for (int k = 4; k > 0 && !clop; k--) {
    int new_x = Figure[0][0] + Figure[k][0];  // Новая координата по x
    int new_y = Figure[0][1] + Figure[k][1];  // Новая координата по y

    // Проверка на выход за границы или на столкновение с другими фигурами
    if (new_y >= MAXROWS || new_y < 0 || new_x >= MAXCOLS || new_x < 0 ||
        Field[new_y][new_x] != '.') {
      clop = 1;  // Столкновение произошло
    }
  }
  return clop;
}

int **createcopy() {
  int **tempFigure = malloc(COUNTCOORDINATE * sizeof(int *));
  for (int k = 0; k < COUNTCOORDINATE; k++) {
    tempFigure[k] = malloc(2 * sizeof(int));
  }
  return tempFigure;
}
int **createpole() {//а очищается??
  int **tempFigure =
      (int **)malloc(MAXROWS * sizeof(int *));  // создание постоянного поля
  for (int i = 0; i < MAXROWS; i++) {
    tempFigure[i] = (int *)malloc(MAXCOLS * sizeof(int));
    for (int j = 0; j < MAXCOLS; j++) {
      tempFigure[i][j] = '.';
    }
  } //вызывать здесь zeroing_temp
  return tempFigure;
}
int deletecopy(int **copy) {
  for (int k = 0; k < COUNTCOORDINATE; k++) {
    free(copy[k]);
  }
  free(copy);
  return 0;
}

int rotateCols2(int **Field, int **Figure) {
  int clop = 0;
  int **tempFigure = createcopy();
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

int moveCols2(int **Field, int **Figure, int i) {
  int clop = 0;
  int **tempFigure = createcopy();
  copyFigure(tempFigure, Figure);

  tempFigure[0][0] += i;
  clop = checkCollision(Field, tempFigure);
  if (!clop) {
    copyFigure(Figure, tempFigure);
  }

  deletecopy(tempFigure);
  return clop;
}

int scoring(GameInfo_t *tetris) {
  int a = stringDel(tetris->field);
  switch (a) {
    case 1:
      tetris->score += 100;
      break;
    case 2:
      tetris->score += 300;
      break;
    case 3:
      tetris->score += 700;
      break;
    case 4:
      tetris->score += 1500;
      break;
    default:
      break;
  }
  if (tetris->score > tetris->high_score) {
    tetris->high_score = tetris->score;
  }
  get_set_info(tetris, PUSH);
  return 0;
}

// score deletai
int fileScoreinput(
    char *name,
    GameInfo_t *info) {  // добавить сразу замену счёта в файле или игре(смотря
                         // что больше) и в конце закрывать файл
  FILE *fp;
  // strcat(name, ".txt");

  if ((fp = fopen(name, "r+")) == NULL) {
    fp = fopen(name, "w+");
  }  // добавить проверок на всякое
  // fgets(score, 100, fp);
  // int fs=atoi(score);
  if (info->high_score<=info->score){
    fprintf(fp, "%d", info->high_score);
  }
  // itoa(info->high_score, info->score,10);
  // fputs(info->score, fp);
  
  fclose(fp);
  return 0;
}


int ** updatefigure(){
  static int** figure;
  static int flag=1;
  if (flag){
    figure = createcopy();
    flag=0;
  }
  // figure = createcopy();
  return figure;
}


//flag==0->остаётся инфо, 1 инфо меняется
// GameInfo_t update(GameInfo_t * info, int flag){ 
//   static GameInfo_t tetris={0};
//   if (flag){
//     *info=tetris;
//   } else {
//     tetris = *info;
//   }
// }

void zeroing_all(GameInfo_t* x ){
  zeroing_temp(x->field);
  x->score=0;
  x->speed=0;
  x->level=0;
  x->pause=0;
  Figuring(x->next, rand()%COUNTFIGURE);
  get_set_info(x, PUSH);
  
}



