#include <stdlib.h>
#define MAXROWS 20
#define MAXCOLS 10

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
    int **field;
    int **next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
} GameInfo_t;

