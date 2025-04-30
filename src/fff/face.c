#include "backend.h"
#include "front.h"
void get_state(fsm_t * state, int push){
    static fsm_t stat =-1;
    if (push){
        stat=*state;
    } else {
        *state=stat;
    }
}

GameInfo_t get_set_info(GameInfo_t * info, int push){ //not included
    static GameInfo_t game_info;
    // static int** figure;
    if (push){
        game_info=*info;
    } else {
        *info=game_info;
    }
    return game_info;
}

void userInput(UserAction_t action, bool hold){ //not declaration
    GameInfo_t game_info=get_set_info(&game_info, PULL);
    fsm_t state;

    // if(game_info.pause){game_info.field[19][1]='P';} else game_info.field[19][1]='D';
    if (!(state==Goodbye||game_info.pause)){
        // game_info.field[19][9]='G';
    state=just_state(action, &game_info, hold);
    } 
    if (action==Pause){
        // game_info.field[19][9]='T';
        // game_info.high_score++;
        game_info.pause=!game_info.pause;
    }
    if (action == Terminate)
    {
        state=Goodbye;
    }
    
    get_set_info(&game_info, PUSH);
    get_state(&state, PUSH);
}

GameInfo_t updateCurrentState(){
    GameInfo_t info_t;
    //  get_set_info(&info_t, PULL);

    return get_set_info(&info_t, PULL);
}


int main(void){
    WINDOW *board, *infopole;
    drawUI(&board, &infopole);
    srand(time(NULL));
    fsm_t state = Hello;
    GameInfo_t tetris;
    UserAction_t signal=ERR;
    tetris.pause = 0;
    tetris.score = 0;
    tetris.high_score = 0;
    tetris.level = 0;
    tetris.field = createpole();
    tetris.next = createcopy();
    get_set_info(&tetris, PUSH);  
    // int ** figure = updatefigure();
    // figure = createcopy(); // заменить
    //функция инициализации

    while (state!=Goodbye)
    {   
        bool hold=0;
        signal= Uzvering(signal, &hold);
        userInput(signal, hold);
        get_state(&state, PULL);
        // just_state(UserAction_t signal, GameInfo_t * info, bool hold );
        gameprint(board,infopole, updateCurrentState(), "user" );//char *name

    }
    
  fileScoreinput("user", &tetris);

  endwin();
  printf("%s %s %d\n", "user", "\n", tetris.high_score);//убрать
  printf("%s %d", "you lose\nyour score: ", tetris.score);//убрать

    return 0;
}