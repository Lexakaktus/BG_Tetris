#include "mozg.h"

void Figuring(int **figure, int Fdonor[][2]) {
  for (int k = 0; k < COUNTCOORDINATE; k++) {
    figure[k][0] = Fdonor[k][0];
    figure[k][1] = Fdonor[k][1];
  }
}

int curtsy(int **Figure, int i) {  // перемещение фигуры по вертикали
  int clop = 0;
  for (int k = 4; k > 0 && !clop; k--) {
    // int new_x = Figure[0][0] + Figure[k][0];  // Новая координата по x
    int new_y = Figure[0][1] + Figure[k][1] + 1;  // Новая координата по y
    if (new_y >= MAXROWS) clop = 1;
  }
  if (!clop) {
    Figure[0][1] += i;
  }
  return clop;
}

void zeroing_temp(int **Field) {  //"обнуление" поля
  for (int i = 0; i < MAXROWS; i++) {
    for (int j = 0; j < MAXCOLS; j++) {
      Field[i][j] = '.';
    }
  }
}

// не используется можно удалять
int sumAhalay(int **Field, int **Figure) {
  for (int k = 4; k > 0; k--) {
    Field[Figure[0][0] + Figure[k][1]][Figure[0][1] + Figure[k][0]] = 'I';
  }
  return 0;
}

