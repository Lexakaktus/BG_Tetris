#include "../../inc/backend.h"

/** @brief Массив с координатами всех возможных фигур тетриса. */
static const int figure_home[COUNTFIGURE][COUNTCOORDINATE][2] /*{x,y}*/ = {
    {{5, 0}, {0, 0}, {1, 0}, {-1, 0}, {1, 1}},   //   -.
    {{5, 1}, {0, 0}, {0, 1}, {0, 2}, {0, -1}},   // |  I
    {{5, 0}, {0, 0}, {0, 1}, {1, 0}, {-1, 0}},   // .|.
    {{5, 0}, {0, 0}, {0, 1}, {1, 1}, {1, 0}},    /// ::
    {{5, 0}, {0, 0}, {-1, 0}, {-1, 1}, {1, 0}},  // .-
    {{5, 0}, {0, 0}, {0, 1}, {1, 1}, {-1, 0}},   // Z
    {{5, 0}, {0, 0}, {0, 1}, {-1, 1}, {1, 0}}    //! Z
};


/**
 * @brief Заполняет массив координатами фигуры по индексу.
 * @param figure Указатель на массив координат фигуры.
 * @param index Индекс фигуры из списка figure_home.
 */

void Figuring(int **figure, int index) {  // не изменено
  for (int k = 0; k < COUNTCOORDINATE; k++) {
    figure[k][0] = figure_home[index][k][0];
    figure[k][1] = figure_home[index][k][1];
  }
}



/**
 * @brief Пытается опустить фигуру вниз.
 * @param field Игровое поле.
 * @param figure Фигура для перемещения.
 * @param i Количество строк для смещения (обычно 1).
 * @return 1 если столкновение или выход за границы, иначе 0.
 */
