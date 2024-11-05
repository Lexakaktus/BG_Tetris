#include <ncurses.h>
#include <string.h> 



#include <stdlib.h>
#include <time.h>

#define MAXROWS 20
#define MAXCOLS 10
#define MAXFIGURE 5
#define COUNTFIGURE 7

// typedef enum {
//     Start,  //0
//     Moving,
//     Pause,
//     Gameover,
//     Hello=-1 //временно
// } fsm_t;


typedef enum {
    Start,  //0
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action  //7
} UserAction_t;

typedef struct {
    int **field; ///поле для отрисовки
    int **figure;
    int **next;  ///следующая фигура
    int score;  ///счёт игры
    int high_score; ///счёт из файла "ИмяИгрока" или максимальный в игре
    int level;
    int speed;
    int pause;
} GameInfo_t;

void sumField(int ** Field, int ** FieldTwo);//прибавление поля с приклеившимися фигурами ///
/// к полю для отрисовки использовать перед sumfigure!!! 

int sumFigure(int ** Field, int**  figure); //прибавление фигуры к полю перед отрисовкой
int subFigure(int** Field, int** Figure); //вычитание фигуры из поля обратноdq
int curtsy(int** Figure, int i); //понижение фигуры
void zeroing_temp(int ** Field); //обнуление поля для отрисовки(да и другого при желании)
void Figuring(int** figure, int Fdonor[][2]); //заполнение следующей и текущей фигур изначальными //
// координатами (позже усложнить до одной из 7ми фигур)
int moveCols(int** Field,int** Figure, int i);
int rotateCols(int** Field,int** Figure, int i); //Переименовать
int stringDel(int** Field);
UserAction_t Uzvering(UserAction_t action );
int fileScore(char* name, char* score,  GameInfo_t* info);


void initg();