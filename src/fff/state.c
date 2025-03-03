#include "backend.h"
GameInfo_t state(){
    static GameInfo_t info={0};
    static fsm_t state = Init;
    info.field = createpole();
    info.figure = createcopy();
    info.next = createcopy(); 
    switch (state)
    {
    case Init:
        /* code */ //initgame
        break;
    case Moving:
        /* code */ //
        break;
    case Paus:
        /* code */ //anything
        break;
    case Gameover:
        /* code */ //delete memory
        break;
    default:
        break;
    }
    return info;
}