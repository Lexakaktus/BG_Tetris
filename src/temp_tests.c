#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "inc/backend.h"
#include "inc/libspec.h"

START_TEST(test_Figuring) {
  int **figure = createpole();
  int index = 0;

  Figuring(figure, index);

  ck_assert_int_eq(figure[0][0], figure_home[index][0][0]);
  ck_assert_int_eq(figure[0][1], figure_home[index][0][1]);
}
END_TEST

START_TEST(test_zeroing_temp) {
  int **field = createpole();
  zeroing_temp(field);

  int zero_count = 0;
  for (int i = 0; i < MAXROWS; i++) {
    for (int j = 0; j < MAXCOLS; j++) {
      if (field[i][j] == '.') {
        zero_count++;
      }
    }
  }

  ck_assert_int_eq(zero_count, MAXROWS * MAXCOLS);
  deletepole(&field);
}
END_TEST

// START_TEST(test_sumField) {
//   int **field1 = createpole();
//   int **field2 = createpole();

//   // Заполняем field1
//   field1[0][0] = 'X';

//   sumField(field1, field2);

//   ck_assert_int_eq(field1[0][0], field2[0][0]);

//   deletecopy(field1);
//   deletecopy(field2);
// }
// END_TEST

START_TEST(test_sumFigure) {
  int **field = createpole();
  int **figure = createcopy();
  Figuring(figure, 1);

  // Сначала проверим, что нет столкновений
  int clop = sumFigure(field, figure);

  // Поле обновляется, если нет столкновений
  ck_assert_int_eq(clop, 0);

  deletepole(&field);
}
END_TEST

START_TEST(test_subFigure) {
  int **field = createpole();
  int **figure = createcopy();
  Figuring(figure, 3);

  // Сначала добавим фигуру
  sumFigure(field, figure);

  // Удалим фигуру
  int clop = subFigure(field, figure);

  // Поле должно быть очищено
  ck_assert_int_eq(field[5][0], '.');
  ck_assert_int_eq(clop, 0);
  deletepole(&field);
}
END_TEST

START_TEST(test_moveCols) {
  int **field = createpole();
  int **figure = createcopy();
  Figuring(figure, 3);

  // Сдвиг вправо
  int clop = moveCols2(field, figure, 1);
  ck_assert_int_eq(clop, 0); // Столкновений быть не должно

  deletepole(&field);
}
END_TEST

START_TEST(test_rotateCols) {
  int **field = createpole();
  int **figure = createcopy();
  Figuring(figure, 3);

  // Поворот фигуры
  int clop = rotateCols2(field, figure);
  ck_assert_int_eq(clop, 0); // Столкновений быть не должно

  deletepole(&field);
}
END_TEST

START_TEST(test_stringDel) {
  int **field = createpole();

  // Заполним несколько строк
  for (int i = 0; i < MAXCOLS; i++) {
    field[0][i] = 'I';
  }

  int delCount = stringDel(field);

  // Проверим, что одна строка была удалена
  ck_assert_int_eq(delCount, 1);

  deletepole(&field);
}
END_TEST

START_TEST(test_checkCollision) {
  int **field = createpole();
  int **figure = createcopy();
  Figuring(figure, 3);

  // Поставим фигуру на поле
  sumFigure(field, figure);

  // Проверим столкновение
  int clop = checkCollision(field, figure);

  ck_assert_int_eq(clop, 1);

  deletepole(&field);
}
END_TEST

START_TEST(test_createcopy) {
  int **copy = createcopy();

  // Проверим, что копия была успешно создана
  ck_assert_ptr_nonnull(copy);

  // Очистим память
  deletecopy(&copy);
}
END_TEST

START_TEST(test_deletecopy) {
  int **copy = createcopy();
  deletecopy(&copy);

  // Проверим, что память была освобождена
  ck_assert_ptr_null(copy);
}
END_TEST

START_TEST(test_curtsy) {
  int **field = createpole();
  int **figure = createcopy();
  // deletecopy(&copy);
  Figuring(figure, 0);
  curtsy2(field, figure, 1);
  // Проверим, что память была освобождена
  // ck_assert_ptr_null(copy);
  ck_assert_int_eq(figure[0][1], 1);
  deletecopy(&figure);
  deletepole(&field);
}
END_TEST

