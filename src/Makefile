K?=autoreport
CC=gcc  -Wall -Wextra -Werror -std=c11
#UBUNTU_FLAGS = -lsubunit -lpthread -lrt -lgcov -lm
SRC =  brick_game/backend/*.c 
FRONT= gui/cli/*.c  brick_game/tetris/*.c  
OS = $(shell uname)
ifeq ($(OS), Darwin)
	det_OS = -lcheck
else
	det_OS = -lcheck -lsubunit -lpthread -lrt -lgcov -lm
endif

#s21_supporting_functions.c 

# all:  clean s21_matrix.a test gcov_report style_test
#test gcov_report
all: clean install play
 
install: clean
	 $(CC) $(SRC)$(FRONT) -o tetris -lncurses
# gcc fff/*.c -lncurses -o tetris 

play:
	./tetris
gcov_report:
	rm -rf test-test_*.gc* test-s21_tests.gc*
	lcov -t "result" -o res.info -c -d . --rc branch_coverage=0
	genhtml -o report res.info --rc branch_coverage=0
	open report/index.html


test: clean
	$(CC)   --coverage $(SRC) temp_tests.c -o test $(det_OS) 
#tests/*.c
	./test

commit:
	git add s21*
	git commit -m '$(K)'    
	git push origin develop


style_test:
	clang-format --style=Google -n */*.c   */*.h

style:
	clang-format --style=Google -i */*.c  */*.h

clean:
	rm -rf report *.gc* *.o *.info *.a  test test.dSYM tests/*.o
