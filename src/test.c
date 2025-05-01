#include "test.h"
// #include "mozg.h"
START_TEST(tetris1) { GameInfo_t tetris; }
END_TEST

Suite *test_tetris(void) {
  Suite *s = suite_create("suite_calc_complements");
  TCase *tc = tcase_create("case_calc_complements");

  tcase_add_test(tc, tetris1);
  //   tcase_add_test(tc, test_not_sqare);
  //   tcase_add_test(tc, test_incorrect);
  //   tcase_add_test(tc, test_one_by_one);

  //   tcase_add_test(tc, s21_calc_complements_01);
  //   tcase_add_test(tc, s21_calc_complements_02);
  //   tcase_add_test(tc, s21_calc_complements_03);
  //   tcase_add_test(tc, s21_calc_complements_04);

  suite_add_tcase(s, tc);
  return s;
}

int main() {
  Suite *s[] = {// test_create_suite(),
                //               test_remove_suite(),
                //               test_eq_suite(),
                //               test_sub_suite(),
                //               test_sum_suite(),
                //               test_mult_matrix_suite(),
                //               test_mult_number_suite(),
                //               test_transpose_suite(),
                test_calc_complements_suite(),
                // test_determinant_suite(),
                // test_inverse_suite(),
                NULL};

  printf("\nTESTS MODULE\n\n");
  SRunner *sr;
  sr = srunner_create(s[0]);
  for (int i = 1; s[i] != NULL; i++)
    srunner_add_suite(sr, s[i]);

  srunner_set_fork_status(sr, CK_FORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);

  return 0;
}