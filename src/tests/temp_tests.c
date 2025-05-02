
#include "test.h"

static const int figure_home[COUNTFIGURE][COUNTCOORDINATE][2] /*{x,y}*/ = {
    {{5, 0}, {0, 0}, {1, 0}, {-1, 0}, {1, 1}},   //   -.
    {{5, 1}, {0, 0}, {0, 1}, {0, 2}, {0, -1}},   // |  I
    {{5, 0}, {0, 0}, {0, 1}, {1, 0}, {-1, 0}},   // .|.
    {{5, 0}, {0, 0}, {0, 1}, {1, 1}, {1, 0}},    /// ::
    {{5, 0}, {0, 0}, {-1, 0}, {-1, 1}, {1, 0}},  // .-
    {{5, 0}, {0, 0}, {0, 1}, {1, 1}, {-1, 0}},   // Z
    {{5, 0}, {0, 0}, {0, 1}, {-1, 1}, {1, 0}}    //! Z
};

START_TEST(test_Figuring) {
  int **figure = CreateField();
  int index = 0;

  Figuring(figure, index);

  ck_assert_int_eq(figure[0][0], figure_home[index][0][0]);
  ck_assert_int_eq(figure[0][1], figure_home[index][0][1]);
  // DeleteCopy(&figure);
  DeleteField(&figure);
}
END_TEST

START_TEST(test_ZeroingTemp) {
  int **field = CreateField();
  ZeroingTemp(field);

  int zero_count = 0;
  for (int i = 0; i < MAXROWS; i++) {
    for (int j = 0; j < MAXCOLS; j++) {
      if (field[i][j] == '.') {
        zero_count++;
      }
    }
  }

  ck_assert_int_eq(zero_count, MAXROWS * MAXCOLS);
  DeleteField(&field);
}
END_TEST

START_TEST(test_SumFigure) {
  int **field = CreateField();
  int **figure = CreateCopy();
  Figuring(figure, 1);
  int clop = SumFigure(field, figure);
  ck_assert_int_eq(clop, 0);
  DeleteCopy(&figure);
  DeleteField(&field);
}
END_TEST

START_TEST(test_SubFigure) {
  int **field = CreateField();
  int **figure = CreateCopy();
  Figuring(figure, 3);
  SumFigure(field, figure);
  int clop = SubFigure(field, figure);
  ck_assert_int_eq(field[5][0], '.');
  ck_assert_int_eq(clop, 0);
  DeleteField(&field);
  DeleteCopy(&figure);
}
END_TEST

START_TEST(test_moveCols) {
  int **field = CreateField();
  int **figure = CreateCopy();
  Figuring(figure, 3);
  int clop = MoveCols(field, figure, 1);
  ck_assert_int_eq(clop, 0);
  DeleteField(&field);
  DeleteCopy(&figure);
}
END_TEST

START_TEST(test_rotateCols) {
  int **field = CreateField();
  int **figure = CreateCopy();
  Figuring(figure, 3);
  int clop = RotateCols(field, figure);
  ck_assert_int_eq(clop, 0);
  DeleteField(&field);
  DeleteCopy(&figure);
}
END_TEST

START_TEST(test_StringDel) {
  int **field = CreateField();
  for (int i = 0; i < MAXCOLS; i++) {
    field[0][i] = 'I';
  }
  int delCount = StringDel(field);
  ck_assert_int_eq(delCount, 1);

  DeleteField(&field);
}
END_TEST

START_TEST(test_CheckCollision) {
  int **field = CreateField();
  int **figure = CreateCopy();
  Figuring(figure, 3);
  SumFigure(field, figure);
  int clop = CheckCollision(field, figure);
  ck_assert_int_eq(clop, 1);
  DeleteField(&field);
  DeleteCopy(&figure);
}
END_TEST

START_TEST(test_CreateCopy) {
  int **copy = CreateCopy();
  ck_assert_ptr_ne(copy, NULL);
  DeleteCopy(&copy);
}
END_TEST

START_TEST(test_DeleteCopy) {
  int **copy = CreateCopy();
  DeleteCopy(&copy);
  ck_assert_ptr_eq(copy, NULL);
}
END_TEST

START_TEST(test_curtsy) {
  int **field = CreateField();
  int **figure = CreateCopy();
  Figuring(figure, 0);
  Curtsy(field, figure, 1);
  ck_assert_int_eq(figure[0][1], 1);
  DeleteCopy(&figure);
  DeleteField(&field);
}
END_TEST

START_TEST(test_curtsy_bad_arg) {
  int **field = CreateField();
  int **figure = CreateCopy();
  Figuring(figure, 0);
  int clop = Curtsy(field, figure, 0);
  ck_assert_int_ne(clop, 0);
  DeleteCopy(&figure);
  DeleteField(&field);
}
END_TEST