void sumField(int **Field,
              int **FieldTwo) {  // складывание полей(можно(?) удалить)
  for (int i = 0; i < MAXROWS; i++) {
    for (int j = 0; j < MAXCOLS; j++) {
      FieldTwo[i][j] = Field[i][j];
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
              int **Figure) {  // стирание фигуры с поля ( непроверенное!)
  int clop = 0;

  // Проверка на выход за границы поля или столкновение с другой фигурой
  // for (int k = 4; k > 0 && !clop; k--) {
  //     int new_x = Figure[0][0] + Figure[k][0];  // Новая координата по x
  //     int new_y = Figure[0][1] + Figure[k][1];  // Новая координата по y

  //     // Проверяем вертикальные границы (y) и горизонтальные (x)
  //     if (new_y >= MAXROWS || new_y < 0 || new_x >= MAXCOLS || new_x < 0) {
  //         clop = 1;  // Если фигура выходит за границы, останавливаемся
  //     }
  //     // Проверка на столкновение с уже существующими блоками на поле
  //     // else if (Field[new_y][new_x] != '.') {
  //     //     clop = 1;
  //     // }
  // }

  // Если не было столкновений и выхода за границы, обновляем поле
  for (int k = 4; k > 0; k--) {
    int new_x = Figure[0][0] + Figure[k][0];  // Новая координата по x
    int new_y = Figure[0][1] + Figure[k][1];
    if (!(new_y >= MAXROWS || new_y < 0 || new_x >= MAXCOLS || new_x < 0))
      Field[new_y][new_x] = '.';  // Устанавливаем фигуру на поле
  }

  return clop;  // Возвращаем флаг столкновения//откуда оно здесь?
}

int moveCols(int **Field, int **Figure, int i) {  /// перемещение по горизонтали
  int clop = 0;
  for (int k = COUNTCOORDINATE - 1; k > 0 && !clop; k--) {
    int new_x = Figure[k][0] + Figure[0][0];  // Новая позиция по горизонтали
    if (new_x <= 0 || new_x >= MAXCOLS - 1 ||
        Field[Figure[0][1] + Figure[k][1]][new_x] != '.') {
      clop = new_x <= 0             ? 3
             : new_x >= MAXCOLS - 1 ? 1
                                    : 2;  // Останавливаем сдвиг, если фигура
                                          // выходит за пределы break;
      // clop = 1;
    }
  }
  // if (clop ==2){

  // }
  if ((clop == 3 && i > 0) || (clop == 1 && i < 0) || (clop == 0)) {
    Figure[0][0] += i;
  }
  return clop;
}

int rotateCols(int **Field, int **Figure, int i) {  /// поворот, убрать и // и?
  int clop = 0;

  for (int k = 4; k > 0 && !clop; k--) {
    if ((Figure[0][1] + Figure[k][0] >= MAXROWS /*? ||*/  /// тут что-то не так
         /* Figure[1][0] + Figure[1][k] < 0) ?*/) ||
        ((Figure[0][0] + -1 * Figure[k][1]) >= MAXCOLS ||
         (Figure[0][0] + -1 * Figure[k][1]) < 0) ||
        Field[(Figure[0][0] + -1 * Figure[k][1])]
             [Figure[0][1] + Figure[k][0]] != /*???*/
            '.') {
      clop = 1;
    }
    // && !clop && Field[(Figure[0][0] + -1*Figure[k][1])][Figure[0][1] +
    // Figure[k][0]] != '.'
    // while (Figure[0][0] - Figure[k][1] >= MAXCOLS && !clop) {
    //   // moveCols( Field, Figure, 1);
    //   Figure[0][0]-=1;
    // }
    // while (Figure[0][0] - Figure[k][1] < 0 && !clop) {
    //   Figure[0][0]+=1;
    //   // moveCols( Field, Figure, -1);
    // }
  }
  for (int k = 4; k > 0 && !clop; k--) {
    int tempx = Figure[k][0];
    Figure[k][0] = -Figure[k][1];
    Figure[k][1] = tempx;
  }

  //   for (int k = 4; k > 0 && !clop; k--) {
  //     int new_x = Figure[0][0] + Figure[k][0];  // Новая координата по x
  //     int new_y = Figure[0][1] + Figure[k][1];  // Новая координата по y

  //     // Проверяем вертикальные границы (y) и горизонтальные (x)
  //     if (new_y >= MAXROWS || new_y < 0 || new_x >= MAXCOLS || new_x < 0) {
  //         clop = 1;  // Если фигура выходит за границы, останавливаемся
  //     }
  //     if ( new_x >= MAXCOLS || new_x < 0) {
  //         clop = 2;  // Если фигура выходит за границы, останавливаемся
  //     }
  //     // Проверка на столкновение с уже существующими блоками на поле
  //     else if (Field[new_y][new_x] != '.') {
  //         clop = 1;
  //     }
  // }
  //   for (int k = 4; k > 0 && clop; k--) {
  //       int tempx=Figure[k][0];
  // Figure[k][0] =Figure[k][1];
  // Figure[k][1]=-tempx;
  // }

  return clop;
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

UserAction_t Uzvering(UserAction_t action) {  // переименовать
  UserAction_t push;                          //=action;
  int a = getch();
  switch (a) {
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
      push = Pause;
      break;
    case 'q':
      push = Terminate;
      break;
    case 27:  // escape
      push = Terminate;
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
      push = Start;
      break;
  }
  return push;
}

// возможно убрать score внутрь функции
int fileScore(
    char *name, char *score,
    GameInfo_t *info) {  // добавить сразу замену счёта в файле или игре(смотря
                         // что больше) и в конце закрывать файл
  FILE *fp;
  strcat(name, ".txt");

  if ((fp = fopen(name, "r+")) == NULL) {
    fp = fopen(name, "w+");
  }  // добавить проверок на всякое
  fgets(score, 100, fp);
  int fs = atoi(score);
  if (fs >= info->high_score) {
    info->high_score = fs;
  }
  fclose(fp);
  return 0;
}

void initg() {  // не работает
  initscr();
  timeout(300);
  noecho();
  keypad(stdscr, true);
  WINDOW *board = newwin(20, 20, 0, 0);
  refresh();
  box(board, 0, 0);
  wrefresh(board);
  mvwaddstr(board, 8, 3, "PRESS");
  mvwaddstr(board, 10, 3, "ENTER");
  // wattroff(board, COLOR_PAIR(COLOR_WORDS));
  wrefresh(board);
  WINDOW *infopole = newwin(20, 10, 0, 21);
  refresh();
  box(infopole, 0, 0);
  wrefresh(infopole);
  mvwaddstr(infopole, 8, 3, "SS");
  mvwaddstr(infopole, 10, 3, "ER");
  // wattroff(infopole, COLOR_PAIR(COLOR_WORDS));
  wrefresh(infopole);
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);  // Цветовая пара 1: красный
  init_pair(2, COLOR_GREEN, COLOR_BLACK);  // Цветовая пара 2: зеленый
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);  // Цветовая пара 3: желтый
}

int FigureDown(int **Field, int **Figure) {
  int clop = 0;
  for (int k = 4; k > 0 && !clop; k--) {
    int new_x = Figure[0][0] + Figure[k][0];  // Новая координата по x
    int new_y = Figure[0][1] + Figure[k][1];  // Новая координата по y
    if (new_y == MAXROWS - 1) clop = 1;
    if (Field[new_y][new_x] != '.') clop = 2;
  }
  return clop;
}

int checkCollision(int **Field, int **Figure) {
  for (int k = 0; k < COUNTCOORDINATE; k++) {
    int new_x = Figure[k][0];
    int new_y = Figure[k][1];
    if (new_y >= MAXROWS || new_y < 0 || new_x >= MAXCOLS || new_x < 0 ||
        Field[new_y][new_x] != '.') {
      return 1;
    }
  }
  return 0;
}