K?=autoreport
CC=gcc  -Wall -Wextra -Werror -std=c11
#UBUNTU_FLAGS = -lsubunit -lpthread -lrt -lgcov -lm
SRC =  brick_game/backend/*.c 
FRONT= gui/cli/*.c  brick_game/tetris/*.c  
OS = $(shell uname)
DIST_DIR = dist_Tetris
ifeq ($(OS), Darwin)
det_OS = -lcheck
else
det_OS = -lcheck -lsubunit -lpthread -lrt -lgcov -lm
endif
ifeq ($(OS), Darwin)
OPEN_CMD = open 
else
OPEN_CMD = xdg-open 
endif

all: clean install play
 
install: clean 
	 mkdir -p build
	 $(CC) $(SRC)$(FRONT) -o build/game -lncurses

uninstall:
	rm -r build
play: 
	./build/game
gcov_report:
	rm -rf test-temp_tests*.gc* 
	lcov -t "result" -o res.info -c -d . --rc branch_coverage=0
	genhtml -o report res.info --rc branch_coverage=0
	# open report/index.html
	$(OPEN_CMD) report/index.html


test: clean
	$(CC)  --coverage $(SRC) ./tests/temp_tests.c -o test $(det_OS) 
	./test

commit:
	git add s21*
	git commit -m '$(K)'    
	git push origin develop

dvi:
	doxygen Doxyfile
	$(OPEN_CMD) dvi/html/index.html
dist:
	mkdir -p $(DIST_DIR)
	cp -a brick_game $(DIST_DIR)
	cp -a gui $(DIST_DIR)
	cp -a tests $(DIST_DIR)
	cp -a *.c $(DIST_DIR)
	cp -a *.h $(DIST_DIR)
	cp -a Documentation.html $(DIST_DIR)
	#hfhfh
	tar -czf dist_Tetris.tar.gz $(DIST_DIR)
	rm -rf $(DIST_DIR)
	

style_test:
	clang-format --style=Google -n */*.c   */*.h

style:
	clang-format --style=Google -i */*.c  */*.h

clean:
	rm -rf report *.gc* *.o *.info *.a  test test.dSYM tests/*.o build test_v
valgrind:
	$(CC) -g --coverage $(SRC) ./tests/temp_tests.c -o test_v $(det_OS) 
	./test_v
	valgrind --leak-check=full --show-leak-kinds=all  --track-origins=yes ./test_v