int Curtsy(int **field, int **figure, int i) {  // бэк спуск фигуры
  int clop = 0;
  int **temp_figure = CreateCopy();
  if (temp_figure==NULL){
    clop = BAD_MALLOC;
  } else {
  CopyFigure(temp_figure, figure);
  }
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




/**
 * @brief Очищает поле, заполняя его точками.
 * @param field Указатель на игровое поле.
 */
void ZeroingTemp(
    int **field) {  
  for (int i = 0; i < MAXROWS; i++) {
    for (int j = 0; j < MAXCOLS; j++) {
      field[i][j] = CELL_EMPTY;
    }
  }
}

/**
 * @brief Размещает фигуру на поле, если возможно.
 * @param field Игровое поле.
 * @param figure Фигура.
 * @return 1 при столкновении или выходе за границы, иначе 0.
 */
int SumFigure(int **field, int **figure) {
  int clop = 0;
  for (int k = 4; k > 0 && !clop; k--) {
    int new_x = figure[0][0] + figure[k][0];
    int new_y = figure[0][1] + figure[k][1];

    if (new_y >= MAXROWS || new_y < 0 || new_x >= MAXCOLS || new_x < 0) {
      clop = 1;
    }
    else if (field[new_y][new_x] != CELL_EMPTY) {
      clop = 1;
    }
  }
  for (int k = 4; k > 0 && !clop; k--) {
    int new_x = figure[0][0] + figure[k][0];
    int new_y = figure[0][1] + figure[k][1];
    field[new_y][new_x] = CELL_FILLED; 
  }

  return clop;  
}


/**
 * @brief Удаляет фигуру с поля.
 * @param field Игровое поле.
 * @param figure Фигура.
 * @return 0.
 */
int SubFigure(int **field,
              int **figure) { 

  for (int k = 4; k > 0; k--) {
    int new_x = figure[0][0] + figure[k][0];  // Новая координата по x
    int new_y = figure[0][1] + figure[k][1];
    if (!(new_y >= MAXROWS || new_y < 0 || new_x >= MAXCOLS || new_x < 0))
      field[new_y][new_x] = CELL_EMPTY;  // возвращаем отсутствие фигуры
  }

  return 0;
}


/**
 * @brief Удаляет заполненные строки и сдвигает остальные вниз.
 * @param field Игровое поле.
 * @return Количество удалённых строк.
 */
int StringDel(    int **field) { 
  int del_counter = 0;
  for (int i = 0; i < MAXROWS; i++) {
    int zer_string = 1;

    for (int j = 0; j < MAXCOLS; j++) {
      if (field[i][j] == CELL_EMPTY) {
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
        field[0][k] = CELL_EMPTY;
      }
      del_counter++;
    }
    // printw("\n");
  }
  return del_counter;
}

/**
 * @brief Загружает рекорд игрока из файла и обновляет high_score.
 * @param name Имя пользователя.
 * @param info Указатель на структуру игры.
 * @return 0 при успешной загрузке.
 */
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

/**
 * @brief Проверяет, достигла ли фигура низа или столкновения.
 * @param field Игровое поле.
 * @param figure Фигура.
 * @return 1 если падение должно прекратиться, иначе 0.
 */
int FigureDown(int **field, int **figure) {
  int clop = 0;
  for (int k = 4; k > 0 && !clop; k--) {
    int new_x = figure[0][0] + figure[k][0];  // Новая координата по x
    int new_y = figure[0][1] + figure[k][1] + 1;  // Новая координата по y
    if (new_y == MAXROWS || field[new_y][new_x] != CELL_EMPTY) clop = 1;  //!!!!
  }
  return clop;
}


/**
 * @brief Копирует координаты одной фигуры в другую.
 * @param dest Массив-приёмник.
 * @param src Массив-источник.
 */
void CopyFigure(int **dest, int **src) {
  for (int k = 0; k < COUNTCOORDINATE; k++) {
    dest[k][0] = src[k][0];
    dest[k][1] = src[k][1];
  }
}

/**
 * @brief Проверяет возможные столкновения фигуры с полем.
 * @param field Игровое поле.
 * @param figure Проверяемая фигура.
 * @return 1 при столкновении, иначе 0.
 */
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


/**
 * @brief Выделяет память под координаты фигуры.
 * @return Указатель на двумерный массив координат, или NULL при ошибке выделения.
 */
int **CreateCopy() {
  int clop=1;
  int **temp_figure = malloc(COUNTCOORDINATE * sizeof(int *));
  if (temp_figure ==NULL){
    clop=0;
  }
  for (int k = 0; k < COUNTCOORDINATE&&clop; k++) {
    temp_figure[k] = malloc(2 * sizeof(int));
    if (temp_figure[k]==NULL){
      for (int j = 0; j < k; j++) {
                free(temp_figure[j]);
            }
            free(temp_figure);
      clop=0;
    }
  }
  return clop?temp_figure:NULL;
}

/**
 * @brief Создаёт и инициализирует игровое поле.
 * @return Указатель на поле, или NULL при ошибке выделения.
 */
int **CreateField() { 
  int clop=1;  
  int **field =
      (int **)malloc(MAXROWS * sizeof(int *));
  if (field ==NULL){
    clop=0;
  }
  for (int i = 0; i < MAXROWS&&clop; i++) {
    field[i] = (int *)malloc(MAXCOLS * sizeof(int));
    if (field[i]==NULL){
      for (int j = 0; j < i; j++) {
                free(field[j]);
            }
            free(field);
      clop=0;
    } else {
    for (int j = 0; j < MAXCOLS; j++) {
      field[i][j] = CELL_EMPTY;
    }}
  } 
  return clop?field: NULL;
}

/**
 * @brief Освобождает память, выделенную под фигуру.
 * @param copy Адрес указателя на фигуру.
 * @return 0 при успешном освобождении.
 */
int DeleteCopy(int ***copy) {
  for (int k = 0; k < COUNTCOORDINATE; k++) {
    free((*copy)[k]);
  }
  free(*copy);
  *copy = NULL;
  return 0;
}

/**
 * @brief Освобождает память, выделенную под поле.
 * @param copy Адрес указателя на поле.
 * @return 0 при успешном освобождении.
 */
int DeleteField(int ***copy) {
  for (int k = 0; k < MAXCOLS; k++) {
    free((*copy)[k]);
  }
  free(*copy);
  *copy = NULL;
  return 0;
}


/**
 * @brief Поворачивает фигуру по часовой стрелке.
 * @param field Игровое поле.
 * @param figure Фигура.
 * @return 1 при невозможности поворота, иначе 0.
 */
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

/**
 * @brief Поворачивает фигуру по часовой стрелке.
 * @param field Игровое поле.
 * @param figure Фигура.
 * @return 1 при невозможности поворота, иначе 0.
 */
int MoveCols(int **field, int **figure, int i) {
  int clop = 0;
  int **temp_figure = CreateCopy();
  if (temp_figure!=NULL){
  CopyFigure(temp_figure, figure);

  temp_figure[0][0] += i;
  clop = CheckCollision(field, temp_figure);
  if (!clop) {
    CopyFigure(figure, temp_figure);
  }

  DeleteCopy(&temp_figure);
  }
  return clop;
}


/**
 * @brief Обновляет счёт и уровень игрока в зависимости от удалённых строк.
 * @param tetris Указатель на игровое состояние.
 * @return 0 при успешном обновлении.
 */
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

/**
 * @brief Сохраняет рекорд в файл, если он был побит.
 * @param name Имя пользователя.
 * @param info Структура с результатом.
 * @return 0 при успешной записи.
 */
int FileScoreInput(
    char *name,
    GameInfo_t *info) {  
  FILE *fp;
  char filename[64];
  snprintf(filename, sizeof(filename), "%s.txt", name);
  if ((fp = fopen(filename, "r+")) == NULL) {
    fp = fopen(filename, "w+");
  } 
  if (info->high_score <= info->score) {
    fprintf(fp, "%d", info->high_score);
  }
  fclose(fp);
  return 0;
}

/**
 * @brief Возвращает статическую фигуру (можно использовать как singleton).
 * @return Указатель на фигуру.
 */
int **UpdateFigure() {
  static int **figure;
  static int flag = 1;
  if (flag) {
    figure = CreateCopy();
    flag = 0;
  }
  return figure;
}


/**
 * @brief Обнуляет данные игры и поле.
 * @param tetris Структура игры.
 */
void ZeroingAll(GameInfo_t *tetris) {
  ZeroingTemp(tetris->field);
  tetris->score = 0;
  tetris->speed = 0;
  tetris->level = 0;
  tetris->pause = 0;
  Figuring(tetris->next, rand() % COUNTFIGURE);
  GetSetInfo(tetris, PUSH);
}


/**
 * @brief Позволяет получить или задать текущее состояние игры.
 * @param info Структура с текущим состоянием (по значению или по указателю).
 * @param push 1 — сохранить состояние, 0 — получить.
 * @return Копия текущего состояния.
 */
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

/**
 * @brief Инициализация структуры GameInfo_t.
 * @param tetris Указатель на структуру для инициализации.
 * @return 0 при успехе, 1 при ошибке выделения памяти.
 */
int InitTetris(GameInfo_t* tetris){
  int clop=0;
  tetris->pause = 0;
  tetris->score = 0;
  tetris->high_score = 0;
  FileScore("user", tetris);
  tetris->level = 0;
  tetris->field = CreateField();
  if (tetris->field==NULL){
    clop =1;
  } else {
    tetris->next = CreateCopy();
  }
  if (tetris->next==NULL&&!clop){
    clop =1;
    DeleteField(&(tetris->field));
  }
  return clop;
}