START_TEST(test_figure_Down2) {
  int **field = CreateField();
  int **figure = CreateCopy();
  Figuring(figure, 0);
  Curtsy(field, figure, 17);
  ck_assert_int_eq(FigureDown(field, figure), 0);
  Curtsy(field, figure, 1);
  ck_assert_int_ne(FigureDown(field, figure), 0);
  DeleteCopy(&figure);
  DeleteField(&field);
}
END_TEST

START_TEST(test_Scoring) {
  GameInfo_t tetris;
  InitTetris(&tetris);
  Scoring(&tetris);
  for (int i = 0; i < 1; i++) {
    for (int j = 0; j < 10; j++) {
      tetris.field[i][j] = 'I';
    }
  }
  Scoring(&tetris);
  ck_assert_int_eq(tetris.score, 100);
  DeleteField(&(tetris.field));
}
END_TEST

START_TEST(test_Scoring_2) {
  GameInfo_t tetris;
  InitTetris(&tetris);
  Scoring(&tetris);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 10; j++) {
      tetris.field[i][j] = 'I';
    }
  }
  Scoring(&tetris);
  ck_assert_int_eq(tetris.score, 300);
  DeleteField(&(tetris.field));
}
END_TEST

START_TEST(test_Scoring_3) {
  GameInfo_t tetris;
  InitTetris(&tetris);
  Scoring(&tetris);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 10; j++) {
      tetris.field[i][j] = 'I';
    }
  }
  Scoring(&tetris);
  ck_assert_int_eq(tetris.score, 700);
  DeleteField(&(tetris.field));
}
END_TEST

START_TEST(test_Scoring_4) {
  GameInfo_t tetris;
  InitTetris(&tetris);
  Scoring(&tetris);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 10; j++) {
      tetris.field[i][j] = 'I';
    }
  }
  Scoring(&tetris);
  ck_assert_int_eq(tetris.score, 1500);
  DeleteCopy(&(tetris.next));
  DeleteField(&(tetris.field));
}
END_TEST

START_TEST(test_ZeroingAll) {
  GameInfo_t tetris;
  InitTetris(&tetris);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 10; j++) {
      tetris.field[i][j] = 'I';
    }
  }
  Scoring(&tetris);
  ck_assert_int_eq(tetris.score, 1500);
  ZeroingAll(&tetris);
  ck_assert_int_eq(tetris.score, 0);
  DeleteCopy(&(tetris.next));
  DeleteField(&(tetris.field));
}
END_TEST

START_TEST(test_HelloState) {
  GameInfo_t tetris;
  InitTetris(&tetris);
  int **figure = UpdateFigure();
  Figuring(figure, 0);
  // FSM
  FSM state = Hello;
  HelloState(Start, &state);
  ck_assert_int_eq(state, Hello);
  HelloState(Terminate, &state);
  ck_assert_int_eq(state, GameOver);
  HelloState(Action, &state);
  ck_assert_int_eq(state, Spawn);
  ZeroingAll(&tetris);
  ck_assert_int_eq(tetris.score, 0);
  DeleteCopy(&(tetris.next));
  DeleteField(&(tetris.field));
}
END_TEST

START_TEST(test_SpawnState) {
  GameInfo_t tetris;
  InitTetris(&tetris);

  int **figure = UpdateFigure();
  Figuring(figure, 0);
  // FSM
  FSM state = Hello;
  SpawnState(&tetris, &state);
  ck_assert_int_eq(state, Moving);
  // SpawnState(Terminate, & state);
  // ck_assert_int_eq(state, GameOver);
  // SpawnState(Action, & state);
  // ck_assert_int_eq(state, Spawn);
  ZeroingAll(&tetris);
  ck_assert_int_eq(tetris.score, 0);
  // ck_assert_int_ne(FigureDown(field, figure), 0);
  DeleteCopy(&(tetris.next));
  DeleteField(&(tetris.field));
}
END_TEST

START_TEST(test_MovingState) {
  GameInfo_t tetris;
  InitTetris(&tetris);
  GetSetInfo(&tetris, PUSH);
  int **figure = UpdateFigure();
  Figuring(figure, 0);
  FSM state = Hello;
  MovingState(&tetris, &state, Left);
  ck_assert_int_eq(tetris.field[0][3], 'I');
  MovingState(&tetris, &state, Right);
  ck_assert_int_eq(tetris.field[0][3], '.');
  // sleep(7);
  for (volatile long i = 0; i < 100000000; ++i);
  MovingState(&tetris, &state, Start);
  ck_assert_int_eq(tetris.field[1][4], 'I');
  MovingState(&tetris, &state, Action);
  MovingState(&tetris, &state, Down);
  ck_assert_int_eq(state, Attaching);
  ck_assert_int_eq(tetris.field[19][4], 'I');
  ZeroingAll(&tetris);
  ck_assert_int_eq(tetris.score, 0);
  DeleteCopy(&(tetris.next));
  DeleteField(&(tetris.field));
}
END_TEST

