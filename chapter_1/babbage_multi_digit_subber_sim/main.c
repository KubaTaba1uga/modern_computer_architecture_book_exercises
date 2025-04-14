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
static void sub(int *subend, int *accumulator, int *borrow_flag);

int main(int argc, char *argv[]) {
  if (argc != 3 || !is_valid_number(argv[1]) || !is_valid_number(argv[2])) {
    puts("Usage: ./subber <first digit> <second digit>");
    return EINVAL;
  }

  int accumulators[MAX_DIGITS] = {0};
  int subends[MAX_DIGITS] = {0};
  int borrow_flags[MAX_DIGITS + 1] = {0};

  populate_numbers(argv[1], accumulators);
  populate_numbers(argv[2], subends);

  printf("=== START ====\n");
  print_numbers("subends", subends);
  print_numbers("accumulators", accumulators);
  print_numbers("borrows", borrow_flags);
  puts("");

  int step = 0;
  for (int i = 0; i < MAX_DIGITS; i++) {
    sub(&subends[i], &accumulators[i], &borrow_flags[i]);

    printf("=== STEP %d ===\n", step++);
    print_numbers("subends", subends);
    print_numbers("accumulators", accumulators);
    print_numbers("borrows", borrow_flags);
    puts("");
  }

  /* bool any_borrow_left; */
  /* do { */
  /* any_borrow_left = false; */

  /* for (int i = 0; i < MAX_DIGITS - 1; i++) { */
  /*   if (borrow_flags[i] == 1) { */
  /*   } */
  /*   sub(&borrow_flags[i + 1], &accumulators[i], &borrow_flags[i]); */

  /*   /\* if (borrow_flags[i] == 1) { *\/ */
  /*   /\*   any_borrow_left = true; *\/ */
  /*   /\* } *\/ */

  /*   printf("=== STEP %d ===\n", step++); */
  /*   print_numbers("accumulators", accumulators); */
  /*   print_numbers("borrows", borrow_flags); */
  /*   puts(""); */
  /* } */

  /* } while (any_borrow_left); */

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

static void sub(int *subend, int *accumulator, int *borrow_flag) {

  printf("subend: %d\n", *subend);
  printf("accumulator: %d\n", *accumulator);
  printf("borrows: %d\n", *borrow_flag);
  puts("");

  while (true) {
    if (*subend == 0) {
      break;
    }

    *subend -= 1;
    *accumulator = *accumulator - 1;

    // If value changed from 0 to 9
    if (*accumulator < 0) {
      *borrow_flag = 1;
    }

    printf("subend: %d\n", *subend);
    printf("accumulator: %d\n", *accumulator);
    printf("borrows: %d\n", *borrow_flag);
    puts("");
  }
};
