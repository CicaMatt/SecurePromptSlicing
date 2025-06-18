#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL)); // seed for random function

  float a = (float) rand() / RAND_MAX; // generate first random number
  float b = (float) rand() / RAND_MAX; // generate second random number
  float c = (float) rand() / RAND_MAX; // generate third random number

  char str1[10];
  sprintf(str1, "%f", a);

  char str2[10];
  sprintf(str2, "%f", b);

  char str3[10];
  sprintf(str3, "%f", c);

  // concatenate the strings and print them
  printf("%s%s%s\n", str1, str2, str3);

  return 0;
}