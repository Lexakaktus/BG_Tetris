#include "../../inc/backend.h"


//mayby rename figurehome https://google.github.io/styleguide/cppguide.html#Constant_Names
static const int figure_home[COUNTFIGURE][COUNTCOORDINATE][2] /*{x,y}*/ = {
    {{5, 0}, {0, 0}, {1, 0}, {-1, 0}, {1, 1}},   //   -.
    {{5, 1}, {0, 0}, {0, 1}, {0, 2}, {0, -1}},   // |  I
    {{5, 0}, {0, 0}, {0, 1}, {1, 0}, {-1, 0}},   // .|.
    {{5, 0}, {0, 0}, {0, 1}, {1, 1}, {1, 0}},    /// ::
    {{5, 0}, {0, 0}, {-1, 0}, {-1, 1}, {1, 0}},  // .-
    {{5, 0}, {0, 0}, {0, 1}, {1, 1}, {-1, 0}},   // Z
    {{5, 0}, {0, 0}, {0, 1}, {-1, 1}, {1, 0}}    //! Z
};


void Figuring(int **figure, int index) {  // не изменено
  for (int k = 0; k < COUNTCOORDINATE; k++) {
    figure[k][0] = figure_home[index][k][0];
    figure[k][1] = figure_home[index][k][1];
  }
}

int Curtsy(int **field, int **figure, int i) {  // бэк спуск фигуры
  int clop = 0;
  int **temp_figure = CreateCopy();
  CopyFigure(temp_figure, figure);
  if (i < 1) {
    clop = BAD_ARGUMENT;
  }
  if (!CheckCollision(field, temp_figure) && clop == 0) {
    temp_figure[0][1] += i;
    clop = CheckCollision(field, temp_figure);
    if (!clop) {
      CopyFigure(figure, temp_figure);
    }
  }  // else clop=BAD_ARGUMENT;
  DeleteCopy(&temp_figure);

  return clop;
}

//"обнуление" поля //использовать в клине (gameover)
void ZeroingTemp(
    int **field) {  
  for (int i = 0; i < MAXROWS; i++) {
    for (int j = 0; j < MAXCOLS; j++) {
      field[i][j] = '.';
    }
  }
}

 // добавление фигуры на поле
int SumFigure(int **field, int **figure) {
  int clop = 0;

  // Проверка на выход за границы поля или столкновение с другой фигурой
  for (int k = 4; k > 0 && !clop; k--) {
    int new_x = figure[0][0] + figure[k][0];  // Новая координата по x
    int new_y = figure[0][1] + figure[k][1];  // Новая координата по y

    // Проверяем вертикальные границы (y) и горизонтальные (x)
    if (new_y >= MAXROWS || new_y < 0 || new_x >= MAXCOLS || new_x < 0) {
      clop = 1;  // Если фигура выходит за границы, останавливаемся
    }
    // Проверка на столкновение с уже существующими блоками на поле
    else if (field[new_y][new_x] != '.') {
      clop = 1;
    }
  }
  // Если не было столкновений и выхода за границы, обновляем поле
  for (int k = 4; k > 0 && !clop; k--) {
    int new_x = figure[0][0] + figure[k][0];  // Новая координата по x
    int new_y = figure[0][1] + figure[k][1];  // Новая координата по y
    field[new_y][new_x] = 'I';  // Устанавливаем фигуру на поле
  }

  return clop;  // Возвращаем флаг столкновения
}

 // стирание фигуры с поля
int SubFigure(int **field,
              int **figure) { 
  int clop = 0;
  // Если не было столкновений и выхода за границы, обновляем поле
  for (int k = 4; k > 0; k--) {
    int new_x = figure[0][0] + figure[k][0];  // Новая координата по x
    int new_y = figure[0][1] + figure[k][1];
    if (!(new_y >= MAXROWS || new_y < 0 || new_x >= MAXCOLS || new_x < 0))
      field[new_y][new_x] = '.';  // возвращаем отсутствие фигуры
  }

  return clop;  // Возвращаем флаг столкновения//откуда оно здесь?//начать
                // следить за клопом
}

 // удаляет заполненные строки и возвращает их количество
int StringDel(    int **field) { 
  int del_counter = 0;
  for (int i = 0; i < MAXROWS; i++) {
    int zer_string = 1;

    for (int j = 0; j < MAXCOLS; j++) {
      if (field[i][j] == '.') {
        zer_string = 0;
      }
    }
    if (zer_string) {
      for (int n = i; n > 0; n--) {
        for (int k = 0; k < MAXCOLS; k++) {
          field[n][k] = field[n - 1][k];
        }
      }
      for (int k = 0; k < MAXCOLS; k++) {
        field[0][k] = '.';
      }
      del_counter++;
    }
    // printw("\n");
  }
  return del_counter;
}

// возможно убрать score внутрь функции
 // добавить сразу замену счёта в файле или игре(смотря
                         // что больше) и в конце закрывать файл
int FileScore(
    char *name,
    GameInfo_t *info) { 
  char *score = (char *)calloc(10, sizeof(char));
  FILE *fp;
  char filename[64];
  // strcat(name, ".txt");
  snprintf(filename, sizeof(filename), "%s.txt", name);
  if ((fp = fopen(filename, "r+")) == NULL) {
    fp = fopen(filename, "w+");
  }  // добавить проверок на всякое
  fgets(score, 10, fp);
  int fs = atoi(score);
  if (fs >= info->high_score) {
    info->high_score = fs;
  }
  GetSetInfo(info, PUSH);
  free(score);
  fclose(fp);
  return 0;
}

