UserAction_t Uzvering(UserAction_t action ){
  UserAction_t push;//=action;
  int a = getch();
  switch(a){
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
    push=Pause;
    break;
  case 'q':
    push=Terminate;
    break;  
  case 27:      //escape
    push=Terminate;
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
  push=Start;
  break;
  }
  return push;
}