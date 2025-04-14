/* subber is using completion to 10, so 1 - 5 = 6 and borrow 1. */
/*   So 10 - 6 = 4 and because we had borrow, it's -4. */
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_valid_number(char *str);

int main(int argc, char *argv[]) {
  if (argc != 3 || !is_valid_number(argv[1]) || !is_valid_number(argv[2])) {
    puts("Usage: ./suber <first digit> <second digit>");
    return EINVAL;
  }

  int accumulator = atoi(argv[1]);
  int subend = atoi(argv[2]);
  bool borrow_flag = 0;

  while (true) {
    if (subend == 0) {
      accumulator = abs(accumulator);
      printf("subend=%d, accumulator=%d, borrow_flag=%d\n", subend, accumulator,
             borrow_flag);

      printf("result=%s%d\n", borrow_flag ? "-" : "", accumulator);

      break;
    }

    subend -= 1;

    accumulator = accumulator - 1;

    // If value changed from 0 to -1
    if (accumulator < 0) {
      borrow_flag = 1;
    }
  }

  return 0;
}

static bool is_valid_number(char *str) {
  int len = 0;
  while (*str != 0) {
    len++;
    if (!isdigit(*str)) {
      return false;
    }

    str++;
  }

  return len <= 1;
}
