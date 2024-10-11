#include "mozg.h"

void Figuring(int** figure, int Fdonor[][2]){
  for(int k=0;k<MAXFIGURE; k++){
      figure[k][0]=Fdonor[k][0];
      figure[k][1]=Fdonor[k][1];
    }
}


int curtsy(int** Figure, int i){
  Figure[0][1]+=i;
  return 0;
}

void zeroing_temp(int ** Field){
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
    Field[i][j] = '.';
  }
  }
}

int sumAhalay(int ** Field, int** Figure){ //оптимизировать эту кашу!!!! //
  // int clop=0;

    for(int k=4;k>0; k--){
       Field[Figure[0][0]+Figure[k][1]][Figure[0][1]+Figure[k][0]]='I';
    }
    //   for(int k=1;k<MAXFIGURE; k++){
    //   Figure[k][0]=0;
    //   Figure[k][1]=0;
    // }
    // Figure[0][0]=0;
  // }}
  return 0;
}

void sumField(int ** Field, int ** FieldTwo ){
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
    FieldTwo[i][j] = Field[i][j];
  }
  }
}

int sumFigure(int ** Field, int** Figure){ //оптимизировать эту кашу!!!!
  int clop=0;
  // for (int i=0;i<MAXROWS&&!clop ;i++){ //Figure[0][0]-1 или -2
  // for (int j=0; j<MAXCOLS&&!clop; j++){
    for(int k=4;k>0&&!clop; k--){
      if ((Figure[0][1]+Figure[k][1]>=MAXROWS||Figure[0][1]+Figure[k][1]<0) ///потом поставить проигрыш при втором условии
      ||
      Field[Figure[0][1]+Figure[k][1]][Figure[0][0]+Figure[k][0]]!='.'){
        clop=1;
      }
    //    else Field[Figure[0][0]+Figure[k][1]][Figure[0][1]+Figure[k][0]]='I';
    }
       for(int k=4;k>0&&!clop; k--){
        Field[Figure[0][1]+Figure[k][1]][Figure[0][0]+Figure[k][0]]='I';
    }
  // }}
  return clop;
}
