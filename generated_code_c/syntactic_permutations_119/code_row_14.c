#include <stdio.h>
#include <stdlib.h>

int main() {
  float f1 = (float)rand()/(float)(RAND_MAX/2.0);
  float f2 = (float)rand()/(float)(RAND_MAX/2.0);
  float f3 = (float)rand()/(float)(RAND_MAX/2.0);
  char str1[50];
  char str2[50];
  char str3[50];
  sprintf(str1, "%f", f1);
  sprintf(str2, "%f", f2);
  sprintf(str3, "%f", f3);
  return 0;
}