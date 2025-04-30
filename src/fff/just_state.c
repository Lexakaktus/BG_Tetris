#include "backend.h"
void Hellostate(UserAction_t signal, fsm_t *state){ //not include!!!
    if (signal==Terminate)
        {
            *state=Gameover;
        } else if (signal== Action){
            *state=Spawn;
        }
}

void Spawnstate(GameInfo_t * info, fsm_t *state){ //not include!!!
        static int random = -1; //наблюдаем
        int ** figure=updatefigure();
        if (random==-1){
            random = rand() % COUNTFIGURE;
        }
        Figuring(figure, random);
        random = rand() % COUNTFIGURE;
        Figuring(info->next, random);
        sumFigure(info->field, figure);
        *state=Moving;   /* code */
}

void Movingstate(GameInfo_t * info, fsm_t *state,UserAction_t signal){
    get_set_info(info,PULL );
    static clock_t lastFallTime = 0;
    int ** figure=updatefigure();
      clock_t currentTime = clock();  // обновление времени с последнего падения
      subFigure(info->field, figure); 
        if (signal == Left) {
        moveCols2(info->field,  figure, -1);
      } else if (signal == Right) {
    //   info->field[19][9]='R';
        moveCols2(info->field,  figure, 1);
      } else if (signal == Action) {
        // info->field[19][9]='B';
        rotateCols2(info->field,  figure);
      } else if (signal == Down){
        while (curtsy2(info->field, figure, 1)==0);
      }
      if ((currentTime - lastFallTime) >=((clock_t)(FALL_DELAY - (3000 * info->level)))) {
        curtsy2(info->field,  figure, 1);  // Спускаем фигуру вниз
        lastFallTime = currentTime;  // Обновляем время последнего падения
      }
        if (FigureDown2(info->field,figure)!=0){*state=Attaching;}
        sumFigure(info->field,  figure);
        
}

void Attachingstate(GameInfo_t * info, fsm_t *state){
    if (info->field[0][5]=='I')
        {
            *state=Gameover;
        } 
        else 
        {
            scoring(info);
            if (info->level < 10) { //поправить, может привести к багу с временно 11ым уровнем
          info->level = info->score / 600;
            } else {
            info->level = 10;
            }
            get_set_info(info, PUSH); //не в хедере!!!
            *state=Spawn;
        }
}

void Gameoverstate(GameInfo_t * info, fsm_t *state,UserAction_t signal){
    // info->field[19][9]='G';
    static clock_t LoseTime = 0;
    clock_t currentTime = clock(); 
    if (LoseTime==0){
        LoseTime = currentTime;
    }
    if (signal==Start)
    {
        // info->score=0;
        zeroing_all(info);
        *state=Spawn;
        //clean_info(функция обнуления значений, мб кроме хайскор((не чистка памяти)))
    } else if (signal==Terminate||currentTime-LoseTime>QUIT_DELAY) {
        *state=Goodbye;
    }
}


fsm_t just_state(UserAction_t signal, GameInfo_t * info, bool hold ){
    hold=0;
    static fsm_t state = Hello;
    get_set_info(info, PULL);
    // static int random = 0; ->in spawnstate
    // info->field = createpole();
    // info->figure = createcopy();
    // info->next = createcopy(); 
    switch (state)
    {
    case Hello:
        Hellostate( signal, &state);
        break;
    case Spawn:
        //если спавнится одна и та же первая фигура добавить ещё этап рандома
        Spawnstate( info, &state);
        break;
    case Moving:
        Movingstate( info, &state, signal);
        break;
    case Attaching:
        Attachingstate( info, &state);
        break;
    case Gameover:
        /* code */ 
        ////рисовка окна проигрыша
        //
        Gameoverstate( info, &state, signal);
        break;
    default:
        if(hold){
            ;
        }
        break;
    }
    return state;
}