START_TEST(test_curtsy_bad_arg) {
  int **field = createpole();
  int **figure = createcopy();
  // deletecopy(&copy);
  Figuring(figure, 0);
  int clop = curtsy2(field, figure, 0);
  // Проверим, что память была освобождена
  // ck_assert_ptr_null(copy);
  ck_assert_int_ne(clop, 0);
  deletecopy(&figure);
  deletepole(&field);
}
END_TEST

START_TEST(test_figure_Down2) {
  int **field = createpole();
  int **figure = createcopy();
  // deletecopy(&copy);
  Figuring(figure, 0);
  curtsy2(field, figure, 17);
  ck_assert_int_eq(FigureDown2(field, figure), 0);
  curtsy2(field, figure, 1);
  // Проверим, что память была освобождена
  // ck_assert_ptr_null(copy);

  ck_assert_int_ne(FigureDown2(field, figure), 0);
  deletecopy(&figure);
  deletepole(&field);
}
END_TEST 

START_TEST(test_scoring) {
  // int **field = createpole();
  // int **figure = createcopy();
  // deletecopy(&copy);
  GameInfo_t  tetris;
  init_tetris(&tetris);
  scoring(&tetris);

  // ck_assert_int_eq(FigureDown2(field, figure), 0);
  // curtsy2(field, figure, 1);
  // Проверим, что память была освобождена
  // ck_assert_ptr_null(copy);
  for (int i=0;i<1;i++){
    for (int j=0;j<10;j++){
      tetris.field[i][j]='I';
    }
  }
  scoring(&tetris);
  ck_assert_int_eq(tetris.score, 100);
  // ck_assert_int_ne(FigureDown2(field, figure), 0);
  // deletecopy(&figure);
  deletepole(&(tetris.field));
}
END_TEST 

START_TEST(test_scoring_2) {
  // int **field = createpole();
  // int **figure = createcopy();
  // deletecopy(&copy);
  GameInfo_t  tetris;
  init_tetris(&tetris);
  scoring(&tetris);

  // ck_assert_int_eq(FigureDown2(field, figure), 0);
  // curtsy2(field, figure, 1);
  // Проверим, что память была освобождена
  // ck_assert_ptr_null(copy);
  for (int i=0;i<2;i++){
    for (int j=0;j<10;j++){
      tetris.field[i][j]='I';
    }
  }
  scoring(&tetris);
  ck_assert_int_eq(tetris.score, 300);
  // ck_assert_int_ne(FigureDown2(field, figure), 0);
  // deletecopy(&figure);
  deletepole(&(tetris.field));
}

START_TEST(test_scoring_3) {
  // int **field = createpole();
  // int **figure = createcopy();
  // deletecopy(&copy);
  GameInfo_t  tetris;
  init_tetris(&tetris);
  scoring(&tetris);

  // ck_assert_int_eq(FigureDown2(field, figure), 0);
  // curtsy2(field, figure, 1);
  // Проверим, что память была освобождена
  // ck_assert_ptr_null(copy);
  for (int i=0;i<3;i++){
    for (int j=0;j<10;j++){
      tetris.field[i][j]='I';
    }
  }
  scoring(&tetris);
  ck_assert_int_eq(tetris.score, 700);
  // ck_assert_int_ne(FigureDown2(field, figure), 0);
  // deletecopy(&figure);
  deletepole(&(tetris.field));
}

START_TEST(test_scoring_4) {
  GameInfo_t  tetris;
  init_tetris(&tetris);
  scoring(&tetris);
  for (int i=0;i<4;i++){
    for (int j=0;j<10;j++){
      tetris.field[i][j]='I';
    }
  }
  scoring(&tetris);
  ck_assert_int_eq(tetris.score, 1500);
  // ck_assert_int_ne(FigureDown2(field, figure), 0);
  deletecopy(&(tetris.next));
  deletepole(&(tetris.field));
}

