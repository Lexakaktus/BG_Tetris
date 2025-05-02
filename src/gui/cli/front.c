#include "../../inc/front.h"


/**
 * @brief Обрабатывает ввод пользователя с клавиатуры.
 * 
 * @param action Предыдущее действие пользователя.
 * @param hold Указатель на флаг зажатия клавиши.
 * @return Новое действие пользователя.
 */
UserAction_t Uzvering(
    UserAction_t action,
    bool *hold) { 
  static UserAction_t push;  //=action;
  push = action;
  int a = getch();
  // if (action != Pause) {
  switch (a) {
    case 'a':
    case KEY_LEFT:
      action = Left;
      break;
    case 'd':
    case KEY_RIGHT:
      action = Right;
      break;
    case 'p':
      action = Pause;
      break;
    case 'q':
      action = Terminate;
      break;
    case 27:  // escape
      action = Terminate;
      break;
    case '\n':
      action = Action;
      break;
    case 's':
    case KEY_DOWN:
      action = Down;
      break;
    case '\\':
      action = Start;
      break;
    case 'w':
    case KEY_UP:
      action = Up;
      break;
    default:
      action = -1;
      break;
  }
  *hold = (push == action && push != Up);
  return action;
}

/**
 * @brief Отрисовывает следующую фигуру в окне информации.
 * 
 * @param info_window Окно ncurses для вывода.
 * @param tetris Текущая информация об игре.
 * @return int 0 при успешной отрисовке.
 */
int NewFigurePrint(WINDOW *info_window, GameInfo_t tetris) {  // фронт
  int x = tetris.next[0][0] - 3;
  int y = tetris.next[0][1] + 1;

  for (int i = 1; i < COUNTCOORDINATE; i++) {
    mvwprintw(info_window, i, 1, "%c   ", ' ');
  }
  mvwprintw(info_window, y, x, "%c", '*');
  for (int i = 2; i < COUNTCOORDINATE; i++) {
    mvwprintw(info_window, y + tetris.next[i][1], x + tetris.next[i][0], "%c",
              '*');
  }
  return 0;
}


/**
 * @brief Отрисовывает информационную панель с данными игры.
 * 
 * @param info_window Окно ncurses для вывода.
 * @param tetris Текущая информация об игре.
 * @param name Имя игрока.
 * @return int 0 при успешной отрисовке.
 */
int InfoPrint(WINDOW *info_window, GameInfo_t tetris, char *name) {
  // wclear(info_window);
  box(info_window, 0, 0);
  
  // clear();
  // wrefresh(info_window);
  NewFigurePrint(info_window, tetris);

  mvwprintw(info_window, 7, 1, "%s", "score");
  mvwprintw(info_window, 8, 2, "%d", tetris.score);
  mvwprintw(info_window, 10, 1, "%s", "username");
  mvwprintw(info_window, 11, 2, "%s", name);
  mvwprintw(info_window, 13, 1, "%s", "highScor");
  mvwprintw(info_window, 14, 3, "%d", tetris.high_score);
  mvwprintw(info_window, 5, 1, "%s", "LEVEL");
  mvwprintw(info_window, 6, 3, "%d", tetris.level);
  wrefresh(info_window);
  return 0;
}


/**
 * @brief Отрисовывает игровое поле.
 * 
 * @param board Окно ncurses, в котором отрисовывается поле.
 * @param tetris Структура с текущим состоянием поля.
 * @return int 0 при успешной отрисовке.
 */
int FieldPrint(WINDOW *board, GameInfo_t tetris) {
  wmove(board, 0, 0);
  for (int i = 0; i < MAXROWS;
       i++) {
    for (int j = 0; j < MAXCOLS; j++) {
      switch (tetris.field[i][j]) {
        case '.': 
          wattron(board, COLOR_PAIR(1));
          wprintw(board, "%s", "..");
          wattroff(board, COLOR_PAIR(1));
          break;
        case 'I':  
          wattron(board, COLOR_PAIR(2));
          wprintw(board, "%s", "II");
          wattroff(board, COLOR_PAIR(2));
          break;
        default:  
          wattron(board, COLOR_PAIR(3));
          wprintw(board, "%c%c", tetris.field[i][j], tetris.field[i][j]);
          wattroff(board, COLOR_PAIR(3));
          break;
      }
    }
  }
  wrefresh(board);
  return 0;
}


/**
 * @brief Инициализирует ncurses, создаёт окна и задаёт цвета.
 * 
 * @param board Указатель на указатель окна с игровым полем.
 * @param info_window Указатель на указатель окна с информацией.
 */
void Draw(WINDOW **board, WINDOW **info_window) {
  initscr();
  timeout(1);
  curs_set(0);
  keypad(stdscr, true);
  noecho();

  // Создаем игровое поле
  *board = newwin(20, 20, 0, 0);
  box(*board, 0, 0);
  mvwaddstr(*board, 2, 3, "Hello, enter");
  mvwaddstr(*board, 3, 3, "your username");
  mvwaddstr(*board, 6, 1, "Pss, the SQUARE ");
  mvwaddstr(*board, 7, 3, " ...rotates... ");
  wrefresh(*board);

  // Создаем информационное поле
  *info_window = newwin(20, 13, 0, 21);
  box(*info_window, 0, 0);
  wrefresh(*info_window);

  // Цвета
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);
}


/**
 * @brief Основная отрисовка интерфейса игры (поле + инфо).
 * 
 * @param board Окно игрового поля.
 * @param info_window Окно информационной панели.
 * @param tetris Структура с состоянием игры.
 * @param name Имя пользователя.
 * @return int 0 при успешной отрисовке.
 */
int GamePrint(WINDOW *board, WINDOW *info_window, GameInfo_t tetris, char *name) {
  FieldPrint(board, tetris);
  InfoPrint(info_window, tetris, name);
  // refresh();
  return 0;
}