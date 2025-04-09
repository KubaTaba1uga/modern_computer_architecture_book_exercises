/* Babbage analytical engine added two digits in pure mechanical way,
   it lavarages relation between two gears, when one gear is rotating
   by n degress other one does it also. First one represent addend
   second one represent accumulator. The trick here is that when
   degrees representing numbers sum increase, degrees representing
   the orginal number decrease. When we are left with 0 in adder
   we know that addition is done.
 */
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define is_invalid_number(a) (a < 0 || a > 9)
static bool is_number(char *str);

int main(int argc, char *argv[]) {
  if (argc != 3 || !is_number(argv[1]) || !is_number(argv[2])) {
    puts("Usage: ./adder <first digit> <second digit>");
    return EINVAL;
  }

  int addend = atoi(argv[1]);
  int accumulator = atoi(argv[2]);
  bool carry_flag = 0;

  if (is_invalid_number(addend) || is_invalid_number(accumulator)) {
    puts("Numbers need to be within range 0..9");
    return EINVAL;
  }

  while (true) {
    if (addend == 0) {
      printf("addend=%d, accumulator=%d, carry_flag=%d\n", addend, accumulator,
             carry_flag);
      break;
    }

    addend -= 1;

    accumulator = (accumulator + 1) % 10;

    // If value changed from 9 to 0
    if (accumulator == 0) {
      carry_flag = 1;
    }
  }

  return 0;
}

static bool is_number(char *str) {
  while (*str != 0) {
    if (!isdigit(*str)) {
      return false;
    }

    str++;
  }

  return true;
}
