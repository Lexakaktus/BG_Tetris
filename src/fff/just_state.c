#include "backend.h"
void just_state(UserAction_t signal, GameInfo_t info ){
    
    static fsm_t state = Init;
    // info.field = createpole();
    // info.figure = createcopy();
    // info.next = createcopy(); 
    switch (state)
    {
    case Init:
        /* code */ //initgame
        if (signal==Terminate)
        {
            state=Gameover;/* code */
        } else if (signal== Action){
            state=Spawn;
        }
        break;
    case Spawn:
        // if ()
        // {
        //     /* code */
        // }
        
        /* code */ //
        break;
    case Moving:
        /* code */ //
        //переход в состояние приклеивания и падения(или без него?)
        break;
    case Attaching:
        if (info.field[0][5]=='I')
        {
            state=Gameover;
        } else {
            state=Spawn;
        }
        break;
    // case Paus:
    //     if (signal==Terminate)
    //     {
    //         state=Gameover;
    //     } else if (signal==Pause){
    //         state=Moving;
    //     }
    //     break;
    case Gameover:
        /* code */ //delete memory
        break;
    default:
        break;
    }
    // return info;
}