START_TEST(test_zeroing_all) {
  GameInfo_t  tetris;
  init_tetris(&tetris);
  for (int i=0;i<4;i++){
    for (int j=0;j<10;j++){
      tetris.field[i][j]='I';
    }
  }
  scoring(&tetris);
  ck_assert_int_eq(tetris.score, 1500);
  zeroing_all(&tetris);
  ck_assert_int_eq(tetris.score, 0);
  // ck_assert_int_ne(FigureDown2(field, figure), 0);
  deletecopy(&(tetris.next));
  deletepole(&(tetris.field));
}

START_TEST(test_Hellostate) {
  GameInfo_t  tetris;
  init_tetris(&tetris);
  // for (int i=0;i<4;i++){
  //   for (int j=0;j<10;j++){
  //     tetris.field[i][j]='I';
  //   }
  // }
  int **figure = updatefigure();
  Figuring(figure, 0);
  // fsm_t 
  fsm_t state =Hello;
  Hellostate(Start, & state);
  ck_assert_int_eq(state, Hello);
  Hellostate(Terminate, & state);
  ck_assert_int_eq(state, Gameover);
  Hellostate(Action, & state);
  ck_assert_int_eq(state, Spawn);
  zeroing_all(&tetris);
  ck_assert_int_eq(tetris.score, 0);
  // ck_assert_int_ne(FigureDown2(field, figure), 0);
  deletecopy(&(tetris.next));
  deletepole(&(tetris.field));
}

START_TEST(test_Spawnstate) {
  GameInfo_t  tetris;
  init_tetris(&tetris);

  int **figure = updatefigure();
  Figuring(figure, 0);
  // fsm_t 
  fsm_t state =Hello;
  Spawnstate(&tetris, & state);
  ck_assert_int_eq(state, Moving);
  // Spawnstate(Terminate, & state);
  // ck_assert_int_eq(state, Gameover);
  // Spawnstate(Action, & state);
  // ck_assert_int_eq(state, Spawn);
  zeroing_all(&tetris);
  ck_assert_int_eq(tetris.score, 0);
  // ck_assert_int_ne(FigureDown2(field, figure), 0);
  deletecopy(&(tetris.next));
  deletepole(&(tetris.field));
}







START_TEST(test_Movingstate) {
  GameInfo_t  tetris;
  init_tetris(&tetris);
  get_set_info(&tetris, PUSH);
  int **figure = updatefigure();
  Figuring(figure, 0);
  fsm_t state =Hello;
  Movingstate(&tetris, & state, Left);
  ck_assert_int_eq(tetris.field[0][3], 'I');
  Movingstate(&tetris, & state, Right);
  ck_assert_int_eq(tetris.field[0][3], '.');
    // sleep(7);
  for (volatile long i = 0; i < 100000000; ++i);
  Movingstate(&tetris, & state, Start);
  ck_assert_int_eq(tetris.field[1][4], 'I');
  Movingstate(&tetris, & state, Action);
  Movingstate(&tetris, & state, Down);
  ck_assert_int_eq(state, Attaching);
  ck_assert_int_eq(tetris.field[19][4], 'I');
  zeroing_all(&tetris);
  ck_assert_int_eq(tetris.score, 0);
  deletecopy(&(tetris.next));
  deletepole(&(tetris.field));
}



START_TEST(test_Attachingstate) {
  GameInfo_t  tetris;
  init_tetris(&tetris);
  int **figure = updatefigure();
  Figuring(figure, 0);
  // fsm_t 
  fsm_t state =Hello;
  Attachingstate(&tetris, & state);
  ck_assert_int_eq(state, Spawn);
  tetris.level=11; ///потом подумать над адекватностью
  Attachingstate(&tetris, & state);
  ck_assert_int_eq(tetris.level, 10);
  tetris.field[0][5] = 'I';
  Attachingstate(&tetris, & state);
  ck_assert_int_eq(state, Gameover);
  zeroing_all(&tetris);
  ck_assert_int_eq(tetris.score, 0);
  deletecopy(&(tetris.next));
  deletepole(&(tetris.field));
}

