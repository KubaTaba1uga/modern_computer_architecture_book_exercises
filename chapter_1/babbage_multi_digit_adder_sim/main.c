/* Babbage analytical engine added two digits in pure mechanical way,
   it lavarages relation between two gears, when one gear is rotating
   by n degress other one does it also. First one represent addend
   second one represent accumulator. The trick here is that when
   degrees representing numbers sum increase, degrees representing
   the orginal number decrease. When we are left with 0 in adder
   we know that addition is done.

   This version is adding multi digits numbers.
 */
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS 5
static bool is_valid_number(char *str);
static void populate_numbers(char *str, int numbers[MAX_DIGITS]);
static void print_numbers(const char *label, int arr[MAX_DIGITS]);
static void add(int *addend, int *accumulator, int *carry_flag);

int main(int argc, char *argv[]) {
  if (argc != 3 || !is_valid_number(argv[1]) || !is_valid_number(argv[2])) {
    puts("Usage: ./adder <first digit> <second digit>");
    return EINVAL;
  }

  int addends[MAX_DIGITS] = {0};
  int accumulators[MAX_DIGITS] = {0};
  int carry_flags[MAX_DIGITS + 1] = {0};

  populate_numbers(argv[1], addends);
  populate_numbers(argv[2], accumulators);

  printf("=== START ====\n");
  print_numbers("addends", addends);
  print_numbers("accumulators", accumulators);
  print_numbers("carries", carry_flags);
  puts("");

  int step = 0;
  for (int i = 0; i < MAX_DIGITS; i++) {
    add(&addends[i], &accumulators[i], &carry_flags[i]);

    printf("=== STEP %d ===\n", step++);
    print_numbers("addends", addends);
    print_numbers("accumulators", accumulators);
    print_numbers("carries", carry_flags);
    puts("");
  }

  bool any_carry_left;
  do {
    any_carry_left = false;

    for (int i = 0; i < MAX_DIGITS; i++) {
      add(&carry_flags[i + 1], &accumulators[i], &carry_flags[i]);

      if (carry_flags[i] == 1) {
        any_carry_left = true;
      }

      printf("=== STEP %d ===\n", step++);
      print_numbers("accumulators", accumulators);
      print_numbers("carries", carry_flags);
      puts("");
    }

  } while (any_carry_left);

  printf("=== FINISH ===\n");
  print_numbers("accumulators", accumulators);
  puts("");

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

  return len <= MAX_DIGITS;
}

static void populate_numbers(char *str, int numbers[MAX_DIGITS]) {
  int numbers_amount = strlen(str);
  char buffer[2];

  for (int i = 0; i < numbers_amount; i++) {
    sprintf(buffer, "%c", str[i]);
    numbers[MAX_DIGITS - (numbers_amount - i)] = atoi(buffer);
  }
}

static void print_numbers(const char *label, int arr[MAX_DIGITS]) {
  printf("%s: ", label);
  for (int i = 0; i < MAX_DIGITS; i++) {
    printf("%d", arr[i]);
  }
  printf("\n");
}

static void add(int *addend, int *accumulator, int *carry_flag) {
  while (true) {
    if (*addend == 0) {
      break;
    }

    *addend -= 1;
    *accumulator = (*accumulator + 1) % 10;

    // If value changed from 9 to 0
    if (*accumulator == 0) {
      *carry_flag = 1;
    }
  }
};
