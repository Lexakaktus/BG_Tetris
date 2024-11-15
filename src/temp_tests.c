#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "mozg.h"

START_TEST(test_Figuring)
{
    int** figure=createpole();
    int index = 0;

    Figuring(figure, index);

    ck_assert_int_eq(figure[0][0], figure_home[index][0][0]);
    ck_assert_int_eq(figure[0][1], figure_home[index][0][1]);
}
END_TEST

START_TEST(test_zeroing_temp)
{
    int** field = createpole();
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
    deletecopy(field);
}
END_TEST

START_TEST(test_sumField)
{
    int** field1 = createpole();
    int** field2 = createpole();
    
    // Заполняем field1
    field1[0][0] = 'X';

    sumField(field1, field2);

    ck_assert_int_eq(field1[0][0], field2[0][0]);

    deletecopy(field1);
    deletecopy(field2);
}
END_TEST

START_TEST(test_sumFigure)
{
    int** field = createpole();
    int** figure = createcopy();
    Figuring(figure, 1);
    
    // Сначала проверим, что нет столкновений
    int clop = sumFigure(field, figure);

    // Поле обновляется, если нет столкновений
    ck_assert_int_eq(clop, 0);

    deletecopy(field);
}
END_TEST

START_TEST(test_subFigure)
{
    int** field = createpole();
    int**figure=createcopy();
    Figuring(figure, 3);

    // Сначала добавим фигуру
    sumFigure(field, figure);

    // Удалим фигуру
    int clop = subFigure(field, figure);

    // Поле должно быть очищено
    ck_assert_int_eq(field[5][0], '.');
    
    deletecopy(field);
}
END_TEST

START_TEST(test_moveCols)
{
    int** field = createpole();
    int**figure=createcopy();
    Figuring(figure, 3);

    // Сдвиг вправо
    int clop = moveCols(field, figure, 1);
    ck_assert_int_eq(clop, 0);  // Столкновений быть не должно
    
    deletecopy(field);
}
END_TEST

START_TEST(test_rotateCols)
{
    int** field = createpole();
    int**figure=createcopy();
    Figuring(figure, 3);

    // Поворот фигуры
    int clop = rotateCols(field, figure, 1);
    ck_assert_int_eq(clop, 0);  // Столкновений быть не должно

    deletecopy(field);
}
END_TEST

START_TEST(test_stringDel)
{
    int** field = createpole();
    
    // Заполним несколько строк
    for (int i = 0; i < MAXCOLS; i++) {
        field[0][i] = 'I';
    }

    int delCount = stringDel(field);
    
    // Проверим, что одна строка была удалена
    ck_assert_int_eq(delCount, 1);

    deletecopy(field);
}
END_TEST

START_TEST(test_checkCollision)
{
    int** field = createpole();
    int**figure=createcopy();
    Figuring(figure, 3);

    // Поставим фигуру на поле
    sumFigure(field, figure);
    
    // Проверим столкновение
    int clop = checkCollision(field, figure);
    
    ck_assert_int_eq(clop, 0);  // Столкновений нет

    deletecopy(field);
}
END_TEST

START_TEST(test_createcopy)
{
    int** copy = createcopy();
    
    // Проверим, что копия была успешно создана
    ck_assert_ptr_nonnull(copy);

    // Очистим память
    deletecopy(copy);
}
END_TEST

START_TEST(test_deletecopy)
{
    int** copy = createcopy();
    deletecopy(copy);
    
    // Проверим, что память была освобождена
    ck_assert_ptr_null(copy);
}
END_TEST

Suite* mozg_suite(void)
{
    Suite* suite = suite_create("Mozg");
    TCase* core = tcase_create("Core");

    tcase_add_test(core, test_Figuring);
    tcase_add_test(core, test_zeroing_temp);
    tcase_add_test(core, test_sumField);
    tcase_add_test(core, test_sumFigure);
    tcase_add_test(core, test_subFigure);
    tcase_add_test(core, test_moveCols);
    tcase_add_test(core, test_rotateCols);
    tcase_add_test(core, test_stringDel);
    tcase_add_test(core, test_checkCollision);
    tcase_add_test(core, test_createcopy);
    tcase_add_test(core, test_deletecopy);
    
    suite_add_tcase(suite, core);

    return suite;
}

int main(void)
{
    int number_failed;
    Suite* suite = mozg_suite();
    SRunner* runner = srunner_create(suite);

    srunner_run_all(runner, CK_NORMAL);
    number_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (number_failed == 0) ? 0 : 1;
}