START_TEST(test_just_state) {
  GameInfo_t  tetris;
  init_tetris(&tetris);
  get_set_info(&tetris, PUSH);
  int **figure = updatefigure();
  Figuring(figure, 0);
  // fsm_t state =Hello;
  // for (int i = 0; i <= 10000; i++)
  // {
    fsm_t state =just_state( Action,&tetris,0);
  // }
  ck_assert_int_eq(state, Spawn);
  state =just_state( Action,&tetris,0);
  ck_assert_int_eq(state, Moving);
  state =just_state( Down,&tetris,0);
  ck_assert_int_eq(state, Attaching);
  tetris.field[0][5]='I';
  state =just_state( Down,&tetris,0);
  ck_assert_int_eq(state, Gameover);
  state =just_state( Down,&tetris,0);
// for (volatile long i = 0; i < 100000000; ++i);
  // just_state(&tetris, &state, Left);
  // ck_assert_int_eq(tetris.field[0][3], 'I');
  // Movingstate(&tetris, & state, Right);
  // ck_assert_int_eq(tetris.field[0][3], '.');
    // sleep(7);
  // for (volatile long i = 0; i < 100000000; ++i);
  // Movingstate(&tetris, & state, Start);
  // ck_assert_int_eq(tetris.field[1][4], 'I');
  // Movingstate(&tetris, & state, Action);
  // Movingstate(&tetris, & state, Down);
  // ck_assert_int_eq(state, Attaching);
  // ck_assert_int_eq(tetris.field[19][4], 'I');
  zeroing_all(&tetris);
  ck_assert_int_eq(tetris.score, 0);
  deletecopy(&(tetris.next));
  deletepole(&(tetris.field));
}

START_TEST(test_Gameoverstate) {
  GameInfo_t  tetris;
  init_tetris(&tetris);
  int **figure = updatefigure();
  Figuring(figure, 0);
  // fsm_t 
  fsm_t state =Hello;
  Gameoverstate(&tetris, & state, Terminate);
  ck_assert_int_eq(state,Goodbye);
  Gameoverstate(&tetris, & state, Start);
  ck_assert_int_eq(state, Hello);
  // Gameoverstate(&tetris, & state, Action);
  // ck_assert_int_eq(state, Spawn);
  zeroing_all(&tetris);
  ck_assert_int_eq(tetris.score, 0);
  // ck_assert_int_ne(FigureDown2(field, figure), 0);
  deletecopy(&(tetris.next));
  deletepole(&(tetris.field));
}








Suite *mozg_suite(void) {
  Suite *suite = suite_create("Mozg");
  TCase *core = tcase_create("Core");

  tcase_set_timeout(core, 20);

  tcase_add_test(core, test_Figuring);
  tcase_add_test(core, test_zeroing_temp);
  // tcase_add_test(core, test_sumField);
  tcase_add_test(core, test_sumFigure);
  tcase_add_test(core, test_subFigure);
  tcase_add_test(core, test_moveCols);
  tcase_add_test(core, test_rotateCols);
  tcase_add_test(core, test_stringDel);
  tcase_add_test(core, test_checkCollision);
  tcase_add_test(core, test_createcopy);
  tcase_add_test(core, test_deletecopy);

  tcase_add_test(core, test_curtsy);
  tcase_add_test(core, test_curtsy_bad_arg);
  tcase_add_test(core, test_figure_Down2);
  tcase_add_test(core, test_scoring);
  tcase_add_test(core, test_scoring_2);
  tcase_add_test(core, test_scoring_3);
  tcase_add_test(core, test_scoring_4);
  tcase_add_test(core, test_zeroing_all);
  tcase_add_test(core, test_Hellostate);
  tcase_add_test(core, test_Spawnstate);
  tcase_add_test(core, test_Movingstate);

  tcase_add_test(core, test_Attachingstate);
  tcase_add_test(core, test_Gameoverstate);
  tcase_add_test(core, test_just_state);
  // tcase_add_test(core, test_curtsy_bad_arg);
  // tcase_add_test(core, test_curtsy_bad_arg);

  suite_add_tcase(suite, core);

  return suite;
}

int main(void) {
  int number_failed;
  Suite *suite = mozg_suite();
  SRunner *runner = srunner_create(suite);

  srunner_run_all(runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (number_failed == 0) ? 0 : 1;
}
