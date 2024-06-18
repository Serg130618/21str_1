CC = gcc
SRCMODULES = s21_string.c format_unit.c handlers.c s21_output.c utils.c
OBJMODULES = $(SRCMODULES:.c=.o)
CFLAGS = -Wall -Werror -Wextra -Wno-format-security -Wno-format -std=c11
LDFLAGS = -L. s21_string.a -lm `pkg-config --cflags --libs check`

TEST_EXEC = test_s21_string
REPORT_DIR = ./report

all: clean s21_string.a

rebuild: clean all

test: clean s21_string.a
	$(CC) $(CFLAGS) --coverage main.c -o $(TEST_EXEC) $(SRCMODULES) $(LDFLAGS)
	./$(TEST_EXEC)

gcov_report: test
	lcov -t "$(TEST_EXEC)" --output-file report.info --capture -q --directory ./
	genhtml -o $(REPORT_DIR) report.info

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

s21_string.a: $(OBJMODULES)
	ar rcs $@ $^
	ranlib $@

clean:
	rm -rf *.o *.a *.gcno *.gcda *.out $(REPORT_DIR)/ report.info $(TEST_EXEC)

format:
	find . -name "*.h" -or -name "*.c" | xargs $(CLANG-FORMAT) -i


clang_test:
	find . -name "*.h" -or -name "*.c" | xargs $(CLANG-FORMAT) -n
