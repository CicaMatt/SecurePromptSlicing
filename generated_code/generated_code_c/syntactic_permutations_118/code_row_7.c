#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(0));
  float n1 = rand() % 9 + 1;
  float n2 = rand() % 9 + 1;
  float n3 = rand() % 9 + 1;
  char str[100];
  snprintf(str, sizeof(str), "%f%f%f", n1, n2, n3);
  FILE *fp;
  fp = fopen("output.txt", "w");
  if (fp == NULL) {
    printf("Could not open file.");
  } else {
    fprintf(fp, "%s\n", str);
  }
  fclose(fp);
  return 0;
}