int FigureDown(int **field, int **figure) {
  int clop = 0;
  for (int k = 4; k > 0 && !clop; k--) {
    int new_x = figure[0][0] + figure[k][0];  // Новая координата по x
    int new_y = figure[0][1] + figure[k][1] + 1;  // Новая координата по y
    if (new_y == MAXROWS || field[new_y][new_x] != '.') clop = 1;  //!!!!
  }
  return clop;
}

void CopyFigure(int **dest, int **src) {
  for (int k = 0; k < COUNTCOORDINATE; k++) {
    dest[k][0] = src[k][0];
    dest[k][1] = src[k][1];
  }
}

int CheckCollision(int **field, int **figure) {
  int clop = 0;
  for (int k = 4; k > 0 && !clop; k--) {
    int new_x = figure[0][0] + figure[k][0];  // Новая координата по x
    int new_y = figure[0][1] + figure[k][1];  // Новая координата по y

    // Проверка на выход за границы или на столкновение с другими фигурами
    if (new_y >= MAXROWS || new_y < 0 || new_x >= MAXCOLS || new_x < 0 ||
        field[new_y][new_x] != '.') {
      clop = 1;  // Столкновение произошло
    }
  }
  return clop;
}

//добавить проверку на маллок
int **CreateCopy() {
  int **temp_figure = malloc(COUNTCOORDINATE * sizeof(int *));
  for (int k = 0; k < COUNTCOORDINATE; k++) {
    temp_figure[k] = malloc(2 * sizeof(int));
  }
  return temp_figure;
}


//добавить проверку на маллок
int **CreateField() {  // а очищается??
  int **field =
      (int **)malloc(MAXROWS * sizeof(int *));  // создание постоянного поля
  for (int i = 0; i < MAXROWS; i++) {
    field[i] = (int *)malloc(MAXCOLS * sizeof(int));
    for (int j = 0; j < MAXCOLS; j++) {
      field[i][j] = '.';
    }
  } 
  return field;
}

int DeleteCopy(int ***copy) {
  for (int k = 0; k < COUNTCOORDINATE; k++) {
    free((*copy)[k]);
  }
  free(*copy);
  *copy = NULL;
  return 0;
}

int DeleteField(int ***copy) {
  for (int k = 0; k < MAXCOLS; k++) {
    free((*copy)[k]);
  }
  free(*copy);
  *copy = NULL;
  return 0;
}

int RotateCols(int **field, int **figure) {
  int clop = 0;
  int **temp_figure = CreateCopy();
  CopyFigure(temp_figure, figure);

  for (int k = 1; k < COUNTCOORDINATE; k++) {
    int temp_x = temp_figure[k][0];
    temp_figure[k][0] = -temp_figure[k][1];
    temp_figure[k][1] = temp_x;
  }

  clop = CheckCollision(field, temp_figure);
  if (!clop) {
    CopyFigure(figure, temp_figure);
  }

  DeleteCopy(&temp_figure);
  return clop;
}

int MoveCols(int **field, int **figure, int i) {
  int clop = 0;
  int **temp_figure = CreateCopy();
  CopyFigure(temp_figure, figure);

  temp_figure[0][0] += i;
  clop = CheckCollision(field, temp_figure);
  if (!clop) {
    CopyFigure(figure, temp_figure);
  }

  DeleteCopy(&temp_figure);
  return clop;
}

int Scoring(GameInfo_t *tetris) {
  int a = StringDel(tetris->field);
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
  GetSetInfo(tetris, PUSH);
  return 0;
}

// score deletai
int FileScoreInput(
    char *name,
    GameInfo_t *info) {  
  FILE *fp;
  // strcat(name, ".txt");
  char filename[64];
  snprintf(filename, sizeof(filename), "%s.txt", name);
  if ((fp = fopen(filename, "r+")) == NULL) {
    fp = fopen(filename, "w+");
  }  // добавить проверок на всякое
  // fgets(score, 100, fp);
  // int fs=atoi(score);
  if (info->high_score <= info->score) {
    fprintf(fp, "%d", info->high_score);
  }
  // itoa(info->high_score, info->score,10);
  // fputs(info->score, fp);

  fclose(fp);
  return 0;
}

int **UpdateFigure() {
  static int **figure;
  static int flag = 1;
  if (flag) {
    figure = CreateCopy();
    flag = 0;
  }
  // figure = CreateCopy();
  return figure;
}


void ZeroingAll(GameInfo_t *tetris) {
  ZeroingTemp(tetris->field);
  tetris->score = 0;
  tetris->speed = 0;
  tetris->level = 0;
  tetris->pause = 0;
  Figuring(tetris->next, rand() % COUNTFIGURE);
  GetSetInfo(tetris, PUSH);
}

GameInfo_t GetSetInfo(GameInfo_t *info, int push) {  // not included
  static GameInfo_t game_info;
  // static int** figure;
  if (push) {
    game_info = *info;
  } else {
    *info = game_info;
  }
  return game_info;
}

int InitTetris(GameInfo_t* tetris){
  tetris->pause = 0;
  tetris->score = 0;
  tetris->high_score = 0;
  FileScore("user", tetris);
  tetris->level = 0;
  tetris->field = CreateField();
  tetris->next = CreateCopy();
  
  return 0;//поменять на возможный вывод ошибок
}