START_TEST(test_AttachingState) {
  GameInfo_t tetris;
  InitTetris(&tetris);
  int **figure = UpdateFigure();
  Figuring(figure, 0);
  // FSM
  FSM state = Hello;
  AttachingState(&tetris, &state);
  ck_assert_int_eq(state, Spawn);
  tetris.level = 11;  /// потом подумать над адекватностью
  AttachingState(&tetris, &state);
  ck_assert_int_eq(tetris.level, 10);
  tetris.field[0][5] = 'I';
  AttachingState(&tetris, &state);
  ck_assert_int_eq(state, GameOver);
  ZeroingAll(&tetris);
  ck_assert_int_eq(tetris.score, 0);
  DeleteCopy(&(tetris.next));
  DeleteField(&(tetris.field));
}
END_TEST

START_TEST(test_JustState) {
  GameInfo_t tetris;
  InitTetris(&tetris);
  GetSetInfo(&tetris, PUSH);
  int **figure = UpdateFigure();
  Figuring(figure, 0);
  FSM state = JustState(Action, &tetris, 0);
  ck_assert_int_eq(state, Spawn);
  state = JustState(Action, &tetris, 0);
  ck_assert_int_eq(state, Moving);
  state = JustState(Down, &tetris, 0);
  ck_assert_int_eq(state, Attaching);
  tetris.field[0][5] = 'I';
  state = JustState(Down, &tetris, 0);
  ck_assert_int_eq(state, GameOver);
  state = JustState(Down, &tetris, 0);
  ZeroingAll(&tetris);
  ck_assert_int_eq(tetris.score, 0);
  DeleteCopy(&(figure));
  DeleteCopy(&(tetris.next));
  DeleteField(&(tetris.field));
}
END_TEST

START_TEST(test_GameOverState) {
  GameInfo_t tetris;
  InitTetris(&tetris);
  int **figure = UpdateFigure();
  Figuring(figure, 0);
  // FSM
  FSM state = Hello;
  GameOverState(&tetris, &state, Terminate);
  ck_assert_int_eq(state, Goodbye);
  GameOverState(&tetris, &state, Start);
  ck_assert_int_eq(state, Hello);
  ZeroingAll(&tetris);
  ck_assert_int_eq(tetris.score, 0);
  DeleteCopy(&(tetris.next));
  DeleteField(&(tetris.field));
}
END_TEST

START_TEST(test_FileScores) {
  GameInfo_t tetris;
  InitTetris(&tetris);
  GetSetInfo(&tetris, PUSH);
  tetris.score = 3000;
  tetris.high_score = 3000;
  FileScoreInput("test", &tetris);
  tetris.high_score = 0;
  ck_assert_int_eq(tetris.high_score, 0);
  FileScore("test", &tetris);
  ck_assert_int_eq(tetris.high_score, 3000);
  ZeroingAll(&tetris);
  ck_assert_int_eq(tetris.score, 0);
  DeleteCopy(&(tetris.next));
  DeleteField(&(tetris.field));
}
END_TEST

Suite *mozg_suite(void) {
  Suite *suite = suite_create("Mozg");
  TCase *core = tcase_create("Core");

  tcase_set_timeout(core, 20);

  tcase_add_test(core, test_Figuring);
  tcase_add_test(core, test_ZeroingTemp);
  tcase_add_test(core, test_SumFigure);
  tcase_add_test(core, test_SubFigure);
  tcase_add_test(core, test_moveCols);
  tcase_add_test(core, test_rotateCols);
  tcase_add_test(core, test_StringDel);
  tcase_add_test(core, test_CheckCollision);
  tcase_add_test(core, test_CreateCopy);
  tcase_add_test(core, test_DeleteCopy);

  tcase_add_test(core, test_curtsy);
  tcase_add_test(core, test_curtsy_bad_arg);
  tcase_add_test(core, test_figure_Down2);
  tcase_add_test(core, test_Scoring);
  tcase_add_test(core, test_Scoring_2);
  tcase_add_test(core, test_Scoring_3);
  tcase_add_test(core, test_Scoring_4);
  tcase_add_test(core, test_ZeroingAll);
  tcase_add_test(core, test_HelloState);
  tcase_add_test(core, test_SpawnState);
  tcase_add_test(core, test_MovingState);

  tcase_add_test(core, test_AttachingState);
  tcase_add_test(core, test_GameOverState);
  tcase_add_test(core, test_JustState);
  tcase_add_test(core, test_FileScores);

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
